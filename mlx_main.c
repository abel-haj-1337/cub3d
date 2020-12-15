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
	printf("|x=%d| |y=%d|\n", player.x, player.y);
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

int			main(void)
{
	int			i = 0;

	// initialize window
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "new window");

	// initialize player
	player.x = 0;
	player.y = 0;

	// handle events
	mlx_hook(mlx.win, 2, 0, handle_keys, (void *)0);
	mlx_hook(mlx.win, 17, 0, destroy_mlx, (void *)0);

	// draw map
	draw_map(RED);

	// draw player
	draw_player_at_start(BLUE);

	// keep game running
	mlx_loop(mlx.mlx);

	return 0;
}
