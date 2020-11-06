/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 10:57:53 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/01 10:58:33 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
/*
void	set_camera(t_rt *rt)
{
	rt->cam = rt->cam_lst->content;
}

void	set_rt(t_rt *rt)
{
	rt->ray.orig = (t_vector){rt->cam->vp.x, rt->cam->vp.y, rt->cam->vp.z};
	rt->aspect = (float)rt->res.x / (float)rt->res.y;
	rt->cam->up = (t_vector){0, -1, 0};
	rt->cam->right = cross(rt->cam->orient, rt->cam->up);
	rt->cam->up = cross(rt->cam->right, rt->cam->orient);
	rt->k = 0;
	rt->t = 0;
}
*/