/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_flash.c
 * @brief      flash������
 * @author     Ұ��Ƽ�
 * @version    v5.0
 * @date       2013-09-01
 */


//����ͷ�ļ�

#include "include.h"

uint32 FlashWrite_Buff[3]; 
uint32 FlashRead_Buff[3];
uint32 ServoFlashWrite_Buff;
uint32 ServoFlashRead_Buff;
uint32 MPU6050FlashWrite_Buff[2];
uint32 MPU6050FlashRead_Buff[2];
uint32 max33FlashWrite_Buff[5];
uint32 max33FlashRead_Buff[5];  
char Flash_Saved=0;   //flash�������
//�궨�� FCCOB Number
#if defined(MKL26Z4)
#define     FCMD        FTFA_FCCOB0         //FTFL ����

#define     FADDR2      FTFA_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFA_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFA_FCCOB3         //Flash address [7:0]

#define     FDATA0      FTFA_FCCOB4         //Data Byte 0       //ע��һ�㣬4�ֽ�����FDATA3�����λ��FDATA0�����λ
#define     FDATA1      FTFA_FCCOB5         //Data Byte 1
#define     FDATA2      FTFA_FCCOB6         //Data Byte 2
#define     FDATA3      FTFA_FCCOB7         //Data Byte 3
#define     FDATA4      FTFA_FCCOB8         //Data Byte 4
#define     FDATA5      FTFA_FCCOB9         //Data Byte 5
#define     FDATA6      FTFA_FCCOBA         //Data Byte 6
#define     FDATA7      FTFA_FCCOBB         //Data Byte 7

//FCMD ����
#define     RD1BLK    0x00   // ������Flash
#define     RD1SEC    0x01   // ����������
#define     PGMCHK    0x02   // д����
#define     RDRSRC    0x03   // ��Ŀ������(4�ֽ�)
#define     PGM4      0x06   // д�볤��(4�ֽ�)
#define     ERSSCR    0x09   // ����Flash����
#define     RD1ALL    0x40   // �����еĿ�
#define     RDONCE    0x41   // ֻ��һ��
#define     PGMONCE   0x43   // ֻдһ��
#define     ERSALL    0x44   // �������п�
#define     VFYKEY    0x45   // ��֤���ŷ���Կ��



#elif defined(MK60DZ10)
#define     FCMD        FTFL_FCCOB0         //FTFL ����

#define     FADDR2      FTFL_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFL_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFL_FCCOB3         //Flash address [7:0]

#define     FDATA0      FTFL_FCCOB4         //Data Byte 0       //ע��һ�㣬4�ֽ�����FDATA3�����λ��FDATA0�����λ
#define     FDATA1      FTFL_FCCOB5         //Data Byte 1
#define     FDATA2      FTFL_FCCOB6         //Data Byte 2
#define     FDATA3      FTFL_FCCOB7         //Data Byte 3
#define     FDATA4      FTFL_FCCOB8         //Data Byte 4
#define     FDATA5      FTFL_FCCOB9         //Data Byte 5
#define     FDATA6      FTFL_FCCOBA         //Data Byte 6
#define     FDATA7      FTFL_FCCOBB         //Data Byte 7

//FCMD ����
#define     RD1BLK    0x00   // ������Flash
#define     RD1SEC    0x01   // ����������
#define     PGMCHK    0x02   // д����
#define     RDRSRC    0x03   // ��Ŀ������(4�ֽ�)
#define     PGM4      0x06   // д�볤��(4�ֽ�)
#define     ERSBLK    0x08   // ��������Flash
#define     ERSSCR    0x09   // ����Flash����
#define     PGMSEC    0x0B   // д������
#define     RD1ALL    0x40   // �����еĿ�
#define     RDONCE    0x41   // ֻ��һ��
#define     PGMONCE   0x43   // ֻдһ��
#define     ERSALL    0x44   // �������п�
#define     VFYKEY    0x45   // ��֤���ŷ���Կ��
#define     PGMPART   0x80   // д�����
#define     SETRAM    0x81   // �趨FlexRAM����

#elif defined(MK60F15)
#define     FCMD        FTFE_FCCOB0         //FTFL ����

#define     FADDR2      FTFE_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFE_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFE_FCCOB3         //Flash address [7:0]
//Must be 64-bit aligned (Flash address [2:0] = 000)  8�ֽڶ���

