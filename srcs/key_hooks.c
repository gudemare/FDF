/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/13 21:29:35 by gudemare         ###   ########.fr       */
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

static int	keycode_to_bitshift(int keycode)
{
	if (keycode == k_LEFT)
		return (k_p_LEFT);
	else if (keycode == k_RIGHT)
		return (k_p_RIGHT);
	else if (keycode == k_UP)
		return (k_p_UP);
	else if (keycode == k_DOWN)
		return (k_p_DOWN);
	ft_printf("Non-handled keycode received : %d.\n", keycode);
	return (0);
}

int			handle_key_press(int x_event, void *param)
{
	t_fdf *d;

	d = param;
	if (x_event == k_ESC)
		quit(d);
	else if (x_event == k_KP_P || x_event == k_KP_M)
	{
		d->zoom += (x_event == k_KP_P) ? 1 : -1;
		d->keys |= k_p_NOT_DRAWN;
	}
	else if (x_event == k_KP_0)
	{
		d->zoom = 1;
		d->y_offset = 0;
		d->x_offset = 0;
		d->keys = 0;
		d->keys |= k_p_NOT_DRAWN;
	}
	else
		d->keys |= keycode_to_bitshift(x_event);
	return (1);
}

int			handle_key_release(int x_event, void *param)
{
	t_fdf *d;

	d = param;
	d->keys &= ~(keycode_to_bitshift(x_event));
	return (1);
}
