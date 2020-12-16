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
#include <float.h>

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

void		draw_square(int posX, int posY, int width, int color)
{
	int		i;
	int		j;

	j = 0;
	while (j < width)
	{
		i = 0;
		while (i < width)
		{
			mlx_pixel_put(mlx.mlx, mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
	a++;
}

void		draw_square_image(int posX, int posY, int width, int color)
{
	int		i;
	int		j;
	t_image image;

	j = 0;
	image.img = mlx_new_image(mlx.mlx, posX, posY);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_height, &image.endian);
	while (j < width)
	{
		i = 0;
		while (i < width)
		{
			my_mlx_pixel_put(posX + j, posY + i, color, image);

			// mlx_pixel_put(mlx.mlx, mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, image.img, posX, posY);
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

void		draw_line(int x, int y, int to_x, int to_y)
{
	int		i;
	int		j;

	i = x;
	j = y;
	while (i <= to_x)
	{
		mlx_pixel_put(mlx.mlx, mlx.win, i, j, WHITE);
		i++;
	}
	i = x;
	while (j <= to_y)
	{
		mlx_pixel_put(mlx.mlx, mlx.win, i, j, WHITE);
		j++;
	}
	b++;
	// printf("line drawn from (%d,%d) to (%d,%d)\n", x, y, to_y, to_x);
}

int is_wall_at(float x, float y) {
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / MAP_TILE_SIZE);
    int mapGridIndexY = floor(y / MAP_TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float		fix_rad(float rad)
{
	rad = remainder(rad, M_PI * 2);
	if (rad < 0)
		rad = (M_PI * 2) + rad;
	return (rad);
}

void		draw_ray(float ray_rad, int ray_index)
{
	t_ray	ray;

	int		y = 0;
	int		x = 0;
	int		is_looking_up = 0;
	int		is_looking_right = 0;

	float	intersection_x = 0;
	float	intersection_y = 0;

	float	step_x = 0;
	float	step_y = 0;

	int		horizontal_wall = 0;
	int		horizontal_wall_content = 0;
	float	horizontal_wall_x = 0;
	float	horizontal_wall_y = 0;

	ray_rad = fix_rad(ray_rad);

	is_looking_up = (ray_rad > 0 && ray_rad < M_PI);
	is_looking_right = (ray_rad < 0.5 * M_PI || ray_rad > 1.5 * M_PI);

	// HORIZONTAL
	intersection_y = floor(player.y / MAP_TILE_SIZE) * MAP_TILE_SIZE;
	intersection_y += !is_looking_up ? MAP_TILE_SIZE : 0;

	intersection_x = player.x + (intersection_y - player.y) / tan(ray_rad);

	step_y = MAP_TILE_SIZE;
	step_y *= is_looking_up ? -1 : 1;

	step_x = MAP_TILE_SIZE / tan(ray_rad);
	step_x *= (!is_looking_right && step_x > 0) ? -1 : 1;
	step_x *= (is_looking_right && step_x < 0) ? -1 : 1;

    float nextHorzTouchX = intersection_x;
    float nextHorzTouchY = intersection_y;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH 
	&& nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
	{
		y = nextHorzTouchY + (is_looking_up ? -1 : 0);
		if (is_wall_at(intersection_x, y))
		{
			horizontal_wall = 1;
			horizontal_wall_content = map[(int)floor(y / MAP_TILE_SIZE)][(int)floor(intersection_x / MAP_TILE_SIZE)];
			horizontal_wall_x = nextHorzTouchX;
			horizontal_wall_y = nextHorzTouchY;
			break;
		}
		else
		{
			nextHorzTouchX += step_x;
			nextHorzTouchY += step_y;
		}
	}

	// VERTICAL
	int		vertical_wall = 0;
	int		vertical_wall_content = 0;
	float	vertical_wall_x = 0;
	float	vertical_wall_y = 0;

	intersection_x = floor(player.x / MAP_TILE_SIZE) * MAP_TILE_SIZE;
	intersection_x += is_looking_right ? MAP_TILE_SIZE : 0;

	intersection_y = player.y + (intersection_x - player.x) / tan(ray_rad);

	step_x = MAP_TILE_SIZE;
	step_x *= !is_looking_right ? -1 : 1;

	step_y = MAP_TILE_SIZE / tan(ray_rad);
	step_y *= (is_looking_up && step_y > 0) ? -1 : 1;
	step_y *= (!is_looking_up && step_y < 0) ? -1 : 1;

    float nextVertTouchX = intersection_x;
    float nextVertTouchY = intersection_y;

	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH 
	&& nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT)
	{
		x = nextVertTouchX + (!is_looking_right ? -1 : 0);
		if (is_wall_at(x, nextVertTouchY))
		{
			vertical_wall = 1;
			vertical_wall_content = map[(int)floor(nextVertTouchY / MAP_TILE_SIZE)][(int)floor(x / MAP_TILE_SIZE)];
			vertical_wall_x = nextVertTouchX;
			vertical_wall_y = nextVertTouchY;
			break;
		}
		else
		{
			nextVertTouchX += step_x;
			nextVertTouchY += step_y;
		}
	}
// printf("(%f,%f) to (%f,%f)\n", intersection_x, intersection_y, nextVertTouchX, nextVertTouchY);

	float horz_hit_distance = horizontal_wall
        ? distanceBetweenPoints(player.x, player.y, horizontal_wall_x, horizontal_wall_y)
        : FLT_MAX;
    float vert_hit_distance = vertical_wall
        ? distanceBetweenPoints(player.x, player.y, vertical_wall_x, vertical_wall_y)
        : FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		ray.distance = vert_hit_distance;
		ray.wall_hit_x = vertical_wall_x;
		ray.wall_hit_y = vertical_wall_y;
		ray.wall_hit_content = vertical_wall;
		ray.was_hit_vertical = 1;
	}
	else
	{
		ray.distance = horz_hit_distance;
		ray.wall_hit_x = horizontal_wall_x;
		ray.wall_hit_y = horizontal_wall_y;
		ray.wall_hit_content = horizontal_wall;
		ray.was_hit_vertical = 0;
	}
	ray.ray_agle = ray_rad;
	ray.is_ray_facing_up = is_looking_up;
	ray.is_ray_facing_right = is_looking_right;
	draw_line(player.x, player.y, ray.wall_hit_x, ray.wall_hit_y);
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
	printf("%.0f\n", ray_rad);
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
	draw_player_at_start(BLUE);

	// draw player rays
	draw_rays();

	// keep game running
	mlx_loop(mlx.mlx);

	return 0;
}
