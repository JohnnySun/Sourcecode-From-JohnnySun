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
#include "include/framebuffer/struct.h"
#include "include/framebuffer/function.h"
#include "include/framebuffer/framebuffer.h"
#include <sys/stat.h>
#include <sys/types.h>


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

int rgba_open_fb()
{
	return open("/dev/fb0", O_RDWR);
}

void rgba_fb_16(char * mmap, long int location, struct point_color * pc)
{
	unsigned short int t = pc->red<<11 | pc->green << 5 | pc->blue;
	*((unsigned short int*)(fbp + location)) = t;
}

void rgba_fb_32(char * mmap, long int location, struct point_color * pc)
{
	*(mmap + location + 0) = pc->blue;
	*(mmap + location + 1) = pc->green;
	*(mmap + location + 2) = pc->red;
	*(mmap + location + 3) = pc->alphy;
}
void openfb()
{

	OPEN_FB(fbfd);

	IOCTL(fbfd, FBIOGET_FSCREENINFO, finfo);
	IOCTL(fbfd, FBIOGET_VSCREENINFO, vinfo);
	GET_SCREEN_SIZE(screensize, vinfo);
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
		printf("bpp:%d\n", vinfo.bits_per_pixel);

}

void closefb()
{

	munmap(fbp, screensize);
	CLOSE_FB(fbfd);
}

void drawline(struct draw_widget draw)
{


	POINT_COLOR_SET(rgba_color, draw.color.red, draw.color.green, draw.color.blue, draw.color.alphy);

	/*
	   if(draw.sy - draw.ey == 0)
	   {
	   for(x = draw.sx; x < draw.ex; x++)
	   {
	   location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (draw.sy+vinfo.yoffset) * finfo.line_length; 
	   DRAW_PT(fbp, location, &rgba_color);
	   }

	   } 
	   else if(draw.sx - draw.ex == 0)
	   {
	   for(y = draw.sy; y < draw.ey; y++)
	   {
	   location = (y+vinfo.yoffset) * (vinfo.bits_per_pixel/8) + (draw.sx+vinfo.xoffset) * finfo.line_length; 

	   DRAW_PT(fbp, location, &rgba_color);
	//		DRAW_PT(fbp, (location + x * finfo.line_length - x * (vinfo.bits_per_pixel/8)), &rgba_color);
	}

	}
	else{
	 */
	int i,deltax,deltay,numpixels,d,dinc1,dinc2,xinc1,xinc2,yinc1,yinc2;
	//calculate delta-x ,delta-y for initialization
	if(draw.ex-draw.sx<0)
	{
		deltax=draw.sx-draw.ex;
	}
	else
	{
		deltax=draw.ex-draw.sx;
	}
	if(draw.ey-draw.sy<0)
	{
		deltay=draw.sy-draw.ey;
	}
	else
	{
		deltay=draw.ey-draw.sy;
	}
	//initialize all vars based on which is the independent variable
	if(deltax>=deltay)
	{
		//x is independent variable
		numpixels=deltax+1;
		d=(2*deltay)-deltax;
		dinc1=deltay<<1;
		dinc2=(deltay-deltax)<<1;
		xinc1=1;
		xinc2=1;
		yinc1=0;
		yinc2=1;
	}
	else
	{
		//y is independent variable
		numpixels=deltay+1;
		d=(2*deltax)-deltay;
		dinc1=deltax<<1;
		dinc2=(deltax-deltay)<<1;
		xinc1=0;
		xinc2=1;
		yinc1=1;
		yinc2=1;
	}
	//make sure x and y mobe in the right directions
	if(draw.sx>draw.ex)
	{
		xinc1=-xinc1;
		xinc2=-xinc2;
	}
	if(draw.sy>draw.ey)
	{
		yinc1=-yinc1;
		yinc2=-yinc2;
	}

	//start drawing at <x1,y1>
	x=draw.sx;
	y=draw.sy;

	//draw the pixels

	for(i=1;i<numpixels;i++)
	{
		//draw pixel
		//draw_pixel(x,y,nColor);

		location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length; 

		if(vinfo.bits_per_pixel == 32){
			DRAW_PT_32(fbp, location, &rgba_color);
		}else{
			DRAW_PT_16(fbp, location, &rgba_color);}


		if(d<0)
		{
			d=d+dinc1;
			x=x+xinc1;
			y=y+yinc1;
		}
		else
		{
			d=d+dinc2;
			x=x+xinc2;
			y=y+yinc2;
		}

	}
	//}

	//	close_keyboard(&init_term);
}

