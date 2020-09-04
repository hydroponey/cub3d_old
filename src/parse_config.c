/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:05:34 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/04 21:25:14 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "errors.h"

int					parse_config(t_conf *conf)
{
	unsigned int	i;
	char			**conf_strings;
	int				err;

	err = ERR_SUCCESS;
	if (!(conf_strings = (char**)malloc(sizeof(char *) * 8)))
		return (ERR_MALLOC_CUBE);
	i = 0;
	while (i < 8)
		conf_strings[i++] = NULL;
	err = read_params(conf, conf_strings);
	err |= read_map(conf);
	printf("read params and map: %d\n", err);
	if (!err)
		err = check_config(conf, conf_strings);
	printf("config check: %d\n", err);
	i = 0;
	while (i < 8)
		free(conf_strings[i++]);
	free(conf_strings);
	return (err);
}
