/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 14:20:33 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

int		fdf_loop(void *param)
{
	t_fdf	*d;
	int		i;
	int		j;
	int		k;

	d = (t_fdf *)param;
	i = 0;
	while (i < d->map_height)
	{
		j = 0;
		while(j < d->map_width)
		{
			d->x = j * 50;
			d->y = i * 50;
			k = 0;
			while (k++ <= 50)
				draw_line(d, d->x + 50, d->y - k, d->grid[i][j] * 450);
			k = 0;
			while (k++ <= 50)
				draw_line(d, d->x + 50 - k, d->y - 50, d->grid[i][j] * 450);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (1);
}
