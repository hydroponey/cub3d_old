/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/04 20:19:11 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"
#include "errors.h"
#include "libft/libft.h"
#include "get_next_line.h"

int						read_params(t_conf *conf, char **conf_strings)
{
	int				param_len;
	unsigned int	i;
	char			*line;
	int				err_gnl;
	int				err;

	err = ERR_SUCCESS;
	err_gnl = -1;
	while ((err_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		i = 0;
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
		free(line);
		if (err_gnl == 0)
			break ;
	}
	if (err_gnl == -1)
		return (ERR_GNL_FAIL);
	return (err);
}

int						read_map(t_conf *conf)
{
	char			*line;
	int				ret_gnl;

	ret_gnl = -1;
	while ((ret_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		if (conf->map == NULL && ft_strlen(ft_strtrim(line, " \t")) > 0)
		{
			if (ft_strchr(line, '1') == NULL)
			{
				if (conf->map == NULL)
				{
					free(line);
					continue;
				}
				else
				{
					ret_gnl = ERR_INVALID_MAP;
					free(line);
					break ;
				}
			}
			if (!(conf->map = realloc(conf->map, sizeof(char *) * (conf->map_lines + 1))))
			{
				ret_gnl = ERR_MALLOC_CUBE;
				free(line);
				break ;
			}
			if (!(conf->map[conf->map_lines++] = ft_strdup(line)))
			{
				ret_gnl = ERR_MALLOC_CUBE;
				free(line);
				break ;
			}
		}
		free(line);
		if (ret_gnl == 0)
			break ;
	}
	return (ret_gnl);
}
