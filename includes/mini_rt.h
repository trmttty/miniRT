/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:00:17 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/14 01:16:57 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "property.h"
# include "get_next_line.h"
# include <math.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SPHERE		0
# define PLANE		1
# define SQUARE		2
# define CYLINDER	3
# define TRIANGLE	4

# define EPSILON 0.0001f
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40
# define HEADER_SIZE 122

typedef union	u_shape
{
	t_sp		*sp;
	t_pl		*pl;
	t_sq		*sq;
	t_cy		*cy;
	t_cp		*cp;
	t_tr		*tr;
}				t_shape;

typedef struct	s_obj
{
	int			type;
	t_shape		shape;
	t_colorf	col;
	t_ip		ip;
}				t_obj;

typedef struct	s_rt
{
	t_res		res;
	float		aspect;
	t_amb		amb;
	t_camera	*cam;
	t_list		*cam_crrnt;
	t_list		*cam_lst;
	t_light		*light;
	t_list		*light_lst;
	t_obj		*obj;
	t_list		*obj_lst;
	t_ray		ray;
	void		*mlx;
	void		*win;
	char		*line;
	char		**tab;
	int			save;
}				t_rt;

typedef struct	s_raytrace
{
	int			sw;
	int			sh;
	t_ray		eye_ray;
	float		fx;
	float		fy;
	t_vector	dx;
	t_vector	dy;
	t_vector	up;
	t_vector	pw;
	t_colorf	col;
	t_vector	light_dir;
}				t_raytrace;

typedef struct	s_calc_ray
{
	float		aspect;
	float		pndc_x;
	float		pndc_y;
	float		pc_x;
	float		pc_y;
	t_vector	v;
}				t_calc_ray;

typedef struct	s_calc_reflection
{
	float		nl_dot;
	t_colorf	t_c;
}				t_calc_reflection;

typedef struct	s_discriminant
{
	float		a;
	float		b;
	float		c;
	float		d;
}				t_discriminant;

/*
** parse
*/
void			parse_rt(int argc, char **argv, t_rt *rt);
void			parse_resolution(t_rt *rt);
void			parse_ambient(t_rt *rt);
void			parse_camera(t_rt *rt);
void			parse_light(t_rt *rt);
void			parse_sphere(t_rt *rt);
void			parse_plane(t_rt *rt);
void			parse_square(t_rt *rt);
void			parse_cylinder(t_rt *rt);
void			parse_triangle(t_rt *rt);
size_t			tabsize(char **tab);
t_colorf		parse_color(char *s, t_rt *rt);
t_vector		parse_vector(char *s, t_rt *rt);
t_vector		parse_normal(char *s, t_rt *rt);

/*
** img
*/
void			create_img(t_rt *rt);
void			set_raytrace(t_rt *rt);
void			raytrace(t_rt *rt, t_raytrace *r);

/*
** camera
*/
void			set_camera(t_rt *rt);

/*
** vector
*/
t_vector		sub(t_vector a, t_vector b);
t_vector		add(t_vector a, t_vector b);
t_vector		multi(t_vector a, float m);
t_vector		v_div(t_vector a, float d);
float			dot(t_vector a, t_vector b);
t_vector		cross(t_vector v1, t_vector v2);
t_vector		vectornew(float a, float b, float c);
float			squared_norm(const t_vector v);
float			normalize(t_vector *v);
float			norm(const t_vector v);

/*
** color
*/
t_colorf		c_multi(t_colorf c, float r);
t_colorf		c_add(t_colorf c1, t_colorf c2);
t_colorf		calc_color(t_colorf c1, t_colorf c2);
int				convert_colorf(t_colorf c);

/*
** intersection
*/
int				get_nearest_object(t_rt *rt, t_ray *ray, t_obj **obj);
int				find_intersection(t_rt *rt, t_ray *ray, t_ip *intp);
int				find_sphere(t_rt *rt, t_ray *ray, t_ip *intp);
int				find_plane(t_rt *rt, t_ray *ray, t_ip *intp);
int				find_square(t_rt *rt, t_ray *ray, t_ip *intp);
int				find_cylinder(t_rt *rt, t_ray *ray, t_ip *intp);
int				find_cap(t_rt *rt, t_ray *ray, t_ip *intp);
int				find_triangle(t_rt *rt, t_ray *ray, t_ip *intp);

/*
** bmp
*/
void			create_bmp_image(t_rt *rt, char *file_name);
void			export_bmp(char *filename, t_rt *my_mlx);
void			create_bmp(t_rt *rt);

/*
** error
*/
void			handle_error(int errnum, char *message, t_rt *rt);
void			handle_perror(char *message, t_rt *rt);
void			handle_argument_error(char *message);

/*
** utils
*/
float			ft_sqr(float x);
float			ft_clamp(float v, float minv, float maxv);

#endif
