
#include "cub3d.h"

void		turn_move_player_by_image(int x, int y, int angle)
{
	int		to_x;
	int		to_y;

	to_x = g_player.x + (cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	to_y = g_player.y + (sin(g_player.view_angle * M_PI / 180) * g_player.view_length);

	draw_square_image(g_player.x - ceil(g_player.size / 2),
	g_player.y - ceil(g_player.size / 2), g_player.size, BLACK);
	draw_line_image(g_player.x, g_player.y, to_x, to_y, BLACK);

	g_player.x += x;
	g_player.y += y;
	g_player.view_angle += angle;

	if (g_player.view_angle <= 0)
		g_player.view_angle = 360;
	else if (g_player.view_angle > 360)
		g_player.view_angle = 1;

	draw_square(g_player.x - ceil(g_player.size / 2),
	g_player.y - ceil(g_player.size / 2), g_player.size, BLUE);
	draw_line_image(g_player.x, g_player.y, to_x, to_y, YELLOW);
	mlx_put_image_to_window(g_mlx.mlx, g_mlx.win, g_img.img, 0, 0);
}

int			handle_keys_image(int key_code)
{
	// quit
	if (key_code == 12 || key_code == 53)
	{
		destroy_mlx();
	}

	// left 'A'
	 if (key_code == 0)
	{
		if (g_player.x > 0)
		{
			turn_move_player_by_image(-1 * g_player.walk_speed, 0, 0);
		}
	}

	// right 'D'
	 if (key_code == 2)
	{
		turn_move_player_by_image(1 * g_player.walk_speed, 0, 0);
	}

	// top 'W'
	 if (key_code == 13 || key_code == 126)
	{
		if (g_player.y > 0)
		{
			turn_move_player_by_image(0, -1 * g_player.walk_speed, 0);
		}
	}

	// bottom 'S'
	 if (key_code == 1 || key_code == 125)
	{
		turn_move_player_by_image(0, 1 * g_player.walk_speed, 0);
	}

	// turn left 'arrow'
	 if (key_code == 123)
	{
		turn_move_player_by_image(0, 0, 1 * g_player.turn_speed);
	}

	// turn right 'arrow'
	 if (key_code == 124)
	{
		turn_move_player_by_image(0, 0, 1 * g_player.turn_speed);
	}
	printf("%d\n", key_code);
	return key_code;
}

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
		if (g_player.x > 0)
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
		if (g_player.y > 0)
		{
			turn_move_player_by(0, -1, 0);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
		}
	}

	// bottom
	 if (key_code == 1 || key_code == 125)
	{
		turn_move_player_by(0, 1, 0);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	}

	// turn left
	 if (key_code == 123)
	{
		turn_move_player_by(0, 0, 5);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	}

	// turn right
	 if (key_code == 124)
	{
		turn_move_player_by(0, 0, -5);
printf("player angle : %.2f %.2f \n", g_player.view_angle, g_player.view_angle * M_PI / 180);
printf("start x, y (%d,%d)\n", g_player.x, g_player.y);
printf("end   x, y (%.2f, %.2f)\n",
	g_player.x+cos(g_player.view_angle * M_PI / 180) * g_player.view_length,
	g_player.y+cos(g_player.view_angle * M_PI / 180) * g_player.view_length);
	}
	printf("%d\n", key_code);

	return key_code;
}
