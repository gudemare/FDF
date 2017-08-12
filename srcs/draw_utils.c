/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:35:30 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 16:15:34 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *mlx, int x1, int y1, int col)
{
	float	dx;
	float	dy;
	int		px_count;
	int		i;

	if ((x1 < 0 && mlx->x < 0) || (x1 >= WIDTH || mlx->x >= WIDTH)
		|| (y1 < 0 && mlx->y < 0) || (y1 > HEIGHT && mlx->y >= HEIGHT))
		return ;
	dx = x1 - mlx->x;
	dy = y1 - mlx->y;
	px_count = ft_max(fabs(dx), fabs(dy));
	i = 0;
	while (i < px_count)
	{
		pxput(mlx, mlx->x + (dx / px_count) * i,
				mlx->y + (dy / px_count) * i, col);
		i++;
	}
}

void	pxput(t_fdf *mlx, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	*((int*)mlx->addr + (x) + (y * mlx->l_size_4)) = color;
}
