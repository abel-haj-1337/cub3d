#include "cub3d.h"

void			ft_print_conf()
{
	printf("window width is     %7d\n", g_conf.w_x);
	printf("window height is    %7d\n", g_conf.w_y);
	printf("east texture is     %s\n", g_conf.east);
	printf("north texture is    %s\n", g_conf.north);
	printf("south texture is    %s\n", g_conf.south);
	printf("west texture is     %s\n", g_conf.west);
	printf("ceiling color is    %7d\n", g_conf.ceiling);
	printf("floor color is      %7d\n", g_conf.floor);
	printf("player x is         %7d\n", g_conf.p_x);
	printf("player y is         %7d\n", g_conf.p_y);
	printf("player direction is %7d\n", g_conf.p_dir);
}

void			ft_print_map()
{
	int		i;

	i = 0;
	ft_putnbr(g_rows);
	ft_putstr("\n");
	while (g_rows > i)
	{
		printf("||%s||\n", g_map[i]);
		i++;
	}
}