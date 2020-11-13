/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:29:17 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 08:36:54 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_plane(t_rt *rt)
{
	t_pl	*pl;
	t_obj	*obj;
	t_list	*element;

	if (!(pl = ft_calloc(1, sizeof(t_pl))))
		handle_perror("Failed to calloc plane", rt);
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc plane object", rt);
	if (!(element = ft_lstnew(obj)))
		handle_perror("Failed to lstnew obj", rt);
	ft_lstadd_back(&rt->obj_lst, element);
	if (tabsize(rt->tab) != 4)
		handle_error(22, "Failed to parse pl", rt);
	pl->pos = parse_vector(rt->tab[1], rt);
	pl->normal = parse_normal(rt->tab[2], rt);
	normalize(&pl->normal);
	pl->col = parse_color(rt->tab[3], rt);
	obj->shape.pl = pl;
	obj->type = PLANE;
	obj->col = pl->col;
	ft_tabfree(rt->tab);
	rt->tab = NULL;
}
