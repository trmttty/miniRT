/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.co.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:29:04 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/06 11:00:50 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	fill_bmp(char **data, t_rt *my_mlx)
{
	int i;
	int j;
	int x;
	int y;

	i = HEADER_SIZE;
	y = my_mlx->res.y;
	while (y--)
	{
		x = -1;
		while (++x < my_mlx->res.x)
		{
			j = (x * (my_mlx->cam->img.bits_per_pixel / 8)) + (y * my_mlx->cam->img.line_length);
			*(*data + i++) = *(my_mlx->cam->img.addr + j++);
			*(*data + i++) = *(my_mlx->cam->img.addr + j++);
			*(*data + i++) = *(my_mlx->cam->img.addr + j);
		}
	}
}

void	header_bmp(char **data, t_rt *my_mlx)
{
	unsigned int size;

	size = my_mlx->res.y * my_mlx->res.x * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = my_mlx->res.x;
	*(unsigned int *)(*data + 22) = my_mlx->res.y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void	export_bmp(char *filename, t_rt *my_mlx)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = my_mlx->res.y * my_mlx->res.x * 3;
	if (!(data = malloc((size + HEADER_SIZE))))
		;
		// print_error_and_exit(-7);
	i = 0;
	while (i < size + HEADER_SIZE)
		data[i++] = 0;
	header_bmp(&data, my_mlx);
	fill_bmp(&data, my_mlx);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		;
		// print_error_and_exit(-8);
	write(fd, data, (size + HEADER_SIZE));
	close(fd);
}

char	*create_bmp_filename(char *file, int i)
{
	char		*filename;
	int			n;

	if (!(filename = malloc(sizeof(char) * (i + 5))))
		;
		// print_error_and_exit(-7);
	n = -1;
	while (++n <= i)
		*(filename + n) = *(file + n);
	*(unsigned int *)(filename + n) =
	*(const unsigned int *)(unsigned long)"bmp\0";
	return (filename);
}