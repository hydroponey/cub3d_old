/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:51:00 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/12 08:26:51 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "errors.h"
#include "err_messages.h"
#include "cub3d.h"

const char	*get_error_msg(int code)
{
	if (code > 0 && code < 29)
		return (g_err_messages[code]);
	return (NULL);
}

void		print_error(int code)
{
	const char *message;

	ft_putstr_fd("Error\n", 1);
	if ((message = get_error_msg(code)) != NULL)
		ft_putstr_fd((char *)message, 1);
}
