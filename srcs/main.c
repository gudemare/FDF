/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:47:44 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 07:47:23 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	ft_putgrid(t_fdf *d)
{
	int		i;
	int		j;

	i = 0;
	while (i < d->map_height)
	{
		j = 0;
		while (j < d->map_width)
		{
			ft_putnbr(d->grid[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int		main(int ac, char **av)
{
	t_fdf	d;

	if (ac != 2)
	{
		ft_putstr_fd("usage : ./fdf <map file>\n", 2);
		return (-1);
	}
	parse_map(&d, av[1]);
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "fdf");
	d.img = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.l_size, &d.endian);
	mlx_loop_hook(d.mlx, &fdf_loop, &d);
	mlx_key_hook(d.win, &handle_key, &d);
	fdf_loop(&d);
	mlx_loop(d.mlx);
	return (0);
}
