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
			src/config.c \
			src/get_conf_values.c \
			src/error.c \
			src/get_next_line.c \
			src/get_next_line_utils.c
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -DBUFFER_SIZE=1024 -g3 -Ilib
CLIBS	=	-Llib/mlx -Llib/libft -lft -lmlx -lXext -lX11
NAME	=	cub3d
MLX		=	lib/mlx/libmlx.a
LIBFT	=	lib/libft/libft.a

all:		$(NAME)

$(OBJDIR):
			mkdir obj

$(OBJS):	$(OBJDIR) $(OBJDIR)/%.o : $(SRCDIR)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
			$(MAKE) -C lib/mlx

$(LIBFT):
			$(MAKE) -C lib/libft

$(NAME):	$(OBJS) $(MLX) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CLIBS)

clean:
			$(MAKE) -C lib/mlx clean
			$(MAKE) -C lib/libft fclean
			rm -f $(OBJS)

fclean:		clean
			rm -f cub3d

re:			fclean all