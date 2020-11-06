/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 11:13:06 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/09 01:56:10 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void	set_img(t_rt *rt)
{
	rt->cam->img.img = mlx_new_image(rt->mlx, rt->res.x, rt->res.y);
	rt->cam->img.addr = mlx_get_data_addr(rt->cam->img.img, &rt->cam->img.bits_per_pixel, &rt->cam->img.line_length, &rt->cam->img.endian);
}

void	create_img(t_rt *rt)
{
	t_list *tmp;

	if (!(rt->mlx = mlx_init()))
		handle_error(4, "Failed to initialize Minilibx", rt);
	if (!rt->save)
	{
		if (!(rt->win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "miniRT")))
			handle_error(4, "Failed to initialize Minilibx", rt);
	}
	tmp = rt->cam_lst;
	while (tmp)
	{
		rt->cam = (t_camera*)(tmp->content);
		set_img(rt);
		set_raytrace(rt);
		tmp = tmp->next;
	}
}