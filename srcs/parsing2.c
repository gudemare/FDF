/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 11:37:04 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 12:44:38 by gudemare         ###   ########.fr       */
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
	i = 0;
	while (i < d->map_height)
	{
		j = 0;
		while (j < d->map_width)
		{
			d->grid[i][j] = get_next_point_value(&s);
			j++;
		}
		i++;
	}
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i])
	{
		ft_dprintf(2, "Invalid file : too many numbers [%s]\n", s);
		exit(EXIT_FAILURE);
	}
}
