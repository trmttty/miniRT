/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 00:55:56 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/04 01:01:22 by ttarumot         ###   ########.fr       */
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

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vector	vectornew(float a, float b, float c)
{
	t_vector v;

	v.x = a;
	v.y = b;
	v.z = c;
	return (v);
}

float		squared_norm(const t_vector v)
{
	return (SQR(v.x) + SQR(v.y) + SQR(v.z));
}

float		norm(const t_vector v)
{
	return (sqrt(squared_norm(v)));
}

float		normalize(t_vector *v)
{
	float vnorm = norm(*v);
	v->x /= vnorm;
	v->y /= vnorm;
	v->z /= vnorm;
	return (vnorm);
}
