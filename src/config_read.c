/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/08 09:58:02 by asimoes          ###   ########.fr       */
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
	if (!err && !(conf->map_text = realloc(conf->map_text, new_size)))
		err = ERR_MALLOC_CUBE;
	if (!err && !(conf->map_text[conf->map_lines++] = ft_strdup(line)))
		err = ERR_MALLOC_CUBE;
	return (err);
}

int					check_line(t_conf *conf, int *end, char *line, int ret_gnl)
{
	int				err;
	char			*trimmed;

	err = ERR_SUCCESS;
	if (!(trimmed = ft_strtrim(line, " \t")))
		err = ERR_MALLOC_CUBE;
	if (!err && conf->map_text == NULL && ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (err);
	}
	if (!err && *end == 1 && ft_strlen(trimmed) > 0)
		err = ERR_MAP_EMPTY_LINE;
	if (!err && ft_strlen(trimmed) == 0 && ret_gnl != 0)
		*end = 1;
	if (!err && *end == 0)
		err = add_map_line(conf, line);
	free(trimmed);
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
		err = check_line(conf, &map_end, line, ret_gnl);
		free(line);
		if (ret_gnl == 0 || map_end == 1 || err != ERR_SUCCESS)
			break ;
	}
	if (ret_gnl == -1)
		err = ERR_GNL_FAIL;
	return (err);
}
