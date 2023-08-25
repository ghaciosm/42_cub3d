#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>

void draw_line(t_data *data, int x, int y, int length, float angle, int color)
{
    float endX = x + length * cos(angle);
    float endY = y - length * sin(angle);

    int steps = 10 ;// 4 piksel adımlarla çizelim

    for (int i = 0; i < steps; i++)
    {
        int pixel_x = x + i * cos(angle) * 4;
        int pixel_y = y - i * sin(angle) * 4;

        if (pixel_x >= 0 && pixel_x < WINDOW_WIDTH && pixel_y >= 0 && pixel_y < WINDOW_HEIGHT)
            mlx_pixel_put(data->mlx, data->win, pixel_x, pixel_y, color);
    }
}

void    buttons(t_data *data)
{
    if (data->left)
    {
        data->pa -= 0.1;
        /*if(data->pa < 0)
            data->pa += 2 *PI;
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;*/
    }
    if (data->right)
    {
        data->pa += 0.1;
        /*if((data->pa) > (2.0 * PI))
            data->pa -= 2.0 *PI;
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;*/
    }
    draw_line(data, data->px, data->py, 4, data->pa, 0x00FF00);
}

void    key_press(t_data *data)
{
    if (data->move_left)
        data->px -= 2;
    if (data->move_right)
        data->px += 2;
    if (data->move_up)
        data->py -= 2;
    if (data->move_down)
        data->py += 2; 
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
        exit(0);
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