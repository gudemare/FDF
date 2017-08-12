/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 11:37:04 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 15:10:31 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

static int	get_next_point_value(char **s)
{
	int		i;
	int		ret;

	i = 0;
	while ((*s)[i] && ((*s)[i] == ' ' || (*s)[i] == '\n'))
		i++;
	ret = ft_atoi((*s) + i);
	if ((*s)[i] == '-' || (*s)[i] == '+')
		i++;
	while (ft_isdigit((*s)[i]))
		i++;
	if (ft_strnequ(*s + i, ",0x", 3) && ft_isxdigit((*s)[i + 3]))
	{
		i += 3;
		while (ft_isxdigit((*s)[i]))
			i++;
	}
	*s += i;
	return (ret);
}

static int	**ft_alloc_grid(int width, int height)
{
	int	**grid;
	int	i;

	ft_assert(grid = (int **)malloc(sizeof(int *) * (height)));
	i = 0;
	while (i < height)
	{
		ft_assert(grid[i] = (int *)malloc(sizeof(int) * (width)));
		i++;
	}
	return (grid);
}

void		fill_grid(t_fdf *d, char *s)
{
	int		i;
	int		j;

	d->grid = ft_alloc_grid(d->map_width, d->map_height);
	d->color = ft_alloc_grid(d->map_width, d->map_height);
	ft_putendl("Allocated");
	i = 0;
	while (i < d->map_height)
	{
		j = 0;
		while (j < d->map_width)
		{
			d->grid[i][j] = get_next_point_value(&s);
			d->color[i][j] = abs(d->grid[i][j] * 1050);
			j++;
		}
		i++;
	}
	while (*s&& *s == ' ')
		s++;
	if (*s && *s != '\n' && *(s + 1))
	{
		ft_putendl_fd("Invalid file : too many numbers", 2);
		exit(EXIT_FAILURE);
	}
}
