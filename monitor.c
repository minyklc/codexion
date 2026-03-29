/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:37:03 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/26 11:37:05 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	has_burned(t_thread **stack, int i)
{
	pthread_mutex_lock(&(*stack)[i].sim->time_mutex);
	*(&(*stack)[i].sim->onthemove) = 0;
	pthread_mutex_unlock(&(*stack)[i].sim->time_mutex);
	pthread_mutex_lock(&(*stack)[i].sim->log_mutex);
	printf("%i has burned out\n", i+1);
	pthread_mutex_unlock(&(*stack)[i].sim->log_mutex);
}

void	*monitor_routine(void *arg)
{
	t_monitor	*args;
	t_thread	*stack;
	struct timeval	now;
	int			i;

	args = (t_monitor*)arg;
	stack = *(*args).stack;
	i = 0;
	while (i < stack[0].pack->coders && args->on)
	{
		if (!stack[0].sim->onthemove)
			return (NULL);
		gettimeofday(&now, NULL);
		if (stack[i].turn == 0)
		{
			if (timediff(&stack[i].sim->start, &now) >= stack[0].pack->burnout)
				return (has_burned(&stack, i), NULL);
		}
		else if (timediff(&stack[i].last, &now) >= stack[0].pack->burnout)
			return (has_burned(&stack, i), NULL);
		if (i == stack[0].pack->coders - 1)
			i = -1;
		usleep(1000);
		i++;
	}
	return (NULL);
}