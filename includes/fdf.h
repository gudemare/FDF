/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:46:48 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/17 13:39:00 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define SCREEN_WIDTH 2560
# define SCREEN_HEIGHT 1440

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_matrix
{
	t_vec		x;
	t_vec		y;
	t_vec		z;
}				t_matrix;

typedef struct	s_line
{
	t_vec		p1;
	t_vec		p2;
	int			c1;
	int			c2;
}				t_line;

typedef struct	s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					endian;
	int					l_size;
	int					l_size_4;
	int					**grid;
	int					**color;
	int					height;
	int					width;
	int					map_height;
	int					map_width;
	float				map_h_center;
	float				map_w_center;
	int					x_offset;
	int					y_offset;
	float				zoom;
	float				fov;
	float				height_mod;
	float				color_mod;
	int					keys;
	int					*bitshifts;
	t_matrix			rot;
}				t_fdf;

# define MAX_KEYCODE 269

enum			e_keycodes
{
	k_KEY_S = 1,
	k_KEY_A = 0,
	k_KEY_F = 3,
	k_KEY_G = 5,
	k_KEY_C = 8,
	k_KEY_B = 11,
	k_KEY_R = 15,
	k_NUM_1 = 18,
	k_NUM_2 = 19,
	k_NUM_3 = 20,
	k_NUM_4 = 21,
	k_NUM_6 = 22,
	k_NUM_5 = 23,
	k_NUM_9 = 25,
	k_NUM_7 = 26,
	k_NUM_8 = 28,
	k_NUM_0 = 29,
	k_SPACE = 49,
	k_ESC = 53,
	k_KP_F = 67,
	k_KP_P = 69,
	k_KP_D = 75,
	k_KP_M = 78,
	k_KP_0 = 82,
	k_KP_1 = 83,
	k_KP_2 = 84,
	k_KP_3 = 85,
	k_KP_4 = 86,
	k_KP_5 = 87,
	k_KP_6 = 88,
	k_KP_7 = 89,
	k_KP_8 = 91,
	k_KP_9 = 92,
	k_LEFT = 123,
	k_RIGHT = 124,
	k_DOWN = 125,
	k_UP = 126,
	k_CTRL_L = 256,
	k_SHIFT_L = 257,
	k_SHIFT_R = 258,
	k_CTRL_R = 269,
	k_KeyPress = 2,
	k_KeyRelease = 3,
	k_KeyPressMask = (1L << 0),
	k_KeyReleaseMask = (1L << 1)
};

enum			e_keys_pressed
{
	k_p_KEY_S = 1 << 1,
	k_p_KEY_A = 1 << 2,
	k_p_KP_P = 1 << 3,
	k_p_KP_M = 1 << 4,
	k_p_KP_1 = 1 << 5,
	k_p_KP_2 = 1 << 6,
	k_p_KP_3 = 1 << 7,
	k_p_KP_4 = 1 << 8,
	k_p_KP_5 = 1 << 9,
	k_p_KP_6 = 1 << 10,
	k_p_KP_7 = 1 << 11,
	k_p_KP_8 = 1 << 12,
	k_p_KP_9 = 1 << 13,
	k_p_LEFT = 1 << 14,
	k_p_RIGHT = 1 << 15,
	k_p_DOWN = 1 << 16,
	k_p_UP = 1 << 17,
	k_p_SHIFT_R = 1 << 18,
	k_p_CTRL_R = 1 << 19,
	k_p_NOT_DRAWN = 1 << 32
};

void			init_values(t_fdf *d);
void			parse_map(t_fdf *d, char *filename);
void			fill_grid(t_fdf *d, char *s);

int				fdf_loop(void *param);
int				inactive_loop(t_fdf *d);

int				handle_key_press(int x_event, void *param);
int				handle_key_release(int x_event, void *param);

void			rot_x(t_matrix *r, float a);
void			rot_y(t_matrix *r, float a);
void			rot_z(t_matrix *r, float a);

/*
** Drawing utilities
*/

void			draw_line(t_fdf *d, t_vec p1, t_vec p2, int color);
void			pxput(t_fdf*d, int x, int y, int color);

#endif
