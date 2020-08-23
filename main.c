/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 03:58:21 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"

typedef struct   s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

int escape_key_hook(int keycode, t_vars *vars)
{
    printf("ESC pressed\n");
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int red_cross_hook(int button, int x, int y, t_vars *vars)
{
    printf("Click on button: %d\n", button);
//    exit(0);
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
    mlx_hook(vars.win, 2, 1L<<0, escape_key_hook, &vars);
    mlx_hook(vars.win, 17, 1L<<2, red_cross_hook, &vars);
    mlx_loop(vars.mlx);

    return (0);
}