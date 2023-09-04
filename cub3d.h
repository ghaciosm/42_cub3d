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

# define	WINDOW_WIDTH  800
# define	WINDOW_HEIGHT 800
# define	MAP_WIDTH  320
# define	MAP_HEIGHT 320
# define	SQR 32
# define	PLAYER (SQR /3)
# define	PI	3.14159
# define	ANGLE_INTERVAL	0.01
# define	BITS 5

# define	GREEN	0x0000FF00
# define	RED		0xFF0000

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
	void	*img_r;
	void	*img_r_addr;
	int		move_left;
	int		move_right;
	int		move_up;
	int		move_down;
	int		left;
	int		right;
	int		**map;
	int width;
	int height;
} t_data;

typedef struct s_rays
{
	float	xo;
	float	yo;
	float	rx;
	float	ry;
}	t_rays;


char    **map_read(char *filename);
void	map_check(char **map, t_data *data);
void    start_window(t_data *data);
int		loop(t_data *data);
void	draw_rays(t_data *data);
void	draw_player(t_data *data);
void	draw_map(t_data *data);
int		buttons_release(int key, t_data *data);
int		buttons_press(int key, t_data *data);
void	start(t_data *data);
void    key_press(t_data *data);
void    buttons(t_data *data);
void	draw_line_dda(t_data *data, int x1, int y1, int x2, int y2, int color);

#endif
