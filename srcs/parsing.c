/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:39:49 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 14:00:58 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include "fdf.h"

static int	next_point(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (ft_strnequ(s + i, ",0x", 3) == 1 && ft_isxdigit(s[i + 3]))
	{
		i += 3;
		while (ft_isxdigit(s[i]))
			i++;
	}
	if (!s[i] || s[i] == ' ' || s[i] == '\n')
		return (i);
	ft_dprintf(2, "Invalid file : bad number formating.\n");
	exit(EXIT_FAILURE);
}

static void	compare_points_in_lines(char *s, int i, int ret)
{
	int		actual;

	actual = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] == '\n')
			i++;
		if (!s[i])
			break ;
		actual = 0;
		while (s[i] && s[i] != '\n')
		{
			i += next_point(s + i);
			actual++;
		}
		if (actual != ret)
		{
			ft_dprintf(2, "Invalid file : incoherent lines lengths\n");
			exit(EXIT_FAILURE);
		}
	}
}

static int	count_points_in_lines(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] && s[i] != '\n')
	{
		i += next_point(s + i);
		ret++;
	}
	compare_points_in_lines(s, i, ret);
	return (ret);
}

static void	get_grid(int fd, t_fdf *d)
{
	char	*entry;

	entry = NULL;
	ft_putendl("Allocating");
	if (ft_read(NULL, fd, &entry, 0) == -1)
		ft_assert(NULL);
	ft_assert(entry);
	ft_putendl("Width");
	d->map_width = count_points_in_lines(entry);
	ft_putendl("Height");
	d->map_height = ft_strchr_count(entry, '\n');
	ft_putendl("grid fill");
	fill_grid(d, entry);
	ft_putendl("done");
	free(entry);
}

void		parse_map(t_fdf *d, char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "fdf: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}
	get_grid(fd, d);
	if (close(fd) == -1)
	{
		ft_dprintf(2, "fdf: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}
}
