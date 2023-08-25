#include "cub3d.h"
#include "mlx/mlx.h"

int    loop(t_data *data)
{
    buttons(data);
    key_press(data); 
    mlx_clear_window(data->mlx, data->win);
    draw_map(data);
    draw_player(data);
    return 1;
}