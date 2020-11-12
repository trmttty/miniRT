/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 22:45:45 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 18:21:22 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	parse_line(t_rt *rt)
{
	if (!(rt->tab = ft_split(rt->line, ' ')))
		handle_perror("Failed split line", rt);
	if (ft_strncmp(*rt->tab, "R", 2) == 0)
		return (parse_resolution(rt));
	else if (ft_strncmp(*rt->tab, "A", 2) == 0)
		return (parse_ambient(rt));
	else if (ft_strncmp(*rt->tab, "l", 2) == 0)
		return (parse_light(rt));
	else if (ft_strncmp(*rt->tab, "sp", 3) == 0)
		return (parse_sphere(rt));
	else if (ft_strncmp(*rt->tab, "pl", 3) == 0)
		return (parse_plane(rt));
	else if (ft_strncmp(*rt->tab, "sq", 3) == 0)
		return (parse_square(rt));
	else if (ft_strncmp(*rt->tab, "cy", 3) == 0)
		return (parse_cylinder(rt));
	else if (ft_strncmp(*rt->tab, "tr", 3) == 0)
		return (parse_triangle(rt));
	else if (ft_strncmp(*rt->tab, "c", 2) == 0)
		return (parse_camera(rt));
	handle_error(-1, "Invalid type identifier", rt);
}

void		parse_rt(int argc, char **argv, t_rt *rt)
{
	int		fd;
	int		rv;

	if (argc == 3)
		rt->save = 1;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		handle_perror("Failed to open scene file", rt);
	while ((rv = get_next_line(fd, &(rt->line))) > 0)
	{
		if (ft_isalpha(*(rt->line)))
			parse_line(rt);
		free(rt->line);
		rt->line = NULL;
	}
	if (ft_isalpha(*(rt->line)))
		parse_line(rt);
	free(rt->line);
	rt->line = NULL;
	if (close(fd) == -1)
		handle_perror("Failed close file", rt);
}
