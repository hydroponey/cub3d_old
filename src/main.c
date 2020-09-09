/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 23:47:09 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
# include <X11/Xlib.h>
#endif
#include "libft/libft.h"
#include "mlx/mlx.h"
#include "cub3d.h"
#include "errors.h"

int     key_hook(int key, t_conf *conf)
{
	printf("key hook called\n");
	if (key == 0xFF1B)
	{
		free_config(conf);
		exit(0);
	}
	return (0);
}

int		exit_hook(t_conf *conf)
{
	printf("exit hook called\n");
	free_config(conf);
	exit(0);
	return (0);
}

int     main(int argc, char **argv)
{
	t_vars	vars;
	t_reso	screen_res;
	t_conf	*conf;
	int		err;

	conf = NULL;
	err = 0;
	//printf("check_args\n");
	if ((err = check_args(&conf, argc, argv)) != 0)
	{
		print_error(err);
		return (-1);
	}
	//printf("parse_config\n");
	if ((err = parse_config(conf)) != 0)
	{
		print_error(err);
		free_config(conf);
		return (-1);
	}
	printf("R: %dx%d\n", conf->res.x, conf->res.y);
	printf("NO: %s\n", conf->textures[TEXTURE_NO]);
	printf("SO: %s\n", conf->textures[TEXTURE_SO]);
	printf("WE: %s\n", conf->textures[TEXTURE_WE]);
	printf("EA: %s\n", conf->textures[TEXTURE_EA]);
	printf("S: %s\n", conf->textures[TEXTURE_S]);
	printf("F: %d,%d,%d\n", conf->floor_color[0], conf->floor_color[1], conf->floor_color[2]);
	printf("C: %d,%d,%d\n", conf->ceil_color[0], conf->ceil_color[1], conf->ceil_color[2]);
	printf("Map: %dx%d\n", conf->map_dim.y, conf->map_dim.x);
	int x, y;
	y = 0;
	while (y < conf->map_dim.y)
	{
		x = 0;
		printf("[ ");
		while (x < conf->map_dim.x)
		{
			if (conf->pos.x == x && conf->pos.y == y)
				printf(" %f ", conf->direction);
			else
				printf(" %d ", conf->map[y][x]);
			x++;
		}
		printf(" ]\n");
		y++;
	}
	printf("map[0][0]: %d\n", conf->map[0][0]);
	if (!(vars.mlx = mlx_init()))
	{
		print_error(ERR_MLX_INIT_FAIL);
		free_config(conf);
		return (-1);
	}
	mlx_get_screen_size(vars.mlx, &screen_res.x, &screen_res.y);
	conf->res.x = (conf->res.x > screen_res.x) ? screen_res.x : conf->res.x;
	conf->res.y = (conf->res.y > screen_res.y) ? screen_res.y : conf->res.y;
	vars.win = mlx_new_window(vars.mlx, conf->res.x, conf->res.y, "Cub3D");
	if (!vars.win)
	{
		print_error(ERR_MLX_NEW_WINDOW_FAIL);
		free_config(conf);
		return (-1);
	}
	mlx_hook(vars.win, 17, (1L<<17), exit_hook, conf);
	mlx_hook(vars.win, 2, (1L<<0), key_hook, conf);
	mlx_loop(vars.mlx);
	return (0);
}
