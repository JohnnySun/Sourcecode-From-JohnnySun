#ifndef __BASE__H__
#define __BASE__H__ 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "function.h"
#include "struct.h"

#define OPEN_FB(FB) FB = rgba_open_fb(); 

#define CLOSE_FB(FBFD) close(FBFD)

#define DRAW_PT_16(FBP, LOCATION, RGBA) rgba_fb_16(FBP, LOCATION, RGBA)

#define DRAW_PT_32(FBP, LOCATION, RGBA) rgba_fb_32(FBP, LOCATION, RGBA)

#define CHECK_FB(FB) if (!FB) \
		{ \
			printf("FB: cannot open framebuffer device.\n"); \
			exit(0); \
		}

#define IOCTL(FB, FUNCTION, STRUCT) 	if (ioctl(FB, FUNCTION, &STRUCT)) \
					{ \
						printf("ioctl: #FUNCTION error\n"); \
						exit(0); \
					}

#define GET_SCREEN_SIZE(SS, VAR) SS = VAR.xres * VAR.yres * VAR.bits_per_pixel / 8;

#define	CHECK_MMAP(FBP) if((int)FBP == -1) \
			{ \
				printf("mmap: failed to map framebuffer device to memory.\n"); \
				exit(0); \
			}

#define POINT_COLOR_SET(A, RED, GREEN, BLUE, ALPHY) \
	A.red = RED; \
	A.green = GREEN; \
	A.blue = BLUE; \
	A.alphy = ALPHY;




#endif

