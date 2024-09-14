/*
 * gt9xx.c
 *
 *  Created on: Jul 2, 2024
 *      Author: biubiu
 */


/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "gt9xx.h"
#include <stdlib.h>

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define GT911_RESET_PORT            GTP_RST_GPIO_Port
#define GT911_INT_PORT              GTP_INT_GPIO_Port
#define GT911_RESET_PIN             GTP_RST_Pin
#define GT911_INT_PIN               GTP_INT_Pin

// 触摸IC设备地址
#define GT911_DIV_W 				0x28
#define GT911_DIV_R 				0x29
#define GT9XX_IIC_TIMEOUT			0xFF

//GT911 部分寄存器定义
#define GT_CTRL_REG                 0x8040  /* GT911控制寄存器 */
#define GT_CFGS_REG                 0x8047  /* GT911配置起始地址寄存器 */
#define GT_CHECK_REG                0x80FF  /* GT911校验和寄存器 */
#define GT_PID_REG                  0x8140  /* GT911产品ID寄存器 */

#define GT_GSTID_REG                0x814E  /* GT911当前检测到的触摸情况 */
#define GT_TP1_REG                  0x814F  /* 第一个触摸点数据地址 */
#define GT_TP2_REG                  0x8157  /* 第二个触摸点数据地址 */
#define GT_TP3_REG                  0x815F  /* 第三个触摸点数据地址 */
#define GT_TP4_REG                  0x8167  /* 第四个触摸点数据地址 */
#define GT_TP5_REG                  0x816F  /* 第五个触摸点数据地址 */

#define GT911_READ_X_MAX_REG        0x8048  /* X输出最大值 */
#define GT911_READ_Y_MAX_REG        0x804a  /* X输出最大值 */

#define GT911_READ_XY_REG           0x814E  /* 坐标寄存器 */
#define GT911_CLEARBUF_REG          0x814E  /* 清除坐标寄存器 */
#define GT911_CONFIG_REG            0x8047  /* 配置参数寄存器 */
#define GT911_COMMAND_REG           0x8040  /* 实时命令 */
#define GT911_PRODUCT_ID_REG        0x8140  /* productid */
#define GT911_VENDOR_ID_REG         0x814A  /* 当前模组选项信息 */
#define GT911_CONFIG_VERSION_REG    0x8047  /* 配置文件版本号 */
#define GT911_CONFIG_CHECKSUM_REG   0x80FF  /* 配置文件校验码 */
#define GT911_FIRMWARE_VERSION_REG  0x8144  /* 固件版本号 */

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**用于存放每一个触控点的id，坐标，大小**/
typedef struct
{
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint16_t size;
} tp_point_info_t;

/**类结构体**/
typedef struct
{
    uint8_t tp_dev_addr;
    uint16_t height;
    uint16_t width;
    tp_rotation_t rotation;
    tp_point_info_t points_info[TOUCH_POINT_TOTAL]; //用于存储五个触控点的坐标
} tp_drv_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static HAL_StatusTypeDef gt911_write_reg(uint16_t reg, uint8_t *buf, uint8_t len);
static HAL_StatusTypeDef gt911_read_reg(uint16_t reg, uint8_t *buf, uint8_t len);
static void gt911_clear_buf();
static void gt911_soft_reset(void);
static void gt911_get_gstid(uint8_t *buf);
static void gt911_get_version(uint8_t *buf);
static void gt911_get_vendor_id(uint8_t *buf);
static void gt911_get_product_id(uint8_t *buf);
static void gt911_get_max_x(uint8_t *buf);
static void gt911_get_max_y(uint8_t *buf);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static I2C_HandleTypeDef *GT9XX_I2C = &hi2c1;

static tp_drv_t g_tp_drv;

static volatile bool g_i2c2_tx_complete = false;
static volatile bool g_i2c2_rx_complete = false;

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

