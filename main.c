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

//#include <mlx.h>
//#include <mat.h>
#include "libft/libft.h"
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
	t_data	*data = (t_data *)malloc(sizeof(t_data));

	if (ac != 2 || !name_check(av[1]))
	{
		printf("%s\n", "Error: Wrong format!!!");
		exit(0);
	}
	map_check(map_read(av[1]));
	start_window(data);
}
