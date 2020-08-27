/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 20:08:54 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 21:10:54 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define CONF_R	0
#define CONF_NO	1
#define CONF_SO	2
#define CONF_WE	3
#define CONF_EA	4
#define CONF_S	5
#define CONF_F	6
#define CONF_C	7

#define TEXTURE_NO	0
#define TEXTURE_SO	1
#define TEXTURE_WE	2
#define TEXTURE_EA	3

typedef struct  s_reso {
    int	x;
    int	y;
}               t_reso;

typedef struct  s_conf {
    char        *map_path;
    int         save_bmp;
    int         map_fd;
    t_reso      resolution;
    char		*textures[5];
    int      	floor_color[3];
    int      	ceil_color[3];
}               t_conf;

typedef struct  s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

// config.h
int		check_args(t_conf **conf, int argc, char **argv);
int     parse_config(t_conf *conf);
void	free_config(t_conf *conf);

// get_conf_values.h
int		get_resolution(t_conf *conf, char **conf_strings);
int		get_textures(t_conf *conf, char **conf_strings);
int		get_ceil_color(t_conf *conf, char **conf_strings);
int		get_floor_color(t_conf *conf, char **conf_strings);

// error.h
void	print_error(int code);