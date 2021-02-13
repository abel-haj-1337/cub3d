#include "cub3d.h"

void			ft_print_conf()
{
	printf("window width is     %7d\n", conf.w_x);
	printf("window height is    %7d\n", conf.w_y);
	printf("east texture is     %s\n", conf.east);
	printf("north texture is    %s\n", conf.north);
	printf("south texture is    %s\n", conf.south);
	printf("west texture is     %s\n", conf.west);
	printf("ceiling color is    %7d\n", conf.ceiling);
	printf("floor color is      %7d\n", conf.floor);
	printf("player x is         %7d\n", conf.p_x);
	printf("player y is         %7d\n", conf.p_y);
	printf("player direction is %7d\n", conf.p_dir);
}

void			ft_print_map()
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