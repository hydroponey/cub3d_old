# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/09/18 12:45:46 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	src/error.c \
			src/get_conf_values.c \
			src/get_next_line.c \
			src/get_next_line_utils.c \
			src/main.c \
			src/raycasting.c \
			src/config/check.c \
			src/config/parse.c \
			src/config/read.c \
			src/config/transform.c \
			src/config/utils.c
DEPS	=	src/cub3d.h \
			src/err_messages.h \
			src/errors.h \
			src/get_next_line.h
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -DBUFFER_SIZE=1024 -g3 -I.
CLIBS	=	-Lmlx -Llibft -lft -lmlx -lXext -lX11
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