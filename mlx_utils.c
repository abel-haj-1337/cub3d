/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:32 by abel-haj          #+#    #+#             */
/*   Updated: 2021/01/31 14:58:33 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		destroy_mlx(void)
{
	mlx_clear_window(mlx.mlx, mlx.win);
	mlx_destroy_window(mlx.mlx, mlx.win);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(int x, int y, int color, t_image image)
{
	char	*dst;

	dst = image.addr + (y * image.line_height + x * (image.bpp / 8));
	*(unsigned int*)dst = color;
}
