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

int				func(char ***ln, char **lf, int srch)
{
	char			*tmp;
	char			*tmp_2;

	tmp_2 = *lf;
	*(tmp_2 + srch) = 0;
	tmp = **ln;
	// copying left to line
	**ln = ft_strdup(*lf);
	// freeing up old value
	free(tmp);
	// backing up old value
	tmp = *lf;
	// backing up whats left
	*lf = ft_strdup(*lf + srch + 1);
	// freeing up old value
	free(tmp);
	return (1);
}

int				get_next_line(char **line, int fd)
{
	int				result;
	char			*tmp;
	char			*srch;
	int				srch_2;
	char			reader[1001];
	static char		*left;

	if (!(*line = ft_strdup("")) || !line)
		return (-1);
	if (left)
	{
		if ((srch_2 = ft_my_strchr(left, '\n')) != -1)
			return func(&line, &left, srch_2);
		tmp = *line;
		*line = ft_strdup(left);
		free_and_return(tmp, left, 0);
		// free(tmp);
		// free(left);
		// left = NULL;
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
