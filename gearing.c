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
	// t_dongle	*dongle;
	int			i;

	i = -1;
	// start = NULL;
	stack = *threads;
	// dongle = *dongles;
	gettimeofday(&stack[0].start, NULL);
	// while (check_compile_time(&stack))
	// {
	printf("stack order : \n");
	while (++i < stack[0].pack->coders)
		printf("%i with dongle %i and %i,\n", stack[i].n, stack[i].left->n, stack[i].right->n);
	i = 0;
	while (i < stack[0].pack->coders)
	{
		// printf("le turn: %i\n", stack[0].turn);
		if (!stack[i].turn)
			gettimeofday(&stack[0].start, NULL);
		pthread_create(&stack[i].th, NULL, thread_routine, &stack[i]);
		// pthread_join(stack[i].th, NULL);
		// printf("oui\n");
		i++;
	}
	i = -1;
	while (++i < stack[0].pack->coders)
		pthread_join(stack[i].th, NULL);
	i = 0;
	// }
	pthread_mutex_destroy(&(*stack[0].print_m));
	i = -1;
	while (++i < stack[0].pack->coders)
	{
		pthread_mutex_destroy(&stack[i].left->mutex);
		pthread_cond_destroy(&stack[i].left->cond);
	}
	return (0);
}
