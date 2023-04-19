# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 08:12:43 by fesper-s          #+#    #+#              #
#    Updated: 2023/04/19 08:33:32 by fesper-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= ./src/main.c ./src/textures.c ./src/map.c  ./src/check.c \
		  ./src/init.c ./src/raycast.c ./src/utils.c ./src/ft_atoi_base.c \
		  ./src/error.c ./src/memory.c ./src/movement.c \
		  ./src/texture_direction.c ./src/texture_utils.c ./src/free_game.c \
		  ./src/draw.c ./src/map_validation.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= ./lib/libft/libft.a 

ifeq ($(shell uname), Linux)
	MLX_FLAGS	= $(CFLAGS) -L ./lib/mlx_linux -lmlx_Linux -L/usr/lib \
				  -Imlx_linux -lXext -lX11 -lm -lz
	MLX_DIR		= ./lib/mlx_linux
else
	MLX_FLAGS	= $(CFLAGS) -L ./lib/mlx -lmlx -framework OpenGL -framework \
				  AppKit
	MLX_DIR		= ./lib/mlx
endif

%.o: %.c
			cc -c $< $(CFLAGS) -I ./include -o $@

$(NAME):	$(OBJS)
			make -C ./lib/libft
			make -C $(MLX_DIR)
			cc $^ $(MLX_FLAGS) $(LIBFT) -o $@

all:		$(NAME)

clean:
			rm -rf $(OBJS)
			make clean -C ./lib/libft
			make clean -C $(MLX_DIR)

fclean:		clean
			rm -rf $(NAME)
			rm -rf $(NAME).dSYM
			make fclean -C ./lib/libft

re:			fclean all

.PHONY:		all clean fclean re
