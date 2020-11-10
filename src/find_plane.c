/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:18:13 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int			find_plane(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_pl		*pl;
	float		dn_dot;
	t_vector	s_p;
	float		t;

	pl = rt->obj->shape.pl;
	dn_dot = dot(ray->dir, pl->normal);
	if (dn_dot != 0)
	{
		s_p = sub(ray->start, pl->pos);
		t = -dot(s_p, pl->normal) / dn_dot;
		if (t > 0)
		{
			intp->dist = t;
			intp->pos = add(ray->start, multi(ray->dir, t));
			if (dot(ray->dir, pl->normal) < 0)
				intp->normal = pl->normal;
			else
				intp->normal = multi(pl->normal, -1);
			normalize(&intp->normal);
			return (1);
		}
	}
	return (0);
}
