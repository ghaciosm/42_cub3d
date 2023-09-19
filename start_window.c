/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:23:23 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/19 12:23:27 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>

void	start(t_data *data)
{
	int	bits_per_pix;
	int	size_lin;
	int	endia;

	data->img_p = mlx_new_image(data->mlx, PLAYER, PLAYER);
	data->img_w = mlx_new_image(data->mlx,
			(SQR * data->width), (SQR * data->height));
	data->img_r = mlx_new_image(data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img_rays = mlx_new_image(data->mlx,
			(SQR * data->width), (SQR * data->height));
	data->img_p_addr = mlx_get_data_addr(data->img_p,
			&bits_per_pix, &size_lin, &endia);
	data->img_w_addr = mlx_get_data_addr(data->img_w,
			&bits_per_pix, &size_lin, &endia);
	data->img_r_addr = mlx_get_data_addr(data->img_r,
			&bits_per_pix, &size_lin, &endia);
	data->img_rays_addr = mlx_get_data_addr(data->img_rays,
			&bits_per_pix, &size_lin, &endia);
}

void	find_direction(char dir, t_data *data)
{
	if (dir == 'N')
		data->pa = (PI / 2);
	else if (dir == 'S')
		data->pa = (3 * PI) / 2;
	else if (dir == 'E')
		data->pa = 0;
	if (dir == 'W')
		data->pa = PI;
	data->pdx = cos(data->pa) * 2;
	data->pdy = sin(data->pa) * 2;
}

void	find_player(t_data *data)
{
	int (i) = 0;
	int (j) = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				find_direction(data->map[i][j], data);
				data->px = (j * SQR) + (SQR / 2);
				data->py = (i * SQR) + (SQR / 2);
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	start_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		perror("Error initializing MiniLibX");
		exit(1);
	}
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!data->win)
	{
		perror("Error creating window");
		exit(1);
	}
	find_player(data);
}
