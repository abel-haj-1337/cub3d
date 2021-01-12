#include <stdio.h>
#include "utils/utils.h"
#include "cub3d.h"

static void		ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

static void		ft_puterr(int errn)
{
	ft_putstr("Error\n");
	// 100 - 199
	// program arguments errors
	if (errn <= 199)
		if (errn == 100)
			ft_putstr("Wrong path provided! Configuration file was not found.");
		else if (errn == 101)
			ft_putstr("Invalid arguments! did you mean '--save'?");
		else if (errn == 102)
			ft_putstr("Too much arguments provided!");
		else if (errn == 103)
			ft_putstr("Too few arguments provided!");
	// 200 - 299
	// errors
	else if (errn <= 299)
		if (errn == 200)
			ft_putstr("An error encountered!");
	else
		ft_putstr("An unregisterd error encountered!");
	
}

static int		ft_strcmp(char *s1, char *s2)
{
	int		i;
	
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
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
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
	// validate data in file
	// store data
	close(fd);
	return (conf);
}

int				main(int argc, char *argv[])
{
	int			fd;
	t_map_conf	conf;

	if (argc > 1)
	{
		// open file
		fd = open(argv[1], O_RDONLY);
		// cannot open file
		if (fd == -1)
		{
			ft_puterr(100);
			return (0);
		}
		// read, validate and store data
		conf = handle_file(fd);
		// launch and play
		if (argc == 2)
		{
			// 
		}
		// launch and screenshot (launch?)
		else if (argc == 3)
		{
			// argument correct
			if (!ft_strcmp(argv[2], "--save"))
			{
				// take screenshot
			}
			// argument incorrect
			else
			{
				ft_puterr(101);
			}
		}
		// extra arguments
		else
		{
			ft_puterr(102);
		}
	}
	// no arguments
	else
	{
		ft_puterr(103);
	}
}
