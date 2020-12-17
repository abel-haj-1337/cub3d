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
	else if (key_code == 0)
	{
		// move player to the left
		if (player.x > 0)
		{
			move_player_by(-1, 0, BLUE);
			// player.y -= 1;
		}
	}
	// right
	else if (key_code == 2)
	{
		move_player_by(1, 0, BLUE);
		// player.x += 1;
	}
	// top
	else if (key_code == 13 || key_code == 126)
	{
		if (player.y > 0)
		{
			move_player_by(0, -1, BLUE);
			// player.y -= 1;
		}
	}
	// bottom
	else if (key_code == 1 || key_code == 125)
	{
		move_player_by(0, 1, BLUE);
		// player.y += 1;
	}

	return key_code;
}
