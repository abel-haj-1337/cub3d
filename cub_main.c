#include <stdio.h>
#include "utils/utils.h"
#include "cub3d.h"

int				main(void)
{
	int		fd;
	int		result;
	char	*line;

	result = 0;
	line = NULL;
	fd = open("../text.txt", O_RDONLY);
	while ((result = get_next_line(&line, fd)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
	return (0);
}