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
#include <X11/Xlib.h>
#include "libft/libft.h"
#include "mlx/mlx.h"
#include "cub3d.h"

int     key_hook(int key, void *p __attribute__((unused)))
{
	printf("key hook called\n");
	if (key == 0xFF1B)
		exit(0);
	return (0);
}

int		exit_hook(void *p __attribute__((unused)))
{
	printf("exit hook called\n");
	exit(0);
	return (0);
}

int     main(int argc, char **argv)
{
    t_vars  vars;
    t_reso  screen_res;
    t_conf  *game_conf;
	int		err;

	game_conf = NULL;
	err = 0;
    if ((err = check_args(&game_conf, argc, argv)) != 0)
	{
		print_error(err);
        return (-1);
	}
    if ((err = parse_config(game_conf)) != 0)
	{
		print_error(err);
		free_config(game_conf);
		return (-1);
	}
	printf("R: %dx%d\n", game_conf->resolution.x, game_conf->resolution.y);
	printf("NO: %s\n", game_conf->textures[TEXTURE_NO]);
	printf("SO: %s\n", game_conf->textures[TEXTURE_SO]);
	printf("WE: %s\n", game_conf->textures[TEXTURE_WE]);
	printf("EA: %s\n", game_conf->textures[TEXTURE_EA]);
	printf("S: %s\n", game_conf->textures[TEXTURE_S]);
	printf("F: %d,%d,%d\n", game_conf->floor_color[0], game_conf->floor_color[1], game_conf->floor_color[2]);
	printf("C: %d,%d,%d\n", game_conf->ceil_color[0], game_conf->ceil_color[1], game_conf->ceil_color[2]);
    if (!(vars.mlx = mlx_init()))
    {
        ft_putstr_fd("Error initializing mlx, exiting.\n", 1);
        return (-1);
    }
    mlx_get_screen_size(vars.mlx, &screen_res.x, &screen_res.y);
	if (game_conf->resolution.x > screen_res.x || game_conf->resolution.y > screen_res.y)
		vars.win = mlx_new_window(vars.mlx, screen_res.x, screen_res.y, "Cub3D");
	else
		vars.win = mlx_new_window(vars.mlx, game_conf->resolution.x, game_conf->resolution.y, "Cub3D");
	if (!vars.win)
		return (-1);
	mlx_hook(vars.win, 17, (1L<<17), exit_hook, 0);
	mlx_hook(vars.win, 2, (1L<<0), key_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}