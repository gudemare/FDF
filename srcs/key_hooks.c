/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 20:34:37 by gudemare         ###   ########.fr       */
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

int			handle_key(int keycode, void *param)
{
	t_fdf *d;

	d = param;
	ft_printf("Called with keycode %d\n",keycode);
	if (keycode == k_ESC)
		quit(d);
/*	else if (keycode == k_LEFT)
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
		d->zoom--;*/
	else if (keycode == k_KP_0)
	{
		d->zoom = 1;
		d->y_offset = 0;
		d->x_offset = 0;
	}
	else
		ft_printf("Non-handled key pressed : %d.\n", keycode);
	return (1);
}

int		handle_key_press(int x_event, void *param)
{
	t_fdf *d;

	d = param;
	ft_printf("Called with press event %d\n", x_event);
	if (x_event == k_ESC)
		quit(d);
	else if (x_event == k_LEFT)
		d->x_offset += 10;
	else if (x_event == k_RIGHT)
		d->x_offset -= 10;
	else if (x_event == k_UP)
		d->y_offset += 10;
	else if (x_event == k_DOWN)
		d->y_offset -= 10;
	else if (x_event == k_KP_P)
		d->zoom++;
	else if (x_event == k_KP_M)
		d->zoom--;
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

int		handle_key_release(int x_event, void *param)
{
	ft_printf("Called with release %d\n",x_event);
	(void)param;
	return (1);
}
