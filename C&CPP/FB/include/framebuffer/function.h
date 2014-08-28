#ifndef __FB__FUNCTION__H__
#define __FB__FUNCTION__H__
#include "struct.h"

int rgba_open_fb();
void rgba_fb(char *, long int, struct point_color *);
void drawline(struct draw_widget);
void openfb();
void closefb();

#endif
