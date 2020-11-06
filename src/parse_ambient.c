/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 11:19:22 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/09 01:46:48 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_ambient(t_rt *rt)
{
	if (rt->amb.read)
		handle_error(22, "Ambient light can be declared once", rt);
	if (tabsize(rt->tab) != 3)
		handle_error(22, "Invalid ambient light", rt);
	// TODO reprodude atof
	rt->amb.ratio = atof(rt->tab[1]);
	if (rt->amb.ratio < 0 || rt->amb.ratio > 1)
		handle_error(22, "Ambient lighting ratio in range [0.0,1.0]", rt);
	rt->amb.color = parse_color(rt->tab[2], rt);
	rt->amb.read = 1;
	ft_tabfree(rt->tab);
}
