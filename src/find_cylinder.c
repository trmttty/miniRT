/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/14 01:02:51 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

static void		discriminant(t_rt *rt, t_ray *ray, t_discriminant *d)
{
	t_cy		*cy;
	t_vector	dp;
	t_vector	a;
	t_vector	b;

	cy = rt->obj->shape.cy;
	dp = sub(ray->start, cy->bottom);
	a = sub(ray->dir, multi(cy->normal, dot(ray->dir, cy->normal)));
	d->a = dot(a, a);
	b = sub(dp, multi(cy->normal, dot(dp, cy->normal)));
	d->b = 2 * dot(a, b);
	d->c = dot(b, b) - ft_sqr(cy->diameter / 2.0f);
	d->d = ft_sqr(d->b) - 4 * d->a * d->c;
}

static int		is_cylinder(t_cy *cy, t_ray *ray, float_t t)
{
	t_vector	p;

	p = add(ray->start, multi(ray->dir, t));
	return (dot(cy->normal, sub(p, cy->bottom)) > 0 \
			&& dot(cy->normal, sub(p, cy->top)) < 0 \
			&& t > 0);
}

static float	calc_t(t_discriminant *d, t_cy *cy, t_ray *ray)
{
	float		t;
	float		t1;
	float		t2;
	t_vector	p;

	t = -1.0f;
	if (d->d == 0)
		t = -d->b / (2 * d->a);
	else if (d->d > 0)
	{
		t1 = (-d->b + sqrt(d->d)) / (2 * d->a);
		t2 = (-d->b - sqrt(d->d)) / (2 * d->a);
		if (is_cylinder(cy, ray, t1))
		{
			t = t1;
			cy->inside = 1;
		}
		if (is_cylinder(cy, ray, t2))
		{
			t = t2;
			cy->inside = 0;
		}
	}
	return (t);
}

int				find_cylinder(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_cy			*cy;
	t_discriminant	d;
	t_vector		p;
	float			t;

	discriminant(rt, ray, &d);
	cy = rt->obj->shape.cy;
	t = calc_t(&d, cy, ray);
	p = add(ray->start, multi(ray->dir, t));
	if (t > 0 && dot(cy->normal, sub(p, cy->bottom)) > 0
	&& dot(cy->normal, sub(p, cy->top)) < 0)
	{
		intp->dist = t;
		intp->pos = p;
		intp->normal = sub(intp->pos, add(cy->bottom, multi(cy->normal, \
		sqrt(dot(sub(intp->pos, cy->bottom), sub(intp->pos, cy->bottom)) -\
		ft_sqr(cy->diameter / 2.0f)))));
		if (cy->inside)
			intp->normal = multi(intp->normal, -1.0f);
		normalize(&intp->normal);
		return (1);
	}
	return (0);
}
