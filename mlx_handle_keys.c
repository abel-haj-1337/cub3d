/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:45:16 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/12 14:49:39 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			handle_keys(int key_code)
{
	// printf("%d (line 94)\n", key_code);

	// quit
	if (key_code == 12 || key_code == 53)
	{
		destroy_mlx();
	}

	// left
	 if (key_code == 0)
	{
		// move player to the left
		if (g_player.x > 0)
		{
			turn_move_player_by(-1, 0, 0);
		}
	}

	// right
	 if (key_code == 2)
	{
		turn_move_player_by(1, 0, 0);
	}

	// top
	 if (key_code == 13 || key_code == 126)
	{
		if (g_player.y > 0)
		{
			turn_move_player_by(0, -1, 0);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
		}
	}

	// bottom
	 if (key_code == 1 || key_code == 125)
	{
		turn_move_player_by(0, 1, 0);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	}

	// turn left
	 if (key_code == 123)
	{
		turn_move_player_by(0, 0, 5);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	}

	// turn right
	 if (key_code == 124)
	{
		turn_move_player_by(0, 0, -5);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	}
	printf("%d\n", key_code);

	return key_code;
}