HAL_StatusTypeDef drv_i2c_touchpad_init(void)
{
    HAL_StatusTypeDef err = HAL_OK;
    uint8_t buf[4];

    /* 选择地址 */
    HAL_GPIO_WritePin(GT911_RESET_PORT, GT911_RESET_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GT911_INT_PORT, GTP_INT_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);

	HAL_GPIO_WritePin(GT911_INT_PORT, GTP_INT_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(GT911_RESET_PORT, GT911_RESET_PIN, GPIO_PIN_SET);
	HAL_Delay(10);

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GTP_INT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GT911_INT_PORT, &GPIO_InitStruct);
	HAL_Delay(100);

    touchpad_set_rotation (TP_ROT_NONE);

    /* 读ID */
    // 厂商标识id
    gt911_get_vendor_id (buf);
    //printf ("gt911 vendor id = %02x %02x %02x %02x\r\n", buf[0], buf[1], buf[2], buf[3]);

    // 产品id
    gt911_get_product_id (buf);
    //printf ("gt911 product id = %02x %02x %02x %02x\r\n", buf[0], buf[1], buf[2], buf[3]);

    // 触摸芯片固件版本
    gt911_get_version (buf);
    //printf ("version = 0x%x\r\n", buf[0]);

    gt911_get_max_x (buf);
    g_tp_drv.width = (uint16_t) ((buf[1] << 8) | buf[0]);
    //printf ("touchpad max x = %d\r\n", g_tp_drv.width);

    gt911_get_max_y (buf);
    g_tp_drv.height = (uint16_t) ((buf[1] << 8) | buf[0]);
    //printf ("touchpad max y = %d\r\n", g_tp_drv.height);

    //gt911_soft_reset();

    return err;
}

HAL_StatusTypeDef touchpad_is_touched(void)
{
    uint8_t touched_state, touch_num, buffer_status;

    gt911_get_gstid (&touched_state);
    touch_num = touched_state & 0x0f;            //触点数量
    buffer_status = (touched_state >> 7) & 1;   // 帧状态
    //printf("touch_num: %d\r\n", touch_num);

    if (buffer_status == 1 && (touch_num <= TOUCH_POINT_TOTAL) && (touch_num > 0))
    {
        uint16_t pointers_regs[TOUCH_POINT_TOTAL] =
        { GT_TP1_REG, GT_TP2_REG, GT_TP3_REG, GT_TP4_REG, GT_TP5_REG };
        // 获取每个触控点的坐标值并保存
        for (int i = 0; i < touch_num; ++i)
        {
            uint8_t point_info_per_size = 7;
            uint8_t *point_info_p = malloc (point_info_per_size * sizeof(uint8_t ));
            gt911_read_reg (pointers_regs[i], point_info_p, point_info_per_size);

            g_tp_drv.points_info[i].id = point_info_p[0];
            g_tp_drv.points_info[i].x = (uint16_t) (point_info_p[1] + (point_info_p[2] << 8));
            g_tp_drv.points_info[i].y = (uint16_t) (point_info_p[3] + (point_info_p[4] << 8));
            g_tp_drv.points_info[i].size = (uint16_t) (point_info_p[5] + (point_info_p[6] << 8));

            free (point_info_p);

            //旋转方向
            uint16_t temp;
            switch (g_tp_drv.rotation)
            {
                case TP_ROT_NONE:
                	g_tp_drv.points_info[i].x = g_tp_drv.points_info[i].x;
                	g_tp_drv.points_info[i].y = g_tp_drv.points_info[i].y;
                break;
                case TP_ROT_270:
                	temp = g_tp_drv.points_info[i].x;
					g_tp_drv.points_info[i].x = g_tp_drv.points_info[i].y;
					g_tp_drv.points_info[i].y = g_tp_drv.height - temp;
                break;
                case TP_ROT_180:
                	g_tp_drv.points_info[i].x = g_tp_drv.width - g_tp_drv.points_info[i].x;
                	g_tp_drv.points_info[i].y = g_tp_drv.height - g_tp_drv.points_info[i].y;
                break;
                case TP_ROT_90:
                	temp = g_tp_drv.points_info[i].x;
					g_tp_drv.points_info[i].x = g_tp_drv.width - g_tp_drv.points_info[i].y;
					g_tp_drv.points_info[i].y = temp;

                break;
                default:
                break;
            }
        }
        gt911_clear_buf();
        return HAL_OK;
    }
    //必须给GT911_POINT_INFO缓冲区置0,不然读取的数据一直为128！！！！
    gt911_clear_buf ();

    return HAL_ERROR;
}

