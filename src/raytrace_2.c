/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 09:43:41 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 12:08:46 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int			get_nearest_object(t_rt *rt, t_ray *ray, t_obj **obj)
{
	t_obj		*nearest_obj;
	t_ip		nearest_intp;
	t_list		*tmp;
	t_ip		intp;

	nearest_obj = NULL;
	nearest_intp.dist = MAXFLOAT;
	tmp = rt->obj_lst;
	while (tmp)
	{
		rt->obj = (t_obj*)tmp->content;
		if (find_intersection(rt, ray, &intp) && intp.dist < nearest_intp.dist)
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
