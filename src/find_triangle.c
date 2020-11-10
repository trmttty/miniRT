/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:19:16 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int			find_triangle(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_tr		*tr;
	float		dn_dot;
	t_vector	s_p;
	float		t;

	tr = rt->obj->shape.tr;
	dn_dot = dot(ray->dir, tr->normal);
	if (dn_dot != 0)
	{
		s_p = sub(ray->start, tr->v0);
		t = -dot(s_p, tr->normal) / dn_dot;
		if (t > 0)
		{
			t_vector p;

			p = add(ray->start, multi(ray->dir, t));
			if (dot(tr->normal, cross(sub(tr->v1, tr->v0), sub(p, tr->v0))) > 0
			&& dot(tr->normal, cross(sub(tr->v2, tr->v1), sub(p, tr->v1))) > 0
			&& dot(tr->normal, cross(sub(tr->v0, tr->v2), sub(p, tr->v2))) > 0)
			{
				intp->dist = t;
				intp->pos = add(ray->start, multi(ray->dir, t));
				if (dot(ray->dir, tr->normal) < 0)
					intp->normal = tr->normal;
				else
					intp->normal = multi(tr->normal, -1);
				normalize(&intp->normal);
				return (1);
			}
		}
	}
	return (0);
}
