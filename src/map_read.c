/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:24:25 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 14:20:44 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <unistd.h>

void	parse_texture_line(t_data *data, char *line, int count)
{
	data->maps->textures[count] = ft_split(line, ' ');
	if (!(ft_strncmp("NO", data->maps->textures[count][0], 5) == 0
		|| ft_strncmp("SO", data->maps->textures[count][0], 5) == 0
		|| ft_strncmp("WE", data->maps->textures[count][0], 5) == 0
		|| ft_strncmp("EA", data->maps->textures[count][0], 5) == 0
		|| ft_strncmp("F", data->maps->textures[count][0], 5) == 0
		|| ft_strncmp("C", data->maps->textures[count][0], 5) == 0))
		error(1, "Map content is wrong", data, count);
	data->maps->textures[count][1][(int)
		ft_strlen(data->maps->textures[count][1]) - 1] = '\0';
	free(line);
}

void	lin_count(char *filename, int *l_count, t_data *data)
{
	char *(line);
	int (fd) = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(data);
		printf("Error: Open file error\n");
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

char	*map_read2(t_data *data, int fd, int *c, int *line_count)
{
	char *(line) = NULL;
	int (count) = 0;
	int (i) = -1;
	data->maps->textures = (char ***)malloc(sizeof(char **) * 6);
	while (++i < (*line_count) && count < 6)
	{
		(*c)++;
		line = get_next_line(fd);
		if (line[0] == '\n')
			free(line);
		else
		{
			parse_texture_line(data, line, count);
			count++;
		}
	}
	set_texture(&(data->maps), data, fd);
	line = get_next_line(fd);
	while (line == NULL || line[0] == '\n')
	{
		(*c)++;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	map_read(char *filename, t_data *data, int c, int i)
{
	int (line_count) = 0;
	char *(line) = NULL;
	int (fd);
	lin_count(filename, &line_count, data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(1, "Error opening file", data, 0);
	data->maps = (t_map *)malloc(sizeof(t_map));
	data->maps->rgb = NULL;
	data->maps->texture = NULL;
	data->maps->textures = NULL;
	line = map_read2(data, fd, &c, &line_count);
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
	close(fd);
}
