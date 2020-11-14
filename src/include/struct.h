/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:10:28 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/14 15:32:00 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_map
{
	char			*path;
	int				fd;
	char			**text;
	int				lines;
	int				width;
	int				height;
	int				**data;
}				t_map;

typedef struct	s_img
{
	void			*ptr;
	int				size_line;
	int				bpp;
	int				endian;
	int				*data;
}				t_img;

typedef struct	s_intVector {
	int			x;
	int			y;
}				t_intVector;

typedef struct	s_doubleVector {
	double			x;
	double			y;
}				t_doubleVector;

typedef struct	s_conf {
	void			*mlx;
	void			*win;
	short int		save;
	t_map			map;
	t_intVector		res;
	t_doubleVector	pos;
	t_doubleVector	dir;
	t_doubleVector	plane;
	char			*textures[5];
	int				floor_color;
	int				ceil_color;
	t_img			img;
}				t_conf;

#endif