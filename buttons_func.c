#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>

void draw_line_dda(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); // Adım sayısı, x veya y eğimi büyük olanı alır

    float x_inc = (float)dx / steps; // X koordinatındaki adım büyüklüğü
    float y_inc = (float)dy / steps; // Y koordinatındaki adım büyüklüğü

    float x = (float)x1; // Başlangıç x koordinatı
    float y = (float)y1; // Başlangıç y koordinatı

    for (int i = 0; i < steps; i++)
    {
        int pixel_x = (int)x;
        int pixel_y = (int)y;
        if (pixel_x >= 0 && pixel_x < (SQR * data->width) && pixel_y >= 0 && pixel_y < (SQR * data->height))
        {
            int pixel_pos = (pixel_y * (SQR * data->width)) + pixel_x;
            ((unsigned int *)data->img_rays_addr)[pixel_pos] = color;
            //mlx_pixel_put(data->mlx, data->win, pixel_x, pixel_y, color);
        }

        x += x_inc; // X koordinatını ilerlet
        y += y_inc; // Y koordinatını ilerlet
    }
}

void    buttons(t_data *data)
{
    if (data->right)
    {
        data->pa -= 0.05;
        if(data->pa < 0)
            data->pa += (2 * PI);
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;
    }
    if (data->left)
    {
        data->pa += 0.05;
        if(data->pa > (2* PI))
            data->pa -= (2 * PI);
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;
    }
    if (data->move_up)
    {
        if ((int)((data->px + (data->pdx)) / SQR) <= (data->width) && (int)(fabs(data->py - (data->pdy)) / SQR) <= (data->height) && data->map[(int)(fabs(data->py - (data->pdy)) / SQR)][(int)((data->px + (data->pdx)) / SQR)] == '0')
        {
            data->px += (data->pdx / 2.0);
            data->py -= (data->pdy / 2.0);
        }
    }
    if (data->move_down)
    {
        if ((int)((data->px - (data->pdx)) / SQR) <= (data->width) && (int)(fabs(data->py + (data->pdy)) / SQR) <= (data->height) && data->map[(int)(fabs(data->py + (data->pdy)) / SQR)][(int)((data->px - (data->pdx)) / SQR)] == '0')
        {
            data->px -= (data->pdx / 2.0);
            data->py += (data->pdy / 2.0);
        }
    }
    if (data->move_right)
    {
        if ((int)((data->px + (data->pdy)) / SQR) <= (data->width) && (int)(fabs(data->py + (data->pdx)) / SQR) <= (data->height) && data->map[(int)(fabs(data->py + (data->pdx)) / SQR)][(int)((data->px + (data->pdy)) / SQR)] == '0')
        {
            data->px += (data->pdy / 2.0);
            data->py += (data->pdx / 2.0);
        }
    }
    if (data->move_left)
    {
        if ((int)((data->px - (data->pdy)) / SQR) <= (data->width) && (int)(fabs(data->py - (data->pdx)) / SQR) <= (data->height) && data->map[(int)(fabs(data->py - (data->pdx)) / SQR)][(int)((data->px - (data->pdy)) / SQR)] == '0')
        {
            data->px -= (data->pdy / 2.0);
            data->py -= (data->pdx / 2.0);
        }
    }
}

int buttons_press(int key, t_data *data)//tusa basildiginde
{
    if (key == 0) // A
        data->move_left = 1;
    else if (key == 2) // D
        data->move_right = 1;
    else if (key == 13) // W
        data->move_up = 1;
    else if (key == 1) // S
        data->move_down = 1;
    else if (key == 123)//left
        data->left = 1;
    else if (key == 124)//right
        data->right = 1;
    else if (key == 53) // ESC
        close_window(data);
    return 0;
}

int buttons_release(int key, t_data *data)//tus birakildiginde
{
    if (key == 0)
        data->move_left = 0;
    else if (key == 2)
        data->move_right = 0;
    else if (key == 13)
        data->move_up = 0;
    else if (key == 1)
        data->move_down = 0;
    else if (key == 123)//left
        data->left = 0;
    else if (key == 124)//right
        data->right = 0;
    return 0;
}