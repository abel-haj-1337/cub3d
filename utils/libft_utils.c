/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:15:10 by abel-haj          #+#    #+#             */
/*   Updated: 2021/02/12 16:10:37 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int				ft_strcmp(char *s1, char *s2)
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

char			*ft_substr(char *s, int start, size_t len)
{
	size_t	i;
	char	*string;

	if (!s)
		return (NULL);
	i = 0;
	string = malloc(len + 1);
	if (string == NULL)
		return (NULL);
	while (len > i && ft_strlen(s) > start)
	{
		string[i] = s[i + start];
		i++;
	}
	string[i] = '\0';
	return (string);
}

int				ft_atoi(char *str)
{
	int				i;
	int				sign;
	size_t			result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		sign = (str[i] == 45) ? -1 : 1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	if (result > 9223372036854775807 && sign == 1)
		return (-1);
	else if (result > 9223372036854775807 && sign == -1)
		return (0);
	return ((int)result * sign);
}

void			ft_putnbr(int n)
{
	size_t result;
	size_t tmp;

	result = 0;
	if (n < 0)
	{
		write(1, (void *)'-', 1);
		result = -((size_t)n);
	}
	else
		result = n;
	if (result < 10)
	{
		tmp = result + 48;
		write(1, &tmp, 1);
	}
	else
	{
		tmp = (result % 10) + 48;
		ft_putnbr(result / 10);
		write(1, &tmp, 1);
	}
}
