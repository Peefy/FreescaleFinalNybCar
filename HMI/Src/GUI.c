#include "GUI.h"
#include "stdio.h"


enum Command ActCommand=None;
enum Command NextCommand=None;

enum CommandState ActCommandState= Begin;
enum ProgramSate  ActProgramSate=Saved;

enum ChangeState  ActChangeState=Once;

//页码号
int PageNum=0;
int ItermNum=0;
int index_FirstItermInPage = 0;
int ItermNumCMD =  0;
int index_FirstItermCMDInPage = 0;

GUIStatusType GUI_PublicStatus={
	ItemNum_MAX,
	Iterm_TOTAL,
	4,0
};

void GUI_Sleep(void);
u8 GUI_IsSleep(void);


extern char ParaNames[Iterm_TOTAL][ItermNameLengthMax+1];
extern const s32 ParaSteps[Iterm_TOTAL];
extern const s32 ParaMax[Iterm_TOTAL];
extern const s32 ParaMin[Iterm_TOTAL];
extern void (*pPannelCmd[Iterm_CMD_TOTAL])(void);
extern char CMDNames[Iterm_CMD_TOTAL][ItermNameLengthMax+1];
extern char* CMDNames_[Iterm_CMD_TOTAL] ;
#ifdef PANNEL_SEND_DATA
extern s32 GUI_ParaFromCOM[Iterm_TOTAL];
#endif

s32  Para16s[Iterm_TOTAL];

///外部函数引用
void LCD_CLEAR(void);
void LCD_PrintString(u8,u8,char*);
void Panel_LoadParas(u8 index);
#ifdef PANNEL_SEND_DATA
void PANNEL_SEND_DATA(void);
#endif
void Panel_SaveParas(void);


