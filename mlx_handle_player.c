/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:13:26 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/12 15:03:50 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_player_at(int x, int y)
{
	g_player.x = x;
	g_player.y = y;
	// odd number
	g_player.size = 7;
	g_player.turn_speed = 50;
	g_player.view_length = 75;
	g_player.color = BLUE;

	// 0 to 360
	g_player.view_angle = 90;
	turn_move_player_by(0, 0, 0);
	printf("%d\n", g_player.x);
	printf("%d\n", g_player.x + (int)ceil(g_player.size / 2));
}

void		turn_move_player_by(int x, int y, int step)
{
	draw_square(g_player.x - ceil(g_player.size / 2), g_player.y - ceil(g_player.size / 2), g_player.size, BLACK);
	draw_line(
		g_player.x,
		g_player.y,
		g_player.x + (cos(g_player.view_angle * M_PI / 180) * g_player.view_length),
		g_player.y + (sin(g_player.view_angle * M_PI / 180) * g_player.view_length),
		BLACK);

	g_player.x += x;
	g_player.y += y;
	g_player.view_angle += step;

	if (g_player.view_angle <= 0)
		g_player.view_angle = 360;
	else if (g_player.view_angle > 360)
		g_player.view_angle = 1;

	draw_square(g_player.x - ceil(g_player.size / 2), g_player.y - ceil(g_player.size / 2), g_player.size, BLUE);
	draw_line(
		g_player.x,
		g_player.y,
		g_player.x + (cos(g_player.view_angle * M_PI / 180) * g_player.view_length),
		g_player.y + (sin(g_player.view_angle * M_PI / 180) * g_player.view_length),
		YELLOW);
}
