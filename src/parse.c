/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 22:45:45 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/09 01:58:29 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


static void	parse_line(t_rt *rt)
{
	if (!(rt->tab = ft_split(rt->line, ' ')))
		handle_perror("Failed split line", rt);
	if (ft_strncmp(*rt->tab, "R", 1) == 0)
		return (parse_resolution(rt));
	else if (ft_strncmp(*rt->tab, "A", 1) == 0)
		return (parse_ambient(rt));
	else if (ft_strncmp(*rt->tab, "l", 1) == 0)
		return (parse_light(rt));
	else if (ft_strncmp(*rt->tab, "sp", 2) == 0)
		return (parse_sphere(rt));
	else if (ft_strncmp(*rt->tab, "pl", 2) == 0)
		return (parse_plane(rt));
	else if (ft_strncmp(*rt->tab, "sq", 2) == 0)
		return (parse_square(rt));
	else if (ft_strncmp(*rt->tab, "cy", 2) == 0)
		return (parse_cylinder(rt));
	else if (ft_strncmp(*rt->tab, "tr", 2) == 0)
		return (parse_triangle(rt));
	else if (ft_strncmp(*rt->tab, "c", 1) == 0)
		return (parse_camera(rt));
}

void		parse_rt(int argc, char **argv, t_rt *rt)
{
	int		fd;
	int		rv;

	if (!(argc == 2 || (argc == 3 && ft_strncmp(argv[2], "–-save", 6) == 0)))
		handle_error(22, "Enter rt file path", rt);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		handle_error(22, "Enter rt file path", rt);
	if (argc == 3)
		rt->save = 1;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		handle_perror("Failed to open scene file", rt);
	// 必要か調べる
	rt->res.read = 0;
	rt->amb.read = 0;
	while ((rv = get_next_line(fd, &(rt->line))) > 0)
	{
		if (*(rt->line) != '\0' && *(rt->line) != '#')
			parse_line(rt);
		free(rt->line);
	}
	if (*(rt->line) != '\0')
		handle_error(22, "Invalid rt file", rt);
	free(rt->line);
	if (close(fd) == -1)
		handle_perror("Failed close file", rt);
}
