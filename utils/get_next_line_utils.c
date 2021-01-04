/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:46:55 by abel-haj          #+#    #+#             */
/*   Updated: 2021/01/04 15:46:56 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (c == 0)
		return (s + len);
	while (len > i)
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	size_t	len;
	char	*new_s;

	i = 0;
	len = ft_strlen(s);
	new_s = malloc(len + 1);
	while (len > i)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		len1;
	size_t		len2;
	char		*new_str;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	while (len1 + len2 > i)
	{
		if (len1 > i)
			new_str[i] = s1[i];
		else
			new_str[i] = s2[i - len1];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
