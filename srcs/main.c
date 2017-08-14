/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:47:44 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/14 23:08:54 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

static void	init_bitshifts(t_fdf *d)
{
	int		i;

	ft_assert(d->bitshifts = (int *)malloc(sizeof(int *) * (MAX_KEYCODE + 1)));
	i = 0;
	while (i <= MAX_KEYCODE)
		d->bitshifts[i++] = 0;
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
	d->bitshifts[k_CTRL_L] = k_p_CTRL_L;
	d->bitshifts[k_SHIFT_L] = k_p_SHIFT_L;
	d->bitshifts[k_SHIFT_R] = k_p_SHIFT_R;
	d->bitshifts[k_CTRL_R] = k_p_CTRL_R;
}

static void	init_values(t_fdf *d, char *map_file)
{
	parse_map(d, map_file);
	ft_printf("Map %s (%d * %d) loaded.\n",
			ft_basename(map_file), d->map_width, d->map_height);
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "fdf");
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->l_size, &d->endian);
	d->x_offset = 0;
	d->y_offset = 0;
	d->zoom = 1;
	d->l_size_4 = d->l_size / 4;
	d->keys = k_p_NOT_DRAWN;
	init_bitshifts(d);
}

int			main(int ac, char **av)
{
	t_fdf	d;

	if (ac != 2)
	{
		ft_putstr_fd("usage : ./fdf <map file>\n", 2);
		return (-1);
	}
	init_values(&d, av[1]);
	mlx_hook(d.win, k_KeyPress, k_KeyPressMask,
			&handle_key_press, &d);
	mlx_hook(d.win, k_KeyRelease, k_KeyReleaseMask,
			&handle_key_release, &d);
	mlx_loop_hook(d.mlx, &fdf_loop, &d);
	mlx_loop(d.mlx);
	return (0);
}
