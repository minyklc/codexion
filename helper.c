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

void	takedongle(t_thread *thread)
{
	struct timeval	now;

	pthread_mutex_lock(&(*thread).left->mutex);
	while ((*thread).left->state == 1)
		pthread_cond_wait(&(*thread).left->cond, &(*thread).left->mutex);
	if (!(*thread).sim->onthemove)
	{
		pthread_mutex_unlock(&(*thread).left->mutex);
		return ;
	}
	(*thread).left->state = 1;
	pthread_mutex_unlock(&(*thread).left->mutex);
	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i has taken a dongle\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
	pthread_mutex_lock(&(*thread).right->mutex);
	while ((*thread).right->state == 1)
		pthread_cond_wait(&(*thread).right->cond, &(*thread).right->mutex);
	// printf("ouais ouais ouais %i\n", (*thread).sim->onthemove);
	if (!(*thread).sim->onthemove)
	{
		pthread_mutex_unlock(&(*thread).right->mutex);
		return ;
	}
	(*thread).right->state = 1;
	pthread_mutex_unlock(&(*thread).right->mutex);
	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i has taken a dongle\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
}

void	rtakedongle(t_thread *thread)
{
	struct timeval	now;

	pthread_mutex_lock(&(*thread).right->mutex);
	while ((*thread).right->state == 1)
		pthread_cond_wait(&(*thread).right->cond, &(*thread).right->mutex);
	if (!(*thread).sim->onthemove)
	{
		pthread_mutex_unlock(&(*thread).right->mutex);
		return ;
	}
	(*thread).right->state = 1;
	pthread_mutex_unlock(&(*thread).right->mutex);
	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i has taken a dongle\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
	pthread_mutex_lock(&(*thread).left->mutex);
	while ((*thread).left->state == 1)
		pthread_cond_wait(&(*thread).left->cond, &(*thread).left->mutex);
	// printf("ouais ouais ouais %i\n", (*thread).sim->onthemove);
	if (!(*thread).sim->onthemove)
	{
		pthread_mutex_unlock(&(*thread).left->mutex);
		return ;
	}
	(*thread).left->state = 1;
	pthread_mutex_unlock(&(*thread).left->mutex);
	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i has taken a dongle\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
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
