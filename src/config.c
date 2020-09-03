/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:37 by asimoes           #+#    #+#             */
/*   Updated: 2020/09/03 19:10:51 by asimoes          ###   ########.fr       */
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

	retval = get_resolution(conf, conf_strings) |
			 get_textures(conf, conf_strings) |
			 get_ceil_color(conf, conf_strings) |
			 get_floor_color(conf, conf_strings) |
			 check_map(conf);
	return (retval);
}

int						read_config(t_conf *conf, char **conf_strings)
{
	int				param_len;
	unsigned int	i;
	char			*line;
	int				ret_gnl;

	ret_gnl = -1;
	while ((ret_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		if (conf_strings[7] != NULL)
		{
			if (conf->map == NULL && ft_strlen(ft_strtrim(line, " \t")) == 0)
				continue;
			printf("line: |%s|\n", line);
			if (conf->map != NULL && ft_strchr(line, '1') == NULL)
			{
				ret_gnl = ERR_INVALID_MAP;
				free(line);
				break ;
			}
			if (!(conf->map = realloc(conf->map, sizeof(char *) * (conf->map_lines + 1))))
			{
				ret_gnl = ERR_MALLOC_CUBE;
				free(line);
				break ;
			}
			if (!(conf->map[conf->map_lines++] = ft_strdup(line)))
			{
				ret_gnl = ERR_MALLOC_CUBE;
				free(line);
				break ;
			}
		}
		else
		{
			i = 0;
			while (i < 8)
			{
				if ((param_len = is_param(line, i)) != -1)
				{
					if (!conf_strings[i])
					{
						if (!(conf_strings[i] = ft_strtrim((line + param_len), " \t")))
							ret_gnl = ERR_MALLOC_CUBE;
					}
					break ;
				}
				i++;
			}
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
	err = read_config(conf, conf_strings);
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
	while (conf->map_lines--)
		free(conf->map[conf->map_lines]);
	free(conf->map);
	free(conf);
}
