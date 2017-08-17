/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:35:30 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/17 13:58:44 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	draw_line(t_fdf *d, t_vec p1, t_vec p2, int color)
{
	float	dx;
	float	dy;
	int		px_count;
	float	x;
	float	y;

	if ((p2.x < 0 && p1.x < 0) || (p2.x >= d->width && p1.x >= d->width)
		|| (p2.y < 0 && p1.y < 0)
		|| (p2.y > d->height && p1.y >= d->height) || !color)
		return ;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if ((px_count = ft_max(fabs(dx), fabs(dy))) == 0)
		return (pxput(d, p1.x, p1.y, color));
	x = p2.x;
	y = p2.y;
	dx /= px_count;
	dy /= px_count;
	while (px_count-- > 0)
	{
		if (x >= 0 && x < d->width && y >= 0 & y < d->height)
			*((int*)d->addr + (int)x + (int)y * d->l_size_4) = color;
		x -= dx;
		y -= dy;
	}
}

void	pxput(t_fdf *d, int x, int y, int color)
{
	if (x >= 0 && x < d->width && y >= 0 & y < d->height)
		*((int*)d->addr + x + y * d->l_size_4) = color;
}
