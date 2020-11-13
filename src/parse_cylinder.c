/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:35:27 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 08:46:30 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	parse_cap_sub(t_cy *cy, t_cp *cap, t_obj *obj)
{
	cap->diameter = cy->diameter;
	cap->col = cy->col;
	obj->shape.cp = cap;
	obj->type = CAP;
	obj->col = cap->col;
}

static void	parse_cap(t_rt *rt, t_cy *cy, int p)
{
	t_cp	*cap;
	t_obj	*obj;
	t_list	*element;

	if (!(cap = ft_calloc(1, sizeof(t_cp))))
		handle_perror("Failed to calloc cap", rt);
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc cap object", rt);
	if (!(element = ft_lstnew(obj)))
		handle_perror("Failed to lstnew obj", rt);
	ft_lstadd_back(&rt->obj_lst, ft_lstnew(obj));
	if (p == TOP)
	{
		cap->pos = cy->top;
		cap->normal = cy->normal;
	}
	else
	{
		cap->pos = cy->bottom;
		cap->normal = multi(cy->normal, -1);
	}
	parse_cap_sub(cy, cap, obj);
}

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
	obj->shape.cy = cy;
	obj->type = CYLINDER;
	obj->col = cy->col;
	ft_tabfree(rt->tab);
	ft_lstadd_back(&rt->obj_lst, ft_lstnew(obj));
	parse_cap(rt, cy, TOP);
	parse_cap(rt, cy, BOTTOM);
}
