/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,野火科技
 *     All rights reserved.
 *     技术讨论：野火初学论坛 http://www.chuxue123.com
 *
 *     除注明出处外，以下所有内容版权均属野火科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留野火科技的版权声明。
 *
 * @file       MK60_flash.c
 * @brief      flash函数库
 * @author     野火科技
 * @version    v5.0
 * @date       2013-09-01
 */


//包含头文件

#include "include.h"

uint32 FlashWrite_Buff[3]; 
uint32 FlashRead_Buff[3];
uint32 ServoFlashWrite_Buff;
uint32 ServoFlashRead_Buff;
uint32 MPU6050FlashWrite_Buff[2];
uint32 MPU6050FlashRead_Buff[2];
uint32 max33FlashWrite_Buff[5];
uint32 max33FlashRead_Buff[5];  
char Flash_Saved=0;   //flash保存变量
//宏定义 FCCOB Number
#if defined(MKL26Z4)
#define     FCMD        FTFA_FCCOB0         //FTFL 命令

#define     FADDR2      FTFA_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFA_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFA_FCCOB3         //Flash address [7:0]

#define     FDATA0      FTFA_FCCOB4         //Data Byte 0       //注意一点，4字节排序，FDATA3是最低位，FDATA0是最高位
#define     FDATA1      FTFA_FCCOB5         //Data Byte 1
#define     FDATA2      FTFA_FCCOB6         //Data Byte 2
#define     FDATA3      FTFA_FCCOB7         //Data Byte 3
#define     FDATA4      FTFA_FCCOB8         //Data Byte 4
#define     FDATA5      FTFA_FCCOB9         //Data Byte 5
#define     FDATA6      FTFA_FCCOBA         //Data Byte 6
#define     FDATA7      FTFA_FCCOBB         //Data Byte 7

//FCMD 命令
#define     RD1BLK    0x00   // 读整块Flash
#define     RD1SEC    0x01   // 读整个扇区
#define     PGMCHK    0x02   // 写入检查
#define     RDRSRC    0x03   // 读目标数据(4字节)
#define     PGM4      0x06   // 写入长字(4字节)
#define     ERSSCR    0x09   // 擦除Flash扇区
#define     RD1ALL    0x40   // 读所有的块
#define     RDONCE    0x41   // 只读一次
#define     PGMONCE   0x43   // 只写一次
#define     ERSALL    0x44   // 擦除所有块
#define     VFYKEY    0x45   // 验证后门访问钥匙



#elif defined(MK60DZ10)
#define     FCMD        FTFL_FCCOB0         //FTFL 命令

#define     FADDR2      FTFL_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFL_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFL_FCCOB3         //Flash address [7:0]

#define     FDATA0      FTFL_FCCOB4         //Data Byte 0       //注意一点，4字节排序，FDATA3是最低位，FDATA0是最高位
#define     FDATA1      FTFL_FCCOB5         //Data Byte 1
#define     FDATA2      FTFL_FCCOB6         //Data Byte 2
#define     FDATA3      FTFL_FCCOB7         //Data Byte 3
#define     FDATA4      FTFL_FCCOB8         //Data Byte 4
#define     FDATA5      FTFL_FCCOB9         //Data Byte 5
#define     FDATA6      FTFL_FCCOBA         //Data Byte 6
#define     FDATA7      FTFL_FCCOBB         //Data Byte 7

//FCMD 命令
#define     RD1BLK    0x00   // 读整块Flash
#define     RD1SEC    0x01   // 读整个扇区
#define     PGMCHK    0x02   // 写入检查
#define     RDRSRC    0x03   // 读目标数据(4字节)
#define     PGM4      0x06   // 写入长字(4字节)
#define     ERSBLK    0x08   // 擦除整块Flash
#define     ERSSCR    0x09   // 擦除Flash扇区
#define     PGMSEC    0x0B   // 写入扇区
#define     RD1ALL    0x40   // 读所有的块
#define     RDONCE    0x41   // 只读一次
#define     PGMONCE   0x43   // 只写一次
#define     ERSALL    0x44   // 擦除所有块
#define     VFYKEY    0x45   // 验证后门访问钥匙
#define     PGMPART   0x80   // 写入分区
#define     SETRAM    0x81   // 设定FlexRAM功能

#elif defined(MK60F15)
#define     FCMD        FTFE_FCCOB0         //FTFL 命令

#define     FADDR2      FTFE_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFE_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFE_FCCOB3         //Flash address [7:0]
//Must be 64-bit aligned (Flash address [2:0] = 000)  8字节对齐

