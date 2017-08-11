/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 10:19:26 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 11:06:07 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int		ft_read(char *filename, int fd, char **buf, size_t len)
{
	int		read_size;
	int		ret;

	if (!buf || (filename != NULL && (fd = open(filename, O_RDONLY)) == -1))
		return (-1);
	if ((read_size = len) == 0)
		read_size = 1000;
	if (*buf)
		ft_strdel(buf);
	if (!(*buf = ft_strnew(read_size)))
		return (-1);
	while ((ret = read(fd, *buf + ft_strlen(*buf), read_size)) == read_size && len == 0)
		if (!(*buf= ft_strextend(*buf, 1000)))
			return (-1);
	if (filename != NULL)
		close(fd);
	return (ret);
}
