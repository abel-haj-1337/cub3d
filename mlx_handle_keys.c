/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:45:16 by abel-haj          #+#    #+#             */
/*   Updated: 2020/12/15 17:45:19 by abel-haj         ###   ########.fr       */
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
		if (player.x > 0)
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
		if (player.y > 0)
		{
			turn_move_player_by(0, -1, 0);
	printf("player angle : %.2f %.2f \n", player.view_angle, player.view_angle * M_PI / 180);
	printf("start x, y (%d,%d)\n", player.x, player.y);
	printf("end   x, y (%.2f, %.2f)\n", player.x+cos(player.view_angle * M_PI / 180) * 25, player.y+cos(player.view_angle * M_PI / 180) * 25);
		}
	}

	// bottom
	 if (key_code == 1 || key_code == 125)
	{
		turn_move_player_by(0, 1, 0);
	printf("player angle : %.2f %.2f \n", player.view_angle, player.view_angle * M_PI / 180);
	printf("start x, y (%d,%d)\n", player.x, player.y);
	printf("end   x, y (%.2f, %.2f)\n", player.x+cos(player.view_angle * M_PI / 180) * 25, player.y+cos(player.view_angle * M_PI / 180) * 25);
	}

	// turn left
	 if (key_code == 123)
	{
		turn_move_player_by(0, 0, 1);
	printf("player angle : %.2f %.2f \n", player.view_angle, player.view_angle * M_PI / 180);
	printf("start x, y (%d,%d)\n", player.x, player.y);
	printf("end   x, y (%.2f, %.2f)\n", player.x+cos(player.view_angle * M_PI / 180) * 25, player.y+cos(player.view_angle * M_PI / 180) * 25);
	}

	// turn right
	 if (key_code == 124)
	{
		turn_move_player_by(0, 0, -1);
	printf("player angle : %.2f %.2f \n", player.view_angle, player.view_angle * M_PI / 180);
	printf("start x, y (%d,%d)\n", player.x, player.y);
	printf("end   x, y (%.2f, %.2f)\n", player.x+cos(player.view_angle * M_PI / 180) * 25, player.y+cos(player.view_angle * M_PI / 180) * 25);
	}

	// printf("%d\n", key_code);

	return key_code;
}
