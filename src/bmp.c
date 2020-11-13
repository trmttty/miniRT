/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:29:04 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 12:31:22 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	fill_bmp(char **data, t_rt *rt)
{
	int i;
	int j;
	int x;
	int y;

	i = HEADER_SIZE;
	y = rt->res.y;
	while (y--)
	{
		x = -1;
		while (++x < rt->res.x)
		{
			j = (x * (rt->cam->img.bits_per_pixel / 8)) + \
				(y * rt->cam->img.line_length);
			*(*data + i++) = *(rt->cam->img.addr + j++);
			*(*data + i++) = *(rt->cam->img.addr + j++);
			*(*data + i++) = *(rt->cam->img.addr + j);
		}
	}
}

void	header_bmp(char **data, t_rt *rt)
{
	unsigned int size;

	size = rt->res.y * rt->res.x * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = rt->res.x;
	*(unsigned int *)(*data + 22) = rt->res.y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void	export_bmp(char *filename, t_rt *rt)
{
	int				fd;
	unsigned int	size;
	char			*data;

	size = rt->res.y * rt->res.x * 3;
	if (!(data = malloc((size + HEADER_SIZE))))
		handle_perror("Failed to malloc bmp data", rt);
	ft_memset(data, 0, size + HEADER_SIZE);
	header_bmp(&data, rt);
	fill_bmp(&data, rt);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		handle_perror("Failed to read bmp file", rt);
	write(fd, data, (size + HEADER_SIZE));
	free(data);
	close(fd);
}

void	create_bmp(t_rt *rt)
{
	t_list	*tmp;
	char	*filename;
	char	*index_str;
	int		index;

	index = 1;
	tmp = rt->cam_lst;
	while (tmp)
	{
		rt->cam = (t_camera*)(tmp->content);
		if (!(index_str = ft_itoa(index)))
			handle_perror("Failed to create index_str", rt);
		if (!(filename = ft_strjoin(index_str, ".bmp")))
			handle_perror("Failed to create filename", rt);
		export_bmp(filename, rt);
		free(index_str);
		free(filename);
		index++;
		tmp = tmp->next;
	}
}
