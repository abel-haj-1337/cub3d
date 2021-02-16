/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:18:06 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/12 15:05:04 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int a = 0;
int b = 0;

int			is_wall_at(float x, float y) {
	if (x <= 0 || x >= WINDOW_WIDTH || y <= 0 || y >= WINDOW_HEIGHT) {
		return 1;
	}
	int map_x = floor(x / MAP_TILE_SIZE);
	int map_y = floor(y / MAP_TILE_SIZE);
	return g_map[map_y][map_x] != 0;
}

float		delta(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float		fix_rad(float rad)
{
	rad = remainder(rad, M_PI * 2);
	if (rad < 0)
		rad = (M_PI * 2) + rad;
	return (rad);
}

float		to_rad(float degree)
{
	return (degree * (M_PI / 180));
}

void		draw_ray(float ray_rad, int index)
{
	return;
}

void		draw_map(int wall_color)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (i < g_rows)
	{
		j = 0;
		len = ft_strlen(g_map[i]);
		while (j < len)
		{
			if (g_map[i][j] == '1')
			{
				draw_square(j * MAP_TILE_SIZE, i * MAP_TILE_SIZE, MAP_TILE_SIZE, wall_color);
			}
			j++;
		}
		i++;
	}
}

void		draw_line_2(int from_x, int from_y, int to_x, int to_y, int color)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		D;

	// Calculate "deltas" of the line (difference between two ending points)
	dx = to_x - from_x;
	dy = to_y - from_y;

	// Calculate the line equation based on deltas
	D = (2 * dy) - dx;
	y = from_y;

	// Draw the line based on arguments provided
	for (x = from_x; x < to_x; x++)
	{
		// Place pixel on the raster display
		mlx_pixel_put(g_mlx.mlx, g_mlx.win, x, y, color);
printf("(%d, %d)\n", x, y);
		if (D >= 0)
		{
			y = y + 1;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
	}

	// b++;
// printf("line drawn from (%d,%d) to (%d,%d)\n", x, y, to_x, to_y);
}

void		draw_rays()
{
	int i;
	float ray_rad;
	
	i		= 0;
	ray_rad	= (M_PI / 2) - (FOV / 2);
	while (i < RAYS)
	{
		draw_ray(ray_rad, i);
		ray_rad += FOV / RAYS;
		i++;
	// printf("%.0f\n", ray_rad);
	}
}

void		handle_mlx()
{
	int		x;
	int		y;

	// initialize window
	g_mlx.mlx = mlx_init();

	mlx_get_screen_size(g_mlx.mlx, &x, &y);
	if (g_conf.w_x > x || 0 > g_conf.w_x)
		g_conf.w_x = x;
	if (g_conf.w_y > y || 0 > g_conf.w_y)
		g_conf.w_y = y;
printf("%9d\n%9d\n%9d\n%9d\n", g_conf.w_x, g_conf.w_y, g_conf.p_x, g_conf.p_y);
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_conf.w_x, g_conf.w_y, "1337 Wolfenstein");

	// initialize player
	g_player.x = g_conf.p_x;
	g_player.y = g_conf.p_y;

	// handle events
	mlx_hook(g_mlx.win, 2, 0, handle_keys, (void *)0);
	mlx_hook(g_mlx.win, 17, 0, destroy_mlx, (void *)0);

	// draw map
	draw_map(RED);

	// draw player
	init_player_at(g_player.x * MAP_TILE_SIZE, g_player.y * MAP_TILE_SIZE);

	// keep game running
	mlx_loop(g_mlx.mlx);
}