void touchpad_set_rotation(tp_rotation_t rotation)
{
    g_tp_drv.rotation = rotation;
}

void touchpad_get_pos(uint16_t *x, uint16_t *y, int index)
{
    *x = g_tp_drv.points_info[index].x;
    *y = g_tp_drv.points_info[index].y;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

static void gt911_soft_reset(void)
{
    uint8_t buf[1];
    buf[0] = 0x02;
    gt911_write_reg (GT911_COMMAND_REG, (uint8_t*) buf, 1);
    HAL_Delay(100);

    buf[0] = 0x0;
    gt911_write_reg (GT911_COMMAND_REG, (uint8_t*) buf, 1);
    HAL_Delay(100);
}

static void gt911_clear_buf()
{
    uint8_t buf[1] = { 0 };

    gt911_write_reg (GT911_CLEARBUF_REG, buf, 1);
}

static HAL_StatusTypeDef gt911_write_reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    HAL_StatusTypeDef err = HAL_OK;

    //uint8_t regl = (uint8_t) (reg & 0xff);
    //uint8_t regh = (uint8_t) (reg >> 8);
    //uint8_t *write_package = malloc ((len + 2) * sizeof(uint8_t));
    //memcpy (write_package, &regh, 1);
    //memcpy (write_package + 1, &regl, 1);
    //memcpy (write_package + 2, buf, len);

    //err = g_i2c_master2.p_api->write (g_i2c_master2.p_ctrl, write_package, len + 2, 0);
    err = HAL_I2C_Mem_Write(GT9XX_I2C, GT911_DIV_W, reg, I2C_MEMADD_SIZE_16BIT, buf, len, GT9XX_IIC_TIMEOUT);

    //i2c2_wait_for_tx ();
    //free (write_package);
    return err;
}

static HAL_StatusTypeDef gt911_read_reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    HAL_StatusTypeDef err = HAL_OK;

    //uint8_t tmpbuf[2];
    //tmpbuf[0] = (uint8_t) (reg >> 8);
    //tmpbuf[1] = (uint8_t) (reg & 0xff);
    //err = g_i2c_master2.p_api->write (g_i2c_master2.p_ctrl, tmpbuf, 2, 0);
    //i2c2_wait_for_tx ();
    //err = g_i2c_master2.p_api->read (g_i2c_master2.p_ctrl, buf, len, 0)
    //i2c2_wait_for_rx ();

    err = HAL_I2C_Mem_Read(GT9XX_I2C, GT911_DIV_R, reg, I2C_MEMADD_SIZE_16BIT, buf, len, GT9XX_IIC_TIMEOUT);

    return err;
}

static void gt911_get_max_x(uint8_t *buf)
{
    gt911_read_reg (GT911_READ_X_MAX_REG, buf, 2);
}

static void gt911_get_max_y(uint8_t *buf)
{
    gt911_read_reg (GT911_READ_Y_MAX_REG, buf, 2);
}

static void gt911_get_product_id(uint8_t *buf)
{
    gt911_read_reg (GT911_PRODUCT_ID_REG, buf, 4);
}

static void gt911_get_vendor_id(uint8_t *buf)
{
    gt911_read_reg (GT911_VENDOR_ID_REG, buf, 4);
}

static void gt911_get_version(uint8_t *buf)
{
    gt911_read_reg (GT911_CONFIG_VERSION_REG, buf, 1);
}

static void gt911_get_gstid(uint8_t *buf)
{
    gt911_read_reg (GT_GSTID_REG, buf, 1);
}
