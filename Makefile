# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 08:12:43 by fesper-s          #+#    #+#              #
#    Updated: 2023/03/10 08:29:29 by fesper-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= ./libft/libft.a 

SRCS	= ./main.c

OBJS	= $(SRCS:.c=.o)

UNAME	:= $(shell uname)

ifeq ($(UNAME), Linux)
	OFLAGS	= $(CFLAGS) -L ./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux \
			  -lXext -lX11 -lm -lz
	MLX		= ./mlx_linux
else
	OFLAGS	= $(CFLAGS) -L ./mlx -lmlx -framework OpenGL -framework AppKit
	MLX		= ./mlx
endif

$(NAME):	$(OBJS)
			make -C ./libft && make -C $(MLX)
			cc $^ $(OFLAGS) $(LIBFT) -o $@

all:		$(NAME)

clean:
			rm -f $(OBJS)
			make clean -C ./libft && make clean -C $(MLX)

fclean:		clean
			rm -f $(NAME)
			rm -rf $(NAME).dSYM
			make fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re
