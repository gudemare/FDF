/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:39:49 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/12 21:27:38 by gudemare         ###   ########.fr       */
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
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i] || ft_isdigit(s[i]) || s[i] == '\n' || s[i] == '-' || s[i] == '+')
		return (i);
	ft_dprintf(2, "Invalid file : bad number formating.\n");
	exit(EXIT_FAILURE);
}

static void	compare_points_in_lines(char *s, int i, int ret)
{
	int		actual;
	int		line;

	line = 2;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		i += (s[i] == '\n');
		if (!s[i])
			return ;
		actual = 0;
		while (s[i] && s[i] != '\n' && (i += next_point(s + i)))
			actual++;
		if (actual != ret)
		{
			ft_dprintf(2, "Invalid file :\
incoherent lines lengths at line %d (actual = %d, ret = %d)\n"\
			, line, actual, ret);
			exit(EXIT_FAILURE);
		}
		line++;
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
	int		ret;

	entry = NULL;
	if ((ret = ft_read(NULL, fd, &entry, 0)) < 0)
		ft_errno_exit((ret == -1), 1);
	ft_assert(entry);
	d->map_width = count_points_in_lines(entry);
	d->map_height = ft_strchr_count(entry, '\n');
	fill_grid(d, entry);
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
