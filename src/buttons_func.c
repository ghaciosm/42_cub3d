/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:30:37 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 14:20:01 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>

void	move_ud(t_data *data)
{
	if (data->move_up)
	{
		if ((int)((data->px + (data->pdx / 5.0)) / SQR) <= (data->width)
			&& (int)(fabs(data->py - (data->pdy / 5.0)) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py - (data->pdy / 5.0)) / SQR)]
			[(int)((data->px + (data->pdx / 5.0)) / SQR)] == '0')
		{
			data->px += ((data->pdx / 5.0));
			data->py -= ((data->pdy / 5.0));
		}
	}
	if (data->move_down)
	{
		if ((int)((data->px - (data->pdx / 5.0)) / SQR) <= (data->width)
			&& (int)(fabs(data->py + (data->pdy / 5.0)) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py + (data->pdy / 5.0)) / SQR)]
			[(int)((data->px - (data->pdx / 5.0)) / SQR)] == '0')
		{
			data->px -= (data->pdx / 5.0);
			data->py += (data->pdy / 5.0);
		}
	}
}

void	move_rl(t_data *data)
{
	if (data->move_right)
	{
		if ((int)((data->px + (data->pdy / 5.0)) / SQR) <= (data->width)
			&& (int)(fabs(data->py + (data->pdx / 5.0)) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py + (data->pdx / 5.0)) / SQR)]
			[(int)((data->px + (data->pdy / 5.0)) / SQR)] == '0')
		{
			data->px += (data->pdy / 5.0);
			data->py += (data->pdx / 5.0);
		}
	}
	if (data->move_left)
	{
		if ((int)((data->px - (data->pdy / 5.0)) / SQR) <= (data->width)
			&& (int)(fabs(data->py - (data->pdx / 5.0)) / SQR) <= (data->height)
			&& data->map[(int)(fabs(data->py - (data->pdx / 5.0)) / SQR)]
			[(int)((data->px - (data->pdy / 5.0)) / SQR)] == '0')
		{
			data->px -= (data->pdy / 5.0);
			data->py -= (data->pdx / 5.0);
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
	{
		close_window2(5, data, 6);
		close_window(data, 6);
	}
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
