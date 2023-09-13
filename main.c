/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:52:03 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/08/17 15:52:07 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/libft.h"
#include "mlx/mlx.h"
#include "cub3d.h"
#include <stdio.h>
//#include <errno.h>//perror fonksiyonu, errno değişkeninin değerine dayalı olarak bir hata mesajı oluşturur ve bu mesajı stderr çıkışına yazdırır.

int	name_check(char *filename)
{
	int	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	char *format;//bu dogru bir kullanım mı
	format = &filename[len -4];
	if (ft_strncmp(format, ".cub", 4) != 0)
		return (0);
	return (1);
}

int close_window(t_data *data) 
{
	int i = 0;
    mlx_destroy_window(data->mlx, data->win);
	if (data->map) 
	{
        while (i < 10)
		{
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
	/*free(data->mlx);
	free(data->img_p);
	free(data->img_p_addr);
	free(data->img_w);
	free(data->img_w_addr);
	free(data->img_r_addr);
	free(data->img_rays);
	free(data->img_rays_addr);
	free(data->img_r);*/
	free(data);
    exit(0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_map map;

	if (ac != 2 || !name_check(av[1]))
	{
		perror("Wrong format!");
		exit(0);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
    {
        perror("Memory allocation error");
        exit(1);
    }
	data->mlx = NULL;
	data->win = NULL;
	data->img_p = NULL;
    data->img_w = NULL;
	data->px = 0;
    data->py = 0;
	data->move_left = 0;
    data->move_right = 0;
    data->move_up = 0;
    data->move_down = 0;
	data->left = 0;
	data->right = 0;
	data->pa = 0;
	data->pdx = cos(data->pa) * 2;
	data->pdy = sin(data->pa) * 2;
	map_read(av[1], &map, data);
	map_check(data);
	start_window(data);
	start(data);
	mlx_hook(data->win, 2, (1L << 0), buttons_press, data);// 2 parametresi tusa basma 3 tusu serbest bırakma
    mlx_hook(data->win, 3, (1L << 1), buttons_release, data); // (1L << 1) bit maskesi
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, &loop, data);
    mlx_loop(data->mlx);
}
