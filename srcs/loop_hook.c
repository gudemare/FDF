/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/18 03:32:10 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

static void	set_point(t_fdf *d, t_vec *p, int j, int i)
{
	t_vec	tmp;
	float	coef;

	p->x = (i - d->map_w_center) * d->zoom;
	p->y = (j - d->map_h_center) * d->zoom;
	p->z = d->grid[j][i] * d->height_mod * d->zoom;
	tmp = (t_vec){p->x, p->y, p->z};
	p->x = tmp.x * d->rot.x.x + tmp.y * d->rot.y.x + tmp.z * d->rot.z.x;
	p->y = tmp.x * d->rot.x.y + tmp.y * d->rot.y.y + tmp.z * d->rot.z.y;
	p->z = -(tmp.x * d->rot.x.z + tmp.y * d->rot.y.z + tmp.z * d->rot.z.z);
	if (d->fov)
	{
		coef = (p->z / (10.0f * d->fov)) + 2.0f;
		p->x /= coef;
		p->y /= coef;
	}
	p->x += d->x_offset;
	p->y += d->y_offset;
}

static void	draw_img(t_fdf *d, float max_z)
{
	t_line	l;
	int		i;
	int		j;

	j = -1;
	while (++j < d->map_height && (i = -1) == -1)
		while (++i < d->map_width)
		{
			set_point(d, &(l.p1), j, i);
			l.c1 = d->color[j][i] * d->color_mod;
			if (i + 1 < d->map_width)
			{
				set_point(d, &(l.p2), j, i + 1);
				l.c2 = d->color[j][i + 1] * d->color_mod;
				if (l.p1.z >= max_z && l.p2.z >= max_z)
					draw_line(d, l.p1, l.p2, (l.c1 + l.c2) / 2);
			}
			if (j + 1 < d->map_height)
			{
				set_point(d, &(l.p2), j + 1, i);
				l.c2 = d->color[j + 1][i] * d->color_mod;
				if (l.p1.z >= max_z && l.p2.z >= max_z)
					draw_line(d, l.p1, l.p2, (l.c1 + l.c2) / 2);
			}
		}
}

static void	apply_key_1(t_fdf *d)
{
	if (d->keys & k_p_LEFT)
		d->x_offset += 10;
	if (d->keys & k_p_RIGHT)
		d->x_offset -= 10;
	if (d->keys & k_p_UP)
		d->y_offset += 10;
	if (d->keys & k_p_DOWN)
		d->y_offset -= 10;
	if (d->keys & k_p_KP_P)
		d->zoom *= 1.01f;
	if (d->keys & k_p_KP_M)
		d->zoom /= 1.01f;
	if (d->keys & k_p_SHIFT_R)
		d->height_mod += 0.03f;
	if (d->keys & k_p_CTRL_R)
		d->height_mod -= 0.03f;
	if (d->keys & k_p_KEY_A)
		d->color_mod *= 1.0001f;
	if (d->keys & k_p_KEY_S)
		d->color_mod /= 1.0001f;
}

static void	apply_key_2(t_fdf *d)
{
	if (d->keys & k_p_KP_8)
		rot_x(&(d->rot), 0.05f);
	if (d->keys & k_p_KP_5)
		rot_x(&(d->rot), -0.05f);
	if (d->keys & k_p_KP_4)
		rot_y(&(d->rot), 0.05f);
	if (d->keys & k_p_KP_6)
		rot_y(&(d->rot), -0.05f);
	if (d->keys & k_p_KP_7)
		rot_z(&(d->rot), 0.05f);
	if (d->keys & k_p_KP_9)
		rot_z(&(d->rot), -0.05f);
	if (d->keys & k_p_KP_1)
		d->fov *= 1.01f;
	if (d->keys & k_p_KP_3)
		d->fov /= 1.01f;
}

int			fdf_loop(void *param)
{
	t_fdf		*d;

	d = (t_fdf *)param;
	if (!(d->keys))
		return (inactive_loop((t_fdf *)param));
	apply_key_1(d);
	apply_key_2(d);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, d->width, d->height);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->l_size, &d->endian);
	draw_img(d, d->fov * -20);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->keys &= ~k_p_NOT_DRAWN;
	return (1);
}
