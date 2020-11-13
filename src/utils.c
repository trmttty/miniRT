/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:58:48 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/14 01:10:55 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float   ft_sqr(float x)
{
    return (x * x);
}

float   ft_min(float x, float y)
{
    if (x < y)
        return (x);
    return (y);
}

float   ft_max(float x, float y)
{
    if (x > y)
        return (x);
    return (y);
}

float   ft_clamp(float v, float minv, float maxv)
{
    return (ft_min(ft_max(v, minv), maxv));
}
