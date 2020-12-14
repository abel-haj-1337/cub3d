/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:26:06 by abel-haj          #+#    #+#             */
/*   Updated: 2020/12/09 11:57:34 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int			window_width	= 500;
int			window_height	= 500;
t_mlx		mlx;
t_player	player;
t_image		image;

int		destroy_mlx(void)
{
	mlx_clear_window(mlx.mlx, mlx.win);
	mlx_destroy_window(mlx.mlx, mlx.win);
	exit(0);
	return 0;
}

void            my_mlx_pixel_put(int x, int y, int color)
{
    char    *dst;

    dst = image.addr + (y * image.line_height + x * (image.bpp / 8));
    *(unsigned int*)dst = color;
}

void		put_square(int posX, int posY, int color)
{
	int		i;
	int		j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			mlx_pixel_put(mlx.mlx, mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
	printf("|x=%d| |y=%d|\n", player.x, player.y);
}

void		put_square_image(int posX, int posY, int color)
{
	int		i;
	int		j;

	j = 0;
	image.img = mlx_new_image(mlx.mlx, posX, posY);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_height, &image.endian);
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			my_mlx_pixel_put(posX + j, posY + i, color);

			// mlx_pixel_put(mlx.mlx, mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, image.img, posX, posY);
}

void		draw_player_at_start(int color)
{
	put_square(0, 0, color);
}

void		move_player(int x, int y, int color)
{
	// erase player
	put_square(player.x, player.y, BLACK);

	// draw new player
	player.x += x;
	player.y += y;
	put_square(player.x, player.y, color);
}

int			handle_key(int key_code)
{
	printf("%d (line 94)\n", key_code);
	//printf("%d\n", mlx_get_screen_size(mlx.mlx));

	// quit
	if (key_code == 12 || key_code == 53)
	{
		destroy_mlx();
		// mlx_clear_window(mlx.mlx, mlx.win);
		// mlx_destroy_window(mlx.mlx, mlx.win);
		// exit(0);
	}
	// left
	else if (key_code == 0)
	{
		// move player to the left
		if (player.x > 0)
		{
			move_player(-1, 0, BLUE);
			// player.y -= 1;
		}
	}
	// right
	else if (key_code == 2)
	{
		move_player(1, 0, BLUE);
		// player.x += 1;
	}
	// top
	else if (key_code == 13 || key_code == 126)
	{
		if (player.y > 0)
		{
			move_player(0, -1, BLUE);
			// player.y -= 1;
		}
	}
	// bottom
	else if (key_code == 1 || key_code == 125)
	{
		move_player(0, 1, BLUE);
		// player.y += 1;
	}

	return key_code;
}

int			main(void)
{
	int			i = 0;

	// initialize window
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, window_width, window_height, "new window");

	// initialize player
	player.x = 0;
	player.y = 0;

	//put_square(mlx, 0, rgb_to_hex(0, 0, 255));
	//put_square(mlx, 10, rgb_to_hex(0, 0, 255));

	// handle events
	mlx_hook(mlx.win, 2, 0, handle_key, (void *)0);
	mlx_hook(mlx.win, 17, 0, destroy_mlx, (void *)0);

	// draw map
	
	// draw player
	draw_player_at_start(BLUE);

	// keep game running
	mlx_loop(mlx.mlx);

	return 0;
}
