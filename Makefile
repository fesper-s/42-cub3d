# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 08:12:43 by fesper-s          #+#    #+#              #
#    Updated: 2023/03/10 08:16:50 by fesper-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= ./libft/libft.a 

SRCS	= ./main.c

OBJS	= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			make -C ./libft
			cc $^ $(CFLAGS) $(LIBFT) -o $@

all:		$(NAME)

clean:
			rm -f $(OBJS)
			make clean -C ./libft

fclean:		clean
			rm -f $(NAME)
			rm -rf $(NAME).dSYM
			make fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re
