# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/08/23 02:38:16 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
LIBS	=	-Lmlx -lmlx -lXext -lX11
NAME	=	cub3d

all:		$(NAME)

$(NAME):	$(OBJS) mlx
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

mlx:
			$(MAKE) -C mlx

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f cub3d

re:			fclean all