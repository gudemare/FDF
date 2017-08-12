/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 09:25:55 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"


int		fdf_loop(void *param)
{
	t_fdf		*d;
	int			i;
	int			j;
	int			k;
	const int	case_size = ft_max(ft_min(HEIGHT / ((t_fdf *)param)->map_height , WIDTH / ((t_fdf *)param)->map_width), 1) * ((t_fdf *)param)->zoom;
	static int	prev_x_offset = 1;
	static int	prev_y_offset = 1;
	static int	prev_zoom = 0;

	d = (t_fdf *)param;
	if (prev_x_offset == d->x_offset && prev_y_offset == d->y_offset && prev_zoom == d->zoom)
		return(1);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	i = 0;
//	ft_putendl("Updating img");
	while (i < d->map_height)
	{
		j = 0;
		d->y = (d->y_offset + i) * case_size;
		if (d->y >= HEIGHT)
			break;
		while(j < d->map_width)
		{
//			ft_printf("Drawing case [%d, %d] = %d\n", i, j, d->grid[i][j]);
			d->x = (d->x_offset + j) * case_size;
			if (d->x >= WIDTH)
				break;
			k = 0;
			while (k++ <= case_size)
			{
				d->y++;
				draw_line(d, d->x + case_size, d->y, ((abs(d->grid[i][j]) << 16) + 7) * 1550);
				//draw_line(d, d->x + case_size, d->y - k, ((abs(d->grid[i][j]) << 16) + 7) * 1550);
				//draw_line(d, d->x + case_size - k, d->y - case_size, ((abs(d->grid[i][j] << 16) +7 )) * 1550);
			}
			d->y -= case_size + 1;
			j++;
		}
		i++;
	}
	prev_x_offset = d->x_offset;
	prev_y_offset = d->y_offset;
	prev_zoom = d->zoom;
//	ft_putendl("done");
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (1);
}
