/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:04:48 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/11 02:40:10 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	handle_error(int errnum, char *message, t_rt *rt)
{
	(void)rt;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	handle_perror(char *message, t_rt *rt)
{
	(void)rt;
	ft_putstr_fd("Error\n", 2);
	perror(message);
	exit(1);
}
