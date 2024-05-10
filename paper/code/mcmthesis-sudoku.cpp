//============================================================================
// Name        : Sudoku.cpp
// Author      : wzlf11
// Version     : a.0
// Copyright   : Your copyright notice
// Description : Sudoku in C++.
//============================================================================

#include "graphics.h"
#define LEFT 0
#define TOP 0
#define RIGHT 639
#define BOTTOM 479
#define LINES 400
#define MAXCOLOR 15
main()
{
	int driver,mode,error;
	int x1,y1;
	int x2,y2;
	int dx1,dy1,dx2,dy2,i=1;
	int count=0;
	int color=0;
	driver=VGA;
	mode=VGAHI;
	initgraph(&driver,&mode,"");
	x1=x2=y1=y2=10;
	dx1=dy1=2;
	dx2=dy2=3;
	while(!kbhit())
	{
　		line(x1,y1,x2,y2);
　		x1+=dx1;y1+=dy1;
　		x2+=dx2;y2+dy2;
　		   if(x1<=LEFT||x1>=RIGHT)
　			dx1=-dx1;
　		   if(y1<=TOP||y1>=BOTTOM)
　　			dy1=-dy1;
　		   if(x2<=LEFT||x2>=RIGHT)
　　			dx2=-dx2;
　		   if(y2<=TOP||y2>=BOTTOM)
　　			dy2=-dy2;
　		   if(++count>LINES)
　		{
　　			setcolor(color);
　　			color=(color>=MAXCOLOR)?0:++color;
　		}
	}
	closegraph();
}

main()
{
	int i,j,k,x0,y0,x,y,driver,mode;
	float a;
	driver=CGA;mode=CGAC0;
	initgraph(&driver,&mode,"");
	setcolor(3);
	setbkcolor(GREEN);
	x0=150;y0=100;
	circle(x0,y0,10);
	circle(x0,y0,20);
	circle(x0,y0,50);
	for(i=0;i<16;i++)
	{
　		a=(2*PAI/16)*i;
　		x=ceil(x0+48*cos(a));
　		y=ceil(y0+48*sin(a)*B);
　		setcolor(2); line(x0,y0,x,y);
　	}
	setcolor(3);circle(x0,y0,60);
	/* Make 0 time normal size letters */
	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
	outtextxy(10,170,"press a key");
	getch();
	setfillstyle(HATCH_FILL,YELLOW);
	floodfill(202,100,WHITE);
	getch();
	for(k=0;k<=500;k++)
	{
　		setcolor(3);
　		for(i=0;i<=16;i++)
　		{
　　			a=(2*PAI/16)*i+(2*PAI/180)*k;
　　			x=ceil(x0+48*cos(a));
　　			y=ceil(y0+48+sin(a)*B);
　　			setcolor(2); line(x0,y0,x,y);
　		}
　		for(j=1;j<=50;j++)
　		{
　　			a=(2*PAI/16)*i+(2*PAI/180)*k-1;
　　			x=ceil(x0+48*cos(a));
　　			y=ceil(y0+48*sin(a)*B);
　　			line(x0,y0,x,y);
　		}
	}
	restorecrtmode();