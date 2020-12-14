/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:49:59 by abel-haj          #+#    #+#             */
/*   Updated: 2020/12/09 09:37:57 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

# define BLACK	rgb_to_hex(0, 0, 0)
# define RED	rgb_to_hex(255, 0, 0)
# define BLUE	rgb_to_hex(0, 0, 255)
# define GREEN	rgb_to_hex(0, 255, 0)
# define WHITE	rgb_to_hex(255, 255, 255)

typedef struct			s_mlx {
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct			s_player {
	int					x;
	int					y;
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

int						rgb_to_hex(int r, int g, int b);

#endif
