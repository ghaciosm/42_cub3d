/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:46:15 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 14:20:22 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <math.h>
#include "../mlx/mlx.h"

void	continue_casting(t_data *data, t_rays *rays)
{
	float (dof) = 0;
	int (mx) = 0;
	int (my) = 0;
	while (dof < data->width)
	{
		mx = (int)rays->rx >> BITS;
		my = (int)rays->ry >> BITS;
		if (my >= 0 && mx >= 0 && my < data->height
			&& mx < data->width && data->map[my][mx] == '1')
			break ;
		rays->rx += rays->xo;
		rays->ry += rays->yo;
		dof += 1;
	}
}

void	right_left(t_data *data, t_rays *rays, float a, float *distV)
{
	float (nTan) = tan(a);
	if (a > (PI / 2) && a < (3 * PI / 2))
	{
		rays->rx = (((int)data->px >> BITS) << BITS) - 0.0001;
		rays->ry = (data->px - rays->rx) * nTan + data->py;
		rays->xo = -SQR;
		rays->yo = -rays->xo * nTan;
	}
	if (a < (PI / 2) || a > (3 * PI / 2))
	{
		rays->rx = (((int)data->px >> BITS) << BITS) + SQR;
		rays->ry = (data->px - rays->rx) * nTan + data->py;
		rays->xo = SQR;
		rays->yo = -rays->xo * nTan;
	}
	if (a == (PI / 2) || a == (3 * PI / 2))
	{
		rays->rx = data->px;
		rays->ry = data->py;
		return ;
	}
	continue_casting(data, rays);
	(*distV) = find_distance(rays->rx, rays->ry, data->px, data->py);
}

void	up_down(t_data *data, t_rays *rays, float a, float *distH)
{
	normalize_angle(&a);
	float (aTan) = 1 / tan(a);
	if (a < PI && a > 0)
	{
		rays->ry = (((int)data->py >> BITS) << BITS) - 0.0001;
		rays->rx = (data->py - rays->ry) * aTan + data->px;
		rays->yo = -SQR;
		rays->xo = -rays->yo * aTan;
	}
	if (a > PI)
	{
		rays->ry = (((int)data->py >> BITS) << BITS) + SQR;
		rays->rx = (data->py - rays->ry) * aTan + data->px;
		rays->yo = SQR;
		rays->xo = -rays->yo * aTan;
	}
	if ((a == 0) || a == PI)
	{
		rays->rx = data->px;
		rays->ry = data->py;
		return ;
	}
	continue_casting(data, rays);
	(*distH) = find_distance(rays->rx, rays->ry, data->px, data->py);
}

//distH = horizantal
//distV = vertical
void	draw_rays2(t_data *data, float *a, int i, t_rays *rays)
{
	float (distV) = 10000;
	float (distH) = 10000;
	t_rays (ud);
	t_rays (rl);
	up_down(data, &ud, *a, &distH);
	right_left(data, &rl, *a, &distV);
	if (distV < distH)
	{
		rays->rx = rl.rx;
		rays->ry = rl.ry;
		data->dist = distV;
		data->color = 0;
		draw3dwalls(data, *a, i, rays->ry);
	}
	else
	{
		rays->rx = ud.rx;
		rays->ry = ud.ry;
		data->dist = distH;
		data->color = 1;
		draw3dwalls(data, *a, i, rays->rx);
	}
	draw_line_dda(data, (int)data->px, (int)data->py, rays);
	(*a) += ANGLE_INTERVAL / 10.5;
}

void	draw_rays(t_data *data)
{
	t_rays (rays);
	float (a);
	int (i) = -1;
	data->maps->c_color = set_colors(data, 1);
	data->maps->f_color = set_colors(data, 0);
	while (++i < (WINDOW_HEIGHT * WINDOW_WIDTH))
	{
		if (i < ((WINDOW_HEIGHT * WINDOW_WIDTH) / 2))
			((unsigned int *)data->img_r_addr)[i] = data->maps->c_color;
		else
			((unsigned int *)data->img_r_addr)[i] = data->maps->f_color;
	}
	i = -1;
	while (++i < ((SQR * data->height) * (SQR * data->width)))
		((unsigned int *)data->img_rays_addr)[i] = TRANSP;
	a = data->pa - (PI / 6);
	i = 0;
	while (a <= (data->pa + (PI / 6)))
	{
		draw_rays2(data, &a, i, &rays);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_r, 0, 0);
}
