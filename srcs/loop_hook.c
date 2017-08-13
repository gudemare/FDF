/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/13 16:53:23 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

int		get_case_size(t_fdf *d)
{
	return (ft_max(ft_min(HEIGHT / d->map_height,
		WIDTH / d->map_width), 1) * d->zoom);
}

void	draw_cases(t_fdf *d)
{
	int			i;
	int			j;
	const int	case_size = get_case_size(d);

	i = (d->y_offset < 0) ? abs(d->y_offset - 1) : -1;
	while (++i < d->map_height)
	{
		j = (d->x_offset < 0) ? abs(d->x_offset - 1) : -1;
		if ((d->y = (d->y_offset + i) * case_size) < HEIGHT)
			while (++j < d->map_width)
				if ((d->x = (d->x_offset + j) * case_size) < WIDTH)
					draw_square(d, case_size, d->color[i][j]);
	}
}

int		fdf_loop(void *param)
{
	t_fdf		*d;
	static int	prev_x_offset = 1;
	static int	prev_y_offset = 1;
	static int	prev_zoom = 0;

	d = (t_fdf *)param;
	if (prev_x_offset == d->x_offset && prev_y_offset == d->y_offset
		&& prev_zoom == d->zoom)
		return (1);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	draw_cases(d);
	prev_x_offset = d->x_offset;
	prev_y_offset = d->y_offset;
	prev_zoom = d->zoom;
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (1);
}
