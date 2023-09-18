/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                           :+:      :+:    :+:   */
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

void	parse_texture_line(t_map *map, char *line, int count)
{
	map->textures[count] = ft_split(line, ' ');
}

void	lin_count(char *filename, int *l_count)
{	
	int		fd = open(filename, O_RDONLY);
	char	*line;
	if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }
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

char	**map_read(char *filename, t_map *map, t_data *data)
{
	map->textures = (char ***)malloc(sizeof(char **) * 6);
	char	**str;
	int		count = 0, c = 0;
	int		line_count = 0;
	int		(i) = -1;
	char	*line = NULL;
	int fd;

	lin_count(filename, &line_count);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }
	while (++i < line_count && count < 6)
	{
		c++;
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
	int j = 0;
	data->map = (char **)malloc(sizeof(char *) * ((line_count - c)));
	data->map[0] = get_next_line(fd);
	while(data->map[0][0] == '\n' || data->map[0] == NULL)
	{
		free(data->map[0]);
		data->map[0] = get_next_line(fd);
	}
	i = 0;
	if(data->map[i][ft_strlen(data->map[i]) - 1] == '\n')
		data->map[i][ft_strlen(data->map[i]) - 1] = 0;
	while (++i < line_count - c - 1)
	{
		data->map[i] = get_next_line(fd);
		if(data->map[i][ft_strlen(data->map[i]) - 1] == '\n')
			data->map[i][ft_strlen(data->map[i]) - 1] = 0;
	}
	data->map[i] = NULL;
	return data->map;
}