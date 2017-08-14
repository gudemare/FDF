/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/14 22:51:53 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static void	quit(t_fdf *d)
{
	int		i;

	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	i = 0;
	while (i < d->map_height)
	{
		free(d->grid[i]);
		free(d->color[i++]);
	}
	free(d->grid);
	free(d->color);
	free(d->bitshifts);
	ft_putstr("Goodbye\n");
	exit(EXIT_SUCCESS);
}

int			handle_key_press(int x_event, void *param)
{
	t_fdf *d;

	d = param;
	if (x_event == k_ESC)
		quit(d);
	else if (x_event == k_KP_0)
	{
		d->zoom = 1;
		d->y_offset = 0;
		d->x_offset = 0;
		d->keys = 0;
		d->keys |= k_p_NOT_DRAWN;
	}
	else
		d->keys |= d->bitshifts[x_event];
	return (1);
}

int			handle_key_release(int x_event, void *param)
{
	t_fdf *d;

	d = param;
	d->keys &= ~(d->bitshifts[x_event]);
	return (1);
}
