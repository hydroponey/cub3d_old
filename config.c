/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 20:06:49 by asimoes           #+#    #+#             */
/*   Updated: 2020/08/23 23:46:39 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "cub3d.h"

void			*conf_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (NULL);
}

t_conf			*check_args(int argc, char **argv)
{
	t_conf	*conf;
	int		path_len;
	int		save_bmp;
	int		fd;

	fd = -1;
	if (argc != 2 && argc != 3)
		return (conf_error(ERR_CONF_USAGE));
	if ((path_len = ft_strlen(argv[1])) < 4)
		return (conf_error(ERR_CONF_NOMAP));
	if (ft_strncmp(&argv[1][path_len - 4], ".cub", 4) != 0)
		return (conf_error(ERR_CONF_WRONG_EXT));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (conf_error(ERR_CONF_OPEN_FAIL));
	if (argc == 3 && (save_bmp = ft_strncmp(argv[2], "--save", 6)) != 0)
		return (conf_error(ERR_CONF_BAD_ARG));
	if (!(conf = (t_conf*)malloc(sizeof(t_conf))))
		return (conf_error(ERR_CONF_MALLOC));
	conf->map_path = argv[1];
	conf->save_bmp = (save_bmp == 0) ? 1 : 0;
	conf->map_fd = fd;
	return (conf);
}

void			ft_freetab(char **tab)
{
	void	*tab_start;

	tab_start = tab;
	while (*tab)
		free(*tab++);
	free(tab_start);
}

int				is_numeric(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void		parse_resolution(char *line, t_conf *conf, short int *parsed)
{
	char	**data;

	data = NULL;
	if (ft_strncmp(line, "R", 1) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL || (data[1] != NULL && data[2] == NULL))
	{
		ft_freetab(data);
		return ;
	}
	if (!is_numeric(data[1]) || !is_numeric(data[2]))
	{
		ft_freetab(data);
		return ;
	}
	conf->resolution.x = ft_atoi(data[1]);
	conf->resolution.y = ft_atoi(data[2]);
	*parsed = 1;
	ft_freetab(data);
}

static void		parse_no(char *line, t_conf *conf, short int *parsed)
{
	char	**data;

	data = NULL;
	if (ft_strncmp(line, "NO", 2) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	conf->textures.no = ft_strdup(data[1]);
	*parsed = 1;
	ft_freetab(data);
}

static void		parse_so(char *line, t_conf *conf, short int *parsed)
{
	char	**data;

	data = NULL;
	if (ft_strncmp(line, "SO", 2) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	conf->textures.so = ft_strdup(data[1]);
	*parsed = 1;
	ft_freetab(data);
}

static void		parse_we(char *line, t_conf *conf, short int *parsed)
{
	char	**data;

	data = NULL;
	if (ft_strncmp(line, "WE", 2) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	conf->textures.we = ft_strdup(data[1]);
	*parsed = 1;
	ft_freetab(data);
}

static void		parse_ea(char *line, t_conf *conf, short int *parsed)
{
	char	**data;

	data = NULL;
	if (ft_strncmp(line, "EA", 2) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	conf->textures.ea = ft_strdup(data[1]);
	*parsed = 1;
	ft_freetab(data);
}

static void		parse_s(char *line, t_conf *conf, short int *parsed)
{
	char	**data;

	data = NULL;
	if (ft_strncmp(line, "S", 1) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	conf->textures.sprite = ft_strdup(data[1]);
	*parsed = 1;
	ft_freetab(data);
}

static void		parse_f(char *line, t_conf *conf, short int *parsed)
{
	char	**data;
	char	**rgb;

	data = NULL;
	if (ft_strncmp(line, "F", 1) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	if ((rgb = ft_split(data[1], ',')) == NULL)
	{
		ft_freetab(data);
		return ;
	}
	if (rgb[0] == NULL || (rgb[0] != NULL && rgb[1] == NULL)
		|| (rgb[0] != NULL && rgb[1] != NULL && rgb[2] == NULL))
	{
		ft_freetab(rgb);
		ft_freetab(data);
		return ;
	}
	conf->floor_color[0] = ft_atoi(rgb[0]);
	conf->floor_color[1] = ft_atoi(rgb[1]);
	conf->floor_color[2] = ft_atoi(rgb[2]);
	*parsed = 1;
	ft_freetab(rgb);
	ft_freetab(data);
}

static void		parse_c(char *line, t_conf *conf, short int *parsed)
{
	char	**data;
	char	**rgb;

	data = NULL;
	if (ft_strncmp(line, "C", 1) != 0)
		return ;
	if ((data = ft_split(line, ' ')) == NULL)
		return ;
	if (data[1] == NULL)
	{
		ft_freetab(data);
		return ;
	}
	if ((rgb = ft_split(data[1], ',')) == NULL)
	{
		ft_freetab(data);
		return ;
	}
	if (rgb[0] == NULL || (rgb[0] != NULL && rgb[1] == NULL)
		|| (rgb[0] != NULL && rgb[1] != NULL && rgb[2] == NULL))
	{
		ft_freetab(rgb);
		ft_freetab(data);
		return ;
	}
	conf->ceil_color[0] = ft_atoi(rgb[0]);
	conf->ceil_color[1] = ft_atoi(rgb[1]);
	conf->ceil_color[2] = ft_atoi(rgb[2]);
	*parsed = 1;
	ft_freetab(rgb);
	ft_freetab(data);
}

int     		parse_config(t_conf *conf)
{
    char    	*line;
	int			ret_gnl;
	t_parsed	parsed_list;

	ret_gnl = -1;
	ft_memset(&parsed_list, 0, sizeof(t_parsed));
    while ((ret_gnl = get_next_line(conf->map_fd, &line)) >= 0)
    {
		parse_resolution(line, conf, &(parsed_list.is_resolution));
		parse_no(line, conf, &(parsed_list.is_no_texture));
		parse_so(line, conf, &(parsed_list.is_so_texture));
		parse_we(line, conf, &(parsed_list.is_we_texture));
		parse_ea(line, conf, &(parsed_list.is_ea_texture));
		parse_s(line, conf, &(parsed_list.is_s_texture));
		parse_f(line, conf, &(parsed_list.is_f_color));
		parse_c(line, conf, &(parsed_list.is_c_color));
		free(line);
		if (!ret_gnl)
			break ;
    }
    return (1);
}

void			free_config(t_conf *conf)
{
	free(conf->map_path);
	free(conf->textures.ea);
	free(conf->textures.no);
	free(conf->textures.so);
	free(conf->textures.we);
	free(conf->textures.ea);
	free(conf->textures.sprite);
	free(conf);
}