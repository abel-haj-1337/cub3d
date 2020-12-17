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
	player.view_angle = M_PI / 2
}

void		move_player_by(int x, int y, int color)
{
	// erase player
	draw_square(player.x, player.y, 4, BLACK);
	// draw_square_image(player.x, player.y, 4, BLACK);

	// draw new player
	player.x += x;
	player.y += y;
	draw_square(player.x, player.y, 4, color);
	// draw_square_image(player.x, player.y, 4, color);
}
