/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 23:47:09 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define CONF_R		0
# define CONF_NO	1
# define CONF_SO	2
# define CONF_WE	3
# define CONF_EA	4
# define CONF_S		5
# define CONF_F		6
# define CONF_C		7
# define TEXTURE_NO	0
# define TEXTURE_SO	1
# define TEXTURE_WE	2
# define TEXTURE_EA	3
# define TEXTURE_S	4

typedef struct	s_reso {
	int	x;
	int	y;
}				t_reso;

typedef struct	s_conf {
	char	*map_path;
	int		save_bmp;
	int		map_fd;
	t_reso	res;
	t_reso	pos;
	double	direction;
	char	*textures[5];
	int		floor_color[3];
	int		ceil_color[3];
	char	**map_text;
	int		map_lines;
	int		**map;
	t_reso	map_dim;
}				t_conf;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int		check_args(t_conf **conf, int argc, char **argv);
int		check_map(t_conf *conf);
int		check_config(t_conf *conf, char **conf_strings);

int		setup_config(t_conf **conf, char **argv, int fd, int save_bmp);
int		is_param(char *data, int param_id);
void	ft_freetab(char **tab);
int		is_numeric(char *str);
int		transform_map(t_conf *conf);
void	free_config(t_conf *conf);

int		set_rgb(int *dest, char **data);
int		get_resolution(t_conf *conf, char **conf_strings);
int		get_textures(t_conf *conf, char **conf_strings);
int		get_ceil_color(t_conf *conf, char **conf_strings);
int		get_floor_color(t_conf *conf, char **conf_strings);

int		parse_config(t_conf *conf);

int		read_params(t_conf *conf, char **conf_strings);
int		read_map(t_conf *conf);

void	print_error(int code);

#endif
