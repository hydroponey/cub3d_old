/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 20:01:26 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/14 15:41:55 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	draw_background(t_conf *conf)
{
	int x;
	int y;
	int max_ceil;

	max_ceil = conf->res.y / 2;
	y = 0;
	while (y < conf->res.y)
	{
		x = 0;
		while (x < conf->res.x)
		{
			if (y < max_ceil)
				conf->img.data[y * conf->res.x + x] = conf->ceil_color;
			else
				conf->img.data[y * conf->res.x + x] = conf->floor_color;
			x++;
		}
		y++;
	}
}

int	draw_line(t_conf *conf, int x, int y_start, int y_end, int color)
{
	int		y;

	y = y_start;
	while (y < y_end)
	{
		conf->img.data[y * conf->res.x + x] = color;
		y++;
	}
	return (0);
}

int	draw_rect(t_conf *conf, t_intVector *center, int w, int h, int color)
{
	int x_end;
    int y_end;
    int cur_x, cur_y;

    x_end = center->x + (w / 2);
    y_end = center->y + (h / 2);

    cur_x = center->x - (w / 2);
    cur_y = center->y - (h / 2);

    while (cur_y < y_end)
    {
        cur_x = center->x - (w / 2);
        while (cur_x < x_end)
        {
            conf->img.data[cur_y * conf->res.x + cur_x] = color;
            cur_x++;
        }
        cur_y++;
    }
    return (0);
}