/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:08:31 by abel-haj          #+#    #+#             */
/*   Updated: 2021/01/04 16:08:33 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int			ft_atoi(char *str);
int			ft_my_strchr(char *s, int c);
void		ft_putnbr(int n);
void		ft_putstr(char *str);
char		**ft_split(char *s, char c);
char		*ft_strdup(char *s);
char		*ft_strchr(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, int start, size_t len);
int			get_next_line(char **line, int fd);

#endif
