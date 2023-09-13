/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:47:13 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/08/18 11:55:54 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "unistd.h"
#include <fcntl.h>

void	add_space(char **line, int width)
{
    char *str;
	str = (char *)malloc(sizeof(char) * (width + 1));
    if(!str)
	{
		perror("Memory allocation error");
		exit(0);
	}
	int (i) = 0; 
	while (i < width - 1)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = 0;
    ft_strlcpy(str, *line, ft_strlen(*line));
	str[ft_strlen(*line) - 1] = ' ';
    free(*line);
	*line = str;
}

int	is_edge_full(char **map, int height, int width)
{
	int	(i) = 0;
	int	(j) = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (j == 0 || j == (width - 1) || i == 0 || i == (height - 1))
				{
					return (0);
				}else if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					return (0);
				else if (map[i][j - 1] == '\0' || map[i][j + 1] == '\0' || map[i + 1][j] == '\0' || map[i - 1][j] == '\0')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	map_check(t_data *data)
{
	int	height = 0;
	int	width = 0;

	while (data->map[height])
	{
		int	current_width = ft_strlen(data->map[height]);
		if (width < current_width)
			width = current_width;
		data->width = width;
		data->height = height;
		height++;
	}
	data->width--;
	height = 0;
	while (data->map[height])
	{
		if(ft_strlen(data->map[height]) < data->width)
			add_space(&data->map[height], data->width);//burda adresini yollamasam da olur mu
		else
			data->map[height][ft_strlen(data->map[height]) - 1] = '\0';
		printf("[%s]\n",data->map[height]);
		height++;
	}
	if(!is_edge_full(data->map, height, data->width))
	{
		printf("Not all edges are filled with wall\n");
		exit(1);
	}
}