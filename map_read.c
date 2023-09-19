/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:24:25 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/19 13:24:27 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "unistd.h"
#include <fcntl.h>

void	parse_texture_line(t_map *map, char *line, int count)
{
	map->textures[count] = ft_split(line, ' ');
}

void	lin_count(char *filename, int *l_count, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(1, "Error opening file", data);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		(*l_count)++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

char	*map_read2(t_map *map, int fd, int *c, int *line_count)
{
	char *(line) = NULL;
	int (count) = 0;
	int (i) = -1;
	while (++i < (*line_count) && count < 6)
	{
		(*c)++;
		line = get_next_line(fd);
		if (line[0] == '\n')
			free(line);
		else
		{
			parse_texture_line(map, line, count);
			free(line);
			count++;
		}
	}
	line = get_next_line(fd);
	while (line == NULL || line[0] == '\n')
	{
		(*c)++;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	map_read(char *filename, t_map *map, t_data *data)
{
	char **(str);
	int (c) = 0;
	int (line_count) = 0;
	int (i) = -1;
	char *(line) = NULL;
	int (fd);
	map->textures = (char ***)malloc(sizeof(char **) * 6);
	lin_count(filename, &line_count, data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(1, "Error opening file", data);
	line = map_read2(map, fd, &c, &line_count);
	data->map = (char **)malloc(sizeof(char *) * ((line_count - c + 1)));
	i = 0;
	data->map[0] = line;
	if (data->map[0][ft_strlen(data->map[0]) - 1] == '\n')
		data->map[0][ft_strlen(data->map[0]) - 1] = 0;
	while (++i < (line_count - c))
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i][ft_strlen(data->map[i]) - 1] == '\n')
			data->map[i][ft_strlen(data->map[i]) - 1] = 0;
	}
	data->map[i] = NULL;
}
