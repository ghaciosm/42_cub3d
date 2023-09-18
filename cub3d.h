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

# define	WINDOW_WIDTH  1100
# define	WINDOW_HEIGHT 1000
# define	SQR 16
# define	PLAYER (SQR /3)
# define	PI	3.14159
# define	ANGLE_INTERVAL	0.01
# define	BITS 4

# define	MOVE_X (data->pdx / 5.0)
# define	MOVE_Y (data->pdy / 5.0)

# define	BLUE	0x000000FF
# define	GREEN	0x0000FF00
# define	RED		0x00FF0000
# define	YELLOW	0x00FFFF00
# define	BLACK 	0x00000000 
# define	TRANSP 	0xFF000000
# define	GRAY	0x888888 
# define	DARK_GRAY	0x333333

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
	void	*img_rays;
	void	*img_rays_addr;
	int		move_left;
	int		move_right;
	int		move_up;
	int		move_down;
	int		left;
	int		right;
	char		**map;
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

typedef struct s_map
{
	char	***textures;
	char	***color_li;
}	t_map;

char    **map_read(char *filename, t_map *map, t_data *data);
void	map_check(t_data *data);
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
int		close_window(t_data *data,int flag);

#endif
