# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 18:26:34 by abel-haj          #+#    #+#              #
#    Updated: 2020/12/08 18:34:22 by abel-haj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		= -Wall -Wextra -Werror

NAME		=

SRC			= *.c

OBJ			= $(SRC:.c=.o)

$(NAME)		:
	@gcc -c $(OBJ) $(SRC) && echo "\033[1;33mCompiled object files"

clean		:
	@rm -rf a.out *.a && echo "\033[1;31mcleaned"

fclean		: clean
	@rm -rf *.a && echo "\033[1;31mforce clean"

re			: fclean all clean

bonus		:


