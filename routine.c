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

void	compiletime(int ms, t_thread *thread)
{
	struct timeval	now;

	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i is compiling\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
	pthread_mutex_lock(&(*thread).sim->time_mutex);
	gettimeofday(&(*thread).last, NULL);
	(*thread).turn++;
	pthread_mutex_unlock(&(*thread).sim->time_mutex);
	usleep(ms * 1000);
}

void	debugtime(int ms, t_thread *thread)
{
	struct timeval	now;

	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i is debugging\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
	usleep(ms * 1000);
}

void	refactortime(int ms, t_thread *thread)
{
	struct timeval	now;

	pthread_mutex_lock(&(*thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i is refactoring\n", timediff(&(*thread).sim->start, &now), (*thread).n);
	pthread_mutex_unlock(&(*thread).sim->log_mutex);
	usleep(ms * 1000);
}

void	release_dongle(int ms, t_thread *thread)
{
	usleep(ms * 1000);
	pthread_mutex_lock(&(*thread).left->mutex);
	(*thread).left->state = 0;
	pthread_cond_broadcast(&(*thread).left->cond);
	pthread_mutex_unlock(&(*thread).left->mutex);
	pthread_mutex_lock(&(*thread).right->mutex);
	(*thread).right->state = 0;
	pthread_cond_broadcast(&(*thread).right->cond);
	pthread_mutex_unlock(&(*thread).right->mutex);
}

void	*thread_routine(void *arg)
{
	t_pack		args;
	t_thread	*thread;

	thread = &(*(t_thread*)arg);
	args = *(*thread).pack;
	while ((*thread).sim->onthemove && (*thread).turn < (*thread).pack->compile_times)
	{
		if (!(*thread).sim->onthemove)
			return (release_dongle(0, &(*thread)), NULL);
		if ((*thread).n % 2 == 0)
			rtakedongle(&(*thread));
		else
			takedongle(&(*thread));
		if (!(*thread).sim->onthemove)
			return (release_dongle(0, &(*thread)), NULL);
		compiletime(args.compile, &(*thread));
		release_dongle(args.cooldown, &(*thread));
		if (!(*thread).sim->onthemove)
			return (NULL);
		debugtime(args.debug, &(*thread));
		if (!(*thread).sim->onthemove)
			return (NULL);
		refactortime(args.refactor, &(*thread));
		// (*thread).turn++;
	}
	return (release_dongle(0, &(*thread)), NULL);
}
