/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 20:06:36 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/04 20:12:30 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "errors.h"

int						check_args(t_conf **conf, int argc, char **argv)
{
	int		path_len;
	int		save_bmp;
	int		fd;
	int		err;
	int		ret;

	fd = -1;
	err = 0;
	*conf = NULL;
	if (argc != 2 && argc != 3)
		err = ERR_CMD_USAGE;
	if (!err && (path_len = ft_strlen(argv[1])) < 4)
		err = ERR_CMD_USAGE;
	if (!err && ft_strncmp(&argv[1][path_len - 4], ".cub", 4) != 0)
		err = ERR_CMD_BAD_EXT;
	if (!err && argc == 3 && (save_bmp = ft_strncmp(argv[2], "--save", 6)) != 0)
		err = ERR_CMD_USAGE;
	if (!err && (fd = open(argv[1], O_RDONLY)) == -1)
		err = ERR_CMD_OPEN_FAIL;
	if (!err && (ret = setup_config(conf, argv, fd, save_bmp)) != 0)
		err = ret;
	return (err);
}

int						check_map(t_conf *conf)
{
	int err;

	(void)conf;
	err = (ERR_SUCCESS);
	return (err);
}

int						check_config(t_conf *conf, char **conf_strings)
{
	int	retval;

	retval = get_resolution(conf, conf_strings) ||
				get_textures(conf, conf_strings) ||
				get_ceil_color(conf, conf_strings) ||
				get_floor_color(conf, conf_strings) ||
				check_map(conf);
	return (retval);
}