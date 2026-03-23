/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 10:33:42 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/11 10:33:45 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	compiletime(int ms, t_thread *thread)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// printf("%i %i is compiling\n", timediff(&(*thread).start, &now), (*thread).n);
	pthread_mutex_lock(&(*(*thread).print_m));
	printf("%i is compiling\n", (*thread).n);
	pthread_mutex_unlock(&(*(*thread).print_m));
	usleep(ms * 1000);
	(*thread).left->state = 0;
	pthread_cond_broadcast(&(*thread).left->cond);
	(*thread).right->state = 0;
	pthread_cond_broadcast(&(*thread).right->cond);
	return (0);
}

int	debugtime(int ms, t_thread *thread)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// printf("%i %i is debugging\n", timediff(&(*thread).start, &now), (*thread).n);
	pthread_mutex_lock(&(*(*thread).print_m));
	printf("%i is debugging\n", (*thread).n);
	pthread_mutex_unlock(&(*(*thread).print_m));
	usleep(ms * 1000);
	return (0);
}

int	refactortime(int ms, t_thread *thread)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// printf("%i %i is refactoring\n", timediff(&(*thread).start, &now), (*thread).n);
	pthread_mutex_lock(&(*(*thread).print_m));
	printf("%i is refactoring\n", (*thread).n);
	pthread_mutex_unlock(&(*(*thread).print_m));
	usleep(ms * 1000);
	return (0);
}

void	*thread_routine(void *arg)
{
	t_pack		args;
	t_thread	*thread;
	// struct timeval	e;

	thread = &(*(t_thread*)arg);
	args = *(*thread).pack;
	while ((*thread).turn < (*thread).pack->compile_times)
	{
		
		// pthread_mutex_lock(&(*(*thread).print_m));
		// gettimeofday(&e, NULL);
		// printf("start of thread %i, turn: %i!\n", (*thread).n, (*thread).turn);
		// pthread_mutex_unlock(&(*(*thread).print_m));
		pthread_mutex_lock(&(*thread).left->mutex);
		while ((*thread).left->state == 1)
			pthread_cond_wait(&(*thread).left->cond, &(*thread).left->mutex);
		(*thread).left->state = 1;
		pthread_mutex_lock(&(*(*thread).print_m));
		printf("%i has taken a dongle\n", (*thread).n);
		pthread_mutex_unlock(&(*(*thread).print_m));
		pthread_mutex_unlock(&(*thread).left->mutex);
		pthread_mutex_lock(&(*thread).right->mutex);
		while ((*thread).right->state == 1)
			pthread_cond_wait(&(*thread).right->cond, &(*thread).right->mutex);
		pthread_mutex_lock(&(*(*thread).print_m));
		printf("%i has taken a dongle\n", (*thread).n);
		pthread_mutex_unlock(&(*(*thread).print_m));
		(*thread).right->state = 1;
		pthread_mutex_unlock(&(*thread).right->mutex);
		//codetime
		compiletime(args.compile, &(*thread));
		debugtime(args.debug, &(*thread));
		refactortime(args.refactor, &(*thread));
		(*thread).turn++;
		// pthread_mutex_unlock(&(*thread).mutex->print_m);
	}
	return (NULL);
}
