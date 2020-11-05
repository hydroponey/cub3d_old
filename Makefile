# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/11/05 19:10:17 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	src/error.c \
			src/gnl/get_next_line.c \
			src/gnl/get_next_line_utils.c \
			src/main.c \
			src/events.c \
			src/helpers.c \
			src/draw_rect.c \
			src/raycasting.c \
			src/config/get_conf_values.c \
			src/config/check.c \
			src/config/parse.c \
			src/config/read.c \
			src/config/transform.c \
			src/config/utils.c
DEPS	=	src/include/cub3d.h \
			src/include/err_messages.h \
			src/include/errors.h \
			src/gnl/get_next_line.h
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -DBUFFER_SIZE=1024 -g3 -Imlx -I.
CLIBS	=	-Lmlx -Llibft -lft -lmlx -lXext -lX11 -lm
NAME	=	cub3d
MLX		=	mlx/libmlx.a
LIBFT	=	libft/libft.a
MLX_MAC	=	mlx-mac/libmlx.dylib

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

%.o:		%.c $(DEPS) $(MLX) $(LIBFT)
			$(CC) $(CFLAGS) -c -o $@ $< $(CLIBS)

$(MLX):		
			$(MAKE) -C mlx

$(LIBFT):	
			$(MAKE) -C libft

clean:
			$(MAKE) -C mlx clean
			$(MAKE) -C libft clean
			rm -f $(OBJS)

fclean:		clean
			rm -f $(MLX)
			rm -f $(LIBFT)
			rm -f $(NAME)

re:			fclean all