/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:49:53 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/16 08:50:02 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	prologue(char **argv, t_pack *args, t_thread **stack, t_dongle **dongles)
{
	if (is_valid(argv))
		return (1);
	*args = check_args(argv);
	if ((*args).coders < 2)
		return (printf("nb_coders must be an integer >= 2"), 1);
	*stack = malloc(sizeof(**stack) * (*args).coders);
	*dongles = malloc(sizeof(**dongles) * (*args).coders);
	return (0);
}

int	assign_args(t_thread **stack, t_dongle **dongles, t_pack *args)
{
	int	i;
	int	r;
	pthread_mutex_t	mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < (*args).coders)
	{
		(*stack)[i].pack = &(*args);
		(*stack)[i].print_m = &mutex;
		// (*stack)[i].start = gettimeofday(NULL, NULL);
		(*stack)[i].turn = 0;
		(*stack)[i].n = i + 1;
		(*dongles)[i].n = i;
		(*dongles)[i].state = 0;
		pthread_cond_init(&(*dongles)[i].cond, NULL);
		(*dongles)[i].cooldown = (*args).cooldown;
		pthread_mutex_init(&(*dongles)[i].mutex, NULL);
		(*stack)[i].left = &(*dongles)[i];
		(*stack)[i].right = &(*dongles)[i + 1];
		if (i == (*args).coders - 1)
			(*stack)[i].right = &(*dongles)[0];
		r = pthread_create(&(*stack)[i].th, NULL,
			thread_create, (void*)&(*stack)[i].n); // maybe ??
		if (r)
			return (printf("not enough resources for new thread"), 1);
		i++;
	}
	i = -1;
	while (++i < (*args).coders)
		pthread_join((*stack)[i].th, NULL);
	return (0);
}
