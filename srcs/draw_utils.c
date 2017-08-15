/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:35:30 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/15 02:09:47 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	draw_square(t_fdf *d, int size, int color)
{
	int		y_origin;
	int		x_end;

	if (!color || d->y + size >= HEIGHT || (x_end = d->x + size) >= WIDTH)
		return ;
	y_origin = d->y;
	while (d->y++ && size-- > 0)
		draw_h_line(d, x_end, color);
	d->y = y_origin;
}

void	draw_h_line(t_fdf *d, int x1, int color)
{
	int		dx;
	int		px_count;
	int		i;
	int		x_i;

	dx = x1 - d->x;
	px_count = abs(dx);
	i = 0;
	while (i < px_count)
	{
		x_i = d->x + (dx / px_count) * i;
		*((int*)d->addr + (x_i) + (d->y * d->l_size_4)) = color;
		i++;
	}
}

void	draw_line(t_fdf *d, int x1, int y1, int col)
{
	float	dx;
	float	dy;
	int		px_count;
	int		i;

	if ((x1 < 0 && d->x < 0) || (x1 >= WIDTH || d->x >= WIDTH)
			|| (y1 < 0 && d->y < 0) || (y1 > HEIGHT && d->y >= HEIGHT))
		return ;
	dx = x1 - d->x;
	dy = y1 - d->y;
	px_count = ft_max(fabs(dx), fabs(dy));
	i = 0;
	while (i < px_count)
	{
		pxput(d, d->x + (dx / px_count) * i,
				d->y + (dy / px_count) * i, col);
		i++;
	}
}

void	pxput(t_fdf *d, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	*((int*)d->addr + (x) + (y * d->l_size_4)) = color;
}
