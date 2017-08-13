/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 21:24:24 by gudemare         ###   ########.fr       */
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
		free(d->color[i++]);
	}
	free(d->grid);
	free(d->color);
	exit(EXIT_SUCCESS);
}

int			handle_key_press(int x_event, void *param)
{
	t_fdf *d;

	d = param;
	if (x_event == k_ESC)
		quit(d);
	else if (x_event == k_LEFT || x_event == k_RIGHT)
		d->x_offset += (x_event == k_LEFT) ? 10 : -10;
	else if (x_event == k_UP || x_event == k_DOWN)
		d->y_offset += (x_event == k_UP) ? 10 : -10;
	else if (x_event == k_KP_P || x_event == k_KP_M)
		d->zoom += (x_event == k_KP_P) ? 1 : -1;
	else if (x_event == k_KP_0)
	{
		d->zoom = 1;
		d->y_offset = 0;
		d->x_offset = 0;
	}
	else
		ft_printf("Non-handled key pressed : %d.\n", x_event);
	return (1);
}

int			handle_key_release(int x_event, void *param)
{
	return (1);
	(void)param;
	(void)x_event;
}
