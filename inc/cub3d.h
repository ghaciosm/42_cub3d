/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:15:33 by ghaciosm          #+#    #+#             */
/*   Updated: 2023/09/21 14:00:35 by myagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WINDOW_WIDTH	1100
# define WINDOW_HEIGHT	1000
# define SQR 			16
# define PLAYER 		5
# define PI				3.14159
# define ANGLE_INTERVAL	0.01
# define BITS			4

# define BLUE	0x000000FF
# define GREEN	0x0000FF00
# define RED		0x00FF0000
# define YELLOW	0x00FFFF00
# define BLACK 	0x00000000
# define TRANSP 	0xFF000000
# define GRAY	0x888888
# define DARK_GRAY	0x333333
# define WHITE	0x00FFFFFF

typedef struct s_map
{
	char	***textures;
	void	**xpm_image;
	char	**xpm_addr;
	char	***rgb;
	char	**texture;
	int		*lengths;
	int		c_color;
	int		f_color;
}	t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
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
	char	**map;
	int		width;
	int		height;
	int		pixel_pos;
	int		color;
	t_map	*maps;
	float	dist;
}	t_data;

typedef struct s_rays
{
	float	xo;
	float	yo;
	float	rx;
	float	ry;
}	t_rays;

void	map_read(char *filename, t_data *data, int c, int i);
void	map_check(t_data *data);
void	start_window(t_data *data);
int		loop(t_data *data);
void	draw_rays(t_data *data);
void	draw_player(t_data *data);
void	set_texture(t_map **map, t_data *data, int fd);
void	draw_map(t_data *data);
int		buttons_release(int key, t_data *data);
int		buttons_press(int key, t_data *data);
void	start(t_data *data);
void	key_press(t_data *data);
void	buttons(t_data *data);
void	draw_line_dda(t_data *data, int x1, int y1, t_rays *rays);
int		close_window(t_data *data, int flag);
void	draw_player(t_data *data);
void	draw_map(t_data *data);
void	error(int i, char *str, t_data *data, int count);
void	draw3dwalls(t_data *data, float a, int i, float x);
float	find_distance(float x1, float y1, float x2, float y2);
void	normalize_angle(float *a);
int		set_colors(t_data *data, int i);
int		get_image(int direction, float pa);
void	open_xpms(t_data *data, int x, int y, int fd);
void	close_window2(int count, t_data *data, int flag);

char	*get_next_line(int fd);
int		nl_checker(char *str);
char	*ft_strjoin_v2(char *s1, char *s2);
char	*till_next_line(char *holder);
char	*after_next_line(char *holder);
#endif
