/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 19:59:41 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/29 19:59:42 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	fifo()
{
	return (1);
}

int	edf()
{
	return (1);
}

void	takedongle(t_thread *thread)
{
	struct timeval	now;
	int				diff;

	pthread_mutex_lock(&(*thread).left->mutex);
	if ((*thread).left->state == 1)
		add_to_lqueue(thread);
	while ((*thread).left->state == 1)
		pthread_cond_wait(&(*thread).left->cond, &(*thread).left->mutex);
	gettimeofday(&now, NULL);
	diff = timediff(&(*thread).left->last, &now) + (*thread).pack->compile;
	if (diff < (*thread).pack->cooldown)
		usleep(((*thread).pack->cooldown - diff) * 1000); //cooldown
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
	gettimeofday(&now, NULL);
	diff = timediff(&(*thread).right->last, &now) + (*thread).pack->compile;
	if (diff < (*thread).pack->cooldown)
		usleep(((*thread).pack->cooldown - diff) * 1000); //cooldown
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
	int				diff;

	pthread_mutex_lock(&(*thread).right->mutex);
	while ((*thread).right->state == 1)
		pthread_cond_wait(&(*thread).right->cond, &(*thread).right->mutex);
	gettimeofday(&now, NULL);
	diff = timediff(&(*thread).right->last, &now) + (*thread).pack->compile;
	if (diff < (*thread).pack->cooldown)
		usleep(((*thread).pack->cooldown - diff) * 1000); //cooldown
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
	gettimeofday(&now, NULL);
	diff = timediff(&(*thread).left->last, &now) + (*thread).pack->compile;
	if (diff < (*thread).pack->cooldown)
		usleep(((*thread).pack->cooldown - diff) * 1000); //cooldown
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
