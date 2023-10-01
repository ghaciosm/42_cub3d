/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xpm_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:52:39 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/20 14:20:32 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include "../libft/libft.h"

// NO SO WE ES
int	get_image(int direction, float pa)
{
	if (direction)
	{
		if (pa >= 0 && pa <= PI)
			return (0);
		else
			return (1);
	}
	else
	{
		if (pa <= (3 * PI / 2) && pa >= PI / 2)
			return (2);
		else
			return (3);
	}
}

int	set_colors(t_data *data, int i)
{
	int (r) = ft_atoi(data->maps->rgb[i][0]);
	int (g) = ft_atoi(data->maps->rgb[i][1]);
	int (b) = ft_atoi(data->maps->rgb[i][2]);
	return ((r << 16) | (g << 8) | b);
}

void	open_xpms(t_data *data, int x, int y, int fd)
{
	data->maps->xpm_image = (void **)malloc(sizeof(void *) * 4);
	while (++x < 4)
	{
		fd = open(data->maps->texture[x], O_RDONLY);
		if (fd < 0)
			error(5, "Xpm file could not be opened", data, 5);
		close(fd);
	}
	data->maps->xpm_image[0] = mlx_xpm_file_to_image(data->mlx,
			data->maps->texture[0], &x, &y);
	data->maps->xpm_image[1] = mlx_xpm_file_to_image(data->mlx,
			data->maps->texture[1], &x, &y);
	data->maps->xpm_image[2] = mlx_xpm_file_to_image(data->mlx,
			data->maps->texture[2], &x, &y);
	data->maps->xpm_image[3] = mlx_xpm_file_to_image(data->mlx,
			data->maps->texture[3], &x, &y);
	data->maps->xpm_addr = (char **)malloc(sizeof(char *) * 4);
	data->maps->xpm_addr[0] = mlx_get_data_addr(data->maps->xpm_image[0],
			&x, &data->maps->lengths[0], &x);
	data->maps->xpm_addr[1] = mlx_get_data_addr(data->maps->xpm_image[1],
			&x, &data->maps->lengths[1], &x);
	data->maps->xpm_addr[2] = mlx_get_data_addr(data->maps->xpm_image[2], &x,
			&data->maps->lengths[2], &x);
	data->maps->xpm_addr[3] = mlx_get_data_addr(data->maps->xpm_image[3], &x,
			&data->maps->lengths[3], &x);
}

void	set_texture2(t_data *data, int fd, char *str, int i)
{
	if (i == 6)
	{
		close(fd);
		error(2, str, data, 5);
	}
	else
		close(fd);
}

void	set_texture(t_map **map, t_data *data, int fd)
{
	(*map)->rgb = (char ***)malloc(sizeof(char **) * 2);
	(*map)->texture = (char **)malloc(sizeof(char *) * 4);
	int (i) = -1;
	while (++i < 6)
	{
		if (ft_strncmp("NO", (*map)->textures[i][0], 4) == 0)
			(*map)->texture[0] = ft_strdup((*map)->textures[i][1]);
		else if (ft_strncmp("SO", (*map)->textures[i][0], 4) == 0)
			(*map)->texture[1] = ft_strdup((*map)->textures[i][1]);
		else if (ft_strncmp("WE", (*map)->textures[i][0], 4) == 0)
			(*map)->texture[2] = ft_strdup((*map)->textures[i][1]);
		else if (ft_strncmp("EA", (*map)->textures[i][0], 4) == 0)
			(*map)->texture[3] = ft_strdup((*map)->textures[i][1]);
		else if (ft_strncmp("F", (*map)->textures[i][0], 2) == 0)
			(*map)->rgb[0] = ft_split((*map)->textures[i][1], ',');
		else if (ft_strncmp("C", (*map)->textures[i][0], 2) == 0)
			(*map)->rgb[1] = ft_split((*map)->textures[i][1], ',');
		else
			set_texture2(data, fd, "Map content is wrong", i);
	}
}