#define     FDATA0      FTFE_FCCOB4         //Data Byte 0       //ע��һ�㣬4�ֽ�����FDATA3�����λ��FDATA0�����λ
#define     FDATA1      FTFE_FCCOB5         //Data Byte 1
#define     FDATA2      FTFE_FCCOB6         //Data Byte 2
#define     FDATA3      FTFE_FCCOB7         //Data Byte 3
#define     FDATA4      FTFE_FCCOB8         //Data Byte 4
#define     FDATA5      FTFE_FCCOB9         //Data Byte 5
#define     FDATA6      FTFE_FCCOBA         //Data Byte 6
#define     FDATA7      FTFE_FCCOBB         //Data Byte 7

//FCMD ����
#define     RD1BLK    0x00   // ������Flash
#define     RD1SEC    0x01   // ����������
#define     PGMCHK    0x02   // д����
#define     RDRSRC    0x03   // ��Ŀ������(8�ֽ�)
#define     PGM8      0x07   // д�볤��(8�ֽ�)
#define     ERSBLK    0x08   // ��������Flash
#define     ERSSCR    0x09   // ����Flash����
#define     PGMSEC    0x0B   // д������
#define     RD1ALL    0x40   // �����еĿ�
#define     RDONCE    0x41   // ֻ��һ��
#define     PGMONCE   0x43   // ֻдһ��
#define     ERSALL    0x44   // �������п�
#define     VFYKEY    0x45   // ��֤���ŷ���Կ��
#define     PGMPART   0x80   // д�����
#define     SETRAM    0x81   // �趨FlexRAM����

#endif









/*!
 *  @brief      Flash����
 *  @return     ����ִ�н��(1�ɹ���0ʧ��)
 *  @since      v5.0
 */
__RAMFUNC uint8 flash_cmd()
{
    //д FTFL_FSTAT ���� Flash����
#if defined(MKL26Z4)
    FTFA_FSTAT =    (0
                     |  FTFA_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFA_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFA_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFA_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );

    while(!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK));    // �ȴ��������

    // �������־
    if( FTFA_FSTAT & (FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_RDCOLERR_MASK | FTFA_FSTAT_FPVIOL_MASK | FTFA_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //ִ���������
    }
    else
    {
        return 1;                                   //ִ������ɹ�
    }

#elif defined(MK60DZ10)
    FTFL_FSTAT =    (0
                     |  FTFL_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFL_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFL_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFL_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );

    while(!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK));    // �ȴ��������

    // �������־
    if( FTFL_FSTAT & (FTFL_FSTAT_ACCERR_MASK | FTFL_FSTAT_RDCOLERR_MASK | FTFL_FSTAT_FPVIOL_MASK | FTFL_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //ִ���������
    }
    else
    {
        return 1;                                   //ִ������ɹ�
    }

#elif defined(MK60F15)
    FTFE_FSTAT =    (0
                     |  FTFE_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFE_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFE_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFE_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );

    while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));    // �ȴ��������

    // �������־
    if( FTFE_FSTAT & (FTFE_FSTAT_ACCERR_MASK | FTFE_FSTAT_RDCOLERR_MASK | FTFE_FSTAT_FPVIOL_MASK | FTFE_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //ִ���������
    }
    else
    {
        return 1;                                   //ִ������ɹ�
    }

#endif




}


/*!
 *  @brief      ��ʼ��flash
 *  @since      v5.0
 */
__RAMFUNC void flash_init(void)
{
#if defined(MKL26Z4)
    while(!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK))
    FTFA_FSTAT =    (0
                     |  FTFA_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFA_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFA_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFA_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );

#elif defined( MK60DZ10)
    // ���FlashԤ��ȡ������
    FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;      //
    FMC_PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;

    while(!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK));    // �ȴ��������

    FTFL_FSTAT =    (0
                     |  FTFL_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFL_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFL_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFL_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );

#elif defined(MK60F15)
    // ���FlashԤ��ȡ������
    FMC_PFB01CR |= FMC_PFB01CR_S_B_INV_MASK;      //
    //FMC_PFB23CR |= FMC_PFB23CR_S_B_INV_MASK;

    while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));    // �ȴ��������

    FTFE_FSTAT =    (0
                     |  FTFE_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFE_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFE_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFE_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );
#endif
}

