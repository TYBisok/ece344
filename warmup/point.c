#include <assert.h>
#include <math.h>
#include "common.h"
#include "point.h"

void
point_translate(struct point *p, double x, double y)
{
	point_set(p,point_X(p) + x,point_Y(p) + y);
}

double
point_distance(const struct point *p1, const struct point *p2)
{
	return sqrt((point_X(p1) - point_X(p2)) * (point_X(p1) - point_X(p2)) 
	+ (point_Y(p1) - point_Y(p2)) * (point_Y(p1) - point_Y(p2)));
}

int
point_compare(const struct point *p1, const struct point *p2)
{
	struct point zero = {.x = 0, .y = 0};
	struct point *point_zero = &zero;
	double dist_1 = point_distance(p1,point_zero);
	double dist_2 = point_distance(p2,point_zero);
	if (dist_1 > dist_2) return 1;
	else if (dist_1 == dist_2) return 0;
	else return -1;
}
