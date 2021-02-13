# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-haj <abel-haj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 18:26:34 by abel-haj          #+#    #+#              #
#    Updated: 2021/02/13 17:50:05 by abel-haj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CFLAGS		= -Wall -Wextra -Werror

# SRC			= *.c
SRC			= cub_main.c \
				printing.c init_things.c \
				utils/libft_utils.c utils/ft_split.c \
				utils/get_next_line.c utils/get_next_line_utils.c \
				mlx_draw.c mlx_utils.c mlx_handle_keys.c mlx_handle_player.c \
				rgb_to_hex.c

OBJ			= $(SRC:.c=.o)

all			: $(NAME)

backup		:
	gcc $(CFLAGS) $(SRC) -o $(NAME) \
		-L /usr/local/lib/ -lmlx \
		-L /usr/lib/ -lz -framework OpenGL -framework AppKit \
		-I /usr/local/include

$(NAME)		:
	@gcc \
		$(CFLAGS) $(SRC) -g -o $(NAME) -fsanitize=address \
		-I /usr/local/include \
		-L /usr/local/lib/ -lmlx \
		-L /usr/lib/ -lz -framework OpenGL -framework AppKit && \
		export ASAN_OPTIONS=detect_leaks=1 && \
		echo "\033[1;33mCompiling object files...\033[0;39m" || \
		echo "\033[1;31mfailed! compilation error or no llvm maybe?\033[0;39m"
	# @/goinfre/$(USER)/.brew//Cellar/llvm/11.0.1/bin/clang \

test		:
	@gcc $(CFLAGS) $(SRC) -g -o $(NAME) \
		-I /usr/local/include \
		-L /usr/local/lib/ -lmlx \
		-L /usr/lib/ -lz -framework OpenGL -framework AppKit && \
		echo "\033[1;33mCompiling object files...\033[0;39m"

clean		:
	@rm -rf $(NAME) $(OBJ) a.out && echo "\033[1;31mcleaning...\033[0;39m"

fclean		: clean
	@clear && rm -rf *.o *.a && echo "\033[1;31mforce clean...\033[0;39m"

re			: fclean all clean

bonus		:
