/********************************** (C) COPYRIGHT *******************************
 * File Name          : Hal3Wire.h
 * Author             : axushilong@163.com
 * Version            : V0.1
 * Date               : 
 * Description
 * Copyright (c) 2022 axushilong
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef __HAL3WIRE_H__
#define __HAL3WIRE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define DE_PinHigh (1)
#define DE_PinLow  (0)

typedef void (* vf3WirePinInitTypes)(void); /*3线串行接口引脚初始化函数指针类型，可以确定是哪3个脚*/
typedef void (* vfPinHighOrLowTypes)(_Bool);/*引脚高低电平设置函数指针类型*/

typedef struct {
    vf3WirePinInitTypes vf3WirePinInit;    /*需要注册进来的函数，用于初始化3线串行接口实例所用到的引脚*/
    vfPinHighOrLowTypes vfCsPinHighOrLow;  /*需要注册进来的函数，用于控制3线串行接口实例的Cs引脚高低电平*/
    vfPinHighOrLowTypes vfClkPinHighOrLow; /*需要注册进来的函数，用于控制3线串行接口实例的Clk引脚高低电平*/
    vfPinHighOrLowTypes vfDataPinHighOrLow;/*需要注册进来的函数，用于控制3线串行接口实例的Data引脚高低电平*/
}stHal3WireTypes;

/**
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
void vHal3WireInit(stHal3WireTypes * pstHal3Wire, vf3WirePinInitTypes vf3WirePinInit, vfPinHighOrLowTypes vfCsPinHighOrLow, vfPinHighOrLowTypes vfClkPinHighOrLow, vfPinHighOrLowTypes vfDataPinHighOrLow);

/**
 * @brief   3线串行接口引脚复位
 *
 * @param   pstHal3Wire - 指向3线串行接口类型。
 *
 * @return  成功返回0
 */
void vHal3WirePinReset(stHal3WireTypes * pstHal3Wire);

/**
 * @brief   3线串行接口Data引脚写入字节，从高位开始写。
 *
 *
 * @param   pstHal3Wire     - 指向3线串行接口类型。
 * @param   ucByte          - 3线串行接口要写入的数据。
 * @param   ucByteBitLength - 要写入的数据位长度。
 *
 * @return  成功返回0
 */
void vHal3WireWriteByteH(stHal3WireTypes * pstHal3Wire, unsigned char ucByte, unsigned char ucByteBitLength);

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
void vHal3WireWriteByteL(stHal3WireTypes * pstHal3Wire, unsigned char ucByte, unsigned char ucByteBitLength);

#ifdef __cplusplus
}
#endif

#endif // __BASE64_H__
