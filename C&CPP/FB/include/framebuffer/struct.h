#ifndef __FB__STRUCT__H__
#define __FB__STRUCT__H__ 4

struct point_color {
	int red;
	int green;
	int blue;
	int alphy;
};

struct draw_widget {
	int sx;
	int sy;
	int ex;
	int ey;
	struct point_color color;
};

#endif
