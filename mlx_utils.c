/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:32 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/17 14:28:12 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		destroy_mlx(void)
{
	mlx_clear_window(g_mlx.mlx, g_mlx.win);
	mlx_destroy_window(g_mlx.mlx, g_mlx.win);
	exit(0);
	return (0);
}
