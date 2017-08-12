/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 09:17:23 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static void	quit(t_fdf *d)
{
	int		i;

	ft_putstr("Goodbye\n");
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	i = 0;
	while (i < d->map_height)
	{
		free(d->grid[i]);
		d->grid[i++] = NULL;
	}
	free(d->grid);
	exit(EXIT_SUCCESS);
}

int			handle_key(int keycode, void *param)
{
	t_fdf *d;

	d = param;
	if (keycode == k_ESC)
		quit(d);
	else if (keycode == k_LEFT)
		d->x_offset += d->map_width / (d->zoom * 10);
	else if (keycode == k_RIGHT)
		d->x_offset -= d->map_width / (d->zoom * 10);
	else if (keycode == k_UP)
		d->y_offset += d->map_height / (d->zoom * 10);
	else if (keycode == k_DOWN)
		d->y_offset -= d->map_height / (d->zoom * 10);
	else if (keycode == k_KP_P)
		d->zoom++;
	else if (keycode == k_KP_M)
		d->zoom--;
	else
		ft_printf("Non-handled key pressed : %d.\n", keycode);
	return (1);
}
