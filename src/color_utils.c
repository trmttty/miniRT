/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 23:47:50 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:37:36 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

t_colorf		c_multi(t_colorf c, float r)
{
	t_colorf ret;

	ret.r = r * c.r;
	ret.g = r * c.g;
	ret.b = r * c.b;
	return (ret);
}

t_colorf		c_add(t_colorf c1, t_colorf c2)
{
	t_colorf ret;

	ret.r = c1.r + c2.r;
	ret.g = c1.g + c2.g;
	ret.b = c1.b + c2.b;
	return (ret);
}

t_colorf		calc_color(t_colorf c1, t_colorf c2)
{
	t_colorf ret;

	ret.r = c1.r * c2.r;
	ret.g = c1.g * c2.g;
	ret.b = c1.b * c2.b;
	return (ret);
}

int				convert_colorf(t_colorf c)
{
	return (((int)(255 * CLAMP(c.r, 0, 1)) << 16) + \
			((int)(255 * CLAMP(c.g, 0, 1)) << 8) + \
			(int)(255 * CLAMP(c.b, 0, 1)));
}
