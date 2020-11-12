/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:42:49 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 11:28:42 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	calc_ray(t_rt *rt, t_raytrace *r, int x, int y)
{
	t_calc_ray	cr;

	cr.aspect = rt->res.x / (float)rt->res.y;
	cr.pndc_x = (x + 0.5f) / rt->res.x;
	cr.pndc_y = (y + 0.5f) / rt->res.y;
	cr.pc_x = (2 * cr.pndc_x - 1) * cr.aspect * tan((rt->cam->fov / 2.0f) * \
				(M_PI / 180.0f));
	cr.pc_y = (1 - 2 * cr.pndc_y) * tan((rt->cam->fov / 2.0f) * \
				(M_PI / 180.0f));
	rt->cam->up = vectornew(0, 1, 0);
	if (norm(cross(rt->cam->up, rt->cam->orient)) == 0)
		rt->cam->up = vectornew(0, 0, 1);
	r->dx = cross(rt->cam->up, rt->cam->orient);
	normalize(&r->dx);
	r->dy = cross(rt->cam->orient, r->dx);
	normalize(&r->dy);
	cr.v = add(rt->cam->vp, rt->cam->orient);
	cr.v = add(cr.v, multi(r->dx, cr.pc_x));
	cr.v = add(cr.v, multi(r->dy, cr.pc_y));
	r->eye_ray.start = rt->cam->vp;
	r->eye_ray.dir = sub(cr.v, rt->cam->vp);
	normalize(&r->eye_ray.dir);
}

void	set_raytrace(t_rt *rt)
{
	t_raytrace		r;
	int				x;
	int				y;

	ft_memset(&r, 0, sizeof(r));
	y = 0;
	while (y < rt->res.y)
	{
		x = 0;
		while (x < rt->res.x)
		{
			calc_ray(rt, &r, x, y);
			raytrace(rt, &r);
			my_mlx_pixel_put(&rt->cam->img, x, y, convert_colorf(r.col));
			x++;
		}
		y++;
	}
}