#define     FDATA0      FTFE_FCCOB4         //Data Byte 0       //注意一点，4字节排序，FDATA3是最低位，FDATA0是最高位
#define     FDATA1      FTFE_FCCOB5         //Data Byte 1
#define     FDATA2      FTFE_FCCOB6         //Data Byte 2
#define     FDATA3      FTFE_FCCOB7         //Data Byte 3
#define     FDATA4      FTFE_FCCOB8         //Data Byte 4
#define     FDATA5      FTFE_FCCOB9         //Data Byte 5
#define     FDATA6      FTFE_FCCOBA         //Data Byte 6
#define     FDATA7      FTFE_FCCOBB         //Data Byte 7

//FCMD 命令
#define     RD1BLK    0x00   // 读整块Flash
#define     RD1SEC    0x01   // 读整个扇区
#define     PGMCHK    0x02   // 写入检查
#define     RDRSRC    0x03   // 读目标数据(8字节)
#define     PGM8      0x07   // 写入长字(8字节)
#define     ERSBLK    0x08   // 擦除整块Flash
#define     ERSSCR    0x09   // 擦除Flash扇区
#define     PGMSEC    0x0B   // 写入扇区
#define     RD1ALL    0x40   // 读所有的块
#define     RDONCE    0x41   // 只读一次
#define     PGMONCE   0x43   // 只写一次
#define     ERSALL    0x44   // 擦除所有块
#define     VFYKEY    0x45   // 验证后门访问钥匙
#define     PGMPART   0x80   // 写入分区
#define     SETRAM    0x81   // 设定FlexRAM功能

#endif









/*!
 *  @brief      Flash命令
 *  @return     命令执行结果(1成功，0失败)
 *  @since      v5.0
 */
__RAMFUNC uint8 flash_cmd()
{
    //写 FTFL_FSTAT 启动 Flash命令
#if defined(MKL26Z4)
    FTFA_FSTAT =    (0
                     |  FTFA_FSTAT_CCIF_MASK        // 指令完成标志(写1清0)
                     |  FTFA_FSTAT_RDCOLERR_MASK    // 读冲突错误标志(写1清0)
                     |  FTFA_FSTAT_ACCERR_MASK      // 访问错误标志位(写1清0)
                     |  FTFA_FSTAT_FPVIOL_MASK      // 非法访问保护标志位(写1清0)
                    );

    while(!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK));    // 等待命令完成

    // 检查错误标志
    if( FTFA_FSTAT & (FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_RDCOLERR_MASK | FTFA_FSTAT_FPVIOL_MASK | FTFA_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //执行命令出错
    }
    else
    {
        return 1;                                   //执行命令成功
    }

#elif defined(MK60DZ10)
    FTFL_FSTAT =    (0
                     |  FTFL_FSTAT_CCIF_MASK        // 指令完成标志(写1清0)
                     |  FTFL_FSTAT_RDCOLERR_MASK    // 读冲突错误标志(写1清0)
                     |  FTFL_FSTAT_ACCERR_MASK      // 访问错误标志位(写1清0)
                     |  FTFL_FSTAT_FPVIOL_MASK      // 非法访问保护标志位(写1清0)
                    );

    while(!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK));    // 等待命令完成

    // 检查错误标志
    if( FTFL_FSTAT & (FTFL_FSTAT_ACCERR_MASK | FTFL_FSTAT_RDCOLERR_MASK | FTFL_FSTAT_FPVIOL_MASK | FTFL_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //执行命令出错
    }
    else
    {
        return 1;                                   //执行命令成功
    }

#elif defined(MK60F15)
    FTFE_FSTAT =    (0
                     |  FTFE_FSTAT_CCIF_MASK        // 指令完成标志(写1清0)
                     |  FTFE_FSTAT_RDCOLERR_MASK    // 读冲突错误标志(写1清0)
                     |  FTFE_FSTAT_ACCERR_MASK      // 访问错误标志位(写1清0)
                     |  FTFE_FSTAT_FPVIOL_MASK      // 非法访问保护标志位(写1清0)
                    );

    while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));    // 等待命令完成

    // 检查错误标志
    if( FTFE_FSTAT & (FTFE_FSTAT_ACCERR_MASK | FTFE_FSTAT_RDCOLERR_MASK | FTFE_FSTAT_FPVIOL_MASK | FTFE_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //执行命令出错
    }
    else
    {
        return 1;                                   //执行命令成功
    }

#endif




}


