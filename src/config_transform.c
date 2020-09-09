/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/09 15:51:23 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "errors.h"

int		get_max_width(t_conf *conf)
{
	int		i;
	int		max_width;
	int		len;

	max_width = -1;
	i = 0;
	while (i < conf->map_lines)
	{
		len = ft_strlen(conf->map_text[i]);
		max_width = (max_width < len) ? len : max_width;
		i++;
	}
	return (max_width);
}

int		set_start_pos(t_conf *conf, int x, int y, int c)
{
	int		err;

	err = ERR_SUCCESS;
	if (x == 0 || y == 0)
		return (ERR_START_POS_ON_BORDER);
	conf->map[x][y] = 0;
	conf->pos.x = y;
	conf->pos.y = x;
	if (c == 'N')
		conf->direction = 90;
	if (c == 'S')
		conf->direction = 270;
	if (c == 'E')
		conf->direction = 180;
	if (c == 'W')
		conf->direction = 0;
	return (err);
}

int		transform_line(t_conf *conf, int x)
{
	int		y;
	int		err;
	int		len;
	char	c;

	err = ERR_SUCCESS;
	y = 0;
	len = ft_strlen(conf->map_text[x]);
	while (y < len)
	{
		c = conf->map_text[x][y];
		if (c == ' ')
			conf->map[x][y] = -1;
		else if (c >= '0' && c <= '2')
			conf->map[x][y] = c - 48;
		else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			err = set_start_pos(conf, x, y, c);
		else
			err = ERR_BAD_MAP_CHAR;
		if (err != ERR_SUCCESS)
			break ;
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
	conf->map_dim.x = width;
	conf->map_dim.y = conf->map_lines;
	if (!(conf->map = (int **)malloc(sizeof(int*) * conf->map_lines)))
		return (ERR_MALLOC_CUBE);
	x = 0;
	while (x < conf->map_lines)
	{
		conf->map[x] = malloc(sizeof(int) * width);
		if (!conf->map[x])
			return (ERR_MALLOC_CUBE);
		if ((err = transform_line(conf, x)) != ERR_SUCCESS)
			break ;
		x++;
	}
	return (err);
}
