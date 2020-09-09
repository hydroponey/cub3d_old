/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:06:36 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/09 16:30:20 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "errors.h"

int						check_args(t_conf **conf, int argc, char **argv)
{
	int		path_len;
	int		save_bmp;
	int		fd;
	int		err;
	int		ret;

	fd = -1;
	err = 0;
	*conf = NULL;
	if (argc != 2 && argc != 3)
		err = ERR_CMD_USAGE;
	if (!err && (path_len = ft_strlen(argv[1])) < 4)
		err = ERR_CMD_USAGE;
	if (!err && ft_strncmp(&argv[1][path_len - 4], ".cub", 4) != 0)
		err = ERR_CMD_BAD_EXT;
	if (!err && argc == 3 && (save_bmp = ft_strncmp(argv[2], "--save", 6)) != 0)
		err = ERR_CMD_USAGE;
	if (!err && (fd = open(argv[1], O_RDONLY)) == -1)
		err = ERR_CMD_OPEN_FAIL;
	if (!err && (ret = setup_config(conf, argv, fd, save_bmp)) != 0)
		err = ret;
	return (err);
}

int						trim_end_of_map(t_conf *conf)
{
	int			err;
	short int	is_empty;
	char		*trimmed;

	err = ERR_SUCCESS;
	is_empty = 1;
	while (is_empty)
	{
		if (!(trimmed = ft_strtrim(conf->map_text[conf->map_lines - 1], " \t")))
		{
			err = ERR_MALLOC_CUBE;
			break ;
		}
		if (ft_strlen(trimmed) == 0)
		{
			free(conf->map_text[conf->map_lines - 1]);
			conf->map_lines--;
		}
		else
			is_empty = 0;
		free(trimmed);
	}
	return (err);
}

int						closed_check(t_conf *conf)
{
	int	i;
	int	j;

	i = 0;
	while (i < conf->map_dim.x)
	{
		j = 0;
		while (j < conf->map_dim.y)
		{
			if (conf->map[i][j] == 0)
			{
				if (i == (conf->map_dim.x - 1))
					return (ERR_MAP_NOT_CLOSED);
				if (j == (conf->map_dim.y - 1))
					return (ERR_MAP_NOT_CLOSED);
			}
			j++;
		}
		i++;
	}
	return (ERR_SUCCESS);
}

int						check_map(t_conf *conf)
{
	int			err;
	char		*trimmed;

	err = ERR_SUCCESS;
	if (conf->map_text == NULL)
		err = ERR_MAP_NOT_PARSED;
	if ((err = trim_end_of_map(conf)) != ERR_SUCCESS)
		return (err);
	trimmed = ft_strtrim(conf->map_text[conf->map_lines - 1], " 1");
	if (ft_strlen(trimmed) != 0)
		err = ERR_BAD_MAP_END;
	free(trimmed);
	trimmed = ft_strtrim(conf->map_text[0], " 1");
	if (ft_strlen(trimmed) != 0)
		err = ERR_BAD_MAP_START;
	free(trimmed);
	if (!err)
		err = transform_map(conf);
	if (!err && (conf->pos.x == -1 || conf->pos.y == -1))
		err = ERR_START_POS_NOT_FOUND;
	if (!err && (conf->pos.x == 0 || conf->pos.y == 0))
		err = ERR_START_POS_ON_BORDER;
	err = closed_check(conf);
	return (err);
}

int						check_config(t_conf *conf, char **conf_strings)
{
	int	retval;

	retval = ERR_SUCCESS;
	retval = get_resolution(conf, conf_strings);
	retval = (!retval) ? get_textures(conf, conf_strings) : retval;
	retval = (!retval) ? get_ceil_color(conf, conf_strings) : retval;
	retval = (!retval) ? get_floor_color(conf, conf_strings) : retval;
	retval = (!retval) ? check_map(conf) : retval;
	return (retval);
}
