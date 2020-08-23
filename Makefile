# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/08/23 03:34:22 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=
LIBS	=	-Lmlx -lmlx -lXext -lX11
NAME	=	cub3d
MLX		=	mlx/libmlx.a

all:		$(NAME)

$(MLX):
			$(MAKE) -C mlx

$(NAME):	$(OBJS) $(MLX)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f cub3d

re:			fclean all