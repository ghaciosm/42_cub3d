#include "cub3d.h"
#include "mlx/mlx.h"

void    start(t_data *data)
{
    data->img_p = mlx_new_image(data->mlx, PLAYER, PLAYER);//creates a new image in memory.
	data->img_w = mlx_new_image(data->mlx, (SQR * data->width), (SQR* data->height));
    data->img_r = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->img_rays = mlx_new_image(data->mlx, (SQR * data->width), (SQR* data->height));
    data->img_p_addr = mlx_get_data_addr(data->img_p, &data->bits_per_pixel, &data->size_line, &data->endian);
    //returns information about the created image, allowing a user to modify it later.
    //bits_per_pixel will be filled with the number of bits needed to represent a pixel color (also called the depth of the image).
    //size_line is the number of bytes used to store one line of the image in memory. This information is needed to move from one line to another in the image.
    //endian tells you wether the pixel color in the image needs to be stored in:
    //little (endian == 0), or big (endian == 1).
    int bits_per_pix;
    int size_lin;
    int endia;
    data->img_w_addr = mlx_get_data_addr(data->img_w, &bits_per_pix, &size_lin, &endia);
    data->img_r_addr = mlx_get_data_addr(data->img_r, &bits_per_pix, &size_lin,&endia);
    data->img_rays_addr = mlx_get_data_addr(data->img_rays, &bits_per_pix, &size_lin,&endia);
    //fill_map(data);
}


void draw_player(t_data *data)
{
    //pixel_matrisi oluşturuyoruz
    for (int i = 0; i < PLAYER; i++)//Bu iç içe döngü, bir PLAYERxPLAYER boyutundaki bir piksel alanına tek tek renk ataması yapmaktadır
    {
        for (int j = 0; j < PLAYER; j++)
        {
            int pixel_pos = (i * PLAYER) + (j);
            ((unsigned int *)data->img_p_addr)[pixel_pos] = 0xFF0000;
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img_p, (data->px - (PLAYER / 2)) , data->py - (PLAYER / 2));
}

void draw_map(t_data *data)
{
    int y = 0;
    int x = 0;
    //printf("%d\n", data->height);
    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            int pixel_start_x = x * SQR;
            int pixel_start_y = y * SQR;
            int dy = 0;
            int dx= 0;
                
            while (dy < SQR)
            {
                dx = 0;
                while (dx < SQR)
                {
                    int pixel_pos = ((pixel_start_y + dy) * ((SQR * data->width)) + (pixel_start_x + dx));
                    if(data->map[y][x] == ' ' || data->map[y][x] == '\n')
                        ((unsigned int *)data->img_w_addr)[pixel_pos] = TRANSP;
                    else if (dx == 0  || dy == 0 )
                        ((unsigned int *)data->img_w_addr)[pixel_pos] = 0x404040;
                    else if (data->map[y][x] == '1')
                        ((unsigned int *)data->img_w_addr)[pixel_pos] = 0x00FFFFFF;
                     else
                     {
                        ((unsigned int *)data->img_w_addr)[pixel_pos] = 0x00000000;
                     }
                    dx++;
                }
                dy++;
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img_w, 0, 0);
}

void    find_player(t_data *data)
{
    int i = 0;
    int j = 0;
    while(i < data->height)
    {
        j = 0;
        while(j < data->width)
        {
            if(data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
            {
                data->px = (j * SQR) - SQR / 2;
                data->py = (i * SQR) - SQR / 2;
            }
            j++;
        }
        i++;
    }
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
    find_player(data);
}