/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:20:12 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/29 12:31:48 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	error(int i, char *str, t_data *data, int count)
{
	printf("Error: %s\n", str);
	if (data->maps)
		close_window2(count, data, i);
	close_window(data, i);
}

void	close_window3(t_data *data, int flag)
{
	int (i) = -1;
	if (data->maps->texture)
	{
		while (++i < 4)
			free(data->maps->texture[i]);
		free(data->maps->texture);
	}
	if (flag == 6)
	{
		mlx_destroy_image(data->mlx, data->maps->xpm_image[0]);
		mlx_destroy_image(data->mlx, data->maps->xpm_image[1]);
		mlx_destroy_image(data->mlx, data->maps->xpm_image[2]);
		mlx_destroy_image(data->mlx, data->maps->xpm_image[3]);
		free(data->maps->xpm_addr);
	}
}

void	close_window2(int count, t_data *data, int flag)
{
	int (i) = -1;
	if (data->maps->textures)
	{
		while (++i <= count)
		{
			free(data->maps->textures[i][1]);
			free(data->maps->textures[i][0]);
			free(data->maps->textures[i]);
		}
		free(data->maps->textures);
	}
	if (data->maps->rgb)
	{
		i = -1;
		while (++i < 3)
			free(data->maps->rgb[0][i]);
		free(data->maps->rgb[0]);
		i = -1;
		while (++i < 3)
			free(data->maps->rgb[1][i]);
		free(data->maps->rgb[1]);
		free(data->maps->rgb);
	}
	close_window3(data, flag);
}

int	close_window(t_data *data, int flag)
{
	int (i) = -1;
	if (data->map && flag != 2)
	{
		i = -1;
		while (++i < data->height)
			free(data->map[i]);
		free(data->map);
	}
	if (flag != 2 && flag != 1)
		mlx_destroy_window(data->mlx, data->win);
	if (flag == 5 || flag == 6)
	{
		mlx_destroy_image(data->mlx, data->img_p);
		mlx_destroy_image(data->mlx, data->img_w);
		mlx_destroy_image(data->mlx, data->img_r);
		mlx_destroy_image(data->mlx, data->img_rays);
		free(data->maps->xpm_image);
		free(data->maps->lengths);
	}
	if (data->maps)
		free(data->maps);
	free(data);
	exit(1);
}
/*
data = NULL;
	while (1);
*/
