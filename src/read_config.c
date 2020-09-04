/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/04 22:55:37 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "errors.h"
#include "libft/libft.h"
#include "get_next_line.h"

int					parse_param(char *line, char **conf_strings)
{
	int				param_len;
	unsigned int	i;
	int				err;

	i = 0;
	err = ERR_SUCCESS;
	while (i < 8)
	{
		if ((param_len = is_param(line, i)) != -1)
		{
			if (!conf_strings[i])
			{
				if (!(conf_strings[i] = ft_strtrim((line + param_len), " \t")))
					err = ERR_MALLOC_CUBE;
			}
			break ;
		}
		i++;
	}
	return (err);
}

int					read_params(t_conf *conf, char **conf_strings)
{
	char			*line;
	int				err_gnl;
	int				err;

	err = ERR_SUCCESS;
	err_gnl = -1;
	while ((err_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		err = parse_param(line, conf_strings);
		free(line);
		if (err != ERR_SUCCESS || conf_strings[7] != NULL || err_gnl == 0)
			break ;
	}
	if (err_gnl == -1)
		return (ERR_GNL_FAIL);
	return (err);
}

int					add_map_line(t_conf *conf, char *line)
{
	int				err;
	int				new_size;

	err = ERR_SUCCESS;
	new_size = sizeof(char *) * (conf->map_lines + 1);
	if (!err && !(conf->map = realloc(conf->map, new_size)))
		err = ERR_MALLOC_CUBE;
	if (!err && !(conf->map[conf->map_lines++] = ft_strdup(line)))
		err = ERR_MALLOC_CUBE;
	return (err);
}

int					read_map(t_conf *conf)
{
	char			*line;
	int				ret_gnl;
	int				err;
	int				map_end;

	err = ERR_SUCCESS;
	map_end = 0;
	ret_gnl = -1;
	while ((ret_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		if (conf->map == NULL && ft_strlen(ft_strtrim(line, " \t")) == 0)
		{
			free(line);
			continue ;
		}
		err = add_map_line(conf, line);
		free(line);
		if (ret_gnl == 0)
			break ;
	}
	if (ret_gnl == -1)
		err = ERR_GNL_FAIL;
	return (err);
}
