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
# SRC			= mlx_main.c mlx_handle_keys.c rgb_to_hex.c

OBJ			= $(SRC:.c=.o)

testit		:
	gcc -g -I /usr/local/include $(SRC) -L /usr/local/lib/ -lmlx -L /usr/lib/ -lz -framework OpenGL -framework AppKit

$(NAME)		:
	@gcc -c $(OBJ) $(SRC) && echo "\033[1;33mCompiled object files"

clean		:
	@rm -rf a.out *.a && echo "\033[1;31mcleaned"

fclean		: clean
	@rm -rf *.a && echo "\033[1;31mforce clean"

re			: fclean all clean

bonus		:


