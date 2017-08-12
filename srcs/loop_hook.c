/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 07:20:56 by gudemare         ###   ########.fr       */
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
	const int		case_size = ft_min(HEIGHT / ((t_fdf *)param)->map_height , WIDTH / ((t_fdf *)param)->map_width);

	d = (t_fdf *)param;
	i = 0;
//	ft_putendl("Updating img");
	while (i < d->map_height)
	{
		j = 0;
		while(j < d->map_width)
		{
//			ft_printf("Drawing case [%d, %d] = %d\n", i, j, d->grid[i][j]);
			d->x = j * case_size;
			d->y = i * case_size;
			k = 0;
			while (k++ <= case_size)
				draw_line(d, d->x + case_size, d->y - k, d->grid[i][j] * 1550);
			k = 0;
			while (k++ <= case_size)
				draw_line(d, d->x + case_size - k, d->y - case_size, d->grid[i][j] * 1550);
			j++;
		}
		i++;
	}
//	ft_putendl("done");
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (1);
}
