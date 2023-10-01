/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:19:05 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 17:50:47 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include "../libft/libft.h"

int	name_check(char *filename)
{
	int		len;
	char	*format;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	format = &filename[len -4];
	if (ft_strncmp(format, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	func(t_data *data)
{
	close_window2(5, data, 6);
	close_window(data, 6);
	return (0);
}

void	initialization(t_data *data)
{
	data->map = NULL;
	data->maps = NULL;
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
}

int	main(int ac, char **av)
{
	if (ac != 2 || !name_check(av[1]))
	{
		printf("Error: Wrong format!\n");
		exit(1);
	}
	t_data *(data) = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		printf("Error: Memory allocation error!\n");
		exit(1);
	}
	initialization(data);
	map_read(av[1], data, 0, -1);
	map_check(data);
	start_window(data);
	start(data);
	open_xpms(data, -1, 0, 0);
	mlx_hook(data->win, 2, (1L << 0), buttons_press, data);
	mlx_hook(data->win, 3, (1L << 1), buttons_release, data);
	mlx_hook(data->win, 17, 0, func, data);
	mlx_loop_hook(data->mlx, &loop, data);
	mlx_loop(data->mlx);
	close_window2(5, data, 6);
	close_window(data, 6);
}
