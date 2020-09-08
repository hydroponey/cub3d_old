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

SRCDIR	= src
OBJDIR	= obj
SRCS	=	src/main.c \
			src/config_check.c \
			src/config_parse.c \
			src/config_read.c \
			src/config_utils.c \
			src/get_conf_values.c \
			src/error.c \
			src/get_next_line.c \
			src/get_next_line_utils.c
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -DBUFFER_SIZE=1024 -g3 -I.
CLIBS	=	-Lmlx -Llibft -lft -lmlx -lXext -lX11
NAME	=	cub3d
MLX		=	mlx/libmlx.a
LIBFT	=	libft/libft.a

all:		$(NAME)

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