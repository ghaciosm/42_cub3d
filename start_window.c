#include "cub3d.h"
#include "mlx/mlx.h"

void    start(t_data *data)
{
    data->img_p = mlx_new_image(data->mlx, PLAYER, PLAYER);
	data->img_w = mlx_new_image(data->mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
    data->img_p_addr = mlx_get_data_addr(data->img_p, &data->bits_per_pixel, &data->size_line, &data->endian);
    int bits_per_pix;
    int size_lin;
    int endia;
    data->img_w_addr = mlx_get_data_addr(data->img_w, &bits_per_pix, &size_lin, &endia);
}

void draw_player(t_data *data)
{
    unsigned int pixel_color = 0xCDAB70;
    //pixel_matrisi oluşturuyoruz
    for (int i = 0; i < PLAYER; i++)//Bu iç içe döngü, bir PLAYERxPLAYER boyutundaki bir piksel alanına tek tek renk ataması yapmaktadır
    {
        for (int j = 0; j < PLAYER; j++)
        {
            int pixel_pos = (i * PLAYER) + (j);
            ((unsigned int *)data->img_p_addr)[pixel_pos] = pixel_color;
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img_p, data->px - (PLAYER / 2), data->py - (PLAYER / 2));
}

void draw_map(t_data *data)
{
    int map[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    unsigned int white_color = 0xFFFFFFF;
    
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (map[y][x] == 1)
            {
                int pixel_start_x = x * SQR;
                int pixel_start_y = y * SQR;
                
                for (int dy = 0; dy < SQR; dy++)
                {
                    for (int dx = 0; dx < SQR; dx++)
                    {
                        int pixel_pos = ((pixel_start_y + dy) * WINDOW_WIDTH + (pixel_start_x + dx));
                        /*if (dx == 0 || dx == SQR - 1 || dy == 0 || dy == SQR - 1)
                        {
                            ((unsigned int *)data->img_w_addr)[pixel_pos] = 0xCDAB70;
                        }*/
                        ((unsigned int *)data->img_w_addr)[pixel_pos] = white_color;
                    }
                }
            }
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img_w, 0, 0);
}


int    buttons(int key, t_data *data)
{
    if(key == 0) //A
        data->px -= 5;
    else if(key == 2) //D
        data->px += 5;
    else if(key == 13) //w
        data->py -= 5;
    else if(key == 1) //S
        data->py += 5;
    else if(key == 53)
        exit(0);
    return 0;
}

void    start_window(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
    {
        perror("Error initializing MiniLibX");
        exit(1);
    }
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    if (!data->win)
    {
        perror("Error creating window");
        exit(1);
    }
    data->px = 300, data->py = 300;
}