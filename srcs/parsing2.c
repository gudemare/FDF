/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 11:37:04 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/13 18:14:43 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

static int	**ft_alloc_grid(int width, int height)
{
	int	**grid;
	int	i;

	ft_assert(grid = (int **)malloc(sizeof(int *) * (height)));
	i = 0;
	while (i < height)
		ft_assert(grid[i++] = (int *)malloc(sizeof(int) * (width)));
	return (grid);
}

static int	get_next_point_value(char **s)
{
	int		ret;

	while (**s && (**s == ' ' || **s == '\n'))
		(*s)++;
	ret = ft_atoi(*s);
	if (**s == '-' || **s == '+')
		(*s)++;
	while (ft_isdigit(**s))
		(*s)++;
	return (ret);
}

static int	get_next_point_color(t_fdf *d, int i, int j, char **s)
{
	if (ft_strnequ(*s, ",0x", 3) && ft_isxdigit((*s)[3]))
	{
		*s += 3;
		while (ft_isxdigit(**s))
			(*s)++;
	}
	return (abs(d->grid[i][j] * 1050));
}

void		fill_grid(t_fdf *d, char *s)
{
	int		i;
	int		j;

	d->grid = ft_alloc_grid(d->map_width, d->map_height);
	d->color = ft_alloc_grid(d->map_width, d->map_height);
	i = -1;
	while (++i < d->map_height)
	{
		j = -1;
		while (++j < d->map_width)
		{
			d->grid[i][j] = get_next_point_value(&s);
			d->color[i][j] = get_next_point_color(d, i, j, &s);
		}
	}
	while (*s && *s == ' ')
		s++;
	if (*s && *s != '\n' && *(s + 1))
	{
		ft_putendl_fd("Invalid file : too many numbers", 2);
		exit(EXIT_FAILURE);
	}
}
