/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/14 15:44:27 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "errors.h"
#include "events.h"

#ifndef CUB3D_H
# define CUB3D_H

# define CONF_R			0
# define CONF_NO		1
# define CONF_SO		2
# define CONF_WE		3
# define CONF_EA		4
# define CONF_S			5
# define CONF_F			6
# define CONF_C			7
# define TEXTURE_NO		0
# define TEXTURE_SO		1
# define TEXTURE_WE		2
# define TEXTURE_EA		3
# define TEXTURE_S		4
# define MOVESPEED		0.5
# define ROTSPEED		0.1
# define KEY_W			0x0077
# define KEY_A			0x0071
# define KEY_S			0x0073
# define KEY_D			0x0064
# define KEY_ESCAPE		0xFF1B
# define KEY_LEFT		0xFF51
# define KEY_UP			0xFF52
# define KEY_RIGHT		0xFF53
# define KEY_DOWN		0xFF54
# define KEY_NUM_PLUS	0xFFAB
# define KEY_NUM_MINUS	0xFFAD

int				check_args(t_conf **conf, int argc, char **argv);
int				check_map(t_conf *conf);
int				check_config(t_conf *conf, char **conf_strings);
int				setup_config(t_conf **conf, char **argv, int fd, int save_bmp);
int				is_param(char *data, int param_id);
void			ft_freetab(char **tab);
int				is_numeric(char *str);
int				transform_map(t_conf *conf);
void			free_config(t_conf *conf);
int				set_rgb(int *dest, char **data);
int				get_resolution(t_conf *conf, char **conf_strings);
int				get_textures(t_conf *conf, char **conf_strings);
int				get_ceil_color(t_conf *conf, char **conf_strings);
int				get_floor_color(t_conf *conf, char **conf_strings);
int				parse_config(t_conf *conf);
int				read_params(t_conf *conf, char **conf_strings);
int				read_map(t_conf *conf);
void			init(t_conf *conf);
int				loop_hook(t_conf *conf);
void			print_error(int code);
int				key_hook(int key, t_conf *conf);
int				exit_hook(t_conf *conf);
void			exit_error(int err, t_conf *conf);
void			get_final_res(t_conf *conf);
int				create_image(t_conf *conf);
int				draw_rect(t_conf *conf, t_intVector *p, int w, int h, int color);
void			draw_background(t_conf *conf);
void			draw_floor_perspective(t_conf *conf);
int				draw_line(t_conf *conf, int x, int start, int end, int color);
void			draw_walls(t_conf *conf);
void			exit_screenshot(t_conf *conf);

void			move_forward(t_conf *conf);
void			move_backward(t_conf *conf);
void			move_left(t_conf *conf);
void			move_right(t_conf *conf);
void			rotate_left(t_conf *conf);
void			rotate_right(t_conf *conf);

#endif
