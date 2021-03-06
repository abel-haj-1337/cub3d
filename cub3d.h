/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:49:59 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/17 18:11:19 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

// # include <mlx.h>
# include "mlx_linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <float.h>
# include "utils/utils.h"

# define BLACK	rgb_to_hex(0, 0, 0)
# define RED	rgb_to_hex(255, 0, 0)
# define BLUE	rgb_to_hex(0, 0, 255)
# define GREEN	rgb_to_hex(0, 255, 0)
# define YELLOW	rgb_to_hex(255, 255, 0)
# define WHITE	rgb_to_hex(255, 255, 255)
# define FOV	(60 * (M_PI / 180))
# define MAP_WIDTH	24
# define MAP_HEIGHT	24
# define MAP_TILE_SIZE 24
# define RAYS 100

typedef struct			s_map_conf
{
	int					w_w;
	int					w_h;
	int					ceiling;
	int					floor;
	char				*sprite;
	char				*north;
	char				*south;
	char				*east;
	char				*west;
	int					p_x;
	int					p_y;
	int					p_dir;
}						t_map_conf;

typedef struct			s_mlx {
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct			s_player {
	int					x;
	int					y;
	int					color;
	int					size;
	int					view_length;
	float				view_angle;
	float				turn_speed;
	float				walk_speed;
}						t_player;

typedef struct			s_image {
	void				*img;
	char				*addr;
	// bits per pixel
	int					bpp;
	int					line_height;
	// system architecture : big/little endian
	int					endian;
}						t_image;

typedef struct			s_ray {
    float				rayAngle;
    float				wallHitX;
    float				wallHitY;
    float				distance;
    int					wasHitVertical;
    int					isRayFacingUp;
    int					isRayFacingDown;
    int					isRayFacingLeft;
    int					isRayFacingRight;
    int					wallHitContent;
}						t_ray;


void					init_mlx();
void					init_conf();
void					init_player();
void					init_others();

int						rgb_to_hex(int r, int g, int b);

int						handle_keys(int key_code);

void					init_player_at(int x, int y);
// void					move_player_by(int x, int y);
// void					turn_player_by(int step);
void					turn_move_player_by(int x, int y, int angle);
void					turn_move_player_by_image(int x, int y, int angle);

void					handle_mlx();
void					my_mlx_pixel_put(int x, int y, int clr, t_image *image);
void					draw_square_image(int x, int y, int width, int color);
void					draw_square(int posX, int posY, int width, int color);
void					draw_line(int x, int y, int to_x, int to_y, int color);
void					draw_my_line(int x, int y, int to_x, int to_y, int clr);
void					draw_line_image(int x, int y, int t_x, int t_y, int c);

int						destroy_mlx(void);


/*
**	FOR TESTING
*/
void					ft_print_conf();
void					ft_print_map();
/*
**	FOR TESTING
*/


t_mlx					g_mlx;
t_player				g_player;
t_map_conf				g_conf;
int						g_rows;
t_image					g_img;
char					**g_map;


/*[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
*/

#endif
