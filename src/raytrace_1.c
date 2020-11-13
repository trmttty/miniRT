/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 09:43:41 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/14 01:11:59 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

static void	calc_specular(t_rt *rt, t_raytrace *r, t_obj *obj, \
							t_calc_reflection *cr)
{
	t_vector	ref_dir;
	t_vector	inv_eye_dir;
	float		vr_dot;
	float		vr_dot_pow;

	if (cr->nl_dot > 0)
	{
		ref_dir = sub(multi(obj->ip.normal, 2 * cr->nl_dot), r->light_dir);
		normalize(&ref_dir);
		inv_eye_dir = multi(r->eye_ray.dir, -1);
		normalize(&inv_eye_dir);
		vr_dot = dot(ref_dir, inv_eye_dir);
		vr_dot = ft_clamp(vr_dot, 0, 1);
		vr_dot_pow = pow(vr_dot, 50.0);
		cr->t_c = c_multi(rt->light->color, 0.3);
		cr->t_c = c_multi(cr->t_c, vr_dot_pow);
		r->col = c_add(r->col, cr->t_c);
	}
}

static void	calc_reflection(t_rt *rt, t_raytrace *r, t_obj *obj)
{
	t_calc_reflection	cr;

	cr.nl_dot = dot(r->light_dir, obj->ip.normal);
	cr.nl_dot = ft_clamp(cr.nl_dot, 0, 1);
	cr.t_c = c_multi(rt->light->color, rt->light->ratio);
	cr.t_c = c_multi(cr.t_c, cr.nl_dot);
	cr.t_c = calc_color(cr.t_c, obj->col);
	r->col = c_add(r->col, cr.t_c);
	calc_specular(rt, r, obj, &cr);
}

static void	setting(t_rt *rt, t_raytrace *r, float *light_dist, t_obj *obj)
{
	r->light_dir = sub(rt->light->lp, obj->ip.pos);
	*light_dist = norm(r->light_dir) - EPSILON;
	normalize(&r->light_dir);
}

void		raytrace(t_rt *rt, t_raytrace *r)
{
	t_obj		*obj;
	t_obj		*obj_s;
	t_list		*tmp;
	float		light_dist;
	t_ray		shadow_ray;

	r->col = (t_colorf){0.0, 0.0, 0.0};
	if (get_nearest_object(rt, &r->eye_ray, &obj))
	{
		r->col = calc_color(c_multi(rt->amb.color, rt->amb.ratio), obj->col);
		tmp = rt->light_lst;
		while (tmp)
		{
			rt->light = (t_light*)tmp->content;
			tmp = tmp->next;
			setting(rt, r, &light_dist, obj);
			shadow_ray.start = add(obj->ip.pos, multi(obj->ip.normal, EPSILON));
			shadow_ray.dir = r->light_dir;
			if (get_nearest_object(rt, &shadow_ray, &obj_s) \
				&& (obj_s->ip.dist < light_dist))
				continue;
			calc_reflection(rt, r, obj);
		}
	}
}
