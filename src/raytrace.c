/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 09:43:41 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/10 16:57:30 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void		raytrace(t_rt *rt, t_raytrace *r)
{
	t_obj		*obj;
	t_obj		*obj_s;
	t_list		*tmp;
	float		light_dist;
	t_ray		shadow_ray;
	float		nl_dot;
	t_colorf	t_c;

	r->col = (t_colorf){0.0, 0.0, 0.0};
	if (get_nearest_object(rt, &r->eye_ray, &obj))
	{
		// ambient
		r->col = calc_color(c_multi(rt->amb.color, rt->amb.ratio), obj->col);
		tmp = rt->light_lst;
		while (tmp)
		{
			rt->light = (t_light*)tmp->content;
			r->light_dir = sub(rt->light->lp, obj->ip.pos);
			light_dist = norm(r->light_dir) - EPSILON;
			normalize(&r->light_dir);
			// shadow_ray.start = add(obj->ip.pos, multi(r->light_dir, EPSILON));
			shadow_ray.start = add(obj->ip.pos, multi(obj->ip.normal, EPSILON));
			shadow_ray.dir = r->light_dir;
			// obj_s = NULL;

			// shadow
			if (get_nearest_object(rt, &shadow_ray, &obj_s))
			{
				// printf("%f %f %f\n", obj->ip.pos.x, obj->ip.pos.y, obj->ip.pos.z);
				// printf("%f %f %f\n", obj->ip.pos.x, obj->ip.pos.y, obj->ip.pos.z);
				if (obj_s->ip.dist < light_dist)
				{
					tmp = tmp->next;
					continue;
				}
			}
			// deffuse
			nl_dot = dot(r->light_dir, obj->ip.normal);
			nl_dot = CLAMP(nl_dot, 0, 1);
			t_c = c_multi(rt->light->color, rt->light->ratio);
			t_c = c_multi(t_c, nl_dot);
			t_c = calc_color(t_c, obj->col);
			r->col = c_add(r->col, t_c); 

			// specular optional
			if (nl_dot > 0)
			{
				t_vector	ref_dir;
				t_vector	inv_eye_dir;
				float		vr_dot;
				float		vr_dot_pow;

				ref_dir = sub(multi(obj->ip.normal, 2 * nl_dot), r->light_dir);
				normalize(&ref_dir);
				inv_eye_dir = multi(r->eye_ray.dir, -1);
				normalize(&inv_eye_dir);

				vr_dot = dot(ref_dir, inv_eye_dir);
				vr_dot = CLAMP(vr_dot, 0, 1);
				vr_dot_pow = pow(vr_dot, 50.0);

				t_c = c_multi(rt->light->color, 0.3);
				t_c = c_multi(t_c, vr_dot_pow);
				r->col = c_add(r->col, t_c); 
			}
			tmp = tmp->next;
		}
	}
}

int			get_nearest_object(t_rt *rt, t_ray *ray, t_obj **obj)
{
	size_t		i;
	t_obj		*nearest_obj = NULL;
	t_ip		nearest_intp;
	t_list		*tmp;

	nearest_intp.dist = MAXFLOAT;
	tmp = rt->obj_lst;
	while (tmp)
	{
		int		res;
		t_ip	intp;

		rt->obj = (t_obj*)tmp->content;
		res = find_intersection(rt, ray, &intp);
		if (res && intp.dist < nearest_intp.dist)
		{
			nearest_obj = rt->obj;
			nearest_intp = intp;
		}
		tmp = tmp->next;
	}
	if (nearest_obj)
	{
		*obj = nearest_obj;
		(*obj)->ip = nearest_intp;
		return (1);
	}
	return (0);
}

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
		{
			t_vector p;
			t_vector cp;

			p = add(ray->start, multi(ray->dir, t));
			cp = sub(p, sq->sc);
			if (dot(cp, sq->dx) >= -sq->side / 2.0f && dot(cp, sq->dx) <= sq->side / 2.0f
			&& dot(cp, sq->dy) >= -sq->side / 2.0f && dot(cp, sq->dy) <= sq->side / 2.0f)
			{
				intp->dist = t;
				intp->pos = add(ray->start, multi(ray->dir, t));
				if (dot(ray->dir, sq->normal) < 0)
					intp->normal = sq->normal;
				else
					intp->normal = multi(sq->normal, -1);
				return (1);
			}
		}
	}
	return (0);
}

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
