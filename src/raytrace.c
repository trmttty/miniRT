/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 09:43:41 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:23:12 by ttarumot         ###   ########.fr       */
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
