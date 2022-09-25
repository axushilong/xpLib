/********************************** (C) COPYRIGHT *******************************
 * File Name          : BL0942.h
 * Author             : axushilong@163.com
 * Version            : V0.1
 * Date               : 
 * Description
 * Copyright (c) 2022 axushilong
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef __BL0942_H__
#define __BL0942_H__

#ifdef __cplusplus
extern "C" {
#endif

#include  "stdint.h"

#define DE_BL0942UartSendByte()  
#define DE_BL0942UartSendData() 

#define DE_Vref  (1.218)
#define DE_Vref2 (1.483524)
#define DE_1_6Vref  (1218000)
#define DE_1_6Vref2 (1483524)

/*电参量寄存器（只读）*/
#define R20_I_WAVE     (1)/*电流波形寄存器,有符号*/
#define R20_V_WAVE     (2)/*电压波形寄存器,有符号*/
#define R24_I_RMS      (3)/*电流有效值寄存器,无符号*/
#define R24_V_RMS      (4)/*电压有效值寄存器,无符号*/
#define R24_I_FAST_RMS (5)/*电流快速有效值寄存器,无符号*/
#define R24_WATT       (6)/*有功功率寄存器,有符号*/
#define R24_CF_CNT     (7)/*有功电能脉冲计数寄存器,无符号*/
#define R16_FREQ       (8)/*复位值:0x4E20,线电压频率寄存器*/
#define R10_STATUS     (9)/*状态寄存器*/

#define DE_AllRegister (0xaa)

/*状态寄存器,位定义*/
#define R10_STATUS_CF_REVP_F  (1<<0)/*有功脉冲 CF 能量反向指示,负能量时置 1*/
#define R10_STATUS_CREEP_F    (1<<1)/*有功功率小于有功防潜动值时置 1*/
#define R10_STATUS_I_ZX_LTH_F (1<<8)/*电流过零输出状态指示*/
#define R10_STATUS_V_ZX_LTH_F (1<<9)/*电压过零输出状态指示*/



/*电参量寄存器（读写）*/
#define R8_I_RMSOS        (0x12)/*电流有效值小信号校正寄存器*/
#define R8_WA_CREEP       (0x14)/*复位值:0x0B,有功功率防潜寄存器*/
#define R16_I_FAST_RMS_TH (0x15)/*复位值:0xFFFF,电流快速有效值阈值寄存器*/
#define R3_I_FAST_RMS_CYC (0x16)/*复位值:0x01,电流快速有效值刷新周期寄存器*/
#define R2_FREQ_CYC       (0x17)/*复位值:0x03,线电压频率刷新周期寄存器*/
#define R6_OT_FUNX        (0x18)/*复位值:0x24,输出配置寄存器*/
#define R10_MODE          (0x19)/*复位值:0x87,用户模式选择寄存器*/
#define R2_GAIN_CR        (0x1a)/*复位值:0x02,电流通道增益控制寄存器,可配置1、4、16(默认)、24*/
#define R24_SOFT_RESET    (0x1c)/*写入 0x5A5A5A 时,用户区寄存器复位*/
#define R8_USR_WRPROT     (0x1d)/*用户写保护设置寄存器。写入 0x55 后,用户操作寄存器可以写入;写入其他值,用户操作寄存器区域不可写入*/

/*复位值:0x24,输出配置寄存器,位定义*/
#define R6_OT_FUNX_CF1_FUNX_SEL (3<<0)/*CF1 输出选择位,b00:输出有功能量脉冲;b01:输出过流报警;b10:输出电压过零指示;b11:输出电流过零指示*/
#define R6_OT_FUNX_CF2_FUNX_SEL (3<<2)/*CF2 输出选择位,b00:输出有功能量脉冲;b01:输出过流报警;b10:输出电压过零指示;b11:输出电流过零指示*/
#define R6_OT_FUNX_ZX_FUNX_SEL  (3<<4)/*ZX 输出选择位,b00:输出有功能量脉冲;b01:输出过流报警;b10:输出电压过零指示;b11:输出电流过零指示*/

