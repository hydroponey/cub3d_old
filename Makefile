# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/08/23 03:22:40 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
LIBS	=	-Lmlx -lmlx -lXext -lX11
NAME	=	cub3d

all:		$(NAME)

mlx:
			$(MAKE) -C mlx

$(NAME):	$(OBJS) mlx/libmlx.a
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f cub3d

re:			fclean all