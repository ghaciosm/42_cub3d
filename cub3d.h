/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:46:56 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/08/18 11:46:58 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# define	WINDOW_WIDTH  500
# define	WINDOW_HEIGHT 500

#include "libft/libft.h"
#include "next_line/get_line.h"

typedef struct s_data
{
	void *mlx;
	void *win;
} t_data;

typedef struct s_player
{
	float	px;
	float	py;
}	t_player;

char    **map_read(char *filename);
void	map_check(char **map);
void    start_window(t_data *data);


#endif
