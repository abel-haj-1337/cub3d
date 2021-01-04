/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:44:35 by abel-haj          #+#    #+#             */
/*   Updated: 2021/01/04 15:44:37 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"

static int		free_and_return(char *fs, char *ss, int ret)
{
	free(fs);
	free(ss);
	fs = NULL;
	ss = NULL;
	return (ret);
}

void			func(void)
{
	*left = NULL;
}

int				get_next_line(char **line, int fd)
{
	int				result;
	char			*tmp;
	char			*srch;
	char			reader[1001];
	static char		*left;

	if (!(*line = ft_strdup("")) || !line)
		return (-1);
	if (left)
	{
		if ((srch = ft_strchr(left, '\n')))
		{
			*srch = '\0';
			tmp = *line;
			*line = ft_strdup(left);
			free(tmp);
			tmp = left;
			left = ft_strdup(srch + 1);
			free(tmp);
			return (1);
		}
		tmp = *line;
		*line = ft_strdup(left);
		free(tmp);
		free(left);
		left = NULL;
	}
	while ((result = read(fd, &reader, 1000)))
	{
		reader[result] = 0;
		if ((srch = ft_strchr(reader, '\n')))
		{
			*srch = '\0';
			tmp = *line;
			*line = ft_strjoin(*line, reader);
			free(tmp);
			left = ft_strdup(srch + 1);
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, reader);
		free(tmp);
	}
	return (0);
}

int				main(void)
{
	int		fd;
	int		result;
	char	*line;

	result = 0;
	line = NULL;
	fd = open("text.txt", O_RDONLY);
	while ((result = get_next_line(&line, fd)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
	return (0);
}
