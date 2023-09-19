/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:20:12 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/19 13:20:21 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
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

void	draw3dwalls(float disT, t_data *data, float a, int i)
{
	int (y);
	float (lineDisT) = disT * cos((a - data->pa));
	int (lineHeight) = (int)((17000) / lineDisT);
	if (lineHeight > WINDOW_HEIGHT)
		lineHeight = WINDOW_HEIGHT;
	y = (WINDOW_HEIGHT / 2) - (lineHeight / 2);
	while (y < (WINDOW_HEIGHT / 2) + (lineHeight / 2))
	{
		data->pixel_pos = (y * WINDOW_WIDTH) + (WINDOW_WIDTH - i - 1);
		if (data->color)
			((unsigned int *)data->img_r_addr)[data->pixel_pos] = RED;
		else
			((unsigned int *)data->img_r_addr)[data->pixel_pos] = YELLOW;
		y++;
	}
}
