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
#include "libft/libft.h"
#include "mlx/mlx.h"
#include "cub3d.h"

int     exit_hook(t_vars *vars)
{
    (void)&vars;
    exit(0);
    return (0);
}

int     main(int argc, char **argv)
{
    t_vars  vars;
    t_reso  screen_res;
    t_conf  *game_conf;

    if (!(game_conf = check_args(argc, argv)))
        return (-1);
    if (!(parse_config(game_conf)))
	{
		free(game_conf->map_path);
		free(game_conf);
		return (-1);
	}
    printf("Screen size: %dx%d\n", game_conf->resolution.x, game_conf->resolution.y);
    printf("North texture: %s\n", game_conf->textures.no);
    if (!(vars.mlx = mlx_init()))
    {
        ft_putstr_fd("Error initializing mlx, exiting.\n", 1);
        return (-1);
    }
    mlx_get_screen_size(vars.mlx, &screen_res.x, &screen_res.y);
    printf("Screen size: %dx%d\n", screen_res.x, screen_res.y);
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Cub3D");
    if (!vars.win)
        return (0);
    mlx_hook(vars.win, 17, 0, &exit_hook, &vars);
    mlx_loop(vars.mlx);

    return (0);
}