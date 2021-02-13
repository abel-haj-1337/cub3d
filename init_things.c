#include "cub3d.h"

void			init_conf()
{
	conf.w_x = -1;
	conf.w_y = -1;
	conf.east = NULL;
	conf.north = NULL;
	conf.south = NULL;
	conf.west = NULL;
	conf.ceiling = -1;
	conf.floor = -1;
	conf.p_x = -1;
	conf.p_y = -1;
	conf.p_dir = -1;
}

void			init_others()
{
	rows = 0;
	map = NULL;
}