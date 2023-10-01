/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:38:47 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/29 11:31:18 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../libft/libft.h"

void	add_space(char **line, int width, t_data *data)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (width + 1));
	if (!str)
		error(1, "Memory allocation error", data, 5);
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
	int (i) = 0;
	int (j) = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (j == 0 || j == (width - 1) || i == 0 || i == (height - 1))
					return (0);
				else if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
					|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	control(t_data *data, int flag, int i, int j)
{
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E'
				|| data->map[i][j] == '1' || data->map[i][j] == '0'
				|| data->map[i][j] == ' ' || data->map[i][j] == '\n'
				|| data->map[i][j] == '\0')
			{
				if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
					|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				{
					if (flag)
						error(1, "There is more than one player!", data, 5);
					flag = 1;
				}
			}
			else
				error(1, "Wrong character on map!", data, 5);
		}
	}
	if (!flag)
		error(1, "No character on map!", data, 5);
}

void	map_check(t_data *data)
{
	int (height) = 0;
	int (width) = 0;
	int (current_width);
	while (data->map[height])
	{
		current_width = ft_strlen(data->map[height]);
		if (width < current_width)
			width = current_width;
		data->width = width;
		height++;
	}
	data->height = height;
	height = 0;
	while (data->map[height])
	{
		if ((int)ft_strlen(data->map[height]) < data->width)
			add_space(&data->map[height], data->width, data);
		height++;
	}
	if (!is_edge_full(data->map, height, data->width))
		error(1, "Not all edges are filled with wall!", data, 5);
	control(data, 0, -1, -1);
}
