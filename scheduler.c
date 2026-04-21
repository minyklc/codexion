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

void	fifol(t_thread *thread)
{
	pthread_cond_t	*cond;

	cond = &(*thread).left->cond;
	if (check_length(&(*thread).left) > 0)
		cond = &(*thread).left->queue->coder->right->cond;
	(void)cond;
	pthread_cond_broadcast(&(*thread).left->cond);
}

void	fifor(t_thread *thread)
{
	pthread_cond_t	*cond;

	cond = &(*thread).right->cond;
	if (check_length(&(*thread).right) > 0)
		cond = &(*thread).right->queue->coder->left->cond;
	(void)cond;
	pthread_cond_broadcast(&(*thread).right->cond);
}

void	edfl(t_thread *thread)
{
	pthread_cond_t	*cond;
	struct timeval	now;

	cond = &(*thread).left->cond;
	gettimeofday(&now, NULL);
	if (check_length(&(*thread).left) > 0)
	{
		if (timediff(&(*thread).last,
				&now) < timediff(&(*thread).left->queue->coder->last,
				&now))
			cond = &(*thread).left->queue->coder->right->cond;
	}
	(void)cond;
	pthread_cond_broadcast(&(*thread).left->cond);
}

void	edfr(t_thread *thread)
{
	pthread_cond_t	*cond;
	struct timeval	now;

	cond = &(*thread).right->cond;
	gettimeofday(&now, NULL);
	if (check_length(&(*thread).right) > 0)
	{
		if (timediff(&(*thread).last,
				&now) < timediff(&(*thread).right->queue->coder->last,
				&now))
			cond = &(*thread).right->queue->coder->left->cond;
	}
	(void)cond;
	pthread_cond_broadcast(&(*thread).right->cond);
}
