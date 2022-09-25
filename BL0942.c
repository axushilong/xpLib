/********************************** (C) COPYRIGHT *******************************
 * File Name          : BL0942.h
 * Author             : axushilong@163.com
 * Version            : V0.1
 * Date               :
 * Description        : BL0942驱动库
 * Copyright (c) 2022 axushilong
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "BL0942.h"



//static float afRL;
//static float afR1;
//static float afR2;
//static float afIFactor;
//static float afVFactor;
//static float afPFactor;
//static float afPulseEnergy;//单个脉冲能量
//static float afImpkWh;

//static stBL0942ParameterTypes astBL0942Parameter;
//
//static vpHalUartSendByteTypes avpHalUartSendByte;
//static vpHalUartSendDataTypes avpHalUartSendData;

/*********************************************************************
 * @brief   和校验
 *
 * @param   ucStartData    - 求和初始值
 * @param   pucData        - 要校验的数据指针
 * @param   pucData        - 要校验的数据长度
 *
 * @return  返回8位校验的累加和值
 */
unsigned char ucBL0942CheckSumAndNo(unsigned char ucStartData,unsigned char * pucData,unsigned short usDataLength){
	unsigned char ucCheckSum = ucStartData;
	while(--usDataLength){
		ucCheckSum += pucData[usDataLength];
	}
	ucCheckSum += pucData[usDataLength];
	return ~ucCheckSum;
}

/*********************************************************************
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
void vBL0942Init(stBL0942Types * pstBL0942,vpHalUartSendByteTypes ps1,vpHalUartSendDataTypes ps2,float fRL,float fR1,float fR2){
    float fTmp1,fTmp2;
    pstBL0942->fRL = fRL;
    pstBL0942->fR1 = fR1;
    pstBL0942->fR2 = fR2;
    pstBL0942->fIFactor6 = DE_1_6Vref / (305978 * fRL);
    pstBL0942->fVFactor6 = DE_1_6Vref * (fR1 + fR2) / (73989 * fR1 * 1000);
    pstBL0942->fPFactor6 = DE_1_6Vref2 * (fR1 + fR2) / (3537 * fRL * fR1 * 1000);
    fTmp1 = 1638.4 * 256 * DE_Vref2 * (fR1 + fR2);
//    fTmp2 = 3600000 * 3537 * fRL * fR1 * 1000;
    fTmp2 = 3600 * 3537 * fRL * fR1;
//    fTmp2 = 3600 * 3537;
//    fTmp2 = fTmp2 * fR1;
//    fTmp2 = fTmp2 * fRL;
    pstBL0942->fPulseEnergy6 = (fTmp1 / fTmp2);// / 1000000;
    pstBL0942->fImpkWh = (fTmp2 * 100 / fTmp1) * 10000;
    pstBL0942->vpHalUartSendByte = ps1;
    pstBL0942->vpHalUartSendData = ps2;
}

/*********************************************************************
 * @brief   读BL0942寄存器数据命令
 *
 * @param   ucBL0942Address - BL0942的地址，最多可支持4个地址，可以是(DE_WriteBL0942Cmd | 0~3 )
 * @param   eBL0942RegNum   - 要写的寄存器编号，可以是0x12、0x14~0x1a、0x1d、0x1c对应的读写寄存器
 * @param   pucData   - 要写的寄存器的值
 *
 * @return  NONE
 */
void vBL0942WriteRegister(stBL0942Types * pstBL0942,unsigned char ucBL0942Address, eBL0942RegistersAddressTypes eBL0942RegNum,unsigned char * pucData){
    static unsigned char ucTemp[6];
    ucTemp[0] = ucBL0942Address;
    ucTemp[1] = (unsigned char)eBL0942RegNum;
    ucTemp[2] = pucData[0];
    ucTemp[3] = pucData[1];
    ucTemp[4] = pucData[2];
    ucTemp[5] = ucBL0942CheckSumAndNo(0,ucTemp,5);
    pstBL0942->vpHalUartSendData(ucTemp,6);
}

/*********************************************************************
 * @brief   读BL0942寄存器数据命令
 *
 * @param   ucBL0942Address - BL0942的地址，最多可支持4个地址，可以是(DE_ReadBL0942Cmd | 0~3 )
 * @param   eBL0942RegNum   - 要读的寄存器编号，可以是1~9、0x12、0x14~0x1a、0x1d、0x1c对应的只读与读写寄存器和0xaa
 *
 * @return  NONE
 */
void vBL0942ReadRegister(stBL0942Types * pstBL0942,unsigned char ucBL0942Address, eBL0942RegistersAddressTypes eBL0942RegNum){
    static unsigned char ucTemp[6];
    ucTemp[0] = ucBL0942Address;
    ucTemp[1] = (unsigned char)eBL0942RegNum;
    // ucTemp[2] = pucData[0];
    // ucTemp[3] = pucData[1];
    // ucTemp[4] = pucData[2];
    // ucTemp[5] = aucCheckSumAndNo(ucTemp,5);
    pstBL0942->vpHalUartSendData(ucTemp,2);
}


/*
需要每隔一段时间设置一次 有功功率防潜动寄存器（WA_CREEP），可以根据功率寄存器WATT的值设置WA_CREEP。
WA_CREEP = (WATT<<8) / 3125。
WA_CREEP 缺省值为 0x0B；对应的 WATT 有功功率寄存器值=11*3125/256≈134；
如果采用 1 毫欧采样电阻，电压采用电阻分压 390K*5+0.51K；对应的实际功率 =134/623.4=0.215 瓦。
实际应用时可根据应用要求，提高有功防潜动阈值寄存器的设置，比如 1 瓦以下不要求计量。
阈值设置为 1W 对应的参数： =623.4/（3125/256） ≈51， WA_CREEP=0x33；

几个重要参数：实际电流值系数IFactor、实际电压值系数VFactor、实际有功功率值系数PFactor

实际电流值 = 实际电流值系数IFactor * （I_RMS）电流有效值寄存器值
实际电压值 = 实际电压值系数VFactor * （V_RMS）电压有效值寄存器值
实际有功功率值 = 实际有功功率值系数PFactor * （WATT）有功功率寄存器值

非隔离方案（RL 单位为毫欧， R2,R1 单位为 K 欧； Vref=1.218 伏,Vref * Vref = 1.483524）
实际电流值系数IFactor = Vref / (305978 * RL)
实际电压值系数VFactor = Vref * (R2 + R1) / (73989 * R1 * 1000)
实际有功功率值系数PFactor = Vref * Vref * (R2 + R1) / (3537 * RL * R1 * 1000)
每个电能脉冲对应的电量PulseEnergy = 1638.4 * 256 * Vref * Vref * (R2 + R1) / (3600000 * 3537 * RL * R1 * 1000)
imp/kWh = 3600000 * 3537 * RL * R1 * 1000 / (1638.4 * 256 * Vref * Vref * (R2 + R1))

初始化时：
需要获取保存的RL、R1、R2的值，根据这3个值，分别计算出IFactor、VFactor、PFactor、每个电能脉冲对应的电量PulseEnergy和impkWh

定时实时获取状态，并上报和打印异常状态

定时获取所有电量数据,并打印电量数据

*/
