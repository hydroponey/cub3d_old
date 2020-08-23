/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 03:55:14 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"

typedef struct   s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

int exit_hook(int keycode, t_vars *vars)
{
    printf("Exit called\n");
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int main(void)
{
    t_vars  vars;

    printf("Starting cub3d...\n");
    vars.mlx = mlx_init();
    printf("mlx initialized\n");
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Cub3D");
    if (!vars.win)
        return (0);
    mlx_hook(vars.win, 2, 1L<<0, exit_hook, &vars);
    mlx_hook(vars.win, 17, 1L<<2, exit_hook, &vars);
    mlx_loop(vars.mlx);

    return (0);
}