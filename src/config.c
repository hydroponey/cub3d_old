/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:52:37 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/27 18:53:46 by asimoes          ###   ########.fr       */
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

	fd = -1;
	if (argc != 2 && argc != 3)
		return (ERR_CMD_USAGE);
	if ((path_len = ft_strlen(argv[1])) < 4)
		return (ERR_CMD_USAGE);
	if (ft_strncmp(&argv[1][path_len - 4], ".cub", 4) != 0)
		return (ERR_CMD_BAD_EXT);
	if (argc == 3 && (save_bmp = ft_strncmp(argv[2], "--save", 6)) != 0)
		return (ERR_CMD_USAGE);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (ERR_CMD_OPEN_FAIL);
	if (!(*conf = (t_conf*)malloc(sizeof(t_conf))))
	{
		close(fd);
		return (ERR_MALLOC);
	}
	ft_bzero(*conf, sizeof(t_conf));
	(*conf)->map_path = ft_strdup(argv[1]);
	(*conf)->save_bmp = (save_bmp == 0) ? 1 : 0;
	(*conf)->map_fd = fd;
	return (0);
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

void					free_conf_strings(char **conf_strings)
{
	int	i;

	i = 0;
	while (i < 8)
		free(conf_strings[i++]);
}

int     				parse_config(t_conf *conf)
{
	char			*line;
	int				ret_gnl;
	unsigned int	i;
	unsigned short	param_len;
	int				ret_check;
	char *params[8] = {"R ", "NO ", "SO ", "WE ", "EA ", "S ", "F ", "C "};
	char *conf_strings[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	ret_gnl = -1;
	while ((ret_gnl = get_next_line(conf->map_fd, &line)) >= 0)
	{
		i = 0;
		while (i < 8)
		{
			param_len = ft_strlen(params[i]);
			if (ft_strncmp(line, params[i], param_len) == 0)
			{
				if (!conf_strings[i])
					conf_strings[i] = ft_strtrim((line + param_len), " \t");
				break ;
			}
			i++;
		}
		free(line);
		if (!ret_gnl)
			break ;
	}
	if (ret_gnl == -1)
		return (ERR_GNL_FAIL);
	ret_check = check_config(conf, conf_strings);
	free_conf_strings(conf_strings);
	return (ret_check);
}

void					free_config(t_conf *conf)
{
	close(conf->map_fd);
	free(conf->map_path);
	free(conf->textures[0]);
	free(conf->textures[1]);
	free(conf->textures[2]);
	free(conf->textures[3]);
	free(conf->textures[4]);
	free(conf);
}