/*!
 *  @brief      ����ָ��flash����
 *  @param      sector_num    �����ţ�K60N512ʵ��ʹ��0~255��
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v5.0
 *  Sample usage:       flash_erase_sector(127);        //��������127
 */
__RAMFUNC uint8 flash_erase_sector(uint16 sector_num)
{
    uint32 addr = sector_num * FLASH_SECTOR_SIZE;

    // ���ò�������
    FCMD = ERSSCR;

    // ����Ŀ���ַ
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];

    if(flash_cmd() == 0)
    {
        return 0;
    }

    if(sector_num == 0)
    {
#if   defined(MKL26Z4)
        return flash_write(sector_num,0x00040C,0xFFFFFFFE);     //KL Ҳ�� 0x40c
#elif defined(MK60DZ10)
        return flash_write(sector_num,0x00040C,0xFFFFFFFE);
#elif defined(MK60F15)
        return flash_write(sector_num,0x000408,0xFFFFFFFEFFFFFFFF );
#endif
    }

    return 1;
}


/*!
 *  @brief      д�볤�ֽ����ݵ� flashָ����ַ
 *  @param      sector_num      �����ţ�0 ~ FLASH_SECTOR_NUM��
 *  @param      offset          д�������ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *  @param      data            ��Ҫд�������
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v5.0
 *  Sample usage:       flash_write(127,0,0xFFFFFFFE);        //����127,ƫ�Ƶ�ַΪ0,д������:0xFFFFFFFE
 */
__RAMFUNC uint8 flash_write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data)
{
    uint32 addr = sector_num * FLASH_SECTOR_SIZE  + offset ;
    uint32 tmpdata;

    ASSERT(offset % FLASH_ALIGN_ADDR == 0);             //ƫ��������Ϊ4�ı���
    //�˴���ʾ���棬���ǰ�ȫ�ġ���
    ASSERT(offset <= FLASH_SECTOR_SIZE);                //������СΪ2K����ƫ�������벻���� 0x800
    //�˴���ʾ���棬���ǰ�ȫ�ġ���

    // ����Ŀ���ַ
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];

    // ���� ��32λ����
    tmpdata = (uint32)data;

    FDATA0 = ((Dtype *)&tmpdata)->B[3];                    // ����д������
    FDATA1 = ((Dtype *)&tmpdata)->B[2];
    FDATA2 = ((Dtype *)&tmpdata)->B[1];
    FDATA3 = ((Dtype *)&tmpdata)->B[0];

#if (defined(MK60DZ10)  || defined(MKL26Z4) )

    // ���ò�������
    FCMD = PGM4;

#elif defined(MK60F15)

    // ���ò�������
    FCMD = PGM8;

    // ���� ��32λ����
    tmpdata = (uint32)(data>>32);

    FDATA4 = ((Dtype *)&tmpdata)->B[3];                 // ����д������
    FDATA5 = ((Dtype *)&tmpdata)->B[2];
    FDATA6 = ((Dtype *)&tmpdata)->B[1];
    FDATA7 = ((Dtype *)&tmpdata)->B[0];
#endif

    if(flash_cmd() == 0)
    {
        return 0;
    }

    return 1;  //�ɹ�ִ��

}


/*!
 *  @brief      д�����ݻ������� flashָ����ַ
 *  @param      sector_num      �����ţ�K60N512ʵ��ʹ��0~255��
 *  @param      offset          д�������ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *  @param      buf             ��Ҫд������ݻ������׵�ַ
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v5.0
 *  Sample usage:           uint32 buff[10];
                            flash_write_buf(127,0,sizeof(buff),buff);        //����127,ƫ�Ƶ�ַΪ0,д������Դ��ַ:buff,��Ŀsizeof(buff)
 */

