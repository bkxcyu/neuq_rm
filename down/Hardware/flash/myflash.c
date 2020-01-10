#include "myflash.h"
#include "stmflash.h"

float xp,xi,xd,yp,yi,yd,rp,ri,rd;
int a[9];



#define FLASH_SAVE_ADDR  0X0800C004 	//设置FLASH 保存地址(必须为偶数，且所在扇区,要大于本代码所占用到的扇区.
										//否则,写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.


// 函数: Write_PID_Address()
// 描述: 将pid参数写入flash
// 参数：无
// 输出：无
void Write_PID_Address(void)    
{
	int off=0;
	a[0]=xp*100;
	a[1]=xi*100;
	a[2]=xd*100;
	a[3]=yp*100;
	a[4]=yi*100;
	a[5]=yd*100;
	a[6]=rp*100;
	a[7]=ri*100;
	a[8]=rd*100;
  STMFLASH_Write(FLASH_SAVE_ADDR+off,(u32*)a,sizeof(a[0])/4*9);
}


// 函数: Read_PID_Address()
// 描述: 将pid参数从flash中读出
// 参数：无
// 输出：无
void Read_PID_Address()
{
	STMFLASH_Read(FLASH_SAVE_ADDR,(u32*)a,sizeof(a[0])/4*9);
	xp=a[0]/100.0;
	xi=a[1]/100.0;
	xd=a[2]/100.0;
	
	yp=a[3]/100.0;
	yi=a[4]/100.0;
	yd=a[5]/100.0;
	
	rp=a[6]/100.0;
	ri=a[7]/100.0;
	rd=a[8]/100.0;
	
}




