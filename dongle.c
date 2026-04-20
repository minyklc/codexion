/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 08:50:46 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/30 08:50:47 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	left(t_thread **thread)
{
	struct timeval	now;
	int				diff;

	pthread_mutex_lock(&(**thread).left->mutex);
	add_to_lqueue(&(*thread));
	while ((**thread).left->state == 1)
		pthread_cond_wait(&(**thread).left->cond, &(**thread).left->mutex);
	(**thread).left->state = 1;
	gettimeofday(&now, NULL);
	diff = timediff(&(**thread).left->last, &now) + (**thread).pack->compile;
	if (diff < (**thread).pack->cooldown &&
		timediff(&(**thread).left->last, &(**thread).sim->start) != 0)
		usleep(((**thread).pack->cooldown - diff) * 1000);
	if (!is_walking(thread))
		return (pthread_mutex_unlock(&(**thread).left->mutex), 1);
	rm_to_lqueue(&(**thread));
	pthread_mutex_unlock(&(**thread).left->mutex);
	pthread_mutex_lock(&(**thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i has taken a dongle\n", timediff(&(**thread).sim->start, &now),
		(**thread).n);
	pthread_mutex_unlock(&(**thread).sim->log_mutex);
	return (0);
}

int	right(t_thread **thread)
{
	struct timeval	now;
	int				diff;

	pthread_mutex_lock(&(**thread).right->mutex);
	add_to_rqueue(&(*thread));
	while ((**thread).right->state == 1)
		pthread_cond_wait(&(**thread).right->cond, &(**thread).right->mutex);
	(**thread).right->state = 1;
	gettimeofday(&now, NULL);
	diff = timediff(&(**thread).right->last, &now) + (**thread).pack->compile;
	if (diff < (**thread).pack->cooldown &&
		timediff(&(**thread).right->last, &(**thread).sim->start) != 0)
		usleep(((**thread).pack->cooldown - diff) * 1000);
	if (!is_walking(thread))
		return (pthread_mutex_unlock(&(**thread).right->mutex), 1);
	rm_to_rqueue(&(**thread));
	pthread_mutex_unlock(&(**thread).right->mutex);
	pthread_mutex_lock(&(**thread).sim->log_mutex);
	gettimeofday(&now, NULL);
	printf("%i %i has taken a dongle\n", timediff(&(**thread).sim->start, &now),
		(**thread).n);
	pthread_mutex_unlock(&(**thread).sim->log_mutex);
	return (0);
}

void	takedongle(t_thread *thread)
{
	if (left(&thread))
		return ;
	if (right(&thread))
		return ;
}

void	rtakedongle(t_thread *thread)
{
	if (right(&thread))
		return ;
	if (left(&thread))
		return ;
}
