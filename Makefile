# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/08/23 22:57:42 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c config.c get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -DBUFFER_SIZE=1024
LIBS	=	-Lmlx -Llibft -lft -lmlx -lXext -lX11
NAME	=	cub3d
MLX		=	mlx/libmlx.a
LIBFT	=	libft/libft.a

all:		$(NAME)

$(MLX):
			$(MAKE) -C mlx

$(LIBFT):
			$(MAKE) -C libft

$(NAME):	$(OBJS) $(MLX) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
			$(MAKE) -C mlx clean
			$(MAKE) -C libft fclean
			rm -f $(OBJS)

fclean:		clean
			rm -f cub3d

re:			fclean all