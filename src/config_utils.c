/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:55:57 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/28 11:00:09 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

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