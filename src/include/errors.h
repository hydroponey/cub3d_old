/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:53:27 by asimoes           #+#    #+#             */
/*   Updated: 2020/10/24 22:52:26 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_SUCCESS				0

# define ERR_CMD_USAGE				1
# define ERR_CMD_BAD_EXT			2
# define ERR_CMD_OPEN_FAIL			3

# define ERR_MALLOC_CUBE			4

# define ERR_SPLIT_FAILED			5
# define ERR_SPLIT_VALUES			6

# define ERR_R_NOT_FOUND			7
# define ERR_R_NON_NUMERIC			8

# define ERR_GNL_FAIL				9
# define ERR_TEXTURE_NOT_FOUND		10
# define ERR_TEXTURE_EMPTY			11
# define ERR_CEIL_COLOR_NOT_FOUND	12
# define ERR_FLOOR_COLOR_NOT_FOUND	13
# define ERR_CEIL_NON_NUMERIC		14
# define ERR_FLOOR_NON_NUMERIC		15
# define ERR_CEIL_WRONG_RGB_VALUE	16

# define ERR_MLX_INIT_FAIL			17
# define ERR_MLX_NEW_WINDOW_FAIL	18

# define ERR_INVALID_MAP			19
# define ERR_MAP_NOT_PARSED			20
# define ERR_BAD_MAP_END			21
# define ERR_BAD_MAP_START			22
# define ERR_BAD_MAP_CHAR			23
# define ERR_MAP_EMPTY_LINE			24
# define ERR_START_POS_ON_BORDER	25
# define ERR_START_POS_NOT_FOUND	26
# define ERR_MAP_NOT_CLOSED			27

# define ERR_CREATING_IMAGE         28

#endif
