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
	struct timeval	now;
	int				j;

	j = -1;
	pthread_mutex_lock(&(*stack)[i].sim->time_mutex);
	*(&(*stack)[i].sim->onthemove) = 0;
	pthread_mutex_unlock(&(*stack)[i].sim->time_mutex);
	while (++j < (*stack)[0].pack->coders)
	{
		pthread_mutex_lock(&(*stack)[j].left->mutex);
		(*stack)[j].left->state = 0;
		pthread_cond_broadcast(&(*stack)[j].left->cond);
		pthread_mutex_unlock(&(*stack)[j].left->mutex);
	}
	pthread_mutex_lock(&(*stack)[i].sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i burned out\n",
		timediff(&(*stack)[i].sim->start, &now), i + 1);
	pthread_mutex_unlock(&(*stack)[i].sim->log_mutex);
}

int	check_burned(t_thread *thread)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (!(*thread).turn)
	{
		if (timediff(&(*thread).sim->start, &now) >= (*thread).pack->burnout)
			return (pthread_mutex_unlock(&(*thread).sim->time_mutex), 1);
	}
	else if (timediff(&(*thread).last, &now) >= (*thread).pack->burnout)
		return (pthread_mutex_unlock(&(*thread).sim->time_mutex), 1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	int				i;
	t_monitor		*args;
	t_thread		*stack;

	args = (t_monitor *)arg;
	stack = *(*args).stack;
	i = 0;
	while (i < stack[0].pack->coders)
	{
		pthread_mutex_lock(&stack[i].sim->time_mutex);
		if (!args->on || !stack[i].sim->onthemove)
			return (pthread_mutex_unlock(&stack[i].sim->time_mutex), NULL);
		if (check_burned(&stack[i]))
			return (has_burned(&stack, i), NULL);
		pthread_mutex_unlock(&stack[i].sim->time_mutex);
		if (i == stack[0].pack->coders - 1)
			i = -1;
		usleep(1000);
		i++;
	}
	return (NULL);
}
