/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_flash.h
 * @brief      flash������
 * @author     Ұ��Ƽ�
 * @version    v5.0
 * @date       2013-09-01
 */


#ifndef _MK60_FLASH_H_
#define _MK60_FLASH_H_

//k60N512����512K�ĳ���Flash
//512K�ĳ���Flash��Ϊ256��������ÿ������2K��С
//K60X256����256K�ĳ���Flash
//512K�ĳ���Flash��Ϊ128��������ÿ������2K��С
//    sector��2K��Ϊ������С��λ
//    ���֣�32b��Ϊд����С��λ

#include "common.h"

#if defined(MKL26Z4)
#define     FLASH_SECTOR_SIZE       (1024)                  //������С Ϊ 1k �ֽ�
#define     FLASH_SECTOR_NUM        (256)                   //������

#define     FLASH_ALIGN_ADDR         4                       //��ַ����������
typedef     uint32                  FLASH_WRITE_TYPE;       //flash_write ����д�� ����������

#elif defined(MK60DZ10)
#define     FLASH_SECTOR_SIZE       (2*1024)                //������С Ϊ 2k �ֽ�
#define     FLASH_SECTOR_NUM        (256)                   //������

#define     FLASH_ALIGN_ADDR        4                       //��ַ����������
typedef     uint32                  FLASH_WRITE_TYPE;       //flash_write ����д�� ����������


#elif defined(MK60F15)
#define     FLASH_SECTOR_SIZE       (4*1024)                //������С Ϊ 4k �ֽ�
#define     FLASH_SECTOR_NUM        (128)                   //������

#define     FLASH_ALIGN_ADDR        8                       //��ַ����������
typedef     uint64                  FLASH_WRITE_TYPE;       //flash_write ����д�� ����������

#endif


__RAMFUNC    void    flash_init();                                                                               //����ָ��flash����

__RAMFUNC    uint8   flash_erase_sector  (uint16 sectorNo);                                                      //����ָ��flash����

__RAMFUNC    uint8   flash_write         (uint16 sectorNo, uint16 offset, FLASH_WRITE_TYPE data);                          //д��flash����
__RAMFUNC    uint8   flash_write_buf     (uint16 sectorNo, uint16 offset, uint16 cnt, uint8 buf[]);              //�ӻ�����д��flash����

#define     flash_read(sectorNo,offset,type)        (*(type *)((uint32)(((sectorNo)*FLASH_SECTOR_SIZE) + (offset))))          //��ȡ����


#define SECTOR_NUM_AD       (FLASH_SECTOR_NUM-1)         //Flash����������������������ȷ����ȫ
#define SECTOR_NUM_SERVO    (FLASH_SECTOR_NUM-2)         //Flash����������������������ȷ����ȫ
#define SECTOR_NUM_MPU      (FLASH_SECTOR_NUM-3)         //Flash����������������������ȷ����ȫ  
#define SECTOR_NUM_ShuiPing (FLASH_SECTOR_NUM-4)         //Flash����������������������ȷ����ȫ 
//#define SECTOR_NUM_CONFIG   (FLASH_SECTOR_NUM-5)         //Flash����������������������ȷ����ȫ

extern void ReadFlash(void);
extern void WriteFlash(void);
extern void ReadFlash_(void);
extern void WriteFlash_ADmax(void);
extern void WriteFlash_ServoMid(void);
extern void WriteFlash_MPUoffset(void);
extern void WriteFlash_Angle_ShuiPing(void);

#endif //_FLASH_H_