__RAMFUNC uint8 flash_write_buf(uint16 sector_num, uint16 offset, uint16 cnt, uint8 *buf)
{
    uint32  size;

    uint32  addr;
    uint32  data;

    ASSERT(offset % FLASH_ALIGN_ADDR == 0);                    //ƫ��������Ϊ4�ı���
    //�˴���ʾ���棬���ǰ�ȫ��(ram��������rom�������𾯸�)
    ASSERT(offset <= FLASH_SECTOR_SIZE );                    //������СΪ2K����ƫ�������벻���� 0x800
    //�˴���ʾ���棬���ǰ�ȫ��(ram��������rom�������𾯸�)

    addr = sector_num * FLASH_SECTOR_SIZE  + offset;      //�����ַ

    // ����д������
#if (defined(MK60DZ10)  || defined(MKL26Z4) )
    FCMD = PGM4;
#elif defined(MK60F15)
    FCMD = PGM8;
#endif

    for(size = 0; size < cnt; size += FLASH_ALIGN_ADDR )
    {

        // ����Ŀ���ַ
        FADDR2 = ((Dtype *)&addr)->B[2];
        FADDR1 = ((Dtype *)&addr)->B[1];
        FADDR0 = ((Dtype *)&addr)->B[0];

        // ���� ��32λ����
        data =  *(uint32 *)buf;

        FDATA0 = ((Dtype *)&data)->B[3];                    // ����д������
        FDATA1 = ((Dtype *)&data)->B[2];
        FDATA2 = ((Dtype *)&data)->B[1];
        FDATA3 = ((Dtype *)&data)->B[0];

#if defined(MK60F15)
        // ���� ��32λ����
        data = *(uint32 *)(buf+4);

        FDATA0 = ((Dtype *)&data)->B[3];                    // ����д������
        FDATA1 = ((Dtype *)&data)->B[2];
        FDATA2 = ((Dtype *)&data)->B[1];
        FDATA3 = ((Dtype *)&data)->B[0];
#endif

        if(flash_cmd() == 0)
        {
            return 0;
        }

        addr += FLASH_ALIGN_ADDR;
        buf += FLASH_ALIGN_ADDR;
    }
    return 1;  //�ɹ�ִ��
}

void ReadFlash(void)
{
          
          FlashRead_Buff[0]=flash_read(SECTOR_NUM_AD, 4, uint32);
          FlashRead_Buff[1]=flash_read(SECTOR_NUM_AD, 8, uint32);
          FlashRead_Buff[2]=flash_read(SECTOR_NUM_AD, 12, uint32);
          F_FL_MAX = (uint16)(FlashRead_Buff[0]%65536);   
          F_L_MAX  = (uint16)(FlashRead_Buff[0]/65536);
          F_M_MAX  = (uint16)(FlashRead_Buff[1]%65536);
          F_R_MAX  = (uint16)(FlashRead_Buff[1]/65536);
          F_FR_MAX = (uint16)(FlashRead_Buff[2]%65536);
          
          max33FlashRead_Buff[0]=flash_read(SECTOR_NUM_AD, 16, uint32);
          max33FlashRead_Buff[1]=flash_read(SECTOR_NUM_AD, 20, uint32);
          max33FlashRead_Buff[2]=flash_read(SECTOR_NUM_AD, 24, uint32);
          max33FlashRead_Buff[3]=flash_read(SECTOR_NUM_AD, 28, uint32);
          max33FlashRead_Buff[4]=flash_read(SECTOR_NUM_AD, 32, uint32);
          max[0][0]= (uint16)(max33FlashRead_Buff[0]%65536);   
          max[0][1]  = (uint16)(max33FlashRead_Buff[0]/65536);
          max[0][2]  = (uint16)(max33FlashRead_Buff[1]%65536);
          max[1][0]  = (uint16)(max33FlashRead_Buff[1]/65536);
          max[1][1] = (uint16)(max33FlashRead_Buff[2]%65536);
          max[1][2] = (uint16)(max33FlashRead_Buff[2]/65536);   
          max[2][0]  = (uint16)(max33FlashRead_Buff[3]%65536);
          max[2][1]  = (uint16)(max33FlashRead_Buff[3]/65536);
          max[2][2]  = (uint16)(max33FlashRead_Buff[4]%65536);
          
          ServoFlashRead_Buff=flash_read(SECTOR_NUM_SERVO,4 , uint32);     
          SerMid_Debug=(uint16)(ServoFlashRead_Buff%65536);
          
          MPU6050FlashRead_Buff[0]=flash_read(SECTOR_NUM_MPU,4 , uint32);
          MPU6050FlashRead_Buff[1]=flash_read(SECTOR_NUM_MPU,12 , uint32);
          Accel_X_Offest=(int32)(MPU6050FlashRead_Buff[0]%65536);
          Gyro_Y_Offest =(int32)(MPU6050FlashRead_Buff[0]/65536);                   
          Accel_Z_Offest=(int32)(MPU6050FlashRead_Buff[1]%65536);
          
          Angle_ShuiPing=flash_read(SECTOR_NUM_ShuiPing,4 ,int32);
}

