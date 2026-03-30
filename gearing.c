/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gearing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:43 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/13 10:22:46 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	gearing(t_thread **threads)
{
	t_thread	*stack;
	t_monitor	monitor;
	int			i;

	i = -1;
	stack = *threads;
	monitor.stack = &stack;
	monitor.on = 1;
	gettimeofday(&stack[0].sim->start, NULL);
	while (++i < stack[0].pack->coders)
	{
		stack[i].last.tv_usec = 0;
		stack[i].left->last.tv_usec = 0;
	}
	i = -1;
	pthread_create(&monitor.th, NULL, monitor_routine, &monitor);
	while (++i < stack[0].pack->coders)
		pthread_create(&stack[i].th, NULL, thread_routine, &stack[i]);
	join_all(&(*threads), &monitor);
	clean_all(&(*threads));
	return (0);
}

void	join_all(t_thread **stack, t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < (*stack)[0].pack->coders)
		pthread_join((*stack)[i].th, NULL);
	pthread_mutex_lock(&(*stack)[0].sim->time_mutex);
	*(&(*monitor).on) = 0;
	pthread_mutex_unlock(&(*stack)[0].sim->time_mutex);
	pthread_join((*monitor).th, NULL);
}

void	clean_all(t_thread **stack)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&(*stack)[0].sim->log_mutex);
	pthread_mutex_destroy(&(*stack)[0].sim->time_mutex);
	pthread_cond_destroy(&(*stack)[0].sim->stop);
	while (++i < (*stack)[0].pack->coders)
	{
		pthread_mutex_destroy(&(*stack)[i].left->mutex);
		pthread_cond_destroy(&(*stack)[i].left->cond);
		free_queue(&(*stack)[i]);
	}
}