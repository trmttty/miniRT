/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 11:07:47 by ttarumot         ###   ########.fr       */
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
	d->c = dot(b, b) - SQR(cy->diameter / 2.0f);
	d->d = SQR(d->b) - 4 * d->a * d->c;
}

static float	calc_t(t_discriminant *d)
{
	float	t;
	float	t1;
	float	t2;

	t = -1.0f;
	if (d->d == 0)
		t = -d->b / (2 * d->a);
	else if (d->d > 0)
	{
		t1 = (-d->b + sqrt(d->d)) / (2 * d->a);
		t2 = (-d->b - sqrt(d->d)) / (2 * d->a);
		if (t1 > 0)
			t = t1;
		if (t2 > 0 && t2 < t1)
			t = t2;
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
	t = calc_t(&d);
	if (t > 0)
	{
		cy = rt->obj->shape.cy;
		p = add(ray->start, multi(ray->dir, t));
		if (dot(cy->normal, sub(p, cy->bottom)) > 0
		&& dot(cy->normal, sub(p, cy->top)) < 0)
		{
			intp->dist = t;
			intp->pos = p;
			intp->normal = sub(intp->pos, add(cy->bottom, multi(cy->normal, \
							sqrt(dot(sub(intp->pos, cy->bottom), \
							sub(intp->pos, cy->bottom)) - \
							SQR(cy->diameter / 2.0f)))));
			normalize(&intp->normal);
			return (1);
		}
	}
	return (0);
}

int				find_cap(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_cp		*cp;
	t_vector	p;
	float		dn_dot;
	float		t;

	cp = rt->obj->shape.cp;
	dn_dot = dot(ray->dir, cp->normal);
	if (dn_dot != 0)
	{
		t = -dot(sub(ray->start, cp->pos), cp->normal) / dn_dot;
		if (t > 0)
		{
			p = sub(add(ray->start, multi(ray->dir, t)), cp->pos);
			if (dot(p, p) < SQR(cp->diameter / 2.0f))
			{
				intp->dist = t;
				intp->pos = add(ray->start, multi(ray->dir, t));
				intp->normal = cp->normal;
				normalize(&intp->normal);
				return (1);
			}
		}
	}
	return (0);
}
