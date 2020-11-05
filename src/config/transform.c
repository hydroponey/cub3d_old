/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/05 20:00:12 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "../include/cub3d.h"
#include "../include/errors.h"

int		get_max_width(t_conf *conf)
{
	int		i;
	int		max_width;
	int		len;

	max_width = -1;
	i = 0;
	while (i < conf->map.lines)
	{
		len = ft_strlen(conf->map.text[i]);
		max_width = (max_width < len) ? len : max_width;
		i++;
	}
	return (max_width);
}

int		transform_line(t_conf *conf, int x)
{
	int		y;
	int		len;
	int		err;
	char	c;

	err = ERR_SUCCESS;
	y = 0;
	ft_memset(conf->map.data[x], -1, sizeof(int) * conf->map.width);
	len = ft_strlen(conf->map.text[x]);
	while (y < len)
	{
		c = conf->map.text[x][y];
		if (c == ' ')
			conf->map.data[x][y] = -1;
		else if (c >= '0' && c <= '2')
			conf->map.data[x][y] = c - 48;
		else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			if (x == 0 || y == 0)
			{
				err = ERR_START_POS_ON_BORDER;
				break ;
			}
			conf->map.data[x][y] = 0;
			conf->pos.y = y;
			conf->pos.x = x;
			if (c == 'N')
				conf->dir.y = 1;
			if (c == 'S')
				conf->dir.y = -1;
			if (c == 'E')
				conf->dir.x = -1;
			if (c == 'W')
				conf->dir.x = 1;
		}
		else
		{
			err = ERR_BAD_MAP_CHAR;
			break ;
		}
		y++;
	}
	return (err);
}

int		transform_map(t_conf *conf)
{
	int	width;
	int	x;
	int	err;

	err = ERR_SUCCESS;
	width = get_max_width(conf);
	conf->map.width = width;
	conf->map.height = conf->map.lines;
	if (!(conf->map.data = (int **)malloc(sizeof(int*) * conf->map.lines)))
		return (ERR_MALLOC_CUBE);
	x = 0;
	while (x < conf->map.lines)
	{
		conf->map.data[x] = malloc(sizeof(int) * width);
		if (!conf->map.data[x])
			return (ERR_MALLOC_CUBE);
		if ((err = transform_line(conf, x)) != ERR_SUCCESS)
			break ;
		x++;
	}
	return (err);
}
