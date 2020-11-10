/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:16:29 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:23:06 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int			find_intersection(t_rt *rt, t_ray *ray, t_ip *intp)
{
	if (rt->obj->type == SPHERE)
		return (find_sphere(rt, ray, intp));
	if (rt->obj->type == PLANE)
		return (find_plane(rt, ray, intp));
	if (rt->obj->type == SQUARE)
		return (find_square(rt, ray, intp));
	if (rt->obj->type == CYLINDER)
		return (find_cylinder(rt, ray, intp));
	if (rt->obj->type == CAP)
		return (find_cap(rt, ray, intp));
	if (rt->obj->type == TRIANGLE)
		return (find_triangle(rt, ray, intp));
	return (0);
}
