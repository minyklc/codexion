/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 08:31:10 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/29 08:31:11 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*new_coder(t_thread *thread)
{
	t_coder	*coder;
	
	coder = malloc(sizeof(t_coder));
	if (!coder)
		exit(1);
	coder->coder = &(*thread);
	coder->next = NULL;
	return (coder);
}

void	add_to_lqueue(t_thread **thread)
{
	t_coder	*queue;
	t_coder	*new;

	new = new_coder(*thread);
	queue = (*thread)->left->queue;
	if (!queue)
	{
		(*thread)->left->queue = new;
	}
	else
	{
		while (queue->next)
			(queue) = (queue)->next;
		(queue)->next = new;
	}
}

void	add_to_rqueue(t_thread **thread)
{
	t_coder	*queue;
	t_coder	*new;

	new = new_coder(*thread);
	queue = (*thread)->right->queue;
	if (!queue)
	{
		(*thread)->right->queue = new;
	}
	else
	{
		while (queue->next)
			(queue) = (queue)->next;
		(queue)->next = new;
	}
}

void	rm_to_lqueue(t_thread *thread)
{
	t_coder	*queue;
	t_coder	*temp;

	queue = (*thread).left->queue;
	if (queue->coder->n == thread->n)
	{
		temp = queue;
		queue = queue->next;
		free(temp);
		(*thread).left->queue = queue;
	}
	else
	{
		temp = queue->next;
		free(temp);
		queue->next = NULL;
	}
}

void	rm_to_rqueue(t_thread *thread)
{
	t_coder	*queue;
	t_coder	*temp;

	queue = (*thread).right->queue;
	if (queue->coder->n == thread->n)
	{
		temp = queue;
		queue = queue->next;
		free(temp);
		(*thread).right->queue = queue;
	}
	else
	{
		temp = queue->next;
		free(temp);
		queue->next = NULL;
	}
}

// void	add_to_queue(t_thread *coder, bool dir)
// {
// 	t_coder	*temp;

// 	temp = (*coder).right->queue;
// 	if (dir)
// 		temp = (*coder).left->queue;
// 	while (!temp)
// 		temp = temp->next;
// 	temp->coder = &(*coder);
// }