/*复位值:0x87,用户模式选择寄存器,位定义*/
#define R10_MODE_CF_EN          (1<<2)/*有功能量和脉冲开关,0:关闭;1:使能*/
#define R10_MODE_RMS_UPDATE_SEL (1<<3)/*有效值寄存器刷新时间选择选择,0:400ms;1:800ms*/
#define R10_MODE_FAST_RMS_SEL   (1<<4)/*快速有效值波形来源选择,0:SINC 后的波形;1:HPF 后的波形*/
#define R10_MODE_AC_FREQ_SEL    (1<<5)/*交流电频率选择,0:50Hz;1:60Hz*/
#define R10_MODE_CF_CNT_CLR_SEL (1<<6)/*CF 计数寄存器读后清零使能位,0:关闭;1:使能*/
#define R10_MODE_CF_ADD_CLR_SEL (1<<7)/*CF 脉冲能量累加模式选择,0:代数和累加;1:绝对值累加*/
#define R10_MODE_UART_RATE_SEL  (3<<8)/*UART 通信波特率选择,0x:波特率由硬件管脚SCLK_BPS 决定,接 0 选择4800bps, 接 1 选择9600bps;10 19200bps;11 38400bps*/

/*复位值:0x02,电流通道增益控制寄存器*/
#define R2_GAIN_CR_GAIN_CR (3<<0)/*00:1 倍增益;01:4 倍增益;10:16 倍增益（默认）;11:24 倍增益*/

#define DE_WriteBL0942Cmd (0xA8)
#define DE_ReadBL0942Cmd (0x58)

typedef enum {
	eI_WAVE = 1,
	eV_WAVE = 2,
	eI_RMS = 3,
	eV_RMS = 4,
	eI_FAST_RMS = 5,
	eWATT = 6,
	eCF_CNT = 7,
	eFREQ = 8,
	eSTATUS = 9,
	eI_RMSOS = 0x12,
	eWA_CREEP = 0x14,
	eI_FAST_RMS_TH = 0x15,
	eI_FAST_RMS_CYC = 0x16,
	eFREQ_CYC = 0x17,
	eOT_FUNX = 0x18,
	eMODE = 0x19,
	eGAIN_CR = 0x1A,
	eSOFT_RESET = 0x1C,
	eUSR_WRPROT = 0x1D,
	eAllRegister = 0xAA
}eBL0942RegistersAddressTypes;

//#pragma pack(1)
//typedef struct {
//    unsigned char ucHead;
//    unsigned char ucIRms0;
//    unsigned char ucIRms1;
//    unsigned char ucIRms2;
//    unsigned char ucVRms0;
//    unsigned char ucVRms1;
//    unsigned char ucVRms2;
//    unsigned char ucIFastRms0;
//    unsigned char ucIFastRms1;
//    unsigned char ucIFastRms2;
//    unsigned char ucWatt0;
//    unsigned char ucWatt1;
//    unsigned char ucWatt2;
//    unsigned char ucCfCnt0;
//    unsigned char ucCfCnt1;
//    unsigned char ucCfCnt2;
//    unsigned char ucFreq0;
//    unsigned char ucFreq1;
//    unsigned char ucFreq2;
//    unsigned char ucStatus0;
//    unsigned char ucStatus1;
//    unsigned char ucStatus2;
//    unsigned char ucCheckSum;
//}stBL0942FrameDataTypes;
//#pragma pack()

#pragma pack(1)
typedef struct {
    unsigned char ucDeviceAddress;
    unsigned char ucRegistersAddress;
    unsigned char ucHead;
    unsigned char ucIRms[3];
    unsigned char ucVRms[3];
    unsigned char ucIFastRms[3];
    unsigned char ucWatt[3];
    unsigned char ucCfCnt[3];
    unsigned char ucFreq[3];
    unsigned char ucStatus[3];
    unsigned char ucCheckSum;
}stBL0942FrameDataTypes;
#pragma pack()

typedef union {
    unsigned char ucBL0942FrameData[25];
    stBL0942FrameDataTypes stBL0942FrameData;
}unBL0942FrameDataTypes;

typedef void (* vpHalUartSendByteTypes)(unsigned char ucByte);//串口发送一个字节
typedef void (* vpHalUartSendDataTypes)(unsigned char * pucData,unsigned short usDataLength);//串口发送N个数据

