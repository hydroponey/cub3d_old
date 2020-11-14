/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/06 01:42:20 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
# include <X11/Xlib.h>
#endif
#include <mlx.h>
#include "libft/libft.h"
#include "include/cub3d.h"

t_conf		*init_game(int argc, char **argv)
{
	t_conf	*conf;
	int		err;

	err = check_args(&conf, argc, argv);
	if (err != ERR_SUCCESS)
		exit_error(err, NULL);
	err = parse_config(conf);
	if (err != ERR_SUCCESS)
		exit_error(err, conf);
	conf->mlx = mlx_init();
	if (!conf->mlx)
		exit_error(ERR_MLX_INIT_FAIL, conf);
	get_final_res(conf);
	err = create_image(conf);
	if (err != ERR_SUCCESS)
		exit_error(ERR_CREATING_IMAGE, conf);
	conf->win = mlx_new_window(conf->mlx, conf->res.x, conf->res.y, "Cub3D");
	if (!conf->win)
		exit_error(ERR_MLX_INIT_FAIL, conf);
	return (conf);
}

int			game_loop(t_conf *conf)
{
	mlx_put_image_to_window(conf->mlx, conf->win, conf->img.ptr, 0, 0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_conf	*conf;

	conf = init_game(argc, argv);
	if (conf->save)
		exit_screenshot(conf);
	mlx_hook(conf->win, 17, (1L << 17), exit_hook, conf);
	mlx_hook(conf->win, 2, (1L << 0), key_pressed_hook, conf);
	mlx_hook(conf->win, 3, (1L << 0), key_released_hook, conf);
	mlx_loop_hook(conf->mlx, game_loop, conf);
	mlx_loop(conf->mlx);
	return (0);
}
