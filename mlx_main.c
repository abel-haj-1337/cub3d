/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 18:18:06 by abel-haj          #+#    #+#             */
/*   Updated: 2020/12/15 18:18:11 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <float.h>

int a = 0;
int b = 0;

int		destroy_mlx(void)
{
	mlx_clear_window(mlx.mlx, mlx.win);
	mlx_destroy_window(mlx.mlx, mlx.win);
	exit(0);
	return (0);
}

void            my_mlx_pixel_put(int x, int y, int color, t_image image)
{
    char    *dst;

    dst = image.addr + (y * image.line_height + x * (image.bpp / 8));
    *(unsigned int*)dst = color;
}

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
			mlx_pixel_put(mlx.mlx, mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
	a++;
}

void		draw_square_image(int posX, int posY, int width, int color)
{
	int		i;
	int		j;
	t_image image;

	j = 0;
	image.img = mlx_new_image(mlx.mlx, posX, posY);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_height, &image.endian);
	while (j < width)
	{
		i = 0;
		while (i < width)
		{
			my_mlx_pixel_put(posX + j, posY + i, color, image);

			// mlx_pixel_put(mlx.mlx, mlx.win, j + posX, i + posY, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, image.img, posX, posY);
}

void		draw_map(int wall_color)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_HEIGHT)
		{
			if (map[i][j] == 1)
			{
				draw_square(i * MAP_TILE_SIZE, j * MAP_TILE_SIZE, MAP_TILE_SIZE, wall_color);
			}
			j++;
		}
		i++;
	}
}

void		draw_line_2(int from_x, int from_y, int to_x, int to_y, int color)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		D;

	// Calculate "deltas" of the line (difference between two ending points)
    dx = to_x - from_x;
    dy = to_y - from_y;

    // Calculate the line equation based on deltas
    D = (2 * dy) - dx;
	y = from_y;

    // Draw the line based on arguments provided
    for (x = from_x; x < to_x; x++)
    {
        // Place pixel on the raster display
        mlx_pixel_put(mlx.mlx, mlx.win, x, y, color);
printf("(%d, %d)\n", x, y);
        if (D >= 0)
        {
             y = y + 1;
             D = D - 2 * dx;
        }
        D = D + 2 * dy;
    }

	// b++;
// printf("line drawn from (%d,%d) to (%d,%d)\n", x, y, to_x, to_y);
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
	int		dx1;
	int		dy1;

    dx = to_x - from_x;
    dy = to_y - from_y;

	dx1 = abs(dx);
	dy1 = abs(dy);

	if (dy1 <= dx1) {
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
		mlx_pixel_put(mlx.mlx, mlx.win, x, y, color);

		// Rasterize the line
        for (int i = 0; x < xe; i++) {
            x = x + 1;
            // Deal with octants...
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            // Draw pixel from line span at
            // currently rasterized position
            mlx_pixel_put(mlx.mlx, mlx.win, x, y, color);
        }
	} else { // The line is Y-axis dominant
        // Line is drawn bottom to top
        if (dy >= 0) {
            x = from_x; y = from_y; ye = to_y;
        } else { // Line is drawn top to bottom
            x = to_x; y = to_y; ye = from_y;
        }
        mlx_pixel_put(mlx.mlx, mlx.win, x, y, color); // Draw first pixel
        // Rasterize the line
        for (int i = 0; y < ye; i++) {
            y = y + 1;
            // Deal with octants...
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            // Draw pixel from line span at
            // currently rasterized position
            mlx_pixel_put(mlx.mlx, mlx.win, x, y, color);
        }
    }
}

int			is_wall_at(float x, float y) {
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / MAP_TILE_SIZE);
    int mapGridIndexY = floor(y / MAP_TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

float		distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float		fix_rad(float rad)
{
	rad = remainder(rad, M_PI * 2);
	if (rad < 0)
		rad = (M_PI * 2) + rad;
	return (rad);
}

void		draw_ray(float ray_rad, int index)
{
	t_ray ray;
	ray_rad = fix_rad(ray_rad);
    
    int isRayFacingDown = ray_rad > 0 && ray_rad < M_PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = ray_rad < 0.5 * M_PI || ray_rad > 1.5 * M_PI;
    int isRayFacingLeft = !isRayFacingRight;
    
    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(player.y / MAP_TILE_SIZE) * MAP_TILE_SIZE;
    yintercept += isRayFacingDown ? MAP_TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player.x + (yintercept - player.y) / tan(ray_rad);

    // Calculate the increment xstep and ystep
    ystep = MAP_TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = MAP_TILE_SIZE / tan(ray_rad);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (is_wall_at(xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = map[(int)floor(yToCheck / MAP_TILE_SIZE)][(int)floor(xToCheck / MAP_TILE_SIZE)];
            foundHorzWallHit = 1;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = 0;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(player.x / MAP_TILE_SIZE) * MAP_TILE_SIZE;
    xintercept += isRayFacingRight ? MAP_TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = player.y + (xintercept - player.x) * tan(ray_rad);

    // Calculate the increment xstep and ystep
    xstep = MAP_TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = MAP_TILE_SIZE * tan(ray_rad);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (is_wall_at(xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = map[(int)floor(yToCheck / MAP_TILE_SIZE)][(int)floor(xToCheck / MAP_TILE_SIZE)];
            foundVertWallHit = 1;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = foundHorzWallHit
        ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
        : FLT_MAX;
    float vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        ray.distance = vertHitDistance;
        ray.wallHitX = vertWallHitX;
        ray.wallHitY = vertWallHitY;
        ray.wallHitContent = vertWallContent;
        ray.wasHitVertical = 1;
    } else {
        ray.distance = horzHitDistance;
        ray.wallHitX = horzWallHitX;
        ray.wallHitY = horzWallHitY;
        ray.wallHitContent = horzWallContent;
        ray.wasHitVertical = 0;
    }
    ray.rayAngle = ray_rad;
    ray.isRayFacingDown = isRayFacingDown;
    ray.isRayFacingUp = isRayFacingUp;
    ray.isRayFacingLeft = isRayFacingLeft;
    ray.isRayFacingRight = isRayFacingRight;

	draw_line(player.x, player.y, ray.wallHitX, ray.wallHitY, WHITE);
	// printf("FROM (%d,%d) TO(%.0f,%.0f)", player.x, player.y, ray.wallHitX, ray.wallHitY);
}

void		draw_rays()
{
	int i;
	float ray_rad;
	
	i		= 0;
	ray_rad	= (M_PI / 2) - (FOV / 2);
	while (i < RAYS)
	{
		draw_ray(ray_rad, i);
		ray_rad += FOV / RAYS;
		i++;
	// printf("%.0f\n", ray_rad);
	}
}

int			main(void)
{
	int		i = 0;

	// initialize window
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "new window");

	// initialize player
	player.x = MAP_TILE_SIZE;
	player.y = MAP_TILE_SIZE;

	// handle events
	mlx_hook(mlx.win, 2, 0, handle_keys, (void *)0);
	mlx_hook(mlx.win, 17, 0, destroy_mlx, (void *)0);

	// // draw map
	// draw_map(RED);

	// // draw player
	// draw_player_at_start(BLUE);

	// // draw player rays
	// draw_rays();

	// // for(int j = 200; j < 351; j++)
	// for(int j = 0; j < 201; j++)
	// {
	// 	// // draw_line(0, 0, j, j, WHITE);
	// 	// draw_line(0, 0, j, 200 + j, WHITE);
	// 	// draw_line(0, 0, 200 + j, j, WHITE);
	// 	if (j < 25)
	// 		draw_line(200, 200, 300 + j, 300 + j, WHITE);
	// 		// printf("%d, %d\n", 300 + j, 300 + j);
	// 	else
	// 		draw_line(200, 200, 300 + 200 - j, 300 + j, WHITE);
	// 		// printf("%d, %d\n", 300 + 50 - j, 300 + j);
	// }
	// draw_line(0, 100, 0, 125, WHITE);

	// keep game running
	mlx_loop(mlx.mlx);

	return 0;
}
