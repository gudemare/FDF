/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 15:47:17 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

int				fdf_loop(void *param)
{
	t_fdf		*d;
	int			i;
	int			j;
	int			k;
	const int	case_size = ft_max(ft_min(HEIGHT / ((t_fdf *)param)->map_height,
				WIDTH / ((t_fdf *)param)->map_width), 1)
				* ((t_fdf *)param)->zoom;
	static int	prev_x_offset = 1;
	static int	prev_y_offset = 1;
	static int	prev_zoom = 0;
	int			color;

	d = (t_fdf *)param;
	if (prev_x_offset == d->x_offset && prev_y_offset == d->y_offset
		&& prev_zoom == d->zoom)
		return(1);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	i = (d->y_offset < 0) ? abs(d->y_offset - 1) : -1;
	while (++i < d->map_height)
	{
		if ((d->y = (d->y_offset + i) * case_size) >= HEIGHT)
			break;
		j = (d->x_offset < 0) ? abs(d->x_offset - 1) : -1;
		while(++j < d->map_width)
		{
			if ((d->x = (d->x_offset + j) * case_size) >= WIDTH)
				break;
			k = 0;
			color = d->color[i][j];
			while (d->y++ && k++ <= case_size)
				if (color)
					draw_line(d, d->x + case_size, d->y, color);
			d->y -= case_size + 2;
		}
	}
	prev_x_offset = d->x_offset;
	prev_y_offset = d->y_offset;
	prev_zoom = d->zoom;
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (1);
}
