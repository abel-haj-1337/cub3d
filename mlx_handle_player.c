/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:13:26 by abel-haj          #+#    #+#             */
/*   Updated: 2020/12/15 18:13:28 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_player_at(int x, int y)
{
	player.x = x;
	player.y = y;
	// odd number
	player.size = 7;
	player.color = BLUE;

	// 0 to 360
	player.view_angle = 90;
	turn_move_player_by(0, 0, 0);
	printf("%d\n", player.x);
	printf("%d\n", player.x + (int)ceil(player.size / 2));
}

void		turn_move_player_by(int x, int y, int step)
{
	draw_square(player.x - ceil(player.size / 2), player.y - ceil(player.size / 2), player.size, BLACK);
	draw_line(
		player.x,
		player.y,
		player.x + cos(player.view_angle * M_PI / 180) * 25,
		player.y + sin(player.view_angle * M_PI / 180) * 25,
		BLACK);

	player.x += x;
	player.y += y;
	player.view_angle += step;

	if (player.view_angle <= 0)
		player.view_angle = 360;
	else if (player.view_angle > 360)
		player.view_angle = 1;

	draw_square(player.x - ceil(player.size / 2), player.y - ceil(player.size / 2), player.size, BLUE);
	draw_line(
		player.x,
		player.y,
		player.x + cos(player.view_angle * M_PI / 180) * 25,
		player.y + sin(player.view_angle * M_PI / 180) * 25,
		YELLOW);
}
