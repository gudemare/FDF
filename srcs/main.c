/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:47:44 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/17 12:09:16 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

static void	init_bitshifts(t_fdf *d)
{
	int		i;

	ft_assert(d->bitshifts = (int *)malloc(sizeof(int *) * (MAX_KEYCODE + 1)));
	i = 0;
	while (i <= MAX_KEYCODE)
		d->bitshifts[i++] = 0;
	d->bitshifts[k_KEY_A] = k_p_KEY_A;
	d->bitshifts[k_KEY_S] = k_p_KEY_S;
	d->bitshifts[k_KP_M] = k_p_KP_M;
	d->bitshifts[k_KP_P] = k_p_KP_P;
	d->bitshifts[k_KP_1] = k_p_KP_1;
	d->bitshifts[k_KP_2] = k_p_KP_2;
	d->bitshifts[k_KP_3] = k_p_KP_3;
	d->bitshifts[k_KP_4] = k_p_KP_4;
	d->bitshifts[k_KP_5] = k_p_KP_5;
	d->bitshifts[k_KP_6] = k_p_KP_6;
	d->bitshifts[k_KP_7] = k_p_KP_7;
	d->bitshifts[k_KP_8] = k_p_KP_8;
	d->bitshifts[k_KP_9] = k_p_KP_9;
	d->bitshifts[k_LEFT] = k_p_LEFT;
	d->bitshifts[k_RIGHT] = k_p_RIGHT;
	d->bitshifts[k_DOWN] = k_p_DOWN;
	d->bitshifts[k_UP] = k_p_UP;
	d->bitshifts[k_SHIFT_R] = k_p_SHIFT_R;
	d->bitshifts[k_CTRL_R] = k_p_CTRL_R;
}

void		init_values(t_fdf *d)
{
	d->zoom = 0.75f / fmax((float)d->map_width / (float)d->width,
			(float)d->map_height / (float)d->height);
	d->y_offset = d->height / 2;
	d->x_offset = d->width / 2;
	d->l_size_4 = d->l_size / 4;
	d->map_h_center = (float)d->map_height / 2.0f;
	d->map_w_center = (float)d->map_width / 2.0f;
	d->keys = k_p_NOT_DRAWN;
	d->height_mod = 0.25f;
	d->color_mod = 1;
	d->fov = 60.0f;
	d->rot.x.x = 1;
	d->rot.x.y = 0;
	d->rot.x.z = 0;
	d->rot.y.x = 0;
	d->rot.y.y = 1;
	d->rot.y.z = 0;
	d->rot.z.x = 0;
	d->rot.z.y = 0;
	d->rot.z.z = 1;
}

int			main(int ac, char **av)
{
	t_fdf	d;

	if (ac != 2)
	{
		ft_putstr_fd("usage : ./fdf <map file>\n", 2);
		return (-1);
	}
	parse_map(&d, av[1]);
	ft_printf("Map %s (%d * %d) loaded.\n",
			ft_basename(av[1]), d.map_width, d.map_height);
	d.width = ft_min(SCREEN_WIDTH, 200 + (d.map_width * 5));
	d.height = ft_min(SCREEN_HEIGHT, 200 + (d.map_height * 5));
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, d.width, d.height, "fdf");
	d.img = mlx_new_image(d.mlx, d.width, d.height);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.l_size, &d.endian);
	init_values(&d);
	init_bitshifts(&d);
	mlx_hook(d.win, k_KeyPress, k_KeyPressMask,
			&handle_key_press, &d);
	mlx_hook(d.win, k_KeyRelease, k_KeyReleaseMask,
			&handle_key_release, &d);
	mlx_loop_hook(d.mlx, &fdf_loop, &d);
	mlx_loop(d.mlx);
	return (0);
}
