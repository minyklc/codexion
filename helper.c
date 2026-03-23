/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:00:42 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/13 10:00:43 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	*need_args(void)
{
	return ("./a.out {nb_coders} {burnout_time} {compile_time}"
			" {debug_time} {refactor_time} {minimum_compile_nb}"
			" {dongle_cooldown} {scheduler}\n");
}

int timediff(struct timeval *start, struct timeval *end)
{
  return (end->tv_usec / 1000 - start->tv_usec / 1000);
}

int	check_compile_time(t_thread **threads)
{
	int	i;
	t_thread	*stack;

	i = 0;
	stack = *threads;
	while (i < stack[0].pack->coders)
	{
		if (stack[i].turn < stack[0].pack->compile_times)
			return (1);
		i++;
	}
	return (0);
}
