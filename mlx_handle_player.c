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

void		draw_player_at_start(int color)
{
	int	x;
	int	y;

	x = MAP_TILE_SIZE * (MAP_WIDTH / 2);
	y = MAP_TILE_SIZE * (MAP_HEIGHT / 2);
	draw_square(x, y, 4, color);
	player.x = x;
	player.y = y;
	// draw_square_image(0, 0, 4, color);
}

void		move_player(int x, int y, int color)
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
