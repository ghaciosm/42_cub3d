/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:31:21 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 14:20:15 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>
#include "../libft/libft.h"

void	normalize_angle(float *a)
{
	if ((*a) >= (2 * PI))
		(*a) -= (2 * PI);
	if ((*a) <= 0)
		(*a) += (2 * PI);
}

float	find_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(fabs(y1 - y2), 2) + pow(fabs(x1 - x2), 2)));
}

void	draw_line_dda(t_data *data, int x1, int y1, t_rays *rays)
{
	int (dx) = rays->rx - x1;
	int (dy) = rays->ry - y1;
	int (steps);
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	float (x_inc) = (float)dx / steps;
	float (y_inc) = (float)dy / steps;
	float (x) = (float)x1;
	float (y) = (float)y1;
	int (i) = -1;
	while (++i < steps)
	{
		dx = ((int)x);
		dy = ((int)y);
		if (dx >= 0 && dx < (SQR * data->width)
			&& dy >= 0 && dy < (SQR * data->height))
		{
			data->pixel_pos = (dy * (SQR * data->width)) + dx;
			((unsigned int *)data->img_rays_addr)[data->pixel_pos] = GREEN;
		}
		x += x_inc;
		y += y_inc;
	}
}