/////子函数
void GUI_Save()
{
	Panel_SaveParas();
#ifdef PANNEL_SEND_DATA
	PANNEL_SEND_DATA();
#endif
}
void GUI_ShowCMDOnePage()
{
		u8 temp[ItemNum_MAX];
#ifdef SHOW_PAGE_NUM
		char string[7] = "";
#endif
		u8 i;
		
		for(i=0;i<ItemNum_MAX;++i)
		{
			if(index_FirstItermCMDInPage+i<Iterm_CMD_TOTAL)
			{
		             //LCD_PrintCMDNameString(LCD_X_NAME,i,CMDNames[index_FirstItermCMDInPage+i]);
                          LCD_PrintCMDNameString(LCD_X_NAME,i,CMDNames_[index_FirstItermCMDInPage+i]);
			}
			temp[i]=(ItermNumCMD+i)%ItemNum_MAX;
		}
#ifdef SHOW_PAGE_NUM
		string[0] = 'P';string[1] = 'a';string[2]='g';string[3]='e';
		sprintf(string+4, "%2d",PageNum);
		LCD_PrintParaNameString(0,i,string);
#endif 
	
		LCD_PrintCMDNameString(0,temp[0],">");
		for(i=1;i<ItemNum_MAX;++i)
			LCD_PrintCMDNameString(0,temp[i]," ");
}
void GUI_showOnePage()
{
	u8 temp[ItemNum_MAX];
#ifdef SHOW_PAGE_NUM
	char string[7] = "";
#endif
	u8 i;
	
	for(i=0;i<ItemNum_MAX;++i)
	{
		if(index_FirstItermInPage+i<Iterm_TOTAL)
		{
			LCD_PrintParaNameString(LCD_X_NAME,i,ParaNames[index_FirstItermInPage+i]);
//			temp[i]=(ItermNum+i)%ItemNum_MAX;
//			sprintf(string, "%6d",Para16s[index_FirstItermInPage+i]);
//			LCD_PrintParaDataString(LCD_X_DATA,i,string);
		}
		temp[i]=(ItermNum+i)%ItemNum_MAX;
	}
#ifdef SHOW_PAGE_NUM
	string[0] = 'P';string[1] = 'a';string[2]='g';string[3]='e';
	sprintf(string+4, "%2d",PageNum);
	LCD_PrintParaNameString(0,i,string);
#endif 

	LCD_PrintParaNameString(0,temp[0],">");
	for(i=1;i<ItemNum_MAX;++i)
		LCD_PrintParaNameString(0,temp[i]," ");
}
void GUI_ShowData()
{
	char string[7] = "";
	u8 i;

	if(ActProgramSate == Changing)
		Panel_LoadParas(index_FirstItermInPage+ItermNum);
	else if(ActProgramSate == Saved)
		Panel_LoadParas(Iterm_TOTAL);
	for(i=0;i<ItemNum_MAX;++i)
	{
		if(index_FirstItermInPage+i<Iterm_TOTAL)
		{
			sprintf(string, "%6d",Para16s[index_FirstItermInPage+i]);
			LCD_PrintParaDataString(LCD_X_DATA,i,string);
		}
	}

}
void Gui(void)
{
 u8 i,indexSelected;
 s8 temp[ItemNum_MAX];
 char string[6] = "";

 
 if(ActCommandState==Begin)
 {  
  switch(ActCommand)
  {  
	case PageUp:
			if(CMDstate == ActProgramSate)
			{			
				index_FirstItermCMDInPage -= ItemNum_MAX;
				//判断是否超出范围
				if(index_FirstItermCMDInPage<0) 
				{
				  PageNum=((s16)Iterm_CMD_TOTAL / (s16)ItemNum_MAX);
				  if(Iterm_CMD_TOTAL%ItemNum_MAX == 0)
					--PageNum;
				  index_FirstItermCMDInPage = PageNum*ItemNum_MAX;
				}
				else
					PageNum=index_FirstItermCMDInPage / ItemNum_MAX;
				
				if(index_FirstItermCMDInPage+ItermNumCMD>=Iterm_CMD_TOTAL)
					ItermNumCMD = Iterm_CMD_TOTAL - index_FirstItermCMDInPage - 1;
				//重新显示
				LCD_CLEAR();
				GUI_ShowCMDOnePage();
			}
			else
			{
                index_FirstItermInPage -= ItemNum_MAX;
				//判断是否超出范围
                if(index_FirstItermInPage<0) 
                {
                  PageNum=((s16)Iterm_TOTAL / (s16)ItemNum_MAX);
				  if(Iterm_TOTAL%ItemNum_MAX == 0)
				  	--PageNum;
				  index_FirstItermInPage = PageNum*ItemNum_MAX;
                }
				else
	                PageNum=index_FirstItermInPage / ItemNum_MAX;

				if(index_FirstItermInPage+ItermNum>=Iterm_TOTAL)
					ItermNum = Iterm_TOTAL - index_FirstItermInPage - 1;
				//重新显示
				LCD_CLEAR();
				GUI_showOnePage();
			}
                ActCommandState=Finished;
                break;
    case PageDown:  
			if(CMDstate == ActProgramSate)
			{			
				index_FirstItermCMDInPage += ItemNum_MAX;
				//判断是否超出范围
				if(index_FirstItermCMDInPage>=Iterm_CMD_TOTAL) 
				{
				  index_FirstItermCMDInPage = 0;
				}
				PageNum=index_FirstItermCMDInPage / ItemNum_MAX;
				
				if(index_FirstItermCMDInPage+ItermNumCMD>=Iterm_CMD_TOTAL)
					ItermNumCMD = Iterm_CMD_TOTAL - index_FirstItermCMDInPage - 1;
				//重新显示
				LCD_CLEAR();
				GUI_ShowCMDOnePage();
			}
			else
			{
                index_FirstItermInPage += ItemNum_MAX;
				//判断是否超出范围
                if(index_FirstItermInPage>=Iterm_TOTAL) 
                {
                  index_FirstItermInPage=0;
                }
                PageNum=index_FirstItermInPage / ItemNum_MAX;

				if(index_FirstItermInPage+ItermNum>=Iterm_TOTAL)
					ItermNum = Iterm_TOTAL - index_FirstItermInPage - 1;
                //重新显示
                LCD_CLEAR();
				GUI_showOnePage();
			}
                
                ActCommandState=Finished;
                break;
    case Select:
                LCD_PrintParaDataString(LCD_X_X,ItermNum,"*");
                ActProgramSate=Changing;
                ActCommandState=Finished;
                break;
    case Exit:
                break;  
    case SelectUp:
			if(CMDstate == ActProgramSate)
			{
                ItermNumCMD--;
                if(ItermNumCMD<0) 
                {
                  ItermNumCMD=ItemNum_MAX-1;
                }
				if(index_FirstItermCMDInPage+ItermNumCMD>=Iterm_CMD_TOTAL)
					ItermNumCMD = Iterm_CMD_TOTAL-index_FirstItermCMDInPage - 1;
                temp[0]=ItermNumCMD;
                LCD_PrintCMDNameString(0,temp[0],">");
				for(i=1;i<ItemNum_MAX;++i)
				{
					temp[i] = (ItermNumCMD+i)%ItemNum_MAX;
					LCD_PrintCMDNameString(0,temp[i]," ");
				}
			}
			else
			{
                ItermNum--;
                if(ItermNum<0) 
                {
                  ItermNum=ItemNum_MAX-1;
                }
				if(index_FirstItermInPage+ItermNum>=Iterm_TOTAL)
					ItermNum = Iterm_TOTAL-index_FirstItermInPage - 1;
                temp[0]=ItermNum;
                LCD_PrintParaNameString(0,temp[0],">");
				for(i=1;i<ItemNum_MAX;++i)
				{
					temp[i] = (ItermNum+i)%ItemNum_MAX;
					LCD_PrintParaNameString(0,temp[i]," ");
				}
			}
            ActCommandState=Finished;
            break;
    case SelectDown:
			if(CMDstate == ActProgramSate)
			{			
				ItermNumCMD++;
				if(ItermNumCMD>=ItemNum_MAX) 
				{
				  ItermNumCMD=0;
				}
				
				if(index_FirstItermCMDInPage+ItermNumCMD>=Iterm_CMD_TOTAL)
					ItermNumCMD = 0;
				temp[0]=ItermNumCMD;
				LCD_PrintCMDNameString(0,temp[0],">");
				for(i=1;i<ItemNum_MAX;++i)
				{
					temp[i] = (ItermNumCMD+i)%ItemNum_MAX;
					LCD_PrintCMDNameString(0,temp[i]," ");
				}
				ActCommandState=Finished;
			}
			else
			{
                ItermNum++;
                if(ItermNum>=ItemNum_MAX) 
                {
                  ItermNum=0;
                }
				
				if(index_FirstItermInPage+ItermNum>=Iterm_TOTAL)
					ItermNum = 0;
                temp[0]=ItermNum;
                LCD_PrintParaNameString(0,temp[0],">");
				for(i=1;i<ItemNum_MAX;++i)
				{
					temp[i] = (ItermNum+i)%ItemNum_MAX;
					LCD_PrintParaNameString(0,temp[i]," ");
				}
                ActCommandState=Finished;
			}
                break;
    case Minus:
				indexSelected = index_FirstItermInPage+ItermNum;
        if(ActChangeState==Continue)
        {  
					if(Para16s[indexSelected]-ParaMin[indexSelected]<ParaSteps[indexSelected]*10)
						Para16s[indexSelected] = ParaMin[indexSelected];
					else
						Para16s[indexSelected] -= ParaSteps[indexSelected]*10;
        }
        else
        {
					if(Para16s[indexSelected]-ParaMin[indexSelected]<ParaSteps[indexSelected] )
						Para16s[indexSelected] = ParaMin[indexSelected];
					else
          	Para16s[indexSelected] -= ParaSteps[indexSelected];
         }
         sprintf(string, "%6d",Para16s[indexSelected]);
         LCD_PrintParaDataString(LCD_X_DATA,ItermNum,string);
         break;
    case Add:
					indexSelected = index_FirstItermInPage+ItermNum;
          if(ActChangeState==Continue)
          {  
						if(ParaMax[indexSelected]-Para16s[indexSelected]<ParaSteps[indexSelected]*10)
							Para16s[indexSelected] = ParaMax[indexSelected];
						else
							Para16s[indexSelected] += ParaSteps[indexSelected]*10;
          }
          else
          {                
						if(ParaMax[indexSelected]-Para16s[indexSelected]<ParaSteps[indexSelected])
							Para16s[indexSelected] = ParaMax[indexSelected];
						else
            	Para16s[indexSelected] += ParaSteps[indexSelected];;
          }
					sprintf(string, "%6d",Para16s[indexSelected]);
          LCD_PrintParaDataString(LCD_X_DATA,ItermNum,string);
          break;             
    case  Save:
          LCD_PrintParaDataString(LCD_X_X,ItermNum," ");
					GUI_Save();
          ActProgramSate=Saved;
          ActCommandState=Finished;
          break;
    case  None:
          GUI_showOnePage();
					ActCommandState=Finished;
					break;
	case ModeUp:
				LCD_CLEAR();
				if(Changing == ActProgramSate || Saved == ActProgramSate)
				{	
					ActProgramSate = CMDstate;					
					PageNum = index_FirstItermCMDInPage / ItemNum_MAX;
					GUI_ShowCMDOnePage();
				}
				else if(CMDstate == ActProgramSate)
				{
					ActProgramSate = Saved;
					PageNum = index_FirstItermInPage / ItemNum_MAX;
					GUI_showOnePage();
				}
				ActCommandState = Finished;
				break;
	case ModeDown:
				LCD_CLEAR();
				if(Changing == ActProgramSate || Saved == ActProgramSate)
				{
					ActProgramSate = CMDstate;
					PageNum = index_FirstItermCMDInPage / ItemNum_MAX;
					GUI_ShowCMDOnePage();
				}
				else if(CMDstate == ActProgramSate)
				{
					ActProgramSate = Saved;
					PageNum = index_FirstItermInPage / ItemNum_MAX;
					GUI_showOnePage();
				}
				ActCommandState = Finished;
				break;
	case DoCmd:
				(*pPannelCmd[index_FirstItermCMDInPage+ItermNumCMD])();
				break;
    default:
				break;   
  }
  ActCommandState= Finished;
 }
 else if(ActCommandState == Finished)
 {               
		if(ActProgramSate==Changing)
    {
			GUI_ShowData();
      LCD_PrintParaDataString(LCD_X_X,ItermNum,"*");
    }
		else if(Saved == ActProgramSate)
    {
			GUI_ShowData();
      LCD_PrintParaDataString(LCD_X_X,ItermNum," ");
    }                
 }

 GUI_PublicStatus.index_FirstItermInPage = index_FirstItermInPage;
 GUI_PublicStatus.ItermNum = ItermNum;
 GUI_PublicStatus.ItermIndex = index_FirstItermInPage + ItermNum;
}   

void GUI_Sleep()
{
	ActCommandState = Sleep;
	LCD_CLEAR();
}

void GUI_None_Func()
{}

///<summary>
///以下为获取GUI状态的函数
///
u8 GUI_IsSleep()
{
	return ActCommandState ==Sleep;
}



