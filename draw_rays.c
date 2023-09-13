#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>

float   find_distance(float x1, float y1, float x2, float y2)
{
    return(sqrt(pow(fabs(y1 - y2), 2) + pow(fabs(x1 - x2), 2)));
}


void    continue_casting(t_data *data, t_rays *rays)
{
    float (dof) = 0;
	int (mx) = 0;
	int (my) = 0;
	while (dof < data->width)
	{
		mx = (int)rays->rx >> BITS;
		my = (int)rays->ry >> BITS;
		if (my >= 0 && mx >= 0 && my < data->height && mx < data->width && data->map[my][mx] == '1')
			break ;
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
        rays->rx = (((int)data->px >> BITS)<< BITS) -0.0001;
        rays->ry= (data->px - rays->rx) * nTan + data->py;
        rays->xo = -SQR;
        rays->yo = -rays->xo *nTan;
    }
    if (a < (PI / 2) || a > (3 * PI / 2))
    {
        rays->rx = (((int)data->px >> BITS)<< BITS) + SQR;
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
    if (a >= (2 * PI))
          a -= (2 * PI);
    if (a <= 0)
          a += (2 * PI);
    float aTan = 1/tan(a);
    if(a < PI && a > 0)
    {
        rays->ry = (((int)data->py >> BITS)<< BITS) - 0.0001;
        rays->rx= (data->py - rays->ry) * aTan + data->px;
        rays->yo = -SQR;
        rays->xo = -rays->yo *aTan;
    }
    if(a > PI)
    {
        rays->ry = (((int)data->py >> BITS)<< BITS) + SQR;
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

void draw3Dwalls(float disT, float lineH, t_data *data, float a, int i, int color)
{
    float lineDisT = disT * cos((a - data->pa));
    int lineHeight = (int)((lineH) / lineDisT);
    if(lineHeight > WINDOW_HEIGHT)
        lineHeight = WINDOW_HEIGHT;
    int y = (WINDOW_HEIGHT / 2) - (lineHeight / 2);
    while (y < (WINDOW_HEIGHT / 2) + (lineHeight / 2))
    {
        int pixel_pos = (y * WINDOW_WIDTH) + (WINDOW_WIDTH - i - 1);
        if (color)
            ((unsigned int *)data->img_r_addr)[pixel_pos] = RED;
        else
            ((unsigned int *)data->img_r_addr)[pixel_pos] = YELLOW;
        y++;
    }
}

void	draw_rays(t_data *data)
{
    t_rays    rays;
    float     a;
    float     x;
    float     y;
    float disT;
    int       i = 0;
    int     color;
    while (i < (WINDOW_HEIGHT * WINDOW_WIDTH))
    {
        if(i<((WINDOW_HEIGHT * WINDOW_WIDTH) / 2))
            ((unsigned int *)data->img_r_addr)[i] = GRAY;
        else
            ((unsigned int *)data->img_r_addr)[i] = DARK_GRAY;

        i++;
    }
    i = 0;
    while (i < ((SQR* data->height) * (SQR * data->width)))
    {
        ((unsigned int *)data->img_rays_addr)[i] = TRANSP;
        i++;
    }
    a = data->pa - (PI / 6);
    i = 0;
    while (a <= (data->pa + (PI / 6)))
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
            disT = distW;
            color = 0;
        }
        else
        {
            rays.rx = ud.rx;
            rays.ry = ud.ry;
            disT = distH;
            color = 1;
        }
        draw3Dwalls(disT,20000,data, a, i, color);
        draw_line_dda(data, (int)data->px, (int)data->py, rays.rx, rays.ry, GREEN);
        a +=  ANGLE_INTERVAL / 6.8;
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img_r, 0, 0);
}
