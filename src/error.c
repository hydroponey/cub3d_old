/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:51:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/28 00:08:20 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "errors.h"
#include "cub3d.h"

void	print_error(int code)
{
	ft_putstr_fd("Error\n", 1);
	if (code == ERR_CMD_USAGE)
		ft_putstr_fd("Usage: ./cub3d <path_to_map.cub> [--save]\n", 1);
	if (code == ERR_CMD_BAD_EXT)
		ft_putstr_fd("Wrong map file extension.\n", 1);
	if (code == ERR_CMD_OPEN_FAIL)
		ft_putstr_fd("Failed to open map file.\n", 1);
	if (code == ERR_MALLOC_CUBE)
		ft_putstr_fd("Failed to allocate memory.\n", 1);
	if (code == ERR_SPLIT_FAILED)
		ft_putstr_fd("Failed to parse data, ft_split returned NULL.\n", 1);
	if (code == ERR_SPLIT_VALUES)
		ft_putstr_fd("Failed to parse data, wrong values.\n", 1);
	if (code == ERR_R_NOT_FOUND)
		ft_putstr_fd("Resolution not found in configuration file.\n", 1);
	if (code == ERR_R_NON_NUMERIC)
		ft_putstr_fd("Resolution values are not numeric.\n", 1);
	if (code == ERR_GNL_FAIL)
		ft_putstr_fd("Failed to read lines from map file.\n", 1);
	if (code == ERR_TEXTURE_NOT_FOUND)
		ft_putstr_fd("A texture file is missing from your map file.\n", 1);
	if (code == ERR_TEXTURE_EMPTY)
		ft_putstr_fd("A texture file has an empty path.\n", 1);
	if (code == ERR_CEIL_COLOR_NOT_FOUND)
		ft_putstr_fd("Ceil color is missing.\n", 1);
	if (code == ERR_FLOOR_COLOR_NOT_FOUND)
		ft_putstr_fd("Floor color is missing.\n", 1);
	if (code == ERR_CEIL_NON_NUMERIC)
		ft_putstr_fd("Ceil color value is not numeric.\n", 1);
	if (code == ERR_FLOOR_NON_NUMERIC)
		ft_putstr_fd("Floor color value is not numeric.\n", 1);
	if (code == ERR_CEIL_WRONG_RGB_VALUE)
		ft_putstr_fd("Ceil has a wrong RGB value.\n", 1);
}
