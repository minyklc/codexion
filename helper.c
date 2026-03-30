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
  return ((end->tv_sec * 1000 + end->tv_usec / 1000) - 
  			(start->tv_sec * 1000 + start->tv_usec / 1000));
}

int	is_walking(t_thread	**thread)
{
	int	state;
	
	state = 0;
	pthread_mutex_lock(&(**thread).sim->time_mutex);
	if ((**thread).sim->onthemove)
		state = 1;
	pthread_mutex_unlock(&(**thread).sim->time_mutex);
	return (state);
}

void	free_queue(t_thread *thread)
{
	t_coder	*current;
	t_coder	*next;

	current = (*thread).left->queue;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	(*thread).left->queue = NULL;
}


// int	check_compile_time(t_thread **threads)
// {
// 	int	i;
// 	t_thread	*stack;

// 	i = 0;
// 	stack = *threads;
// 	while (i < stack[0].pack->coders)
// 	{
// 		if (stack[i].turn < stack[0].pack->compile_times)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
