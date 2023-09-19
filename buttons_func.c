/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:30:37 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/19 11:30:42 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>

void	move_ud(t_data *data)
{
	if (data->move_up)
	{
		if ((int)((data->px + MOVE_X) / SQR) <= (data->width)
			&& (int)(fabs(data->py - MOVE_Y) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py - MOVE_Y) / SQR)]
			[(int)((data->px + MOVE_X) / SQR)] == '0')
		{
			data->px += (MOVE_X);
			data->py -= (MOVE_Y);
		}
	}
	if (data->move_down)
	{
		if ((int)((data->px - MOVE_X) / SQR) <= (data->width)
			&& (int)(fabs(data->py + MOVE_Y) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py + MOVE_Y) / SQR)]
			[(int)((data->px - MOVE_X) / SQR)] == '0')
		{
			data->px -= MOVE_X;
			data->py += MOVE_Y;
		}
	}
}

void	move_rl(t_data *data)
{
	if (data->move_right)
	{
		if ((int)((data->px + MOVE_Y) / SQR) <= (data->width)
			&& (int)(fabs(data->py + MOVE_X) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py + MOVE_X) / SQR)]
			[(int)((data->px + MOVE_Y) / SQR)] == '0')
		{
			data->px += MOVE_Y;
			data->py += MOVE_X;
		}
	}
	if (data->move_left)
	{
		if ((int)((data->px - MOVE_Y) / SQR) <= (data->width)
			&& (int)(fabs(data->py - MOVE_X) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py - MOVE_X) / SQR)]
			[(int)((data->px - MOVE_Y) / SQR)] == '0')
		{
			data->px -= MOVE_Y;
			data->py -= MOVE_X;
		}
	}
}

void	buttons(t_data *data)
{
	if (data->right)
	{
		data->pa -= 0.05;
		if (data->pa < 0)
			data->pa += (2 * PI);
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	if (data->left)
	{
		data->pa += 0.05;
		if (data->pa > (2 * PI))
			data->pa -= (2 * PI);
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	move_ud(data);
	move_rl(data);
}

int	buttons_press(int key, t_data *data)
{
	if (key == 0)
		data->move_left = 1;
	else if (key == 2)
		data->move_right = 1;
	else if (key == 13)
		data->move_up = 1;
	else if (key == 1)
		data->move_down = 1;
	else if (key == 123)
		data->left = 1;
	else if (key == 124)
		data->right = 1;
	else if (key == 53)
		close_window(data, 0);
	return (0);
}

int	buttons_release(int key, t_data *data)
{
	if (key == 0)
		data->move_left = 0;
	else if (key == 2)
		data->move_right = 0;
	else if (key == 13)
		data->move_up = 0;
	else if (key == 1)
		data->move_down = 0;
	else if (key == 123)
		data->left = 0;
	else if (key == 124)
		data->right = 0;
	return (0);
}
