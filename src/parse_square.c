/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:23:40 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/10 22:59:55 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_square(t_rt *rt)
{
	t_sq	*sq;
	t_obj	*obj;

	if (!(sq = ft_calloc(1, sizeof(t_sq))))
		handle_perror("Failed to calloc square", rt);
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc square object", rt);
	if (tabsize(rt->tab) != 5)
		handle_error(22, "Failed to parse sq", rt);
	sq->sc = parse_vector(rt->tab[1], rt);
	sq->normal = parse_vector(rt->tab[2], rt);
	normalize(&sq->normal);
	sq->side = ft_atof(rt->tab[3]);
	sq->col = parse_color(rt->tab[4], rt);
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
	ft_lstadd_back(&rt->obj_lst, ft_lstnew(obj));
}
