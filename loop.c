#include "cub3d.h"
#include "mlx/mlx.h"

int    loop(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    draw_rays(data);
    draw_map(data);
    draw_player(data);
    buttons(data);
    return 1;
}