/*!
 *  @brief      初始化flash
 *  @since      v5.0
 */
__RAMFUNC void flash_init(void)
{
#if defined(MKL26Z4)
    while(!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK))
    FTFA_FSTAT =    (0
                     |  FTFA_FSTAT_CCIF_MASK        // 指令完成标志(写1清0)
                     |  FTFA_FSTAT_RDCOLERR_MASK    // 读冲突错误标志(写1清0)
                     |  FTFA_FSTAT_ACCERR_MASK      // 访问错误标志位(写1清0)
                     |  FTFA_FSTAT_FPVIOL_MASK      // 非法访问保护标志位(写1清0)
                    );

#elif defined( MK60DZ10)
    // 清除Flash预读取缓冲区
    FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;      //
    FMC_PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;

    while(!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK));    // 等待命令完成

    FTFL_FSTAT =    (0
                     |  FTFL_FSTAT_CCIF_MASK        // 指令完成标志(写1清0)
                     |  FTFL_FSTAT_RDCOLERR_MASK    // 读冲突错误标志(写1清0)
                     |  FTFL_FSTAT_ACCERR_MASK      // 访问错误标志位(写1清0)
                     |  FTFL_FSTAT_FPVIOL_MASK      // 非法访问保护标志位(写1清0)
                    );

#elif defined(MK60F15)
    // 清除Flash预读取缓冲区
    FMC_PFB01CR |= FMC_PFB01CR_S_B_INV_MASK;      //
    //FMC_PFB23CR |= FMC_PFB23CR_S_B_INV_MASK;

    while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));    // 等待命令完成

    FTFE_FSTAT =    (0
                     |  FTFE_FSTAT_CCIF_MASK        // 指令完成标志(写1清0)
                     |  FTFE_FSTAT_RDCOLERR_MASK    // 读冲突错误标志(写1清0)
                     |  FTFE_FSTAT_ACCERR_MASK      // 访问错误标志位(写1清0)
                     |  FTFE_FSTAT_FPVIOL_MASK      // 非法访问保护标志位(写1清0)
                    );
#endif
}

/*!
 *  @brief      擦除指定flash扇区
 *  @param      sector_num    扇区号（K60N512实际使用0~255）
 *  @return     执行结果(1成功，0失败)
 *  @since      v5.0
 *  Sample usage:       flash_erase_sector(127);        //擦除扇区127
 */
__RAMFUNC uint8 flash_erase_sector(uint16 sector_num)
{
    uint32 addr = sector_num * FLASH_SECTOR_SIZE;

    // 设置擦除命令
    FCMD = ERSSCR;

    // 设置目标地址
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
        return flash_write(sector_num,0x00040C,0xFFFFFFFE);     //KL 也是 0x40c
#elif defined(MK60DZ10)
        return flash_write(sector_num,0x00040C,0xFFFFFFFE);
#elif defined(MK60F15)
        return flash_write(sector_num,0x000408,0xFFFFFFFEFFFFFFFF );
#endif
    }

    return 1;
}


/*!
 *  @brief      写入长字节数据到 flash指定地址
 *  @param      sector_num      扇区号（0 ~ FLASH_SECTOR_NUM）
 *  @param      offset          写入扇区内部偏移地址（0~2043 中 4的倍数）
 *  @param      data            需要写入的数据
 *  @return     执行结果(1成功，0失败)
 *  @since      v5.0
 *  Sample usage:       flash_write(127,0,0xFFFFFFFE);        //扇区127,偏移地址为0,写入数据:0xFFFFFFFE
 */
__RAMFUNC uint8 flash_write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data)
{
    uint32 addr = sector_num * FLASH_SECTOR_SIZE  + offset ;
    uint32 tmpdata;

    ASSERT(offset % FLASH_ALIGN_ADDR == 0);             //偏移量必须为4的倍数
    //此处提示警告，但是安全的……
    ASSERT(offset <= FLASH_SECTOR_SIZE);                //扇区大小为2K，即偏移量必须不大于 0x800
    //此处提示警告，但是安全的……

    // 设置目标地址
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];

    // 设置 低32位数据
    tmpdata = (uint32)data;

    FDATA0 = ((Dtype *)&tmpdata)->B[3];                    // 设置写入数据
    FDATA1 = ((Dtype *)&tmpdata)->B[2];
    FDATA2 = ((Dtype *)&tmpdata)->B[1];
    FDATA3 = ((Dtype *)&tmpdata)->B[0];

