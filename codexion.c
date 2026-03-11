/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:19:55 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/08 17:19:58 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*thread_create(void *arg)
{
	// int	*i;

	// i = (int *)arg;
	// // pthread_t tid = pthread_self();
	// printf("%i new thread created\n", *i);
	return (arg);
}

int	main(int argc, char *argv[])
{
	t_thread		*stack_thread;
	int				nbargs;
	int				*dongles;
	int				i;
	int				r;
	// struct timeval	s;
	// struct timeval	e;

	i = 0;
	if (argc >= 2)
		nbargs = atoi(argv[1]);
	else
		return (printf("./a.out {nb}\n"), 1);
	if (nbargs > 1)
	{
		stack_thread = malloc(sizeof(*stack_thread) * nbargs);
		dongles = malloc(sizeof(int) * nbargs);
    }
	else
		return (printf("arg must be an integer >= 2"), 1);
	// gettimeofday(&s, NULL);
	while (i < nbargs)
	{
		stack_thread[i].n = i + 1;
		r = pthread_create(&(stack_thread[i].th), NULL,
				thread_create, (void*)&stack_thread[i].n);
		if (r)
			return (perror("pthread_create"), 1);
		// printf("%ld\n", stack_thread[i].th);
		// gettimeofday(&e, NULL);
		i++;
	}
	i = -1;
	while (++i < nbargs)
		pthread_join(stack_thread[i].th, NULL);
	i = 0;
	while (i < nbargs)
	{
		printf("%i\n", stack_thread[i].n);
		i++;
	}
	free(stack_thread);
	return (0);
}
