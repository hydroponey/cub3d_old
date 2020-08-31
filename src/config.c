/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:37 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/01 00:03:13 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "cub3d.h"
#include "errors.h"

int						check_args(t_conf **conf, int argc, char **argv)
{
	int		path_len;
	int		save_bmp;
	int		fd;
	int		err;
	int ret;

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

int						check_config(t_conf *conf, char **conf_strings)
{
	int	retval;

	retval = 0;
	if ((retval = get_resolution(conf, conf_strings)) != 0)
		return (retval);
	if ((retval = get_textures(conf, conf_strings)) != 0)
		return (retval);
	if ((retval = get_ceil_color(conf, conf_strings)) != 0)
		return (retval);
	if ((retval = get_floor_color(conf, conf_strings)) != 0)
		return (retval);
	return (0);
}

int						read_config(t_conf *conf, char **conf_strings)
{
	int				param_len;
	unsigned int	i;
	char			*line;
	int				ret_gnl;
	short int		parse_map;

	ret_gnl = -1;
	parse_map = 0;
	while ((ret_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		if (line[0] == '\r' || line[0] == '\n')
			continue;
		i = 0;
		while (i < 8)
		{
			if ((param_len = is_param(line, i)) != -1)
			{
				if (!conf_strings[i])
					conf_strings[i] = ft_strtrim((line + param_len), " \t");
				break ;
			}
			i++;
		}
		if (conf_strings[8] != NULL)
			parse_map = 1;
		if (parse_map)
		{
			
		}
		free(line);
		if (!ret_gnl)
			break ;
	}
	return (ret_gnl);
}

int						parse_config(t_conf *conf)
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
	if (read_config(conf, conf_strings) == -1)
		err = ERR_GNL_FAIL;
	if (!err)
		err = check_config(conf, conf_strings);
	i = 0;
	while (i < 8)
		free(conf_strings[i++]);
	free(conf_strings);
	return (err);
}

void					free_config(t_conf *conf)
{
	if (!conf)
		return ;
	close(conf->map_fd);
	free(conf->map_path);
	free(conf->textures[0]);
	free(conf->textures[1]);
	free(conf->textures[2]);
	free(conf->textures[3]);
	free(conf->textures[4]);
	free(conf);
}
