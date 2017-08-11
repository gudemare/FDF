/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:46:48 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 12:44:43 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			l_size;
	int			endian;
	int			**grid;
	int			map_height;
	int			map_width;
	int			x;
	int			y;
}				t_fdf;

enum			e_key
{
	k_LEFT = 123,
	k_RIGHT = 124,
	k_DOWN = 125,
	k_UP = 126,
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
	k_KP_P = 69,
	k_KP_M = 78,
	k_KP_F = 67,
	k_KP_D = 75,
	k_SPACE = 49,
	k_ESC = 53,
	k_NUM_1 = 18,
	k_NUM_2 = 19,
	k_NUM_3 = 20,
	k_NUM_4 = 21,
	k_NUM_5 = 23,
	k_NUM_6 = 22,
	k_NUM_7 = 26,
	k_NUM_8 = 28,
	k_NUM_9 = 25,
	k_NUM_0 = 29,
	k_KEY_R = 15,
	k_KEY_G = 5,
	k_KEY_B = 11,
	k_KEY_C = 8,
	k_CTRL_L = 256,
	k_CTRL_R = 269,
	k_SHIFT_L = 257,
	k_SHIFT_R = 258
};

int				fdf_loop(void	*param);
int				handle_key(int keycode, void *param);

void			parse_map(t_fdf *d, char *filename);
void			fill_grid(t_fdf *d, char *s);

void			draw_line(t_fdf *mlx, int x1, int y1);
void			pxput(t_fdf*mlx, int x, int y, int color);

#endif