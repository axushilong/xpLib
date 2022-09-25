/********************************** (C) COPYRIGHT *******************************
 * File Name          : TM1621C.h
 * Author             : axushilong@163.com
 * Version            : V0.1
 * Date               :
 * Description        :TM1621C驱动
 * Copyright (c) 2022 axushilong
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "TM1621C.h"



/*********************************************************************
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
void vTm1621cInit(stTm1621cTypes *pstTm1621c, stHal3WireTypes * pstHal3Wire, vfHal3WireInitTypes vfHal3WireInit, vfHal3WirePinResetTypes vfHal3WirePinReset, vfHal3WireWriteByteHTypes vfHal3WireWriteByteH, vfHal3WireWriteByteLTypes vfHal3WireWriteByteL, unsigned char * pucALcdRam){
    pstTm1621c->pstHal3Wire = pstHal3Wire;
    pstTm1621c->vfHal3WireInit = vfHal3WireInit;
    pstTm1621c->vfHal3WirePinReset   = vfHal3WirePinReset;
    pstTm1621c->vfHal3WireWriteByteH = vHal3WireWriteByteH;
    pstTm1621c->vfHal3WireWriteByteL = vHal3WireWriteByteL;
    pstTm1621c->pucALcdRam = pucALcdRam;
}

/*********************************************************************
 * @brief   TM1621C写显存RAM连续数据
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   pucRamData       - TM1621C要刷新的内存数据，只有低4位有效，每秒刷新一次
 * @param   ucDataLength     - 要写入内存地址的数据个数
 *
 * @return  NONE
 */
void vTm1621cWriteRam(stTm1621cTypes *pstTm1621c, unsigned char ucAddress, unsigned char * pucRamData, unsigned char ucDataLength){
    unsigned char ucIndex;
    pstTm1621c->vfHal3WirePinReset(pstTm1621c->pstHal3Wire);//3线串行接口复位
    pstTm1621c->pstHal3Wire->vfCsPinHighOrLow(DE_PinLow);
    pstTm1621c->vfHal3WireWriteByteH(pstTm1621c->pstHal3Wire,0xa0,3);
    pstTm1621c->vfHal3WireWriteByteH(pstTm1621c->pstHal3Wire,ucAddress << 2,6);
    for (ucIndex = 0; ucIndex < ucDataLength; ++ucIndex) {
        pstTm1621c->vfHal3WireWriteByteL(pstTm1621c->pstHal3Wire,pucRamData[ucIndex],4);
    }
//    pstTm1621c->vfHal3WirePinReset(pstTm1621c->pstHal3Wire);//3线串行接口复位
    pstTm1621c->pstHal3Wire->vfCsPinHighOrLow(DE_PinHigh);
}

/*********************************************************************
 * @brief   TM1621C写显存RAM连续相同数据
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   ucSetData        - TM1621C要设置的内存数据，只有低4位有效
 * @param   ucDataLength     - 要写入内存地址的数据个数
 *
 * @return  NONE
 */
void vTm1621cRamSet(stTm1621cTypes *pstTm1621c, unsigned char ucAddress, unsigned char ucSetData, unsigned char ucDataLength){
    unsigned char ucIndex;
    pstTm1621c->vfHal3WirePinReset(pstTm1621c->pstHal3Wire);//3线串行接口复位
    pstTm1621c->pstHal3Wire->vfCsPinHighOrLow(DE_PinLow);
    pstTm1621c->vfHal3WireWriteByteH(pstTm1621c->pstHal3Wire,0xa0,3);
    pstTm1621c->vfHal3WireWriteByteH(pstTm1621c->pstHal3Wire,ucAddress << 2,6);
    for (ucIndex = 0; ucIndex < ucDataLength; ++ucIndex) {
        pstTm1621c->vfHal3WireWriteByteL(pstTm1621c->pstHal3Wire,ucSetData,4);
    }
//    pstTm1621c->vfHal3WirePinReset(pstTm1621c->pstHal3Wire);//3线串行接口复位
    pstTm1621c->pstHal3Wire->vfCsPinHighOrLow(DE_PinHigh);
}

/*********************************************************************
 * @brief   TM1621C显存全部清零
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   pucRamData       - TM1621C要刷新的内存数据，只有低4位有效，每秒刷新一次
 * @param   ucDataLength     - BL0942外围电路R1的值，单位为千欧
 *
 * @return  NONE
 */
void vTm1621cRamClear(stTm1621cTypes *pstTm1621c){
    vTm1621cRamSet(pstTm1621c, 0, 0, 6);
    vTm1621cRamSet(pstTm1621c, 13, 0, 20-13);
    vTm1621cRamSet(pstTm1621c, 26, 0, 31-26);
}

/*********************************************************************
 * @brief   TM1621C显存RAM全填充
 *
 * @param   pstTm1621c       - TM1621C实例,确定是哪一个TM1621C
 * @param   ucAddress        - 要写入的显存Ram的位置
 * @param   pucRamData       - TM1621C要刷新的内存数据，只有低4位有效，每秒刷新一次
 * @param   ucDataLength     - BL0942外围电路R1的值，单位为千欧
 *
 * @return  NONE
 */
void vTm1621cRamFull(stTm1621cTypes *pstTm1621c){
    vTm1621cRamSet(pstTm1621c, 0, 0, 6);
    vTm1621cRamSet(pstTm1621c, 13, 0xff, 20-13);
    vTm1621cRamSet(pstTm1621c, 26, 0xff, 31-26);
}

/*********************************************************************
 * @brief   TM1621C写命令
 *
 * @param   pstTm1621c - TM1621C实例,确定是哪一个TM1621C
 * @param   ucCommand  - 要写入LCD驱动器的命令
 *
 * @return  返回BL0942相关参数类型数据
 */
void vTm1621cWriteCmd(stTm1621cTypes * pstTm1621c, unsigned char ucCommand){
    unsigned char ucHead;
    if(ucCommand > 0xc0) {
        ucHead = 0x90;
    }else{
        ucHead = 0x80;
    }
    pstTm1621c->vfHal3WirePinReset(pstTm1621c->pstHal3Wire);//3线串行接口复位
    pstTm1621c->pstHal3Wire->vfCsPinHighOrLow(DE_PinLow);
    pstTm1621c->vfHal3WireWriteByteH(pstTm1621c->pstHal3Wire,ucHead,4);
    pstTm1621c->vfHal3WireWriteByteH(pstTm1621c->pstHal3Wire,ucCommand,8);
//    pstTm1621c->vfHal3WirePinReset(pstTm1621c->pstHal3Wire);//3线串行接口复位
    pstTm1621c->pstHal3Wire->vfCsPinHighOrLow(DE_PinHigh);
}



