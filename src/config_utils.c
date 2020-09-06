/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:55:57 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/06 19:14:18 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "errors.h"

int		setup_config(t_conf **conf, char **argv, int fd, int save_bmp)
{
	int err;

	err = ERR_SUCCESS;
	if (!(*conf = (t_conf*)malloc(sizeof(t_conf))))
		return (ERR_MALLOC_CUBE);
	if (!err)
		ft_bzero(*conf, sizeof(t_conf));
	if (!err && !((*conf)->map_path = ft_strdup(argv[1])))
		err = ERR_MALLOC_CUBE;
	(*conf)->save_bmp = (save_bmp == 0) ? 1 : 0;
	(*conf)->map_fd = fd;
	(*conf)->map = NULL;
	(*conf)->map_text = NULL;
	(*conf)->map_lines = 0;
	(*conf)->pos.x = -1;
	(*conf)->pos.y = -1;
	if (err != ERR_SUCCESS)
	{
		free(*conf);
		close(fd);
	}
	return (err);
}

int		is_param(char *data, int param_id)
{
	char			*params[8];
	unsigned short	param_len;

	params[0] = "R ";
	params[1] = "NO ";
	params[2] = "SO ";
	params[3] = "WE ";
	params[4] = "EA ";
	params[5] = "S ";
	params[6] = "F ";
	params[7] = "C ";
	param_len = ft_strlen(params[param_id]);
	if (ft_strncmp(data, params[param_id], param_len) == 0)
		return (param_len);
	return (-1);
}

int						get_max_width(t_conf *conf)
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

int						transform_line(t_conf *conf, int **map, int x)
{
	int		y;
	int		len;
	int		err;
	char	c;

	err = ERR_SUCCESS;
	y = 0;
	len = ft_strlen(conf->map_text[x]);
	while (y < len)
	{
		c = conf->map_text[x][y];
		if (c == ' ')
			map[x][y] = 0;
		else if (c >= '0' && c <= '2')
			map[x][y] = c - 48;
		else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			map[x][y] = 0;
			conf->pos.x = x;
			conf->pos.y = y;
			if (c == 'N')
				conf->direction = 90;
			if (c == 'S')
				conf->direction = 270;
			if (c == 'E')
				conf->direction = 180;
			if (c == 'W')
				conf->direction = 0;
		}
		else
		{
			printf("bad character: %c\n", c);
			err = ERR_BAD_MAP_CHAR;
			break;
		}
		y++;
	}
	return (err);
}

int						transform_map(t_conf *conf)
{
	int	**map;
	int	width;
	int	x;
	int	err;

	err = ERR_SUCCESS;
	width = get_max_width(conf);
	if (!(map = (int **)malloc(sizeof(int*) * conf->map_lines)))
		return (ERR_MALLOC_CUBE);
	x = 0;
	while (x < conf->map_lines)
	{
		map[x] = malloc(sizeof(int) * width);
		if (!map[x])
			return (ERR_MALLOC_CUBE);
		if ((err = transform_line(conf, map, x)) != ERR_SUCCESS)
			break ;
		x++;
	}
	return (err);
}

void	ft_freetab(char **tab)
{
	char **start;

	if (!tab)
		return ;
	start = tab;
	while (*tab)
		free(*tab++);
	free(start);
}

int		is_numeric(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	free_config(t_conf *conf)
{
	if (!conf)
		return ;
	close(conf->map_fd);
	free(conf->map_path);
	free(conf->textures[0]);
	free(conf->textures[1]);
	free(conf->textures[2]);
	free(conf->textures[3]);
	free(conf->textures[4]);
	while (conf->map_lines--)
		free(conf->map_text[conf->map_lines]);
	free(conf->map);
	free(conf);
}
