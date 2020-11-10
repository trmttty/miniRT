/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:16:52 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int			find_sphere(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_sp		*sp = rt->obj->shape.sp;
	t_vector	v_ce;
	float		a, b, c, d;
	float		t;

	v_ce = sub(ray->start, sp->sc);
	a = dot(ray->dir, ray->dir);
	b = 2 * dot(ray->dir, v_ce);
	c = dot(v_ce, v_ce) - SQR(sp->diameter / 2.0f);
	d = SQR(b) - 4 * a * c;
	t = -1.0f;
	if (d == 0)
		t = -b / (2 * a);
	else if (d > 0)
	{
		float	t1 = (-b + sqrt(d)) / (2 * a);
		float	t2 = (-b - sqrt(d)) / (2 * a);
	
		if (t1 > 0)	t = t1;
		if (t2 > 0 && t2 < t1) t = t2;
	}
	if (t > 0)
	{
		intp->dist = t;
		intp->pos = add(ray->start, multi(ray->dir, t));
		intp->normal = sub(intp->pos, sp->sc);
		normalize(&intp->normal);
		return (1);
	}
	return (0);
}
