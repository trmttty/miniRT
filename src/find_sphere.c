/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 10:09:53 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

static void		discriminant(t_rt *rt, t_ray *ray, t_discriminant *d)
{
	t_sp			*sp;
	t_vector		v_ce;

	sp = rt->obj->shape.sp;
	v_ce = sub(ray->start, sp->sc);
	d->a = dot(ray->dir, ray->dir);
	d->b = 2 * dot(ray->dir, v_ce);
	d->c = dot(v_ce, v_ce) - SQR(sp->diameter / 2.0f);
	d->d = SQR(d->b) - 4 * d->a * d->c;
}

static float	calc_t(t_discriminant *d)
{
	float			t;
	float			t1;
	float			t2;

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

int				find_sphere(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_discriminant	d;
	float			t;

	discriminant(rt, ray, &d);
	t = calc_t(&d);
	if (t > 0)
	{
		intp->dist = t;
		intp->pos = add(ray->start, multi(ray->dir, t));
		intp->normal = sub(intp->pos, rt->obj->shape.sp->sc);
		normalize(&intp->normal);
		return (1);
	}
	return (0);
}
