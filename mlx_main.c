/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:18:06 by abel-haj          #+#    #+#             */
/*   Updated: 2020/12/15 18:18:11 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int a = 0;
int b = 0;

int		destroy_mlx(void)
{
	mlx_clear_window(mlx.mlx, mlx.win);
	mlx_destroy_window(mlx.mlx, mlx.win);
	exit(0);
	return (0);
}

void            my_mlx_pixel_put(int x, int y, int color, t_image image)
{
    char    *dst;

    dst = image.addr + (y * image.line_height + x * (image.bpp / 8));
    *(unsigned int*)dst = color;
}

void		draw_map(int wall_color)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_HEIGHT)
		{
			if (map[i][j] == 1)
			{
				draw_square(i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, wall_color);
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
        mlx_pixel_put(mlx.mlx, mlx.win, x, y, color);
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

int			is_wall_at(float x, float y) {
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / MAP_TILE_SIZE);
    int mapGridIndexY = floor(y / MAP_TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

float		distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float		fix_rad(float rad)
{
	rad = remainder(rad, M_PI * 2);
	if (rad < 0)
		rad = (M_PI * 2) + rad;
	return (rad);
}

void		draw_ray(float ray_rad, int index)
{
	return;
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

int			main(void)
{
	int		i = 0;

	// initialize window
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "new window");

	// initialize player
	player.x = MAP_TILE_SIZE;
	player.y = MAP_TILE_SIZE;

	// handle events
	mlx_hook(mlx.win, 2, 0, handle_keys, (void *)0);
	mlx_hook(mlx.win, 17, 0, destroy_mlx, (void *)0);

	// draw map
	draw_map(RED);

	// draw player
	init_player_at((MAP_WIDTH * MAP_TILE_SIZE) / 2, (MAP_HEIGHT * MAP_TILE_SIZE) / 2);

	// draw player rays
	// draw_rays();

	// // for(int j = 200; j < 351; j++)
	// for(int j = 0; j < 201; j++)
	// {
	// 	// // draw_line(0, 0, j, j, WHITE);
	// 	// draw_line(0, 0, j, 200 + j, WHITE);
	// 	// draw_line(0, 0, 200 + j, j, WHITE);
	// 	if (j < 25)
	// 		draw_line(200, 200, 300 + j, 300 + j, WHITE);
	// 		// printf("%d, %d\n", 300 + j, 300 + j);
	// 	else
	// 		draw_line(200, 200, 300 + 200 - j, 300 + j, WHITE);
	// 		// printf("%d, %d\n", 300 + 50 - j, 300 + j);
	// }
	// draw_line(0, 100, 0, 125, WHITE);

	// keep game running
	mlx_loop(mlx.mlx);

	return 0;
}