typedef struct {
    float fRL;
    float fR1;
    float fR2;
    float fIFactor6;
    float fVFactor6;
    float fPFactor6;
    float fPulseEnergy6;
    float fImpkWh;
    vpHalUartSendByteTypes vpHalUartSendByte;
    vpHalUartSendDataTypes vpHalUartSendData;
}stBL0942Types;

typedef struct {
    unsigned int uiRL3;
    unsigned int uiR13;
    unsigned int uiR23;
    unsigned int uiIFactor63;
    unsigned int uiVFactor63;
    unsigned int uiPFactor63;
    unsigned int uiPulseEnergy63;
    unsigned int uiImpkWh3;
}stBL0942CalcParameterTypes;

//typedef struct {
//    // float fRL;
//    // float fR1;
//    // float fR2;
//    // float fIFactor;
//    // float fVFactor;
//    // float fPFactor;
//    // float fPulseEnergy;
//    // float fImpkWh;
//
//    // vpHalUartSendByteTypes vpHalUartSendByte;
//    // vpHalUartSendDataTypes vpHalUartSendData;//初始化时注册的，用于与BL0942通讯的发送数据函数
//    unBL0942FrameDataTypes unBL0942FrameData;//用于BL0942通讯的帧缓存
//}stBL0942Types;

#pragma pack(1)
typedef struct {
	unsigned char ucIndex;
	unsigned char ucAddress;
	unsigned char ucData[3];
}stBL0942WriteCommandTypes;

typedef struct {
	unsigned char ucIndex;
	unsigned char ucAddress;
	// unsigned char ucData[3];
}stBL0942ReadCommandTypes;
#pragma pack()


/**
 * @brief   和校验
 *
 * @param   ucStartData    - 求和初始值
 * @param   pucData        - 要校验的数据指针
 * @param   pucData        - 要校验的数据长度
 *
 * @return  返回8位校验的累加和值
 */
unsigned char ucBL0942CheckSumAndNo(unsigned char ucStartData,unsigned char * pucData,unsigned short usDataLength);

/**
 * @brief   BL0942初始化，需要指定对应的串口发送函数和外围电路参数，然后根据外围电路参数计算相关系数
 *
 * @param   ps1        - 串口发送单个字节数据函数指针
 * @param   ps2        - 串口发送多个字节数据函数指针
 * @param   fRL        - BL0942外围电路RL的值，单位为毫欧
 * @param   fR1        - BL0942外围电路R1的值，单位为千欧
 * @param   fR2        - BL0942外围电路R2的值，单位为千欧
 *
 * @return  返回BL0942相关参数类型数据
 */
void vBL0942Init(stBL0942Types * pstBL0942,vpHalUartSendByteTypes ps1,vpHalUartSendDataTypes ps2,float fRL,float fR1,float fR2);

/**
 * @brief   读BL0942寄存器数据命令
 *
 * @param   ucBL0942Address - BL0942的地址，最多可支持4个地址，可以是(DE_WriteBL0942Cmd | 0~3 )
 * @param   eBL0942RegNum   - 要写的寄存器编号，可以是0x12、0x14~0x1a、0x1d、0x1c对应的读写寄存器
 * @param   pucData         - 要写入寄存器的数据3个字节
 *
 * @return  NONE
 */
void vBL0942WriteRegister(stBL0942Types * pstBL0942,unsigned char ucBL0942Address, eBL0942RegistersAddressTypes eBL0942RegNum,unsigned char * pucData);

/**
 * @brief   读BL0942寄存器数据命令
 *
 * @param   ucBL0942Address - BL0942的地址，最多可支持4个地址，可以是(DE_ReadBL0942Cmd | 0~3 )
 * @param   eBL0942RegNum   - 要读的寄存器编号，可以是1~9、0x12、0x14~0x1a、0x1d、0x1c对应的只读与读写寄存器和0xaa
 *
 * @return  NONE
 */
void vBL0942ReadRegister(stBL0942Types * pstBL0942,unsigned char ucBL0942Address, eBL0942RegistersAddressTypes eBL0942RegNum);



#ifdef __cplusplus
}
#endif

#endif // __BL0942_H__
