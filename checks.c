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
	str = (char *)malloc(sizeof(char) * (width));
    if(!str)
	{
		perror("Memory allocation error");
		exit(0);
	}
	int (i) = 0; 
	while (i < width)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
    ft_strlcpy(str, *line, ft_strlen(*line) + 1);
	str[ft_strlen(*line)] = ' ';
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

void	control(t_data *data)
{
    int i = 0;
    int j = 0;
	int flag = 0;
    while(i < data->height)
    {
        j = 0;
        while(j < data->width)
        {
            if(data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E' || data->map[i][j] == '1' || data->map[i][j] == '0' || data->map[i][j] == ' ' || data->map[i][j] == '\n' || data->map[i][j] == '\0')
            {
				if(data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
                {	
					if(flag)
					{
						perror("There is more than one player!");
						close_window(data, 1);
					}
					flag = 1;
				}
            }
			else
			{
				perror("Wrong character on map!");
				close_window(data, 1);
			}
            j++;
        }
        i++;
    }
	if(!flag)
	{
		perror("No character on map!");
		close_window(data, 1);
	}
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
		height++;
	}
	data->height = height;
	height = 0;
	while (data->map[height])
	{
		if(ft_strlen(data->map[height]) < data->width)
			add_space(&data->map[height], data->width);//burda adresini yollamasam da olur mu
		height++;
	}
	if(!is_edge_full(data->map, height, data->width))
	{
		perror("Not all edges are filled with wall!");
		close_window(data, 1);
	}
	control(data);

}