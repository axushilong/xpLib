/********************************** (C) COPYRIGHT *******************************
 * File Name          : Hal3Wire.c
 * Author             : axushilong@163.com
 * Version            : V0.1
 * Date               :
 * Description        : 3线串行接口驱动库
 * Copyright (c) 2022 axushilong
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "Hal3Wire.h"

/*********************************************************************
 * @brief   3线串行接口初始化
 *
 * @param   pstHal3Wire        - 指向3线串行接口类型。
 * @param   if3WirePinInit     - 3线串行接口用到的引脚初始化。
 * @param   ifCsPinHighOrLow   - 指向3线串行接口CS引脚高低电平设置。
 * @param   ifClkPinHighOrLow  - 指向3线串行接口Clk引脚高低电平设置。
 * @param   ifDataPinHighOrLow - 指向3线串行接口Data引脚高低电平设置。
 *
 * @return  成功返回0
 */
void vHal3WireInit(stHal3WireTypes * pstHal3Wire,  vf3WirePinInitTypes vf3WirePinInit, vfPinHighOrLowTypes vfCsPinHighOrLow, vfPinHighOrLowTypes vfClkPinHighOrLow, vfPinHighOrLowTypes vfDataPinHighOrLow){
    pstHal3Wire->vf3WirePinInit = vf3WirePinInit;
    vf3WirePinInit();
    pstHal3Wire->vfCsPinHighOrLow   = vfCsPinHighOrLow;
    pstHal3Wire->vfClkPinHighOrLow  = vfClkPinHighOrLow;
    pstHal3Wire->vfDataPinHighOrLow = vfDataPinHighOrLow;
}

/**
 * @brief   3线串行接口引脚复位
 *
 * @param   pstHal3Wire - 指向3线串行接口类型。
 *
 * @return  成功返回0
 */
void vHal3WirePinReset(stHal3WireTypes * pstHal3Wire){
    pstHal3Wire->vfCsPinHighOrLow(DE_PinHigh);
    pstHal3Wire->vfClkPinHighOrLow(DE_PinHigh);
    pstHal3Wire->vfDataPinHighOrLow(DE_PinHigh);
//    pstHal3Wire->vf3WirePinInit();
}

/**
 * @brief   3线串行接口Data引脚写入字节，从高位开始写。
 *
 *
 * @param   pstHal3Wire     - 指向3线串行接口类型。
 * @param   ucByte          - 3线串行接口要写入的数据。
 * @param   ucByteBitLength - 要写入的数据位长度,不允许超过8位。
 *
 * @return  成功返回0
 */
void vHal3WireWriteByteH(stHal3WireTypes * pstHal3Wire, unsigned char ucByte, unsigned char ucByteBitLength){
    unsigned char ucIndex;
    for (ucIndex = 0; ucIndex < ucByteBitLength; ++ucIndex) {
        pstHal3Wire->vfClkPinHighOrLow(DE_PinLow);//时钟低电平
//        _nop();_nop();
        pstHal3Wire->vfDataPinHighOrLow((_Bool)(ucByte & 0x80));//数据电平
//        __nop();__nop();//等待低电平稳定
        pstHal3Wire->vfClkPinHighOrLow(DE_PinHigh);//时钟高电平
        ucByte <<= 1;
    }
//    pstSerialInterface3Wire->ifClkPinHighOrLow(DE_PinLow);//时钟低电平
//    pstHal3Wire->vfDataPinHighOrLow(DE_PinHigh);//数据电平
}

/**
 * @brief   3线串行接口Data引脚写入字节，从低位开始写。
 *
 *
 * @param   pstHal3Wire     - 指向3线串行接口类型。
 * @param   ucByte          - 3线串行接口要写入的数据。
 * @param   ucByteBitLength - 要写入的数据位长度。
 *
 * @return  成功返回0
 */
void vHal3WireWriteByteL(stHal3WireTypes * pstHal3Wire, unsigned char ucByte, unsigned char ucByteBitLength){
    unsigned char ucIndex;
    for (ucIndex = 0; ucIndex < ucByteBitLength; ++ucIndex) {
        pstHal3Wire->vfClkPinHighOrLow(DE_PinLow);//时钟低电平
//        _nop();_nop();
        pstHal3Wire->vfDataPinHighOrLow((_Bool)(ucByte & 0x01));//数据电平
//        __nop();__nop();//等待低电平稳定
        pstHal3Wire->vfClkPinHighOrLow(DE_PinHigh);//时钟高电平
        ucByte >>= 1;
    }
//    pstSerialInterface3Wire->ifClkPinHighOrLow(DE_PinLow);//时钟低电平
//    stHal3Wire->vfDataPinHighOrLow(DE_PinHigh);//数据电平
}



