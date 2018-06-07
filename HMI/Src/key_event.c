/************************* (C) COPYRIGHT 2013 DZXH ************************
* ��  ��  ��      : KEY_EVENT.C
* ��      ��      : DZXH@Dream Creater
* ��      ��      ��DZXH ������V2.1/V1.0��
* ��  ��  ��      : http://shop102062100.taobao.com/
* ��      ��      : V1.0
* ��      ��      : 2013/11
* ��  ��  MCU     : STM32F103VET6
* ��  ��  ��      : Keil ARM 4.54
* ��      ��      : �����¼�����
**************************************************************************/
#include "include.h"
#include "key.h"
#include "GUI.h"

/************************************************************************
* ��  ��  ��  : deal_key_event
* ��      ��  : �����¼�����
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void deal_key_event()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //��ð����ͽ��д���
    {     	
        if(keymsg.status == KEY_DOWN)
        {
//////////������д�Լ����¼�����       
            switch(keymsg.key)
            {
            case KEY_0:
				break;

            case KEY_1:
				break;

            case KEY_2:
				break;

            case KEY_3:
				break;

            case KEY_4:
				break;            
            case KEY_UPP:
               // up_fmq();
            if(Game_Mode==1)
            {
                 
            }
            else
            { 
              if(ActProgramSate == Saved)
           		{
              		ActChangeState=Once;
					ActCommand=SelectUp;//PageUp;
           		}
				else if(ActProgramSate == Changing)
           		{
              		ActChangeState=Once;
              		ActCommand=Add;
           		}
				else if(CMDstate == ActProgramSate)
				{
              		ActChangeState=Once;
					ActCommand=SelectUp;
				}
            
            	ActCommandState=Begin;
            }
                break;

            case KEY_DOWNN:
                //down_fmq();
            if(Game_Mode==1)
            {
                 
            }
            else
            { 
            	if(ActProgramSate == Saved)
           		{
              		ActChangeState=Once;
					ActCommand=SelectDown;//PageDown;
           		}
				else if(ActProgramSate == Changing)
           		{
              		ActChangeState=Once;
              		ActCommand=Minus;
           		}
				else if(CMDstate == ActProgramSate)
				{
              		ActChangeState=Once;
					ActCommand=SelectDown;
				}
            
            	ActCommandState=Begin;
            }
                break;

            case KEY_L:
               if(Game_Mode==1)
            {
                 
            }
            else
            { 
                        //left_fmq();
    		 	if(ActProgramSate == Saved | CMDstate == ActProgramSate)
    		 	{    		 		  
           	  		ActCommand=PageUp;
              		ActCommandState=Begin;
    		 	}
            }
				break;

            case KEY_R:
               if(Game_Mode==1)
            {
                 
            }
            else
            { 
                        //right_fmq();
        		if(ActProgramSate == Saved | CMDstate == ActProgramSate)
    		 	{	  
           	  		ActCommand=PageDown;
              		ActCommandState=Begin;
    		 	}
            }
				break;

            case KEY_OK:
            if(Game_Mode==1)
            {    
                 Gamestatus_Pre=Gamestatus;
                 Gamestatus=ING;
                
            }
            else
            { 
                               // ok_fmq();
				if(ActProgramSate == Changing)
					ActCommand=Save;
				else if(ActProgramSate == Saved)
					ActCommand=Select;
				else if(ActProgramSate == CMDstate)
					ActCommand = DoCmd;
				ActCommandState=Begin;
            }
				break;

            default:
				break;
            }
//            down_fmq();
        }
        else if(keymsg.status == KEY_HOLD)
        {
         
            switch(keymsg.key)
            {
            case KEY_0:
                break;
            case KEY_1:
				break;
            case KEY_2:
				break;
            case KEY_3:     
				break;
            case KEY_4:	
				break;            
            case KEY_UPP:
            if(Game_Mode==1)
            {
                 Game_Key = game_UP;
            }
            else
            { 
	           if(ActProgramSate == Saved)
	           {
	              ActChangeState=Continue;
							  ActCommand=PageUp;
	           }else if(ActProgramSate == Changing)
	           {
	              ActChangeState=Continue;
	              ActCommand=Add;
	           }
	            
	            ActCommandState=Begin;
            }
				break;
				
            case KEY_DOWNN:
            if(Game_Mode==1)
            {
                 Game_Key = game_DOWN;
            }
            else
            { 
				if(ActProgramSate == Saved)
		        {
		        	ActChangeState=Continue;
					ActCommand=PageDown;
		        }
				else if(ActProgramSate == Changing)
		        {
		        	ActChangeState=Continue;
		            ActCommand=Minus;
		        }
		        ActCommandState=Begin;
              }
                break;

            case KEY_L:
            if(Game_Mode==1)
            {
                 Game_Key = game_LEFT;
            }
            else
            { 
              
				ActCommand = ModeUp;
				ActCommandState = Begin;
            }
                break;

            case KEY_R:
            if(Game_Mode==1)
            {
                 Game_Key = game_RIGHT;
            }
            else
            { 
				ActCommand = ModeDown;
				ActCommandState = Begin;
				break;
            }

            case KEY_OK:
            if(Game_Mode==1)
            {
                 Gamestatus=OVER;
                 Game_Mode=0;
            }
            else
            { 
				ActCommandState = Finished;
            }
				break;

            default:
				break;
		
            }
					//	ok_hold_fmq();
						
        }
        else
           Game_Key = game_NO;
    }
}

