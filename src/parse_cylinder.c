/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:35:27 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 22:34:36 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		parse_cylinder(t_rt *rt)
{
	t_cy	*cy;
	t_obj	*obj;

	if (!(cy = ft_calloc(1, sizeof(t_cy))))
		handle_perror("Failed to calloc cylinder", rt);
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc cylinder object", rt);
	if (tabsize(rt->tab) != 6)
		handle_error(22, "Failed to parse cy", rt);
	cy->bottom = parse_vector(rt->tab[1], rt);
	cy->normal = parse_vector(rt->tab[2], rt);
	normalize(&cy->normal);
	cy->col = parse_color(rt->tab[3], rt);
	cy->diameter = ft_atof(rt->tab[4]);
	cy->height = ft_atof(rt->tab[5]);
	cy->top = add(cy->bottom, multi(cy->normal, cy->height));
	cy->inside = 0;
	obj->shape.cy = cy;
	obj->type = CYLINDER;
	obj->col = cy->col;
	ft_tabfree(rt->tab);
	ft_lstadd_back(&rt->obj_lst, ft_lstnew(obj));
}
