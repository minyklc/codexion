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

void	add_to_lqueue(t_thread *coder)
{
	t_coder	*temp;

	temp = (*coder).left->queue;
	while (!temp)
		temp = temp->next;
	temp->coder = &(*coder);
}

void	add_to_rqueue(t_thread *coder)
{
	t_coder	*temp;

	temp = (*coder).right->queue;
	while (!temp)
		temp = temp->next;
	temp->coder = &(*coder);
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
