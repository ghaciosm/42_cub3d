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
        yo = -64;
        xo = -yo *aTan;
    }
    if(a < PI)
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
        dof = 8;
    }
    while(dof < 8)
    {
        mx = (int)(rx) >> 6;
        my = (int)(ry) >> 6;
        if(data->map[my][mx] == 1)
        {
            dof = 8;
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

void	draw_rays(t_data *data)
{
    float   a;
    float     x;
    float     y;
    
    a = data->pa - (PI / 8.33);
    while (a < (data->pa + (PI / 8.33)))
    {
        // float endX = data->px + (40 * cos(a));
        // float endY = data->py - (40 * sin(a));
        // draw_line_dda(data, (int)data->px, (int)data->py, endX, endY, GREEN);

        find_wall_x_y(&x, &y, data, a);
        draw_line_dda(data, (int)data->px, (int)data->py, x, y, GREEN);
        a = a + ANGLE_INTERVAL;
    }
}
