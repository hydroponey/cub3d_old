/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 22:43:36 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/06 01:39:14 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "./include/cub3d.h"
#include "../libft/libft.h"
#include "./include/errors.h"

void		exit_error(int err, t_conf *conf)
{
	print_error(err);
	if (conf)
		free_config(conf);
	exit(-1);
}

void		get_final_res(t_conf *conf)
{
	t_intVector		screen_res;

	mlx_get_screen_size(conf->mlx, &screen_res.x, &screen_res.y);
	if (conf->res.x > screen_res.x || conf->res.y > screen_res.y)
	{
		conf->res.x = screen_res.x;
		conf->res.y = screen_res.y;
	}
}

void		fill_image(t_conf *conf)
{
	draw_background(conf);
}

int			create_image(t_conf *conf)
{
	t_img	*img;

	img = &conf->img;
	img->ptr = mlx_new_image(conf->mlx, conf->res.x, conf->res.y);
	if (!conf->img.ptr)
		return (-1);
	img->data = (int*)mlx_get_data_addr(img->ptr, &img->bpp,
										&img->size_line, &img->endian);
	draw_background(conf);
	draw_walls(conf);
	return (0);
}

void	exit_screenshot(t_conf *conf)
{
	char		*bmp;
	int			fd;
	int			size;

	size = conf->res.x * conf->res.y * conf->img.bpp / 8 + 54;
	if (!(bmp = (char*)malloc(sizeof(char) * size)))
		exit_error(ERR_MALLOC_CUBE, conf);
	ft_bzero(bmp, size);
	ft_memcpy(&bmp[0], "BM", 2);
	fd = 54;
	ft_memcpy(&bmp[10], &fd, 4);
	fd = 40;
	ft_memcpy(&bmp[14], &fd, 4);
	ft_memcpy(&bmp[18], &conf->res.x, 4);
	fd = -conf->res.y;
	ft_memcpy(&bmp[22], &fd, 4);
	fd = 1;
	ft_memcpy(&bmp[26], &fd, 2);
	ft_memcpy(&bmp[28], &conf->img.bpp, 2);
	ft_memcpy(&bmp[54], conf->img.data, size - 54);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd = write(fd, bmp, size);
	free(bmp);
	close(fd);
	if (fd < 0)
		exit_error(ERR_MALLOC_CUBE, conf);
	else
	{
		free_config(conf);
		exit(0);
	}
}