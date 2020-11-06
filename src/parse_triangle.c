/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:10:12 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/05 22:19:34 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_triangle(t_rt *rt)
{
	t_tr	*tr;
	t_obj	*obj;

	if (!(tr = ft_calloc(1, sizeof(t_tr))))
		handle_perror("Failed to calloc triangle", rt);
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc triangle object", rt);
	if (tabsize(rt->tab) != 5)
		handle_error(22, "Failed to parse tr", rt);
	tr->v0 = parse_vector(rt->tab[1], rt);
	tr->v1 = parse_vector(rt->tab[2], rt);
	tr->v2 = parse_vector(rt->tab[3], rt);
	tr->col = parse_color(rt->tab[4], rt);
	tr->normal = cross(sub(tr->v1, tr->v0), sub(tr->v2, tr->v0));
	normalize(&tr->normal);
	obj->shape.tr = tr;
	obj->type = TRIANGLE;
	obj->col = tr->col;
	ft_tabfree(rt->tab);
	ft_lstadd_back(&rt->obj_lst, ft_lstnew(obj));
}
