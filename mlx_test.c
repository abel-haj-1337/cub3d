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

#include	<stdio.h>
#include	"cub3d.h"

#define		BLACK	rgb_to_hex(0, 0, 0)
#define		RED		rgb_to_hex(255, 0, 0)
#define		BLUE	rgb_to_hex(0, 0, 255)
#define		GREEN	rgb_to_hex(0, 255, 0)
#define		WHITE	rgb_to_hex(255, 255, 255)

t_player	player;
t_mlx		mlx;

int		destroy_mlx(void *a)
{
	// mlx_clear_window(mlx.mlx, mlx.win);
	// mlx_destroy_window(mlx.mlx, mlx.win);
	// exit(0);
	return 0;
}

int			rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
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
	printf("%d\n", key_code);
	//printf("%d\n", mlx_get_screen_size(mlx.mlx));

	// quit
	if (key_code == 12 || key_code == 53)
	{
		// destroy_mlx();
		mlx_clear_window(mlx.mlx, mlx.win);
		mlx_destroy_window(mlx.mlx, mlx.win);
		exit(0);
	}
	// left
	else if (key_code == 0)
	{
		// move player to the left
		move_player(-1, 0, BLUE);
	}
	// right
	else if (key_code == 2)
	{
		move_player(1, 0, BLUE);
	}
	// top
	else if (key_code == 13)
	{
		move_player(0, -1, BLUE);
	}
	// bottom
	else if (key_code == 1)
	{
		move_player(0, 1, BLUE);
	}

	return key_code;
}

int			main(void)
{
	int			i = 0;

	// initialize window
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 250, 250, "new window");
	// initialize player
	player.x = 0;
	player.y = 0;

	// draw something
	draw_player_at_start(BLUE);

	//put_square(mlx, 0, rgb_to_hex(0, 0, 255));
	//put_square(mlx, 10, rgb_to_hex(0, 0, 255));

	// handle events
	mlx_key_hook(mlx.win, handle_key, (void *)0);
	// EXCEPTION
	mlx_hook(mlx.mlx, 17, 0, destroy_mlx, (void *)0);

	// keep game running
	mlx_loop(mlx.mlx);

	return 0;
}
