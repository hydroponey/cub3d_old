/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conf_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:25:28 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/29 16:26:53 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "errors.h"
#include "cub3d.h"

#include <stdio.h>

int						set_rgb(int *dest, char **data)
{
	char	*rgb[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(rgb[i] = ft_strtrim(data[i], " ")))
		{
			while (i--)
				free(rgb[i]);
			return (ERR_MALLOC_CUBE);
		}
		if (!is_numeric(rgb[i]))
		{
			while (i--)
				free(rgb[i]);
			return (ERR_FLOOR_NON_NUMERIC);
		}
		dest[i] = ft_atoi(rgb[i]);
		free(rgb[i]);
		i++;
	}
	return (ERR_SUCCESS);
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

	i = TEXTURE_NO;
	err = 0;
	while (i <= TEXTURE_S)
	{
		if (!conf_strings[i + 1])
		{
			err = ERR_TEXTURE_NOT_FOUND;
			break ;
		}
		if (ft_strlen(conf_strings[i + 1]) == 0)
		{
			err = ERR_TEXTURE_EMPTY;
			break ;
		}
		conf->textures[i] = ft_strdup(conf_strings[i + 1]);
		i++;
	}
	return (err);
}

int						get_ceil_color(t_conf *conf, char **conf_strings)
{
	int			err;
	char		**tab;

	err = 0;
	tab = NULL;
	if (!conf_strings[CONF_C])
		err = ERR_CEIL_COLOR_NOT_FOUND;
	if (!err && !(tab = ft_split(conf_strings[CONF_C], ',')))
		err = ERR_SPLIT_VALUES;
	if (!err && (tab[0] == NULL || (tab[0] != NULL && tab[1] == NULL)
		|| (tab[0] != NULL && tab[1] != NULL && tab[2] == NULL)))
		err = ERR_SPLIT_VALUES;
	if (!err)
		err = set_rgb(conf->ceil_color, tab);
	ft_freetab(tab);
	return (err);
}

int						get_floor_color(t_conf *conf, char **conf_strings)
{
	int		err;
	char	**tab;

	err = 0;
	tab = NULL;
	if (!conf_strings[CONF_F])
		err = ERR_FLOOR_COLOR_NOT_FOUND;
	if (!err && !(tab = ft_split(conf_strings[CONF_F], ',')))
		err = ERR_SPLIT_VALUES;
	if (!err && (tab[0] == NULL || (tab[0] != NULL && tab[1] == NULL)
		|| (tab[0] != NULL && tab[1] != NULL && tab[2] == NULL)))
		err = ERR_SPLIT_VALUES;
	if (!err)
		err = set_rgb(conf->floor_color, tab);
	ft_freetab(tab);
	return (err);
}
