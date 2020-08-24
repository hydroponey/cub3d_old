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

#define ERR_CONF_USAGE		"Error\nUsage: ./cub3d <map_file.cub> [--save]\n"
#define ERR_CONF_NOMAP		"Error\nMap file has no name.\n"
#define ERR_CONF_WRONG_EXT	"Error\nMap file needs to have .cub extension.\n"
#define ERR_CONF_OPEN_FAIL	"Error\nCannot open map file.\n"
#define ERR_CONF_BAD_ARG	"Error\nUsage: ./cub3d <map_file.cub> [--save]\n"
#define ERR_CONF_MALLOC		"Error\nConfig structure allocation failed.\n"

typedef struct  s_reso {
    int     x;
    int     y;
}               t_reso;

typedef struct  s_textures {
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *sprite;
}               t_textures;

/**
 * \struct s_conf
 * \brief Contains all necessary game informations parsed from map file
 * \param map_path Path to the map file
 * \param save_bmp Equals 1 if --save is used as argument
 * \param map_fd File descriptor to map file
**/
typedef struct  s_conf {
    char        *map_path;
    int         save_bmp;
    int         map_fd;
    t_reso      resolution;
    t_textures  textures;
    int      	floor_color[3];
    int      	ceil_color[3];
}               t_conf;

typedef struct s_parsed {
	short int	is_resolution;
	short int	is_no_texture;
	short int	is_so_texture;
	short int	is_we_texture;
	short int	is_ea_texture;
	short int	is_s_texture;
	short int	is_f_color;
	short int	is_c_color;
	short int	count;
}				t_parsed;


typedef struct  s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

t_conf  *check_args(int argc, char **argv);
int     parse_config(t_conf *conf);