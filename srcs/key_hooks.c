/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 09:10:11 by gudemare         ###   ########.fr       */
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
	else
		ft_printf("Non-handled key pressed : %d.\n", keycode);
	return (1);
}
