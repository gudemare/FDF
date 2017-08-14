/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/14 23:10:31 by gudemare         ###   ########.fr       */
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

void	apply_key(t_fdf *d)
{
	if (d->keys & k_p_LEFT)
		d->x_offset -= 10;
	if (d->keys & k_p_RIGHT)
		d->x_offset += 10;
	if (d->keys & k_p_UP)
		d->y_offset -= 10;
	if (d->keys & k_p_DOWN)
		d->y_offset += 10;
	if (d->keys & k_p_KP_P)
		d->zoom++;
	if (d->keys & k_p_KP_M)
		d->zoom--;
}

int		fdf_loop(void *param)
{
	t_fdf		*d;

	d = (t_fdf *)param;
	if (!(d->keys))
		return (inactive_loop((t_fdf *)param));
	apply_key(d);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	draw_cases(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->keys &= ~k_p_NOT_DRAWN;
	return (1);
}
