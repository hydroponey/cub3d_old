/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_messages.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 22:36:32 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/29 23:27:43 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MESSAGES_H
# define ERR_MESSAGES_H

static const char *g_err_messages[17] = {	"",
											"Usage: ./cub3d <path_to_map.cub> [--save]\n",
											"Wrong map file extension.\n",
											"Failed to open map file.\n",
											"Failed to allocate memory.\n",
											"Failed to parse data, ft_split returned NULL.\n",
											"Failed to parse data, wrong values.\n",
											"Resolution not found in configuration file.\n",
											"Resolution values are not numeric.\n",
											"Failed to read lines from map file.\n",
											"A texture file is missing from your map file.\n",
											"A texture file has an empty path.\n",
											"Ceil color is missing.\n",
											"Floor color is missing.\n",
											"Ceil color value is not numeric.\n",
											"Floor color value is not numeric.\n",
											"Ceil has a wrong RGB value.\n"
										};

#endif
