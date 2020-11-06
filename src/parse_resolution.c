/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 08:48:54 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/09 02:11:28 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		parse_resolution(t_rt *rt)
{
	int	sizex;
	int	sizey;

	if (rt->res.read)
		handle_error(22, "Resolution can only be declared once", rt);
	if (tabsize(rt->tab) != 3)
		handle_error(22, "Invalid resolution", rt);
	if ((rt->res.x = ft_atoi(rt->tab[1])) <= 0)
		handle_error(22, "Failed parse x render size", rt);
	if ((rt->res.y = ft_atoi(rt->tab[2])) <= 0)
		handle_error(22, "Failed parse y render size", rt);
	mlx_get_screen_size(rt->mlx, &sizex, &sizey);
	if (rt->res.x > sizex)
		rt->res.x = sizex;
	if (rt->res.y > sizey)
		rt->res.y = sizey;
	rt->res.read = 1;
	ft_tabfree(rt->tab);
}
