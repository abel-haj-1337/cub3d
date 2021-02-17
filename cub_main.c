/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:50 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/17 14:36:19 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_puterr(int errn)
{
	ft_putstr("Error\n");
	// 100 - 199
	// program arguments errors
	if (errn <= 199)
	{
		if (errn == 100)
			ft_putstr("Wrong path provided! Configuration file was not found.\n");
		else if (errn == 101)
			ft_putstr("Invalid arguments! did you mean '--save'?\n");
		else if (errn == 102)
			ft_putstr("Too few arguments provided!\n");
		else if (errn == 103)
			ft_putstr("Too much arguments provided!\n");
		else if (errn == 104)
			ft_putstr("Wrong file extension!\n");
	}
	// 200 - 299
	// config file errors
	else if (errn <= 299)
	{
		if (errn == 200)
			ft_putstr("An error encountered!\n");
		else if (errn == 201)
			ft_putstr("Bad configuration!\n");
		else if (errn == 202)
			ft_putstr("Bad identifier or incorrect information!\n");
		else if (errn == 203)
			ft_putstr("East wall texture was not found!\n");
		else if (errn == 204)
			ft_putstr("North wall texture was not found!\n");
		else if (errn == 205)
			ft_putstr("Sprite texture was not found!\n");
		else if (errn == 206)
			ft_putstr("South wall texture was not found!\n");
		else if (errn == 207)
			ft_putstr("West wall texture was not found!\n");
		else if (errn == 208)
			ft_putstr("Forbidden spaces in information!\n");
		else if (errn == 209)
			ft_putstr("Incorrect or forbidden value in resolution!\n");
		else if (errn == 210)
			ft_putstr("Incorrect ceiling color!\n");
		else if (errn == 211)
			ft_putstr("Missing information or incorrect order of information!\n");
	}
	else if (errn <= 399)
	{
		if (errn == 300)
			ft_putstr("Incorrect map!\n");
		if (errn == 301)
			ft_putstr("Forbidden character in map!\n");
	}
	else
		ft_putstr("An unregisterd error encountered!\n");
	exit(0);
}

int				ft_pplen(char **ps)
{
	int		i;

	i = 0;
	while (ps[i])
	{
		i++;
	}
	return (i);
}

int				check_identifier(char *id)
{
	if (!ft_strcmp(id, "C") || !ft_strcmp(id, "EA") ||
		!ft_strcmp(id, "F") || !ft_strcmp(id, "NO") ||
		!ft_strcmp(id, "R") || !ft_strcmp(id, "S") ||
		!ft_strcmp(id, "SO") || !ft_strcmp(id, "WE"))
		return (1);
	return (0);
}

void			ft_freesplitted(char **s, size_t len)
{
	if (s != NULL)
	{
		while (len + 1 > 0)
		{
			if (s[len] != NULL)
			{
				free(s[len]);
				s[len] = NULL;
			}
			len--;
		}
		free(s);
	}
}

int				ft_strrgb(char *str)
{
	int		i;
	int		len;
	
	i = 0;
	if ((len = ft_strlen(str)) > 3)
		return (0);
	while (len > i)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int				rgb_char_to_int(char *rgb)
{
	int		len;
	int		color;
	char	**colors;

	colors = ft_split(rgb, ',');
	len = ft_pplen(colors);
	color = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]),
			ft_atoi(colors[2]));
	if (!ft_strrgb(colors[0]) || !ft_strrgb(colors[1]) || !ft_strrgb(colors[2]) || len != 3)
		color = -1;
	ft_freesplitted(colors, len);
	return (color);
}

int				check_map(char *m)
{
	if (*m == '0' || *m == '1' || *m == '2' ||
		*m == 'E' || *m == 'N' || *m == 'S' ||
		*m == 'W')
		return (1);
	else
		return (0);
}

int				ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int				is_order_good()
{
	if (
		g_conf.w_w == -1 ||
		g_conf.w_h == -1 ||
		g_conf.east == NULL ||
		g_conf.north == NULL ||
		g_conf.south == NULL ||
		g_conf.west == NULL ||
		g_conf.ceiling == -1 ||
		g_conf.floor == -1
	)
		return (0);
	return (1);
}

