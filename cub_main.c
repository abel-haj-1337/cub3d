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
	}
	else
		ft_putstr("An unregisterd error encountered!\n");
	exit(0);
}

int				ft_pplen(char **ps)
{
// ft_putstr("entered ft_pplen\n");
	int		i;

	i = 0;
	while (ps[i])
	{
		i++;
	}
	return (i);
// ft_putstr("exited ft_pplen\n");
}

int				check_identifier(char *id)
{
// ft_putstr("entered check_identifier\n");
	if (!ft_strcmp(id, "C") || !ft_strcmp(id, "EA") ||
		!ft_strcmp(id, "F") || !ft_strcmp(id, "NO") || 
		!ft_strcmp(id, "R") || !ft_strcmp(id, "S") || 
		!ft_strcmp(id, "SO") || !ft_strcmp(id, "WE"))
		return (1);
	return (0);
// ft_putstr("exited check_identifier\n");
}

void			ft_freesplitted(char **s, size_t len)
{
// ft_putstr("entered ft_freesplitted\n");
	while (len + 1 > 0)
	{
		free(s[len]);
		len--;
	}
	free(s);
// ft_putstr("exited ft_freesplitted\n");
}

int				rgb_char_to_int(char *rgb)
{
	int		color;
	char	**colors;

	colors = ft_split(rgb, ',');
	color = rgb_to_hex(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	ft_freesplitted(colors, 3);
	return (color);
// ft_putstr("exited rgb_char_to_int\n");
}

int				check_map(char *m)
{
// ft_putstr("entered check_map\n");
	write(1, &m[0], 1);
	if (*m == '1' || *m == '2')
	{
		return (1);
	}
	else
	{
		return (0);
	}
// ft_putstr("exited check_map\n");
}

int				ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void			handle_line(char *line)
{
// ft_putstr("entered handle_line\n");
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
	else if (len <= 3)
	{
		// is information
		if (check_identifier(*infos))
		{
			// which information
			// TODO:
			// 		handle duplicate information
			// 		convert rgb to int
			// 		handle resolution
			if (len == 2 && !ft_strcmp(*infos, "C"))
			{
				conf.ceiling = rgb_char_to_int(infos[1]);
				ft_putstr("ceiling good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "EA"))
			{
				conf.east = infos[1];
				// file not found
				if (open(conf.east, O_RDONLY) != -1)
					ft_putstr("east good!\n");
				else
				{
					free(line);
					ft_puterr(203);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "F"))
			{
				conf.floor = rgb_char_to_int(infos[1]);
				ft_putstr("floor good!\n");
			}
			else if (len == 2 && !ft_strcmp(*infos, "NO"))
			{
				conf.north = infos[1];
				// file not found
				if (open(conf.north, O_RDONLY) != -1)
					ft_putstr("north good!\n");
				else
				{
					free(line);
					ft_puterr(204);
				}
			}
			else if (len == 3 && !ft_strcmp(*infos, "R"))
			{
				conf.w_x = ft_atoi(infos[1]);
				conf.w_y = ft_atoi(infos[2]);
				if (*infos[1] != '-' && *infos[2] != '-' && ft_isdigit(*infos[1]) && ft_isdigit(*infos[2]))
					ft_putstr("resolution good!\n");
				else
				{
					free(line);
					ft_puterr(209);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "S"))
			{
				conf.sprite = infos[1];
				// file not found
				if (open(conf.sprite, O_RDONLY) != -1)
					ft_putstr("sprite good!\n");
				else
				{
					free(line);
					ft_puterr(205);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "SO"))
			{
				conf.south = infos[1];
				// file not found
				if (open(conf.south, O_RDONLY) != -1)
					ft_putstr("south good!\n");
				else
				{
					// ft_freesplitted(infos, len);
					free(line);
					ft_puterr(206);
				}
			}
			else if (len == 2 && !ft_strcmp(*infos, "WE"))
			{
				conf.west = infos[1];
				// file not found
				if (open(conf.west, O_RDONLY) != -1)
					ft_putstr("west good!\n");
				else
				{
					free(line);
					ft_puterr(207);
				}
			}
			else
			{
				// bad information
				free(line);
				ft_puterr(202);
			}
		}
		// is map
		else if (check_map(*infos))
		{
			// is order correct
			ft_putstr("map is good!\n");
				// line contains information and begins or ends with spaces
		}
		// forbidden data
		else
		{
			// 
			// ft_putstr("h");
			free(line);
			ft_puterr(201);
		}
	}
	// incorrect information
	else if (len > 3)
	{
		// bad conf
		free(line);
		ft_puterr(201);
	}
	// free array
	// ft_freesplitted(infos, len);
// ft_putstr("exited handle_line\n");
}

void			init_map_conf()
{
// ft_putstr("entered init_map_conf\n");

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
// ft_putstr("exited init_map_conf\n");
}

void			handle_file(int fd)
{
// ft_putstr("entered handle_file\n");
	int			result;
	char		*line;

	line = NULL;
	// read from file
	init_map_conf();
	while ((result = get_next_line(&line, fd)) > 0)
	{
		ft_putstr("line:|");
		ft_putstr(line);
		ft_putstr("|\n");
		handle_line(line);
		free(line);
	}
	ft_putstr("line:|");
	ft_putstr(line);
	ft_putstr("|\n");
	handle_line(line);
	free(line);
	// validate data in file
	// store data
	close(fd);
// ft_putstr("exited handle_file\n");
}

void			ft_print_conf()
{
	printf("window width is %d\n", conf.w_x);
	printf("window height is %d\n", conf.w_y);
	printf("east texture is %s\n", conf.east);
	printf("north texture is %s\n", conf.north);
	printf("south texture is %s\n", conf.south);
	printf("west texture is %s\n", conf.west);
	printf("ceiling color is %d\n", conf.ceiling);
	printf("floor color is %d\n", conf.floor);
	printf("player x is %d\n", conf.p_x);
	printf("player y is %d\n", conf.p_y);
	printf("player direction is %d\n", conf.p_dir);
}

int				main(int argc, char *argv[])
{
// ft_putstr("entered main\n");
	int			fd;

	init_map_conf();
	if (argc > 1)
	{
		// ft_putstr(argv[1]);
		// cannot open file
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			ft_puterr(100);
			return (0);
		}
		// read, validate and store data
		handle_file(fd);
		// only map
		if (argc == 2)
		{
			// launch n play
			ft_putstr("play\n");
			ft_print_conf();
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
	return (0);
// ft_putstr("exited main\n");
}
