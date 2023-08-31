#include "cub3d.h"
#include <math.h>

/*void    find_wall_x_y(float *x, float *y,t_data *data, float a)
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
}*/
float   find_distance(float x1, float y1, float x2, float y2)
{
    return(sqrt(pow(fabs(y1 - y2), 2) + pow(fabs(x1 - x2), 2)));
}


void    continue_casting(t_data *data, t_rays *rays)
{
    float (dof) = 0;
	int (mx) = 0;
	int (my) = 0;
	while (dof < 6 )
	{
		mx = (int)rays->rx >> 6;
		my = (int)rays->ry >> 6;
		if (my >= 0 && mx >= 0 && my < 10 && mx < 10 && data->map[my][mx] == '1')
		{
           // *dist = distance(data, rays);
			break ;
		}
		rays->rx += rays->xo;
		rays->ry += rays->yo;
		dof += 1;
	}
}

void    right_left(t_data *data,t_rays *rays, float a, float *distW)
{
    float nTan = tan(a);
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
    (*distW) = find_distance(rays->rx, rays->ry, data->px, data->py);
}

void    up_down(t_data *data, t_rays *rays, float a, float *distH)
{
    // a += PI;
    // if(a >= (2 * PI))
    //     a -= (2 * PI);
    float aTan = 1/tan(a);
    if(a < PI && a > 0)
    {
        rays->ry = (((int)data->py >> 6)<< 6) -0.0001;
        rays->rx= (data->py - rays->ry) * aTan + data->px;
        rays->yo = -SQR;
        rays->xo = -rays->yo *aTan;
    }
    if(a > PI)
    {
        rays->ry = (((int)data->py >> 6)<< 6) + SQR;
        rays->rx= (data->py - rays->ry) * aTan + data->px;
        rays->yo = SQR;
        rays->xo = -rays->yo *aTan;
    }
    if((a == 0) || a == PI)
    {
        rays->rx = data->px;
        rays->ry = data->py;
        return;
    }
    continue_casting(data, rays);
    (*distH) = find_distance(rays->rx, rays->ry, data->px, data->py);
}

void	draw_rays(t_data *data)
{
    t_rays    rays;
    float     a;
    float     x;
    float     y;

    a = data->pa - (PI / 3);
    if(a < 0)
        a += (2 * PI);
    printf("%f\n",a);
    while (a <= (data->pa + ((PI / 3))))
    {
        float   distW = 10000;
        float   distH = 10000;
        t_rays  ud,rl;

        up_down(data, &ud, a, &distH);
        right_left(data, &rl, a, &distW);
        if(distW < distH)
        {
            rays.rx = rl.rx;
            rays.ry = rl.ry;
        }
        else
        {
            rays.rx = ud.rx;
            rays.ry = ud.ry;
        }
        draw_line_dda(data, (int)data->px, (int)data->py, rays.rx, rays.ry, GREEN);
        a +=  ANGLE_INTERVAL;
        if(a > (2 * PI))
            a -= (2 * PI);
    }
}