void			handle_map(char *l)
{
	int		i;
	char	**tmp;

	i = 0;
	if (g_rows == 0)
		// 0 + 1
		g_map = malloc((g_rows + 1) * sizeof(int *));
	else
	{
		tmp = g_map;
		// 1 + 1
		g_map = malloc((g_rows + 1) * sizeof(int *));
		while (g_rows > i)
		{
			g_map[i] = ft_strdup(tmp[i]);
			i++;
		}
		ft_freesplitted(tmp, g_rows - 1);
	}
	g_map[g_rows] = ft_strdup(l);
	g_rows++;
}

void			handle_line(char *line)
{
	int		len;
	char	**infos;

	infos = ft_split(line, ' ');
	len = ft_pplen(infos);
	// empty line
	if (len == 0)
	{
		// skip
	}
	// 1 2 3
	else // if (len <= 3)
	{
		// is information
		if (check_identifier(*infos))
		{
			// TODO:
			// 		missing player
			// 		handle duplicate information
			// 		texture and sprite files validation
			if (len == 2 && !ft_strcmp(*infos, "C"))
			{
				g_conf.ceiling = rgb_char_to_int(infos[1]);
				if (g_conf.ceiling == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(210);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "EA"))
			{
				g_conf.east = infos[1];
				// file not found
				if (open(g_conf.east, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(203);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "F"))
			{
				g_conf.floor = rgb_char_to_int(infos[1]);
				if (g_conf.floor == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(211);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "NO"))
			{
				g_conf.north = infos[1];
				// file not found
				if (open(g_conf.north, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(204);
				}
			}
			else if (len == 3 && !ft_strcmp(*infos, "R"))
			{
				g_conf.w_w = ft_atoi(infos[1]);
				g_conf.w_h = ft_atoi(infos[2]);
				if (*infos[1] != '-' && *infos[2] != '-' &&
					ft_isdigit(*infos[1]) && ft_isdigit(*infos[2]))
				{
					g_conf.w_w = (g_conf.w_w < 0) ? -2 : g_conf.w_w;
					g_conf.w_h = (g_conf.w_h < 0) ? -2 : g_conf.w_h;
				}
				else
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(209);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "S"))
			{
				g_conf.sprite = infos[1];
				// file not found
				if (open(g_conf.sprite, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(205);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "SO"))
			{
				g_conf.south = infos[1];
				// file not found
				if (open(g_conf.south, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(206);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "WE"))
			{
				g_conf.west = infos[1];
				// file not found
				if (open(g_conf.west, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(207);
				}
			}
			else
			{
				// bad information
				free(line);
				ft_freesplitted(infos, len);
				ft_puterr(202);
			}
		}
		// is map
		else if (check_map(*infos))
		{
			// is order correct
			if (!is_order_good())
			{
				free(line);
				ft_freesplitted(infos, len);
				ft_puterr(211);
			}
			// parse map
			handle_map(line);
		}
		// forbidden data
		else
		{
			free(line);
			ft_freesplitted(infos, len);
			ft_puterr(201);
		}
	}
	ft_freesplitted(infos, len);
}

/*
** check_forbidden_map
** y is current row index
** 0 is good
** 1 is bad
*/

int				check_forbidden_map(char *line, int y)
{
	int			i;

	i = 0;
	while (line[i])
	{
		// if player
		if (line[i] == 'E' || line[i] == 'N' ||
			line[i] == 'S' || line[i] == 'W')
		{
			// if player not defined
			if (g_conf.p_dir == -1)
			{
				g_conf.p_dir = line[i];
				g_conf.p_x = i;
				g_conf.p_y = y;
			}
			// else duplicate player
			else
			{
				printf("%d %c\n", i + 1, line[i]);
				return (1);
			}
		}
		// else if forbidden character
		else if ((line[i] != '0' && line[i] != '1' &&
				line[i] != '2' && line[i] != ' '))
		{
			printf("|%d %c|\n", i + 1, line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** rborder_check
** 0 is good
** 1 is bad
*/

int				rborder_check(char *line, int len)
{
	while (line[len - 1] && line[len - 1] == ' ')
	{
		len--;
	}
	if (line[len - 1] == '1')
		return (0);
	return (1);
}

/*
** lborder_check
** 0 is good
** 1 is bad
*/

int				lborder_check(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '1')
		return (0);
	return (1);
}

/*
** yborder_check
** y is current row index
** 0 is good
** 1 is bad
*/

int				yborder_check(char *line, int y)
{
	int		i;

	i = 0;
	while (line[i])
	{
		// [] that needs to be bordered
		if (line[i] == '0' || line[i] == 'S' ||
			line[i] == 'E' || line[i] == 'N' ||
			line[i] == 'S' || line[i] == 'W' ||
			line[i] == '2')
		{
			// if top or bottom
			if (y == 0 || y == g_rows - 1)
			{
				// not bordered
				if (line[i] == '0' || line[i] == '2' ||
					line[i] == 'E' || line[i] == 'N' ||
					line[i] == 'S' || line[i] == 'W')
				{
					printf("|%d %c|\n", i + 1, line[i]);
					return (1);
				}
			}
			// if body
			else
			{
				if (line[i] == '0' || line[i] == '2' ||
					line[i] == 'E' || line[i] == 'N' ||
					line[i] == 'S' || line[i] == 'W')
				{
					// not bordered
					if ( (i >= ft_strlen(g_map[y - 1])) ||
						g_map[y - 1][i] == ' ' ||
						(i >= ft_strlen(g_map[y + 1])) ||
						g_map[y + 1][i] == ' ' ||
						line[i - 1] == ' ' || line[i + 1] == ' ')
					{
						printf("|%d %c|\n", i + 1, line[i]);
						return (1);
					}
				}
			}
		}
		i++;
	}
	return (0);
}

void			validate_map()
{
	int		i;
	int		len;
	int		a, b, c, d;

	i = 0;
	while (g_rows > i)
	{
		len = ft_strlen(g_map[i]);
		if ((a = rborder_check(g_map[i], len)) ||
			(b = lborder_check(g_map[i])) ||
			(c = yborder_check(g_map[i], i)) ||
			(d = check_forbidden_map(g_map[i], i)))
		{
			printf("|%d| |%d %d %d %d|\n", i + 0, a,
			b, c, d);
			ft_freesplitted(g_map, g_rows - 1);
			ft_puterr(300);
		}
		i++;
	}
}

void			handle_file(int fd)
{
	int			result;
	char		*line;

	line = NULL;
	result = 0;
	// read from file
	// init_conf();
	while ((result = get_next_line(&line, fd)) > 0)
	{
		handle_line(line);
		free(line);
	}
	handle_line(line);
	free(line);
	close(fd);
	validate_map();
}

int				main(int argc, char *argv[])
{
	int			fd;

	// init problem
	init_mlx();
	init_conf();
	init_player();
	init_others();
	if (argc > 1)
	{
		// cannot open file
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			ft_puterr(100);
		// if extension is not 'cub'
		else if (ft_strcmp(ft_strchr(argv[1], '.'), ".cub"))
			ft_puterr(104);
		// read, validate and store data
		handle_file(fd);
		// only map
		if (argc == 2)
		{
			ft_putstr("play\n");
			// RAYCAST
			handle_mlx();
				// g_mlx.mlx = mlx_init();
				// g_mlx.win = mlx_new_window(g_mlx.mlx, 500, 500, "1337 Wolfenstein");

				// int x = 0;
				// int y = 0;

				// void *img;
				// char *addr;
				// int bits_per_pixel;
				// int line_length;
				// int endian;
				// img = mlx_new_image(g_mlx.mlx, 500, 500);
				// addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);

				// for (int a=0; a<30; a++)
				// {
				// char *dst = addr + ((y + a) * line_length + x * (bits_per_pixel / 8));
				// *(unsigned int*)dst = RED;
				// dst = addr + ((y + a) * line_length + (x + 1) * (bits_per_pixel / 8));
				// *(unsigned int*)dst = RED;
				// mlx_put_image_to_window(g_mlx.mlx, g_mlx.win, img, 0, 0);
				// }

				// mlx_hook(g_mlx.win, 2, 0, handle_keys, (void *)0);
				// mlx_hook(g_mlx.win, 17, 0, destroy_mlx, (void *)0);

				// mlx_loop(g_mlx.mlx);

		}
		// map with save option
		else if (argc == 3)
		{
			if (!ft_strcmp(argv[2], "--save"))
				ft_putstr("take screenshot!\n");
			else
				ft_puterr(101);
		}
		else
			ft_puterr(103);
	}
	// no arguments
	else
		ft_puterr(102);
	return (0);
}
