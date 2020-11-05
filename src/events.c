/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:50:11 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/05 19:48:50 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

int		key_pressed_hook(int key, t_conf *conf)
{
	printf("[EVENT] %08X pressed\n", key);
	if (key == KEY_ESCAPE)
	{
		free_config(conf);
		exit(0);
	}
	if (key == KEY_W)
		conf->keys.w = 1;
	if (key == KEY_A)
		conf->keys.a = 1;
	if (key == KEY_S)
		conf->keys.s = 1;
	if (key == KEY_D)
		conf->keys.d = 1;
	if (key == KEY_LEFT)
		conf->keys.left = 1;
	if (key == KEY_RIGHT)
		conf->keys.right = 1;
	return (0);
}

int		key_released_hook(int key, t_conf *conf)
{
	printf("[EVENT] %08X released\n", key);
	if (key == KEY_W)
		conf->keys.w = 0;
	if (key == KEY_A)
		conf->keys.a = 0;
	if (key == KEY_S)
		conf->keys.s = 0;
	if (key == KEY_D)
		conf->keys.d = 0;
	if (key == KEY_LEFT)
		conf->keys.left = 0;
	if (key == KEY_RIGHT)
		conf->keys.right = 0;
	return (0);
}
/*
int		key_hook(int key, t_conf *conf)
{
	short int	redraw;
	int x;
	int y;

	redraw = 0;
	printf("key hook called: %04X\n", key);
	if (key == KEY_ESCAPE)
	{
		free_config(conf);
		exit(0);
	}
	if (key == KEY_W)
	{
		x = (int)(conf->posx + conf->dirx * MOVESPEED);
		y = (int)conf->posy;
		if (conf->map[x][y] == 0)
		{
			conf->posx += conf->dirx * MOVESPEED;
			redraw = 1;
		}
		x = (int)conf->posx;
		y = (int)(conf->posy + conf->diry * MOVESPEED);
		if (conf->map[x][y] == 0)
		{
			conf->posy += conf->diry * MOVESPEED;
			redraw = 1;
		}
	}
	if (key == KEY_LEFT)
	{
		double olddirx = conf->dirx;
		conf->dirx = conf->dirx * cos(ROTSPEED) - conf->diry * sin(ROTSPEED);
		conf->diry = olddirx * sin(ROTSPEED) + conf->diry * cos(ROTSPEED);
		double oldplanex = conf->planex;
		conf->planex = conf->planex * cos(ROTSPEED) - conf->planey * sin(ROTSPEED);
		conf->planey = oldplanex * sin(ROTSPEED) + conf->planey * cos(ROTSPEED);
		redraw = 1;
	}
	if (key == KEY_RIGHT)
	{
		double olddirx = conf->dirx;
		conf->dirx = conf->dirx * cos(-ROTSPEED) - conf->diry * sin(-ROTSPEED);
		conf->diry = olddirx * sin(-ROTSPEED) + conf->diry * cos(-ROTSPEED);
		double oldplanex = conf->planex;
		conf->planex = conf->planex * cos(-ROTSPEED) - conf->planey * sin(-ROTSPEED);
		conf->planey = oldplanex * sin(-ROTSPEED) + conf->planey * cos(-ROTSPEED);
		redraw = 1;
	}
	if (redraw)
	{
		draw_background(conf);
		draw_walls(conf);
		mlx_put_image_to_window(conf->mlx, conf->win, conf->img.ptr, 0, 0);
	}
	return (0);
}*/

int		exit_hook(t_conf *conf)
{
	printf("exit hook called\n");
	free_config(conf);
	exit(0);
	return (0);
}