#if (defined(MK60DZ10)  || defined(MKL26Z4) )

    // 设置擦除命令
    FCMD = PGM4;

#elif defined(MK60F15)

    // 设置擦除命令
    FCMD = PGM8;

    // 设置 高32位数据
    tmpdata = (uint32)(data>>32);

    FDATA4 = ((Dtype *)&tmpdata)->B[3];                 // 设置写入数据
    FDATA5 = ((Dtype *)&tmpdata)->B[2];
    FDATA6 = ((Dtype *)&tmpdata)->B[1];
    FDATA7 = ((Dtype *)&tmpdata)->B[0];
#endif

    if(flash_cmd() == 0)
    {
        return 0;
    }

    return 1;  //成功执行

}


/*!
 *  @brief      写入数据缓冲区到 flash指定地址
 *  @param      sector_num      扇区号（K60N512实际使用0~255）
 *  @param      offset          写入扇区内部偏移地址（0~2043 中 4的倍数）
 *  @param      buf             需要写入的数据缓冲区首地址
 *  @return     执行结果(1成功，0失败)
 *  @since      v5.0
 *  Sample usage:           uint32 buff[10];
                            flash_write_buf(127,0,sizeof(buff),buff);        //扇区127,偏移地址为0,写入数据源地址:buff,数目sizeof(buff)
 */

__RAMFUNC uint8 flash_write_buf(uint16 sector_num, uint16 offset, uint16 cnt, uint8 *buf)
{
    uint32  size;

    uint32  addr;
    uint32  data;

    ASSERT(offset % FLASH_ALIGN_ADDR == 0);                    //偏移量必须为4的倍数
    //此处提示警告，但是安全的(ram函数调用rom函数引起警告)
    ASSERT(offset <= FLASH_SECTOR_SIZE );                    //扇区大小为2K，即偏移量必须不大于 0x800
    //此处提示警告，但是安全的(ram函数调用rom函数引起警告)

    addr = sector_num * FLASH_SECTOR_SIZE  + offset;      //计算地址

    // 设置写入命令
#if (defined(MK60DZ10)  || defined(MKL26Z4) )
    FCMD = PGM4;
#elif defined(MK60F15)
    FCMD = PGM8;
#endif

    for(size = 0; size < cnt; size += FLASH_ALIGN_ADDR )
    {

        // 设置目标地址
        FADDR2 = ((Dtype *)&addr)->B[2];
        FADDR1 = ((Dtype *)&addr)->B[1];
        FADDR0 = ((Dtype *)&addr)->B[0];

        // 设置 低32位数据
        data =  *(uint32 *)buf;

        FDATA0 = ((Dtype *)&data)->B[3];                    // 设置写入数据
        FDATA1 = ((Dtype *)&data)->B[2];
        FDATA2 = ((Dtype *)&data)->B[1];
        FDATA3 = ((Dtype *)&data)->B[0];

#if defined(MK60F15)
        // 设置 高32位数据
        data = *(uint32 *)(buf+4);

        FDATA0 = ((Dtype *)&data)->B[3];                    // 设置写入数据
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
    return 1;  //成功执行
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
           flash_erase_sector(SECTOR_NUM_AD);//擦除扇区           
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
     flash_erase_sector(SECTOR_NUM_SERVO);//擦除扇区 
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
     /******开关OFF读取flash，ON时重新校订*******/
     if( BoMa_Key_Up == GetKeyStatus(BoMa_Key1)) //开关ON：0 == GetKeyStatus(BoMa_Key1)  向下拨 拨码开关
     {       
        delay_fmq(10);                     
        if( BoMa_Key_Up == GetKeyStatus(BoMa_Key1))
        {
           ReadFlash();                //读取flash中的电感最大值     
        }
     }
     
}
uint8 F_Scces=0;
void WriteFlash_ADmax(void)
{
     /******检测电感最大值*******/   //用于归一化
     if( BoMa_Key_Down == GetKeyStatus(BoMa_Key1)&&Flash_Saved==0) //开关ON：0 == GetKeyStatus(BoMa_Key1)  向上拨 拨码开关
     {   
          delay_fmq(10);
          if( BoMa_Key_Down == GetKeyStatus(BoMa_Key1))
          {
               AD_GetMaxValue();    //不断采集刷新电感AD最大值
          }
          F_Scces=1;
     }
     else if(Flash_Saved==0&&F_Scces==1)
     {
          WriteFlash();         //向flash中写入电感的最大值供下次开机使用 
          Flash_Saved=1;        //锁存
     }   
}