void WriteFlash(void)
{          
           flash_erase_sector(SECTOR_NUM_AD);//��������           
           FlashWrite_Buff[0]=F_FL_MAX + F_L_MAX*65536;
           FlashWrite_Buff[1]=F_M_MAX + F_R_MAX*65536;
           FlashWrite_Buff[2]=F_FR_MAX ;//+ F_L_MAX*65536; 
           flash_write(SECTOR_NUM_AD, 4, FlashWrite_Buff[0]); 
           flash_write(SECTOR_NUM_AD, 8, FlashWrite_Buff[1]); 
           flash_write(SECTOR_NUM_AD, 12, FlashWrite_Buff[2]); 
           
           max33FlashWrite_Buff[0]=(uint32)(max[0][0] + max[0][1]*65536);
           max33FlashWrite_Buff[1]=(uint32)(max[0][2] + max[1][0]*65536);
           max33FlashWrite_Buff[2]=(uint32)(max[1][1] + max[1][2]*65536);
           max33FlashWrite_Buff[3]=(uint32)(max[2][0] + max[2][1]*65536);
           max33FlashWrite_Buff[4]=(uint32)(max[2][2]);
           flash_write(SECTOR_NUM_AD, 16, max33FlashWrite_Buff[0]); 
           flash_write(SECTOR_NUM_AD, 20, max33FlashWrite_Buff[1]); 
           flash_write(SECTOR_NUM_AD, 24, max33FlashWrite_Buff[2]); 
           flash_write(SECTOR_NUM_AD, 28, max33FlashWrite_Buff[3]); 
           flash_write(SECTOR_NUM_AD, 32, max33FlashWrite_Buff[4]); 
                    
}

void WriteFlash_ServoMid(void)
{
     flash_erase_sector(SECTOR_NUM_SERVO);//�������� 
     ServoFlashWrite_Buff=SerMid_Debug*65536+SerMid_Debug;
     flash_write(SECTOR_NUM_SERVO, 4, ServoFlashWrite_Buff);
}

void WriteFlash_MPUoffset(void)
{    
     flash_erase_sector(SECTOR_NUM_MPU);
     MPU6050FlashWrite_Buff[0]=(uint32)(Accel_X_Offest+Gyro_Y_Offest*65536);
     MPU6050FlashWrite_Buff[1]=(uint32)(Accel_Z_Offest+Accel_Z_Offest*65536);
     flash_write(SECTOR_NUM_MPU,4,MPU6050FlashWrite_Buff[0]);
     flash_write(SECTOR_NUM_MPU,12,MPU6050FlashWrite_Buff[1]);
}

void WriteFlash_Angle_ShuiPing(void)
{
     flash_erase_sector(SECTOR_NUM_ShuiPing);
     flash_write(SECTOR_NUM_ShuiPing,4,Angle_ShuiPing);
}

void ReadFlash_(void)
{
     /******����OFF��ȡflash��ONʱ����У��*******/
     if( BoMa_Key_Up == GetKeyStatus(BoMa_Key1)) //����ON��0 == GetKeyStatus(BoMa_Key1)  ���²� ���뿪��
     {       
        delay_fmq(10);                     
        if( BoMa_Key_Up == GetKeyStatus(BoMa_Key1))
        {
           ReadFlash();                //��ȡflash�еĵ�����ֵ     
        }
     }
     
}
uint8 F_Scces=0;
void WriteFlash_ADmax(void)
{
     /******��������ֵ*******/   //���ڹ�һ��
     if( BoMa_Key_Down == GetKeyStatus(BoMa_Key1)&&Flash_Saved==0) //����ON��0 == GetKeyStatus(BoMa_Key1)  ���ϲ� ���뿪��
     {   
          delay_fmq(10);
          if( BoMa_Key_Down == GetKeyStatus(BoMa_Key1))
          {
               AD_GetMaxValue();    //���ϲɼ�ˢ�µ��AD���ֵ
          }
          F_Scces=1;
     }
     else if(Flash_Saved==0&&F_Scces==1)
     {
          WriteFlash();         //��flash��д���е����ֵ���´ο���ʹ�� 
          Flash_Saved=1;        //����
     }   
}


