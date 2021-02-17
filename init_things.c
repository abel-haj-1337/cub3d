#include "cub3d.h"

void			init_mlx()
{
	g_mlx.mlx = NULL;
	g_mlx.win = NULL;
}

void			init_conf()
{
	g_conf.w_w = -1;
	g_conf.w_h = -1;
	g_conf.east = NULL;
	g_conf.north = NULL;
	g_conf.south = NULL;
	g_conf.west = NULL;
	g_conf.ceiling = -1;
	g_conf.floor = -1;
	g_conf.p_x = -1;
	g_conf.p_y = -1;
	g_conf.p_dir = -1;
}

/*
** player
*/
void			init_player()
{
	g_player.x = -1;
	g_player.y = -1;
	g_player.color = -1;
	g_player.size = -1;
	g_player.view_length = -1;
	g_player.view_angle = 0;
	g_player.turn_speed = 5.0;
	g_player.walk_speed = 1.0;
}

void			init_others()
{
	g_rows = 0;
	g_map = NULL;
}

void			init_image()
{
	g_img.img = NULL;
	g_img.addr = NULL;
	g_img.bpp = -1;
	g_img.line_height = -1;
	g_img.endian = -1;
}
