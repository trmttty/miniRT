/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 01:11:53 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 08:37:03 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_light(t_rt *rt)
{
	t_light		*light;
	t_list		*element;

	if (!(light = ft_calloc(1, sizeof(t_light))))
		handle_perror("Failed to calloc light", rt);
	if (!(element = ft_lstnew(light)))
		handle_perror("Failed to lstnew light", rt);
	ft_lstadd_back(&rt->light_lst, element);
	if (tabsize(rt->tab) != 4)
		handle_error(22, "Failed to parse l", rt);
	light->lp = parse_vector(rt->tab[1], rt);
	light->ratio = ft_atof(rt->tab[2]);
	if (light->ratio < 0 || light->ratio > 1)
		handle_error(22, "Light brightness ratio in range [0.0,1.0]", rt);
	light->color = parse_color(rt->tab[3], rt);
	ft_tabfree(rt->tab);
	rt->tab = NULL;
}
