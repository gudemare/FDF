/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:35:30 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 07:39:05 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *mlx, int x1, int y1)
{
	float	dx;
	float	dy;
	int		px_count;
	int		i;

	dx = x1 - mlx->x;
	dy = y1 - mlx->y;
	px_count = ft_max(fabs(dx), fabs(dy));
	i = 0;
	while (i < px_count)
	{
		pxput(mlx, mlx->x + (dx / px_count) * i,
				mlx->y + (dy / px_count) * i, 255);
		i++;
	}
}

void	pxput(t_fdf *mlx, int x, int y, int color)
{
	int	pos;

	if (x < 0 || x >= WIDTH || y < 0 || y > HEIGHT)
		return ;
	pos = (x * mlx->bpp / 8) + (y * mlx->l_size);
	mlx->addr[pos + 0] = color;
	mlx->addr[pos + 1] = color >> 8;
	mlx->addr[pos + 2] = color >> 16;
}
