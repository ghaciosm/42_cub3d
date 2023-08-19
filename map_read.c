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

char	**map_read(char *filename)
{
	int		(fd) = open(filename, O_RDONLY);
	char	**str;
	char	*line;
	int		(line_count) = 0;
	int		(i) = -1;
	if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
    {
        perror("Error opening file");
        exit(1);
    }
	str = (char **)malloc(sizeof(char *) * (line_count + 1));
	while (++i < line_count)
		str[i] = get_next_line(fd);
	str[i] = NULL;
	return str;
}