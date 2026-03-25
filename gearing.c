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
	int			i;

	i = -1;
	stack = *threads;
	// dongle = *dongles;

	gettimeofday(&stack[0].sim->start, NULL);
	i = 0;
	while (i < stack[0].pack->coders)
	{
		// printf("le turn: %i\n", stack[0].turn);
		pthread_create(&stack[i].th, NULL, thread_routine, &stack[i]);
		i++;
	}
	i = -1;
	while (++i < stack[0].pack->coders)
		pthread_join(stack[i].th, NULL);
	pthread_mutex_destroy(&stack[0].sim->log_mutex);
	i = -1;
	while (++i < stack[0].pack->coders)
	{
		pthread_mutex_destroy(&stack[i].left->mutex);
		pthread_cond_destroy(&stack[i].left->cond);
	}
	return (0);
}
