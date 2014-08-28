#include<stdio.h>
#include<stdlib.h>

#include "include/framebuffer/framebuffer.h"
#include "include/framebuffer/function.h"
#include "include/keyboard/function.h"

main()
{
	struct draw_widget hline;
	hline.sx = 30;
	hline.sy = 10;
	hline.ex = 300;
	hline.ey = 200;
	hline.color.red = 45;
	hline.color.green = 125;
	hline.color.blue = 200;
	hline.color.alphy = 100;
	//	drawline(hline);
	//	printf("Enter R,G,B Code (0-255):");
	//	scanf("$d,%d,%d",&hline.color.red,&hline.color.green,&hline.color.blue);
	openfb();
	for (hline.sy == 0;hline.ey < 239;hline.sy++)
	{
		hline.ey++ ;
//				hline.color.green--;
		drawline(hline);
	}
	/*
	   int i = 0;
	   while(hline.color.alphy == 0)
	   {
	   if(i==0){
	   hline.ey++;
	   }else if(i==1){
	   hline.ey--;
	   }
	   hline.ex++;
	   hline.color.red--;
	   hline.color.green=hline.color.green-hline.color.blue;
	   hline.color.blue=hline.color.blue-hline.color.red+hline.color.green;
	   if (hline.color.red==0){
	   hline.color.red=255;
	   }else if (hline.color.green<2){
	   hline.color.green=255;
	   }else if (hline.color.blue<3){
	   hline.color.blue=255;
	   }
	   drawline(hline);
	   if(hline.ey == 239)
	   {
	   i=1;
	   }else if(hline.ey == 120){
	   i=0;
	   }
	   if(hline.ex == 239){
	   hline.ex=0;
	   }
	   }
	 */
	closefb();

}


/*
#include <time.h>
#include <term.h>
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <termios.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "include/framebuffer/framebuffer.h"
#include "include/framebuffer/function.h"
#include "include/keyboard/function.h"
int main()
{
int x = 0;
int y = 0;
int fd = 0;
int fbfd = 0;
long int location = 0;
long int screensize = 0;
struct point_color rgba_color = {0,};
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
struct termios new_term = {0,};
struct termios init_term = {0,};
struct termios * nterm = NULL;
char *fbp = 0;

POINT_COLOR_SET(rgba_color, 0, 255, 0, 0);

//	nterm = init_keyboard(&init_term, &new_term);

OPEN_FB(fbfd);

IOCTL(fbfd, FBIOGET_FSCREENINFO, finfo);

IOCTL(fbfd, FBIOGET_VSCREENINFO, vinfo); 

GET_SCREEN_SIZE(screensize, vinfo);

fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

for(x = 50; x < 1000; x++)
{
location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length; 
DRAW_PT(fbp, location, &rgba_color);
}

for(x = 50; x < 200; x++)
{
location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length; 
DRAW_PT(fbp, (location + x * finfo.line_length - x * (vinfo.bits_per_pixel/8)), &rgba_color);
}

munmap(fbp, screensize);
CLOSE_FB(fbfd);
//	switch_key(nterm);
//	close_keyboard(&init_term);
return 0;
}
 */
