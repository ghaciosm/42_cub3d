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
# define	SQR 70
# define	PLAYER (SQR /4)
# define	PI	3.14159


#include "libft/libft.h"
#include "next_line/get_line.h"

typedef struct s_data
{
	void *mlx;
	void *win;

	int bits_per_pixel;
    int size_line;
    int endian;
	float px;
	float py;
	float pdx;
	float pdy;
	float pa;
	void	*img_p;
	void	*img_p_addr;
	void	*img_w;
	void	*img_w_addr;
	int		move_left;
	int		move_right;
	int		move_up;
	int		move_down;
} t_data;

char    **map_read(char *filename);
void	map_check(char **map);
void    start_window(t_data *data);
int		loop(t_data *data);
void	draw_player(t_data *data);
void	draw_map(t_data *data);
int		buttons_release(int key, t_data *data);
int		buttons_press(int key, t_data *data);
void	start(t_data *data);
void    key_press(t_data *data);
void    buttons(t_data *data);

#endif
