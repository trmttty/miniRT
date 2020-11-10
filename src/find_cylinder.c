/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:21:46 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int			find_cylinder(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_cy		*cy = rt->obj->shape.cy;
	t_vector	v_ce, A, dP, B;
	float		a, b, c, d;
	float		t;

	dP = sub(ray->start, cy->bottom);
	A = sub(ray->dir, multi(cy->normal, dot(ray->dir, cy->normal)));
	a = dot(A, A);
	B = sub(dP, multi(cy->normal, dot(dP, cy->normal)));	
	b = 2 * dot(A, B);
	c = dot(B, B) - SQR(cy->diameter / 2.0f);
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
		t_vector p;
		
		p = add(ray->start, multi(ray->dir, t));

		if (dot(cy->normal, sub(p, cy->bottom)) > 0
		&& dot(cy->normal, sub(p, cy->top)) < 0)
		{
			intp->dist = t;
			intp->pos = p;
			intp->normal = sub(intp->pos, add(cy->bottom, multi(cy->normal, sqrt(dot(sub(intp->pos, cy->bottom), sub(intp->pos, cy->bottom)) - SQR(cy->diameter / 2.0f)))));
			normalize(&intp->normal);
			return (1);
		}
	}
	return (0);
}

int			find_cap(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_cp		*cp;
	float		dn_dot;
	t_vector	s_p;
	float		t;

	cp = rt->obj->shape.cp;
	dn_dot = dot(ray->dir, cp->normal);
	if (dn_dot != 0)
	{
		s_p = sub(ray->start, cp->pos);
		t = -dot(s_p, cp->normal) / dn_dot;
		if (t > 0)
		{
			t_vector p;

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
