/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:47:44 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/13 21:10:38 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

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
