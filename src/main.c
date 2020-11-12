/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 07:09:47 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 15:58:07 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	next_camera(int keycode, t_rt *rt)
{
	if (keycode == 53)
	{
		exit(0);
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

int			print(int keycode, t_rt *rt)
{
	printf("a\n");
	return (0);
}

void		check_argument(int argc, char *argv[])
{
	if (!(argc == 2 || (argc == 3 && ft_strncmp(argv[2], "–-save", 7) == 0)))
		handle_argument_error("Invalid arguments");
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 4))
		handle_argument_error("Invalid file extension");
}

int			main(int argc, char *argv[])
{
	t_rt	rt;

	check_argument(argc, argv);
	ft_memset(&rt, 0, sizeof(t_rt));
	if (!(rt.mlx = mlx_init()))
		handle_error(4, "Failed to initialize Minilibx", &rt);
	parse_rt(argc, argv, &rt);
	create_img(&rt);
	// free all;
	rt.cam_crrnt = rt.cam_lst;
	rt.cam = (t_camera*)(rt.cam_crrnt->content);
	// create_bmp_image(&rt, "test");
	export_bmp("test", &rt);
	mlx_put_image_to_window(rt.mlx, rt.win, rt.cam->img.img, 0, 0);
	mlx_hook(rt.win, 2, 1L<<0, next_camera, &rt);
	mlx_hook(rt.win, 17, 1L<<17, print, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
