/********************************** (C) COPYRIGHT *******************************
 * File Name          : TM1621C.h
 * Author             : axushilong@163.com
 * Version            : V0.1
 * Date               : 
 * Description
 * Copyright (c) 2022 axushilong
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef __TM1621C_H__
#define __TM1621C_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include <stdbool.h>
#include "Hal3Wire.h"

#define DE_Com(n) ((n-2) << 3)
#define DE_DefaultComN DE_Com(4)

#define DE_SysDis  (0x00)
#define DE_SysEn   (0x02)
#define DE_LcdOff  (0x04)
#define DE_LcdOn   (0x06)
#define DE_Xtal32k (0x28)
#define DE_RC256k  (0x30)
#define DE_Bias1_2 (0x40)
#define DE_Bias1_3 (0x42)
#define DE_Topt    (0xc0)
#define DE_Tnormal (0xc6)

typedef void (* vfHal3WireInitTypes)(stHal3WireTypes * pstHal3Wire, vf3WirePinInitTypes vf3WirePinInit, vfPinHighOrLowTypes vfCsPinHighOrLow, vfPinHighOrLowTypes vfClkPinHighOrLow, vfPinHighOrLowTypes vfDataPinHighOrLow);
typedef void (* vfHal3WirePinResetTypes)(stHal3WireTypes * pstHal3Wire);
typedef void (* vfHal3WireWriteByteHTypes)(stHal3WireTypes * pstHal3Wire, unsigned char ucByte, unsigned char ucByteBitLength);
typedef void (* vfHal3WireWriteByteLTypes)(stHal3WireTypes * pstHal3Wire, unsigned char ucByte, unsigned char ucByteBitLength);

typedef struct {
    stHal3WireTypes * pstHal3Wire;
    vfHal3WireInitTypes vfHal3WireInit;/*需要注册进来的函数*/
    vfHal3WirePinResetTypes vfHal3WirePinReset;/*需要注册进来的函数*/
    vfHal3WireWriteByteHTypes vfHal3WireWriteByteH;/*需要注册进来的函数*/
    vfHal3WireWriteByteLTypes vfHal3WireWriteByteL;/*需要注册进来的函数*/
    unsigned char * pucALcdRam;
}stTm1621cTypes;

/**
 * @brief   TM1621C实例初始化
 *
 * @param   pstTm1621c           - TM1621C实例
 * @param   pstHal3Wire          - TM1621C实例硬件层3线串行接口实例，用于注册函数的参数
 * @param   vfHal3WireInit       - TM1621C实例硬件层3线串行接口初始化函数
 * @param   vfHal3WirePinReset   - TM1621C实例硬件层3线串行接口引脚复位
 * @param   vfHal3WireWriteByteH - TM1621C实例硬件层3线串行接口从高位开始写字节
 * @param   vfHal3WireWriteByteL - TM1621C实例硬件层3线串行接口从低位开始写字节
 * @param   pucALcdRam           - TM1621C实例用于显示的内存
 *
 * @return  NONE
 */
void vTm1621cInit(stTm1621cTypes *pstTm1621c, stHal3WireTypes * pstHal3Wire, vfHal3WireInitTypes vfHal3WireInit, vfHal3WirePinResetTypes vfHal3WirePinReset, vfHal3WireWriteByteHTypes vfHal3WireWriteByteH, vfHal3WireWriteByteLTypes vfHal3WireWriteByteL, unsigned char * pucALcdRam);

/**
 * @brief   TM1621C写显存RAM连续数据
 *
 * @param   pstTm1621c   - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress    - 要写入的显存Ram的位置
 * @param   pucRamData   - TM1621C要刷新的内存数据，只有低4位有效，每秒刷新一次
 * @param   ucDataLength - BL0942外围电路R1的值，单位为千欧
 *
 * @return  NONE
 */
void vTm1621cWriteRam(stTm1621cTypes *pstTm1621c, unsigned char ucAddress, unsigned char * pucRamData, unsigned char ucDataLength);

/**
 * @brief   TM1621C写显存RAM连续相同数据
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   ucSetData        - TM1621C要设置的内存数据，只有低4位有效
 * @param   ucDataLength     - 要写入内存地址的数据个数
 *
 * @return  NONE
 */
void vTm1621cRamSet(stTm1621cTypes *pstTm1621c, unsigned char ucAddress, unsigned char ucSetData, unsigned char ucDataLength);

/**
 * @brief   TM1621C显存全部清零
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   pucRamData       - TM1621C要刷新的内存数据，只有低4位有效，每秒刷新一次
 * @param   ucDataLength     - BL0942外围电路R1的值，单位为千欧
 *
 * @return  NONE
 */
void vTm1621cRamClear(stTm1621cTypes *pstTm1621c);

/**
 * @brief   TM1621C显存RAM全填充
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   pucRamData       - TM1621C要刷新的内存数据，只有低4位有效，每秒刷新一次
 * @param   ucDataLength     - BL0942外围电路R1的值，单位为千欧
 *
 * @return  NONE
 */
void vTm1621cRamFull(stTm1621cTypes *pstTm1621c);

/**
 * @brief   TM1621C写命令
 *
 * @param   pstTm1621c - TM1621C实例,确定是哪一个TM1621C
 * @param   ucCommand  - 要写入内存地址的数据个数
 *
 * @return  NONE
 */
void vTm1621cWriteCmd(stTm1621cTypes * pstTm1621c, unsigned char ucCommand);



#ifdef __cplusplus
}
#endif

#endif // __BL0942_H__
