#include "cub3d.h"
#include <math.h>

void    find_wall_x_y(float *x, float *y,t_data *data, float a)
{
    float xo, yo, rx, ry;
    int dof = 0;
    int mx, my, mp;
    float aTan = -1/tan(a);
    if(a > PI)
    {
        ry = (((int)data->py >> 6)<< 6) -0.0001;
        rx= (data->py - ry) * aTan + data->px; 
        yo = -SQR;
        xo = -yo *aTan;
    }
    if(a < PI && a > 0)
    {
        ry = (((int)data->py >> 6)<< 6) + 64;
        rx= (data->py - ry) * aTan + data->px;
        yo = 64;
        xo = -yo *aTan;
    }
    if((a == 0) || a== PI)
    {
        rx = data->px;
        ry = data->py;
        dof = 10;
    }
    while(dof < 10)
    {
        mx = (int)(rx) >> 6;
        my = (int)(ry) >> 6;
        if(my >= 0 && mx >= 0 && my < 10 && mx < 10 && data->map[my][mx] == '1')
        {
            dof = 10;
        }
        else
        {
            rx += xo;
            ry += yo;
            dof += 1;
        }
    }
    *x = rx;
    *y = ry;
}

void    continue_casting(t_data *data, t_rays *rays)
{
    float (dof) = 0;
	int (mx) = 0;
	int (my) = 0;
	while (dof < 10 + 1)
	{
		mx = (int)rays->rx >> 6;
		my = (int)rays->ry >> 6;
		if (my >= 0 && mx >= 0 && my < 10 && mx < 10 + 1 && data->map[my][mx] == '1')
		{
			break ;
		}
		rays->rx += rays->xo;
		rays->ry += rays->yo;
		dof += 1;
	}
}

void    right_left(t_data *data,t_rays *rays, int a)
{
    float nTan = -tan(a);
    if (a > (PI / 2) && a < (3 * PI / 2))
    {
        rays->rx = (((int)data->px >> 6)<< 6) -0.0001;
        rays->ry= (data->px - rays->rx) * nTan + data->py; 
        rays->xo = -SQR;
        rays->yo = -rays->xo *nTan;
    }
    if (a < (PI / 2) || a > (3 * PI / 2))
    {
        rays->rx = (((int)data->px >> 6)<< 6) + SQR;
        rays->ry= (data->px - rays->rx) * nTan + data->py;
        rays->xo = SQR;
        rays->yo = -rays->xo *nTan;
    }
    if (a == (PI / 2) || a == (3 * PI / 2))
    {
        rays->rx = data->px;
        rays->ry = data->py;
        return;
    }
    continue_casting(data, rays);
}

void    up_down(t_data *data, t_rays *rays, int a)
{
    float aTan = -1/tan(a);
    if(a > PI)
    {
        rays->ry = (((int)data->py >> 6)<< 6) -0.0001;
        rays->rx= (data->py - rays->ry) * aTan + data->px; 
        rays->yo = -SQR;
        rays->xo = -rays->yo *aTan;
    }
    if(a < PI && a > 0)
    {
        rays->ry = (((int)data->py >> 6)<< 6) + SQR;
        rays->rx= (data->py - rays->ry) * aTan + data->px;
        rays->yo = SQR;
        rays->xo = -rays->yo *aTan;
    }
    if((a == 0) || a== PI)
    {
        rays->rx = data->px;
        rays->ry = data->py;
        return;
    }
    continue_casting(data, rays);
}

void	draw_rays(t_data *data)
{
    t_rays    rays;
    float     a;
    float     x;
    float     y;
    
    a = data->pa - (PI / 8.33);
    while (a < (data->pa + (PI / 8.33)))
    {
        // float endX = data->px + (40 * cos(a));
        // float endY = data->py - (40 * sin(a));
        // draw_line_dda(data, (int)data->px, (int)data->py, endX, endY, GREEN);

        //find_wall_x_y(&x, &y, data, a);
        up_down(data, &rays, a);
        right_left(data, &rays, a);
        draw_line_dda(data, (int)data->px, (int)data->py, x, y, GREEN);
        a = a + ANGLE_INTERVAL;
    }
}
