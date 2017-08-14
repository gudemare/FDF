/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:46:48 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/14 22:50:50 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define WIDTH 2560
# define HEIGHT 1440

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
	int					map_height;
	int					map_width;
	int					x;
	int					y;
	int					x_offset;
	int					y_offset;
	int					zoom;
	int					keys;
	int					*bitshifts;
}				t_fdf;

# define MAX_KEYCODE 269

enum			e_keycodes
{
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
	k_p_KP_P = 1 << 1,
	k_p_KP_M = 1 << 2,
	k_p_KP_1 = 1 << 3,
	k_p_KP_2 = 1 << 4,
	k_p_KP_3 = 1 << 5,
	k_p_KP_4 = 1 << 6,
	k_p_KP_5 = 1 << 7,
	k_p_KP_6 = 1 << 8,
	k_p_KP_7 = 1 << 9,
	k_p_KP_8 = 1 << 10,
	k_p_KP_9 = 1 << 11,
	k_p_LEFT = 1 << 12,
	k_p_RIGHT = 1 << 13,
	k_p_DOWN = 1 << 14,
	k_p_UP = 1 << 15,
	k_p_CTRL_L = 1 << 16,
	k_p_SHIFT_L = 1 << 17,
	k_p_SHIFT_R = 1 << 18,
	k_p_CTRL_R = 1 << 19,
	k_p_NOT_DRAWN = 1 << 32
};

void			parse_map(t_fdf *d, char *filename);
void			fill_grid(t_fdf *d, char *s);

int				fdf_loop(void *param);
int				inactive_loop(t_fdf *d);

int				handle_key_press(int x_event, void *param);
int				handle_key_release(int x_event, void *param);

/*
** Drawing utilities
*/

void			draw_line(t_fdf *d, int x1, int y1, int col);
void			draw_h_line(t_fdf *d, int x1, int col);
void			draw_square(t_fdf *d, int size, int color);
void			pxput(t_fdf*d, int x, int y, int color);

#endif
