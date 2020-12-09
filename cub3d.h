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

#include "/usr/local/include/mlx.h"
#include <stdlib.h>

typedef struct			s_mlx {
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct			s_player {
	int					x;
	int					y;
}						t_player;
