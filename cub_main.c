#include "utils/utils.h"
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
	}
	else
		ft_putstr("An unregisterd error encountered!\n");
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
	else if (len <= 3)
	{
		// is information
		if (check_identifier(*infos))
		{}
		// is map
		else if ()
		{
			// is order correct
		}
		else
		{
			
		}
		
	}
	// incorrect information
	else if (len > 3)
	{
		// bad conf
		ft_puterr(201);
	}
}

t_map_conf		handle_file(int fd)
{
	int			result;
	char		*line;
	t_map_conf	conf;

	line = NULL;
	// read from file
	while ((result = get_next_line(&line, fd)) > 0)
	{
		handle_line(line);
		ft_putstr(line);
		ft_putstr("\n");
		free(line);
	}
	ft_putstr(line);
	ft_putstr("\n");
	free(line);
	// validate data in file
	// store data
	close(fd);
	return (conf);
}

t_map_conf		init_map_conf()
{
	t_map_conf	c;

	c.w_x = -1;
	c.w_y = -1;
	c.east = NULL;
	c.north = NULL;
	c.south = NULL;
	c.west = NULL;
	c.ceiling = -1;
	c.floor = -1;
	c.p_x = -1;
	c.p_y = -1;
	c.p_dir = -1;
}

int				main(int argc, char *argv[])
{
	int			fd;
	t_map_conf	conf;

	conf = init_map_conf();
	if (argc > 1)
	{
		// cannot open file
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			ft_puterr(100);
			return (0);
		}
		// read, validate and store data
		conf = handle_file(fd);
		// only map
		if (argc == 2)
		{
			// launch n play
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
	return (0);
}
