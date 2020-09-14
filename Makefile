# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/23 01:43:43 by asimoes           #+#    #+#              #
#    Updated: 2020/09/12 15:44:00 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR		=	src
OBJDIR		=	obj
SRCS		=	src/main.c \
				src/config_check.c \
				src/config_parse.c \
				src/config_read.c \
				src/config_transform.c \
				src/config_utils.c \
				src/get_conf_values.c \
				src/error.c \
				src/raycasting.c \
				src/get_next_line.c \
				src/get_next_line_utils.c
OBJS		=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CC			=	gcc
CFLAGS		=	-MMD -Wall -Wextra -Werror -DBUFFER_SIZE=1024 -g3 -I.
CLIBS		=	-Lmlx -Llibft -lft -lmlx -lXext -lX11
CLIBSOSX	=	-Lmlx-mac -Llibft -lft -lmlx -framework OpenGL -framework AppKit
NAME		=	cub3d
MLX			=	mlx/libmlx.a
LIBFT		=	libft/libft.a
MLX_MAC		=	mlx-mac/libmlx.dylib

all:		$(NAME)

-include $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.d)

mac:		$(OBJS) $(MLX_MAC) $(LIBFT)
			cp ./mlx-mac/libmlx.dylib libmlx.dylib
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CLIBSOSX)

$(MLX_MAC):
			$(MAKE) -C mlx-mac

$(OBJS):	$(OBJDIR)/%.o : $(SRCDIR)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
			$(MAKE) -C mlx

$(LIBFT):
			$(MAKE) -C libft

$(NAME):	$(OBJS) $(MLX) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CLIBS)

clean:
			$(MAKE) -C mlx clean
			$(MAKE) -C libft fclean
			rm -f $(OBJS)

fclean:		clean
			rm -f cub3d

re:			fclean all