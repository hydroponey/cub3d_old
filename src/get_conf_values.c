/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conf_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:25:28 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/27 05:57:54 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "errors.h"
#include "cub3d.h"

#include <stdio.h>

static void				ft_freetab(char **tab)
{
	char **start;

	if (!tab)
		return ;
	start = tab;
	while (*tab)
		free(*tab++);
	free(start);
}

static int				is_numeric(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int						get_resolution(t_conf *conf, char **conf_strings)
{
	char	**tab;
	int		err;

	tab = NULL;
	err = 0;
	if (!conf_strings[CONF_R])
		err = ERR_R_NOT_FOUND;
	if (!err && !(tab = ft_split(conf_strings[CONF_R], ' ')))
		err = ERR_SPLIT_FAILED;
	if (!err && (tab[0] == NULL || (tab[0] != NULL && tab[1] == NULL)))
		err = ERR_SPLIT_VALUES;
	if (!err && (!is_numeric(tab[0]) || !is_numeric(tab[1])))
		err = ERR_R_NON_NUMERIC;
	if (err == 0)
	{
		conf->resolution.x = ft_atoi(tab[0]);
		conf->resolution.y = ft_atoi(tab[1]);
	}
	ft_freetab(tab);
	return (err);
}

int						get_textures(t_conf *conf, char **conf_strings)
{
	int		i;
	int		err;

	i = CONF_NO;
	err = 0;
	while (i <= CONF_S)
	{
		if (!conf_strings[i])
		{
			err = ERR_TEXTURE_NOT_FOUND;
			break ;
		}
		if (ft_strlen(conf_strings[i]) == 0)
		{
			err = ERR_TEXTURE_EMPTY;
			break ;
		}
		conf->textures[i - 1] = ft_strdup(conf_strings[i]);
		i++;
	}
	return (err);
}

int						get_ceil_color(t_conf *conf, char **conf_strings)
{
	int			err;
	char		**tab;
	char		*rgb[3];

	err = 0;
	tab = NULL;
	ft_bzero(rgb, sizeof(char*) * 3);
	if (!conf_strings[CONF_C])
		err = ERR_CEIL_COLOR_NOT_FOUND;
	if (!err && !(tab = ft_split(conf_strings[CONF_C], ',')))
		err = ERR_SPLIT_VALUES;
	if (!err && (tab[0] == NULL || (tab[0] != NULL && tab[1] == NULL)
		|| (tab[0] != NULL && tab[1] != NULL && tab[2] == NULL)))
		err = ERR_SPLIT_VALUES;
	if (!err && (!(rgb[0] = ft_strtrim(tab[0], " "))
		|| !(rgb[1] = ft_strtrim(tab[1], " "))
		|| !(rgb[2] = ft_strtrim(tab[2], " "))))
		err = ERR_MALLOC_CUBE;
	if (!err && !(is_numeric(rgb[0]) && is_numeric(rgb[1]) && is_numeric(rgb[2])))
		err = ERR_CEIL_NON_NUMERIC;
	if (!err)
	{
		conf->ceil_color[0] = ft_atoi(rgb[0]);
		conf->ceil_color[1] = ft_atoi(rgb[1]);
		conf->ceil_color[2] = ft_atoi(rgb[2]);
		if (conf->ceil_color[0] < 0 || conf->ceil_color[0] > 255
			|| conf->ceil_color[1] < 0 || conf->ceil_color[1] > 255
			|| conf->ceil_color[2] < 0 || conf->ceil_color[2] > 255)
			err = ERR_CEIL_WRONG_RGB_VALUE;
	}
	ft_freetab(tab);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	return (err);
}

int						get_floor_color(t_conf *conf, char **conf_strings)
{
	int		err;
	char	**tab;
	char	*rgb[3];

	err = 0;
	tab = NULL;
	ft_bzero(rgb, sizeof(char*) * 3);
	if (!conf_strings[CONF_F])
		err = ERR_FLOOR_COLOR_NOT_FOUND;
	if (!err && !(tab = ft_split(conf_strings[CONF_F], ',')))
		err = ERR_SPLIT_VALUES;
	if (!err && (tab[0] == NULL || (tab[0] != NULL && tab[1] == NULL)
		|| (tab[0] != NULL && tab[1] != NULL && tab[2] == NULL)))
		err = ERR_SPLIT_VALUES;
	if (!err)
	{
		rgb[0] = ft_strtrim(tab[0], " ");
		rgb[1] = ft_strtrim(tab[1], " ");
		rgb[2] = ft_strtrim(tab[2], " ");
	}
	if (!err && (!is_numeric(rgb[0]) || !is_numeric(rgb[1])
				|| !is_numeric(rgb[2])))
		err = ERR_FLOOR_NON_NUMERIC;
	if (!err)
	{
		conf->floor_color[0] = ft_atoi(rgb[0]);
		conf->floor_color[1] = ft_atoi(rgb[1]);
		conf->floor_color[2] = ft_atoi(rgb[2]);
	}
	ft_freetab(tab);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	return (err);
}