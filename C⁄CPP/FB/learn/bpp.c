if (vinfo.bits_per_pixel == 32)
			{
				*(fbp + location) = 100; // Some blue 
				*(fbp + location + 1) = 15+(x-100)/2;// A little green
				*(fbp + location + 2) = 200-(y-100)/5;// A lot of red
				*(fbp + location + 3) = 0;// No transparency
			}
			else
			{ 
				int b = 10;//assume 16bpp
				int g = (x-100)/6;// A little green
				int r = 31-(y-100)/16;// A lot of red
				unsigned short int t = r<<11 | g << 5 | b;
				*((unsigned short int*)(fbp + location)) = t;
			}
