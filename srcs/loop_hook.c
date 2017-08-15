/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/15 03:06:08 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

/*int		get_case_size(t_fdf *d)
{
	static int	ret = 0;

	if (ret == 0)
		ret = ft_max(ft_min(HEIGHT / d->map_height,
		WIDTH / d->map_width), 1);
	return (ret * d->zoom);
}

void	draw_cases(t_fdf *d)
{
	int			i;
	int			j;
	const int	case_size = get_case_size(d);

	i = (d->y_offset < 0) ? abs(d->y_offset) - 1 : -1;
	while (++i < d->map_height)
	{
		j = (d->x_offset < 0) ? abs(d->x_offset) - 1 : -1;
		if ((d->y = (d->y_offset + i) * case_size) < HEIGHT)
			while (++j < d->map_width)
				if ((d->x = (d->x_offset + j) * case_size) < WIDTH)
					draw_square(d, case_size, d->color[i][j]);
	}
}*/

static void	draw_img(t_fdf *d)
{
	int		x;
	int		y;
	int		case_size = d->zoom;

	d->x_origin = 0;
	d->y_origin = 0;
	x = -1;
	while (++x < d->map_width)
	{
		y = -1;
		while (++y < d->map_height)
		{
			d->x = x * case_size + y;
			d->y = y * case_size + x;
			draw_line(d, d->x + case_size + y, d->y + case_size + x, d->color[x][y]);
		}
	}
}

static void	apply_key(t_fdf *d)
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

int			fdf_loop(void *param)
{
	t_fdf		*d;

	d = (t_fdf *)param;
	if (!(d->keys))
		return (inactive_loop((t_fdf *)param));
	apply_key(d);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
//	draw_cases(d);
	draw_img(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->keys &= ~k_p_NOT_DRAWN;
	return (1);
}
