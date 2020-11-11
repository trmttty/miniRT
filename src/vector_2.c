/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 00:55:56 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 18:45:14 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	float vnorm;

	vnorm = norm(*v);
	v->x /= vnorm;
	v->y /= vnorm;
	v->z /= vnorm;
	return (vnorm);
}
