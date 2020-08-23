/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 02:39:28 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx/mlx.h"

int main(void)
{
    void    *mlx;
    void    *mlx_win;

    printf("Starting cub3d...\n");
    mlx = mlx_init();
    printf("mlx initialized\n");
    mlx_win = mlx_new_window(mlx, 640, 480, "Cub3D");
    if (!mlx_win)
        return (0);
    mlx_loop(mlx);

    return (0);
}