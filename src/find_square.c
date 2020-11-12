/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 10:26:08 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

static int	find_intp(t_rt *rt, t_ray *ray, t_ip *intp, float t)
{
	t_sq		*sq;
	t_vector	p;
	t_vector	cp;

	sq = rt->obj->shape.sq;
	p = add(ray->start, multi(ray->dir, t));
	cp = sub(p, sq->sc);
	if (dot(cp, sq->dx) >= -sq->side / 2.0f && dot(cp, sq->dx) \
		<= sq->side / 2.0f
	&& dot(cp, sq->dy) >= -sq->side / 2.0f && dot(cp, sq->dy) \
		<= sq->side / 2.0f)
	{
		intp->dist = t;
		intp->pos = add(ray->start, multi(ray->dir, t));
		if (dot(ray->dir, sq->normal) < 0)
			intp->normal = sq->normal;
		else
			intp->normal = multi(sq->normal, -1);
		return (1);
	}
	return (0);
}

int			find_square(t_rt *rt, t_ray *ray, t_ip *intp)
{
	t_sq		*sq;
	float		dn_dot;
	t_vector	s_p;
	float		t;

	sq = rt->obj->shape.sq;
	dn_dot = dot(ray->dir, sq->normal);
	if (dn_dot != 0)
	{
		s_p = sub(ray->start, sq->sc);
		t = -dot(s_p, sq->normal) / dn_dot;
		if (t > 0)
			return (find_intp(rt, ray, intp, t));
	}
	return (0);
}
