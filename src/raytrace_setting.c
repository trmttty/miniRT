/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:42:49 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/10 10:15:16 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	calc_ray(t_rt *rt, t_raytrace *r, int x, int y)
{
	float aspect;
	float pndc_x;
	float pndc_y;
	float pc_x;
	float pc_y;
	t_vector v1;
	t_vector v2;
	t_vector v3;
	t_vector v4;

	aspect = rt->res.x / (float)rt->res.y;
	pndc_x = (x + 0.5f) / rt->res.x;
	pndc_y = (y + 0.5f) / rt->res.y;
	pc_x = (2 * pndc_x - 1) * aspect * tan((rt->cam->fov / 2.0f) * (M_PI / 180.0f));
	pc_y = (1 - 2 * pndc_y) * tan((rt->cam->fov / 2.0f) * (M_PI / 180.0f));
	
	rt->cam->up = vectornew(0, 1, 0);
	if (norm(cross(rt->cam->up, rt->cam->orient)) == 0)
		rt->cam->up = vectornew(0, 0, 1);
	r->dx = cross(rt->cam->up, rt->cam->orient);
	normalize(&r->dx);
	r->dy = cross(rt->cam->orient, r->dx);
	normalize(&r->dy);

	v1 = multi(r->dx, pc_x);
	v2 = multi(r->dy, pc_y);
	v3 = add(rt->cam->vp, rt->cam->orient);
	v3 = add(v3, v1);
	v3 = add(v3, v2);
	r->eye_ray.start = rt->cam->vp;
	r->eye_ray.dir = sub(v3, rt->cam->vp);
	normalize(&r->eye_ray.dir);
	// printf("%f %f %f\n", r->dx.x, r->dx.y, r->dx.z);
	// printf("%f %f %f\n", r->dy.x, r->dy.y, r->dy.z);
	// printf("%f %f %f\n", v3.x, v3.y, v3.z);
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