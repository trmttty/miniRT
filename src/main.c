/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 07:09:47 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 12:11:29 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			exit_minirt(int keycode, t_rt *rt)
{
	exit(EXIT_SUCCESS);
}

static int	next_camera(int keycode, t_rt *rt)
{
	if (keycode == 53)
	{
		exit(EXIT_SUCCESS);
	}
	if (keycode == 48)
	{
		rt->cam_crrnt = rt->cam_crrnt->next;
		if (!rt->cam_crrnt)
			rt->cam_crrnt = rt->cam_lst;
		rt->cam = (t_camera*)(rt->cam_crrnt->content);
		mlx_clear_window(rt->mlx, rt->win);
		mlx_put_image_to_window(rt->mlx, rt->win, rt->cam->img.img, 0, 0);
	}
	mlx_hook(rt->win, 2, 1L<<0, next_camera, rt);
	mlx_loop(rt->mlx);
	return (0);
}

void		check_argument(int argc, char *argv[])
{
	if (!(argc == 2 || (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)))
		handle_argument_error("Invalid arguments");
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 4))
		handle_argument_error("Invalid file extension");
}

int			main(int argc, char *argv[])
{
	t_rt	rt;

	check_argument(argc, argv);
	ft_memset(&rt, 0, sizeof(t_rt));
	parse_rt(argc, argv, &rt);
	create_img(&rt);
	rt.cam_crrnt = rt.cam_lst;
	rt.cam = (t_camera*)(rt.cam_crrnt->content);
	// create_bmp_image(&rt, "test");
	if (rt.save)
		create_bmp(&rt);
		// export_bmp("test", &rt);
	else
	{
		mlx_put_image_to_window(rt.mlx, rt.win, rt.cam->img.img, 0, 0);
		mlx_hook(rt.win, 2, 1L<<0, next_camera, &rt);
		mlx_hook(rt.win, 17, 1L<<17, exit_minirt, &rt);
		mlx_loop(rt.mlx);
	}
	return (0);
}
