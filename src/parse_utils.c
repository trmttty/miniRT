/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 09:15:00 by ttarumot          #+#    #+#             */
/*   Updated: 2020/08/03 23:44:32 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

size_t		tabsize(char **tab)
{
	size_t size;

	size = 0;
	if (!tab)
		return (size);
	while (*tab)
	{
		size++;
		tab++;
	}
	return (size);
}

t_colorf		parse_color(char *s, t_rt *rt)
{
	t_colorf	c;
	char	**rgb;
	size_t	size;
	int		n;

	if (!(rgb = ft_split(s, ',')))
		handle_perror("Failed to split color", rt);
	size = tabsize(rgb);
	if (size != 3)
	{
		ft_tabfree(rgb);
		handle_error(22, "Failed to parse color", rt);
	}
	while (size--)
	{
		if (ft_strlen(rgb[size]) > 3)
		{
			ft_tabfree(rgb);
			handle_error(22, "RGB colors in range [0-255]", rt);
		}
		n = ft_atoi(rgb[size]);
		if (n < 0 || n > 255)
		{
			ft_tabfree(rgb);
			handle_error(22, "RGB colors in range [0-255]", rt);
		}
	}
	c.r = ft_atoi(rgb[0]) / 255.0f;
	c.g = ft_atoi(rgb[1]) / 255.0f;
	c.b = ft_atoi(rgb[2]) / 255.0f;
	ft_tabfree(rgb);
	return (c);
}

t_vector	parse_vector(char *s, t_rt *rt)
{
	t_vector	v;
	char		**vec3;

	if (!(vec3 = ft_split(s, ',')))
		handle_perror("Failed split vector", rt);
	if (tabsize(vec3) != 3)
	{
		ft_tabfree(vec3);
		handle_error(22, "Failed parse vector", rt);
	}
	// TODO reproduce atof
	v.x = atof(vec3[0]);
	v.y = atof(vec3[1]);
	v.z = atof(vec3[2]);
	ft_tabfree(vec3);
	return (v);
}
