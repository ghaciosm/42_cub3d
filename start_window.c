#include "cub3d.h"
#include "mlx/mlx.h"

void draw_player(t_player player, t_data data)
{
    void *img = mlx_new_image(data.mlx, 8, 8);
    int bits_per_pixel;
    int size_line;
    int endian;
    char *img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    
    unsigned int pixel_color = 0xFF0000;
    if (endian == 1) {
        pixel_color = ((pixel_color >> 24) & 0xFF) |       // A
                      ((pixel_color >> 8) & 0xFF00) |      // R
                      ((pixel_color << 8) & 0xFF0000) |    // G
                      ((pixel_color << 24) & 0xFF000000);  // B
    }
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int pixel_pos = (i * size_line) + (j * (bits_per_pixel / 8));
            *((unsigned int *)(img_data + pixel_pos)) = pixel_color;
        }
    }
    
    mlx_put_image_to_window(data.mlx, data.win, img, player.px - (8 / 2), player.py - (8 / 2));
    
    mlx_destroy_image(data.mlx, img);
}

void    start_window(t_data *data)
{
    t_player    player;

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
    player.px = 300, player.py = 300;
    draw_player(player, *data);
    mlx_loop(data->mlx);
}