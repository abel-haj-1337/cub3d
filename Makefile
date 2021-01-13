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

NAME		= cub3D

CFLAGS		= -Wall -Wextra -Werror

# SRC			= *.c
SRC			= cub_main.c utils/libft_utils.c utils/ft_split.c utils/get_next_line.c utils/get_next_line_utils.c mlx_draw.c mlx_utils.c mlx_handle_keys.c mlx_handle_player.c rgb_to_hex.c
# SRC			= mlx_main.c mlx_handle_keys.c rgb_to_hex.c

OBJ			= $(SRC:.c=.o)

all			: $(NAME)

$(NAME)		:
	gcc $(SRC) -I /usr/local/include -L /usr/local/lib/ -lmlx -L /usr/lib/ -lz -framework OpenGL -framework AppKit -o $(NAME)
# /goinfre/abel-haj/.brew//Cellar/llvm/11.0.0/bin/clang $(CFLAGS) $(SRC) -fsanitize=address && export ASAN_OPTIONS=detect_leaks=1
# gcc -g -I /usr/local/include $(SRC) -L /usr/local/lib/ -lmlx -L /usr/lib/ -lz -framework OpenGL -framework AppKit
# @gcc $(SRC) -o CUB3D && echo "\033[1;33mCompiled object files\033[0;39m"

clean		:
	@rm -rf $(NAME) $(OBJ) a.out && echo "\033[1;31mcleaned\033[0;39m"

fclean		: clean
	@rm -rf *.o *.a && echo "\033[1;31mforce clean\033[0;39m"

re			: fclean all clean

bonus		:
