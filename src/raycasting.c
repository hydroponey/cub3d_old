/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:46:06 by asimoes           #+#    #+#             */
/*   Updated: 2020/11/05 19:52:39 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void	draw_walls(t_conf *conf __attribute__((unused)))
{
	/*int x;

	printf("Player position x: %f | y: %f\n", conf->posx, conf->posy);

	x = 0;
	while (x < conf->res.x)
	{
		double cameraX = 2 * x / (double)conf->res.x - 1;
		double rayPosX = conf->posx;
		double rayPosY = conf->posy;
		double rayDirX = conf->dirx + conf->planex * cameraX;
		double rayDirY = conf->diry + conf->planey * cameraX;

		printf("cameraX: %f\n", cameraX);
		printf("rayPosX: %f\n", rayPosX);
		printf("rayPosY: %f\n", rayPosY);
		printf("rayDirX: %f\n", rayDirX);
		printf("rayDirY: %f\n", rayDirY);

		int mapX = (int)rayPosX;
		int mapY = (int)rayPosY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (conf->map[mapX][mapY] > 0) hit = 1;
		}

		if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
		else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

		//printf("perpWallDist: %f\n", perpWallDist);
		//printf("perpInt: %d\n", (int)perpWallDist);

		int perpInt = (int)perpWallDist;
		int lineHeight = abs(conf->res.y / perpInt);

		int drawStart = -lineHeight / 2 + conf->res.y / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + conf->res.y / 2;
		if (drawEnd >= conf->res.y)
			drawEnd = conf->res.y - 1;

		//printf("line %d start: %d | end: %d\n", x, drawStart, drawEnd);
		draw_line(conf, x, drawStart, drawEnd, 0x9E491C);
		x++;
	}*/
}