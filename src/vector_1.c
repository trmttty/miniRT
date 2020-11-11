/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 00:55:56 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 18:44:27 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	sub(t_vector a, t_vector b)
{
	t_vector v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}

t_vector	add(t_vector a, t_vector b)
{
	t_vector v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vector	multi(t_vector a, float m)
{
	t_vector v;

	v.x = a.x * m;
	v.y = a.y * m;
	v.z = a.z * m;
	return (v);
}

t_vector	v_div(t_vector a, float d)
{
	t_vector v;

	v.x = a.x / d;
	v.y = a.y / d;
	v.z = a.z / d;
	return (v);
}

float		dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
