/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:50 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/12 19:34:44 by abel-haj         ###   ########.fr       */
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
			ft_putstr("Missing information or incorrct order of information!\n");
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
				free(s[len]);
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
	color = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	// check r g b
	// check if number &&
	// check if forbidden character ('.', 'a', ...)
	if (!ft_strrgb(colors[0]) || !ft_strrgb(colors[1]) || !ft_strrgb(colors[2]) || len != 3)
		color = -1;
	ft_freesplitted(colors, len);
	return (color);
}

int				check_map(char *m)
{
	if (*m == '0' || *m == '1' || *m == '2' || *m == 'E' || *m == 'N' || *m == 'S' || *m == 'W')
	{
		return (1);
	}
	else
	{
		return (0);
	}
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
		conf.w_x == -1 ||
		conf.w_y == -1 ||
		conf.east == NULL ||
		conf.north == NULL ||
		conf.south == NULL ||
		conf.west == NULL ||
		conf.ceiling == -1 ||
		conf.floor == -1
	)
		return (0);
	return (1);
}

void			handle_map(char *l)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	len = ft_strlen(l);

	if (rows == 0)
	{
		// 0 + 1
		map = malloc((rows + 1) * sizeof(int *));
	}
	else
	{
		tmp = map;
		// 1 + 1
		map = malloc((rows + 1) * sizeof(int *));
		while (rows > i)
		{
			// 1
			map[i] = ft_strdup(tmp[i]);
			i++;
		}
		ft_freesplitted(tmp, rows - 1);
	}
	map[rows] = ft_strdup(l);
	rows++;
}

void			print_map()
{
	int		i;

	i = 0;
	ft_putnbr(rows);
	ft_putstr("\n");
	while (rows > i)
	{
		printf("||%s||\n", map[i]);
		i++;
	}
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
			// which information
			// TODO:
			// 		handle duplicate information
			//		validate map
			if (len == 2 && !ft_strcmp(*infos, "C"))
			{
				conf.ceiling = rgb_char_to_int(infos[1]);
				if (conf.ceiling == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(210);
				}
				ft_putstr("ceiling good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "EA"))
			{
				conf.east = infos[1];
				// file not found
				if (open(conf.east, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(203);
				}
				ft_putstr("east good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "F"))
			{
				conf.floor = rgb_char_to_int(infos[1]);
				if (conf.floor == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(211);
				}
				ft_putstr("floor good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "NO"))
			{
				conf.north = infos[1];
				// file not found
				if (open(conf.north, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(204);
				}
				ft_putstr("north good!\n");
			}
			else if (len == 3 && !ft_strcmp(*infos, "R"))
			{
				conf.w_x = ft_atoi(infos[1]);
				conf.w_y = ft_atoi(infos[2]);
				if (*infos[1] != '-' && *infos[2] != '-' &&
					ft_isdigit(*infos[1]) && ft_isdigit(*infos[2]))
				{
					conf.w_x = (conf.w_x < 0) ? -2 : conf.w_x;
					conf.w_y = (conf.w_y < 0) ? -2 : conf.w_y;
					ft_putstr("resolution good!\n");
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
				conf.sprite = infos[1];
				// file not found
				if (open(conf.sprite, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(205);
				}
				ft_putstr("sprite good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "SO"))
			{
				conf.south = infos[1];
				// file not found
				if (open(conf.south, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(206);
				}
				ft_putstr("south good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "WE"))
			{
				conf.west = infos[1];
				// file not found
				if (open(conf.west, O_RDONLY) == -1)
				{
					free(line);
					ft_freesplitted(infos, len);
					ft_puterr(207);
				}
				ft_putstr("west good!\n");
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
	// incorrect information
	// else if (len > 3)
	// {
	// 	// bad conf
	// 	free(line);
	// 	ft_freesplitted(infos, len);
	// 	ft_puterr(201);
	// }
	// free array
	ft_freesplitted(infos, len);
}

void			init_map_conf()
{
	conf.w_x = -1;
	conf.w_y = -1;
	conf.east = NULL;
	conf.north = NULL;
	conf.south = NULL;
	conf.west = NULL;
	conf.ceiling = -1;
	conf.floor = -1;
	conf.p_x = -1;
	conf.p_y = -1;
	conf.p_dir = -1;
}

void			init_others()
{
	rows = 0;
	map = NULL;
}

int				check_forbidden_map(char *line, int y)
{
	int			i;

	i = 0;
	while (line[i])
	{
		
		if (line[i] == 'E' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W')
		{
			if (conf.p_dir == -1)
			{
				conf.p_dir = line[i];
				conf.p_x = i;
				conf.p_y = y;
			}
			else
			{
				printf("%d %d %c\n", i, y, line[i]);
				return (1);
			}
		}
		else if ((line[i] == '0' && (y == 0 || y == rows - 1)) ||
			(line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' '))
		{
			printf("%d %d %c\n", i, y, line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

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

int				yborder_check(char *line, int y)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == 'S' ||
			line[i] == 'E' || line[i] == 'N' ||
			line[i] == 'S' || line[i] == 'W' ||
			line[i] == '2')
		{
			// TODO:
			// 		check top border
			// 		check bottom border
			// if prev line not bordered
			if (y != 0)
			{}
				// 0
		}
		i++;
	}
	return (1);
}

void			validate_map()
{
	// 
	int		i;
	int		len;

	i = 0;
	while (rows > i)
	{
		len = ft_strlen(map[i]);
		if (rborder_check(map[i], len) ||
			lborder_check(map[i]) ||
			yborder_check(map[i], i) ||
			check_forbidden_map(map[i], i))
		{
			// 
			printf("|%d %c|\n", i, map[i][len - 1]);
			ft_freesplitted(map, rows - 1);
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
	init_map_conf();
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

void			ft_print_conf()
{
	printf("window width is %7d\n", conf.w_x);
	printf("window height is %7d\n", conf.w_y);
	printf("east texture is %s\n", conf.east);
	printf("north texture is %s\n", conf.north);
	printf("south texture is %s\n", conf.south);
	printf("west texture is %s\n", conf.west);
	printf("ceiling color is %7d\n", conf.ceiling);
	printf("floor color is %7d\n", conf.floor);
	printf("player x is %7d\n", conf.p_x);
	printf("player y is %7d\n", conf.p_y);
	printf("player direction is %7d\n", conf.p_dir);
}

int				main(int argc, char *argv[])
{
	int			fd;

	init_map_conf();
	init_others();
	if (argc > 1)
	{
		// cannot open file
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			ft_puterr(100);
		}
		// if extension is not 'cub'
		else if (ft_strcmp(ft_strchr(argv[1], '.'), ".cub"))
		{
			ft_puterr(104);
		}
		// read, validate and store data
		handle_file(fd);
		// only map
		if (argc == 2)
		{
			// launch n play
			// print_map();
			ft_putstr("play\n");
		}
		// map with save option
		else if (argc == 3)
		{
			// launch n take screenshot
			if (!ft_strcmp(argv[2], "--save"))
			{
				// 
				ft_putstr("take screenshot!\n");
			}
			else
			{
				ft_puterr(101);
			}
		}
		else
		{
			ft_puterr(103);
		}
	}
	// no arguments
	else
	{
		ft_puterr(102);
	}
	ft_putstr("all good\n");
	return (0);
}
