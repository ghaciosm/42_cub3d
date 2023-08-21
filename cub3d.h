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

# define	WINDOW_WIDTH  700
# define	WINDOW_HEIGHT 700

#include "libft/libft.h"
#include "next_line/get_line.h"

typedef struct s_data
{
	void *mlx;
	void *win;

	float px;
	float py;
} t_data;

/*stypedef struct s_player
{
	float	px;
	float	py;
}	t_player;*/

char    **map_read(char *filename);
void	map_check(char **map);
void    start_window(t_data *data);
int		loop(t_data *data);
void	draw_player(t_data *data);
void	draw_map(t_data *data);
int    buttons(int key, t_data *data);


#endif
