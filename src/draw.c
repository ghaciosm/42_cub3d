/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:20:12 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 14:20:28 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	draw_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLAYER)
	{
		j = 0;
		while (j < PLAYER)
		{
			data->pixel_pos = (i * PLAYER) + (j);
			((unsigned int *)data->img_p_addr)[data->pixel_pos] = 0xFF0000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_p,
		(data->px - (PLAYER / 2)), data->py - (PLAYER / 2));
}

void	put_color(t_data *data, int x, int y)
{
	int (pixel_start_x) = x * SQR;
	int (pixel_start_y) = y * SQR;
	int (dy) = -1;
	int (dx) = -1;
	while (++dy < SQR)
	{
		dx = -1;
		while (++dx < SQR)
		{
			data->pixel_pos = ((pixel_start_y + dy)
					* ((SQR * data->width)) + (pixel_start_x + dx));
			if (data->map[y][x] == ' ' || data->map[y][x] == '\n')
				((unsigned int *)data->img_w_addr)[data->pixel_pos] = TRANSP;
			else if (dx == 0 || dy == 0)
				((unsigned int *)data->img_w_addr)[data->pixel_pos] = 0x404040;
			else if (data->map[y][x] == '1')
				((unsigned int *)data->img_w_addr)[data->pixel_pos] = WHITE;
			else
				((unsigned int *)data->img_w_addr)[data->pixel_pos] = BLACK;
		}
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	x = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
			put_color(data, x, y);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_w, 0, 0);
}

void	get_line(float *ty_off, int *lineH)
{
	if (*lineH > WINDOW_HEIGHT)
	{
		*ty_off = (*lineH - WINDOW_HEIGHT) / 4;
		*lineH = WINDOW_HEIGHT;
	}
}

void	draw3dwalls(t_data *data, float a, int i, float x)
{
	int (y);
	int (wall) = get_image(data->color, a);
	int (length) = (data->maps->lengths[wall] / 4.0);
	float (wall_dist) = data->dist * cos((a - data->pa));
	int (lineH) = (int)((17000) / wall_dist);
	float (ty_step) = length / (float)lineH;
	float (ty_off) = 0;
	get_line(&ty_off, &lineH);
	float (ty) = ty_step * ty_off * 2 ;
	float (tx) = (int)(x * SQR * 8);
	unsigned int *(img);
	y = (WINDOW_HEIGHT / 2) - (lineH / 2);
	while (y < ((WINDOW_HEIGHT / 2) + (lineH / 2)))
	{
		data->pixel_pos = (y * WINDOW_WIDTH) + (WINDOW_WIDTH - i - 1);
		img = (unsigned int *)data->maps->xpm_addr[wall];
		if (data->pixel_pos >= 0 && ((int)tx + (((int)ty) * length)
				< length * length))
			((unsigned int *)data->img_r_addr)[data->pixel_pos]
				= img[(int)tx + (((int)ty) * length)];
		ty += ty_step;
		y++;
	}
}
