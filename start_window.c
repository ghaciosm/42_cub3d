#include "cub3d.h"
#include "mlx/mlx.h"

void draw_player(t_data *data)
{
    void *img = mlx_new_image(data->mlx, 8, 8);
    int bits_per_pixel;
    int size_line;
    int endian;
    char *img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    unsigned int pixel_color = 0xFF0000;
    //pixel_matrisi oluşturuyoruz
    for (int i = 0; i < 8; i++)//Bu iç içe döngü, bir 8x8 boyutundaki bir piksel alanına tek tek renk ataması yapmaktadır
    {
        for (int j = 0; j < 8; j++)
        {
            int pixel_pos = (i * size_line) + (j * (bits_per_pixel / 8));
            *((unsigned int *)(img_data + pixel_pos)) = pixel_color;
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, img, data->px - (8 / 2), data->py - (8 / 2));
    mlx_destroy_image(data->mlx, img);
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
    int bits_per_pixel;
    int size_line;
    int endian;
    void *img = mlx_new_image(data->mlx, 8, 8);
    char *img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    unsigned int white_color = 0xFFFFFFF;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (map[y][x] == 1) {
                for (int dy = 0; dy < 32; dy++) {
                    for (int dx = 0; dx < 32; dx++) {
                        int pixel_pos = ((y * 32 + dy) * 10 + (x * 32 + dx)) * 4;
                        *((unsigned int *)(img_data + pixel_pos)) = white_color;
                    }
                }
            }
        }
    }
    printf("aaaa\n");
    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    printf("bbbbbaaaa\n");
    mlx_destroy_image(data->mlx, img);
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