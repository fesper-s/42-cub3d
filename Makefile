# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 08:12:43 by fesper-s          #+#    #+#              #
#    Updated: 2023/03/13 10:31:23 by fesper-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= ./lib/libft/libft.a 

SRCS	= ./main.c ./src/map.c ./src/error.c ./src/utils.c

OBJS	= $(SRCS:.c=.o)

UNAME	:= $(shell uname)

ifeq ($(UNAME), Linux)
	OFLAGS	= $(CFLAGS) -L ./lib/mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux \
			  -lXext -lX11 -lm -lz
	MLX		= ./lib/mlx_linux
else
	OFLAGS	= $(CFLAGS) -L ./lib/mlx -lmlx -framework OpenGL -framework AppKit
	MLX		= ./lib/mlx
endif

.c.o:
			cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./include

$(NAME):	$(OBJS)
			make -C ./lib/libft && make -C $(MLX)
			cc $^ $(OFLAGS) $(LIBFT) -o $@

all:		$(NAME)

clean:
			rm -f $(OBJS)
			make clean -C ./lib/libft && make clean -C $(MLX)

fclean:		clean
			rm -f $(NAME)
			rm -rf $(NAME).dSYM
			make fclean -C ./lib/libft

re:			fclean all

.PHONY:		all clean fclean re
