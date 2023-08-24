#include "cub3d.h"
#include "mlx/mlx.h"

int    loop(t_data *data)
{
   /* if (!data->move_left)
        data->px -= 5;
    if (!data->move_right)
        data->px += 5;
    if (!data->move_up)
        data->py -= 5;
    if (!data->move_down)
        data->py += 5;
    */mlx_clear_window(data->mlx, data->win);
    draw_map(data);
    draw_player(data);
    return 1;
}