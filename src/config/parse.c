/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:34 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/05 19:56:33 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/cub3d.h"
#include "../include/errors.h"
#include "libft/libft.h"

int					parse_config(t_conf *conf)
{
	unsigned int	i;
	char			**conf_strings;
	int				err;

	err = ERR_SUCCESS;
	conf_strings = (char**)malloc(sizeof(char *) * 8);
	if (!conf_strings)
		return (ERR_MALLOC_CUBE);
	ft_bzero(conf_strings, sizeof(char *) * 8);
	err = read_params(conf, conf_strings);
	err = (!err) ? read_map(conf) : err;
	err = (!err) ? check_config(conf, conf_strings) : err;
	i = 0;
	while (i < 8)
		free(conf_strings[i++]);
	free(conf_strings);
	return (err);
}
