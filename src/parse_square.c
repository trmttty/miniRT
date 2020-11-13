/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:23:40 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 09:15:00 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	parse_square_sub(t_rt *rt, t_sq *sq, t_obj *obj)
{
	sq->up = (t_vector){0, 1, 0};
	if (norm(cross(sq->up, sq->normal)) == 0)
		sq->up = vectornew(0, 0, 1);
	sq->dx = cross(sq->up, sq->normal);
	normalize(&sq->dx);
	sq->dy = cross(sq->normal, sq->dx);
	normalize(&sq->dy);
	obj->shape.sq = sq;
	obj->type = SQUARE;
	obj->col = sq->col;
	ft_tabfree(rt->tab);
	rt->tab = NULL;
}

void		parse_square(t_rt *rt)
{
	t_sq	*sq;
	t_obj	*obj;
	t_list	*element;

	if (!(sq = ft_calloc(1, sizeof(t_sq))))
		handle_perror("Failed to calloc square", rt);
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc square object", rt);
	if (!(element = ft_lstnew(obj)))
		handle_perror("Failed to lstnew obj", rt);
	ft_lstadd_back(&rt->obj_lst, element);
	if (tabsize(rt->tab) != 5)
		handle_error(22, "Failed to parse sq", rt);
	sq->sc = parse_vector(rt->tab[1], rt);
	sq->normal = parse_normal(rt->tab[2], rt);
	normalize(&sq->normal);
	sq->side = ft_atof(rt->tab[3]);
	sq->col = parse_color(rt->tab[4], rt);
	parse_square_sub(rt, sq, obj);
}
