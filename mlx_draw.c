/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:28:02 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/17 18:21:25 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_square(int posX, int posY, int width, int color)
{
	int		i;
	int		j;

	j = 0;
	while (j < width)
	{
		i = 0;
		while (i < width)
		{
			mlx_pixel_put(g_mlx.mlx, g_mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
}

void	my_mlx_pixel_put(int x, int y, int color, t_image *image)
{
	char	*dst;

	if ((x >= 0 || x < g_conf.w_w) && (y >= 0 || y < g_conf.w_h))
	{
		dst = image->addr + (y * image->line_height + x * (image->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void		draw_line_image(int frm_x, int frm_y, int to_x, int to_y, int color)
{
	int		i;
	int		dx;
	int		dy;
	int		opposite_or_adjacent;
	float	curr_x;
	float	curr_y;

	i = 0;
	dx = frm_x - to_x;
	dy = frm_y - to_y;
	curr_x = frm_x;
	curr_y = frm_y;
	opposite_or_adjacent = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);
	while (i < opposite_or_adjacent)
	{
		// put pixel in image
		my_mlx_pixel_put(round(curr_x), round(curr_y), color, &g_img);
		curr_x += dx / (float)opposite_or_adjacent;
		curr_y += dy / (float)opposite_or_adjacent;
	}
}

void		draw_my_line(int from_x, int from_y, int to_x, int to_y, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	slope;

	// distance between start point and end point in x axis
	dx = to_x - from_x;

	// distance between start point and end point in x axis
	dy = to_y - from_y;

	// number of steps to complete drawing the line
	steps = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

	//
	slope = dx / dy;

	// increment x by (dx / steps)
	while (steps > 0)
	{
		mlx_pixel_put(g_mlx.mlx, g_mlx.win, from_x, from_y, color);
		from_x = round(from_x + dx / steps);
		from_y = round(from_y + dy / steps);
		steps--;
	}
}

void		draw_line(int from_x, int from_y, int to_x, int to_y, int color)
{
	int		x;	//
	int		y;	//
	int		xe;
	int		ye;
	int		py;
	int		px;
	int		dx;	//
	int		dy;	//

	// Get distance in each axis
	dx = to_x - from_x;
	dy = to_y - from_y;

	// Calculate error intervals for both axis
    px = 2 * abs(dy) - abs(dx);
    py = 2 * abs(dx) - abs(dy);

	if (abs(dy) <= abs(dx))
	{
		if (dx >= 0)
		{
			x = from_x;
			y = from_x;
			xe = to_x;
		}
		else
		{
			x = to_x;
			y = to_y;
			xe = from_x;
		}
		mlx_pixel_put(g_mlx.mlx, g_mlx.win, x, y, color);

		// Rasterize the line
		while (x < xe)
		{
			x++;
			// Deal with octants...
			if (px < 0)
				px = px + 2 * abs(dy);
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y++;
				else
					y--;
				px = px + 2 * (abs(dy) - abs(dx));
			}
			// Draw pixel from line span at
			// currently rasterized position
			mlx_pixel_put(g_mlx.mlx, g_mlx.win, x, y, color);
		}
	}
	else
	{ // The line is Y-axis dominant
		// Line is drawn bottom to top
		if (dy >= 0)
		{
			x = from_x;
			y = from_y;
			ye = to_y;
		}
		else
		{ // Line is drawn top to bottom
			x = to_x;
			y = to_y;
			ye = from_y;
		}
		mlx_pixel_put(g_mlx.mlx, g_mlx.win, x, y, color); // Draw first pixel
		// Rasterize the line
		while (y < ye)
		{
			y++;
			// Deal with octants...
			if (py <= 0)
				py = py + 2 * abs(dx);
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x++;
				else
					x--;
				py = py + 2 * (abs(dx) - abs(dy));
			}
			// Draw pixel from line span at
			// currently rasterized position
			mlx_pixel_put(g_mlx.mlx, g_mlx.win, x, y, color);
		}
	}
}