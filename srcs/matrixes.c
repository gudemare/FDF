/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 04:46:35 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/17 12:19:09 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	rot_x(t_matrix *r, float a)
{
	t_vec	tmp;

	tmp = (t_vec){0, r->x.y, r->x.z};
	r->x.y = tmp.y * cos(a) + tmp.z * -sin(a);
	r->x.z = tmp.y * sin(a) + tmp.z * cos(a);
	tmp = (t_vec){0, r->y.y, r->y.z};
	r->y.y = tmp.y * cos(a) + tmp.z * -sin(a);
	r->y.z = tmp.y * sin(a) + tmp.z * cos(a);
	tmp = (t_vec){0, r->z.y, r->z.z};
	r->z.y = tmp.y * cos(a) + tmp.z * -sin(a);
	r->z.z = tmp.y * sin(a) + tmp.z * cos(a);
}

void	rot_y(t_matrix *r, float a)
{
	t_vec	tmp;

	tmp = (t_vec){r->x.x, 0, r->x.z};
	r->x.x = tmp.x * cos(a) + tmp.z * sin(a);
	r->x.z = tmp.x * -sin(a) + tmp.z * cos(a);
	tmp = (t_vec){r->y.x, 0, r->y.z};
	r->y.x = tmp.x * cos(a) + tmp.z * sin(a);
	r->y.z = tmp.x * -sin(a) + tmp.z * cos(a);
	tmp = (t_vec){r->z.x, 0, r->z.z};
	r->z.x = tmp.x * cos(a) + tmp.z * sin(a);
	r->z.z = tmp.x * -sin(a) + tmp.z * cos(a);
}

void	rot_z(t_matrix *r, float a)
{
	t_vec	tmp;

	tmp = (t_vec){r->x.x, r->x.y, 0};
	r->x.x = tmp.x * cos(a) + tmp.y * -sin(a);
	r->x.y = tmp.x * sin(a) + tmp.y * cos(a);
	tmp = (t_vec){r->y.x, r->y.y, 0};
	r->y.x = tmp.x * cos(a) + tmp.y * -sin(a);
	r->y.y = tmp.x * sin(a) + tmp.y * cos(a);
	tmp = (t_vec){r->z.x, r->z.y, 0};
	r->z.x = tmp.x * cos(a) + tmp.y * -sin(a);
	r->z.y = tmp.x * sin(a) + tmp.y * cos(a);
}
