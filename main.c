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

int	name_check(char *filename)
{
	int (len) = ft_strlen(filename);
	if (len < 4)
		return (0);
	char *(format) = &filename[len -4];
	if (ft_strncmp(format, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2 || !name_check(av[1]))
	{
		printf("%s\n", "Error: Wrong format!!!");
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
	map_check(map_read(av[1]), data);
	start_window(data);
	start(data);
	mlx_hook(data->win, 2, (1L << 0), buttons_press, data);// 2 parametresi tusa basilma olayını ifade eder
    mlx_hook(data->win, 3, (1L << 1), buttons_release, data); // (1L << 1) bit maskesi
	mlx_loop_hook(data->mlx, &loop, data);
    mlx_loop(data->mlx);
	for(int mu = 0; mu < 10; mu++)
    {
        free(data->map[mu]);
    }
	mlx_destroy_image(data->mlx, data->img_w); // Önce görüntüyü serbest bırak
	mlx_destroy_window(data->mlx, data->win);
	free(data->map);
	free(data->mlx);
	free(data);
}
