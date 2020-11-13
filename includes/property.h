/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:23:16 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 22:23:11 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTY_H
# define PROPERTY_H

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_colorf
{
	float		r;
	float		g;
	float		b;
}				t_colorf;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_res
{
	int			x;
	int			y;
	int			read;
}				t_res;

typedef struct	s_amb
{
	float		ratio;
	t_colorf	color;
	int			read;
}				t_amb;

typedef struct	s_camera
{
	t_vector	vp;
	t_vector	orient;
	t_vector	up;
	t_vector	right;
	int			fov;
	t_img		img;
}				t_camera;

typedef struct	s_light
{
	t_vector	lp;
	float		ratio;
	t_colorf	color;
}				t_light;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_sp
{
	t_vector	sc;
	float		diameter;
	t_colorf	color;
}				t_sp;

typedef struct	s_pl
{
	t_vector	pos;
	t_vector	normal;
	t_colorf	col;
}				t_pl;

typedef struct	s_sq
{
	t_vector	sc;
	t_vector	normal;
	float		side;
	t_vector	up;
	t_vector	dx;
	t_vector	dy;
	t_colorf	col;
}				t_sq;

typedef struct	s_cy
{
	t_vector	bottom;
	t_vector	top;
	t_vector	normal;
	float		diameter;
	float		height;
	t_colorf	col;
	int			inside;
}				t_cy;

typedef struct	s_cp
{
	t_vector	pos;
	t_vector	normal;
	float		diameter;
	t_colorf	col;
}				t_cp;

typedef struct	s_tr
{
	t_vector	v0;
	t_vector	v1;
	t_vector	v2;
	t_vector	normal;
	t_colorf	col;
}				t_tr;

typedef struct	s_ip
{
	float		dist;
	t_vector	pos;
	t_vector	normal;
}				t_ip;

#endif