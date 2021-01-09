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

#include "utils.h"

static int		part_one(char ***ln, char **lf)
{
	int				srch;
	char			*tmp;
	char			*tmp_2;

	if ((srch = ft_my_strchr(*lf, '\n')) != -1)
	{
		tmp_2 = *lf;
		*(tmp_2 + srch) = 0;
		tmp = **ln;
		**ln = ft_strdup(*lf);
		free(tmp);
		tmp = *lf;
		*lf = ft_strdup(*lf + srch + 1);
		free(tmp);
		return (1);
	}
	tmp = **ln;
	**ln = ft_strdup(*lf);
	free(tmp);
	free(*lf);
	*lf = NULL;
	return (0);
}

static int		part_two(char ***ln, char **lf, char *rdr, char **srch)
{
	char	*tmp;

	**srch = '\0';
	tmp = **ln;
	**ln = ft_strjoin(**ln, rdr);
	free(tmp);
	*lf = ft_strdup(*srch + 1);
	return (1);
}

int				get_next_line(char **line, int fd)
{
	int			result;
	char		*srch;
	char		*tmp;
	char		reader[101];
	static char	*left;

	if (!line || !(*line = ft_strdup("")))
		return (-1);
	if (left)
		if (part_one(&line, &left) == 1)
			return (1);
	while ((result = read(fd, &reader, 100)))
	{
		reader[result] = 0;
		if ((srch = ft_strchr(reader, '\n')))
			return (part_two(&line, &left, reader, &srch));
		tmp = *line;
		*line = ft_strjoin(*line, reader);
		free(tmp);
	}
	return (0);
}
