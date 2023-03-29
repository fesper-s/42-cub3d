# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 08:12:43 by fesper-s          #+#    #+#              #
#    Updated: 2023/03/29 11:44:55 by gussoare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRCS	= ./src/main.c ./src/textures.c ./src/map.c  ./src/check.c \
		  ./src/init.c ./src/raycast.c ./src/utils.c ./src/ft_atoi_base.c \
		  ./src/error.c ./src/memory.c ./src/movement.c ./src/texture_direction.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g

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
