/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:55:57 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/13 09:59:23 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "errors.h"

int		setup_config(t_conf **conf_ptr, char **argv, int fd, int save_bmp)
{
	int		err;
	t_conf	*conf;

	err = ERR_SUCCESS;
	conf = (t_conf*)malloc(sizeof(t_conf));
	if (!conf)
		return (ERR_MALLOC_CUBE);
	ft_bzero(conf, sizeof(t_conf));
	conf->map_path = ft_strdup(argv[1]);
	if (!conf->map_path)
		err = ERR_MALLOC_CUBE;
	conf->mlx = NULL;
	conf->win = NULL;
	conf->save_bmp = (save_bmp == 0) ? 1 : 0;
	conf->map_fd = fd;
	conf->map = NULL;
	conf->map_text = NULL;
	conf->map_lines = 0;
	conf->pos.x = -1;
	conf->pos.y = -1;
	if (err != ERR_SUCCESS)
	{
		free(conf);
		close(fd);
	}
	*conf_ptr = conf;
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
	int i;

	if (!conf)
		return ;
	close(conf->map_fd);
	free(conf->map_path);
	free(conf->textures[0]);
	free(conf->textures[1]);
	free(conf->textures[2]);
	free(conf->textures[3]);
	free(conf->textures[4]);
	i = 0;
	while (i < conf->map_lines)
	{
		if (conf->map_text != NULL)
			free(conf->map_text[i]);
		if (conf->map != NULL)
			free(conf->map[i]);
		i++;
	}
	free(conf->map_text);
	free(conf->map);
	free(conf);
}
