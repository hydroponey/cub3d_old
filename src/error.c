/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:51:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/28 21:52:48 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "errors.h"
#include "cub3d.h"

char	*get_error_msg(int code)
{
	char	**errors;

	if ((errors = (char**)malloc(sizeof(char *) * 16)))
	errors[ERR_CMD_USAGE] = ft_strdup("Usage: ./cub3d <path_to_map.cub> "\
									  "[--save]\n");
	errors[ERR_CMD_BAD_EXT] = ft_strdup("Wrong map file extension.\n");
	errors[ERR_CMD_OPEN_FAIL] = ft_strdup("Failed to open map file.\n");
	errors[ERR_MALLOC_CUBE] = ft_strdup("Failed to allocate memory.\n");
	errors[ERR_SPLIT_FAILED] = ft_strdup("Failed to parse data, ft_split "\
										"returned NULL.\n");
	errors[ERR_SPLIT_VALUES] = ft_strdup("Failed to parse data, "\
										 "wrong values.\n");
	errors[ERR_R_NOT_FOUND] = ft_strdup("Resolution not found in configuration"\
										" file.\n");
	errors[ERR_R_NON_NUMERIC] = ft_strdup("Resolution values are not "\
										  "numeric.\n");
	errors[ERR_GNL_FAIL] = ft_strdup("Failed to read lines from map file.\n");
	errors[ERR_TEXTURE_NOT_FOUND] = ft_strdup("A texture file is missing from "\
											"your map file.\n");
	errors[ERR_TEXTURE_EMPTY] = ft_strdup("A texture file has an empty "\
										  "path.\n");
	errors[ERR_CEIL_COLOR_NOT_FOUND] = ft_strdup("Ceil color is missing.\n");
	errors[ERR_FLOOR_COLOR_NOT_FOUND] = ft_strdup("Floor color is missing.\n");
	errors[ERR_CEIL_NON_NUMERIC] = ft_strdup("Ceil color value is not "\
											 "numeric.\n");
	errors[ERR_FLOOR_NON_NUMERIC] = ft_strdup("Floor color value is not "\
											  "numeric.\n");
	errors[ERR_CEIL_WRONG_RGB_VALUE] = ft_strdup("Ceil has a wrong RGB "\
												 "value.\n");
	if (code > 0 && code < 16)
		return (errors[code]);
	return (NULL);
}

void	print_error(int code)
{
	char *message;

	printf("Code: %d\n", code);
	ft_putstr_fd("Error\n", 1);
	if ((message = get_error_msg(code)) != NULL)
		ft_putstr_fd(message, 1);
}
