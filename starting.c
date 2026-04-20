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
	if ((*args).coders < 1)
		return (printf("nb_coders must be an integer >= 1\n"), 1);
	*stack = malloc(sizeof(**stack) * (*args).coders);
	if (!*stack)
		return (printf("malloc of stack failed"), 1);
	*dongles = malloc(sizeof(**dongles) * (*args).coders);
	if (!*dongles)
		return (printf("malloc of dongles failed"), 1);
	return (0);
}

void	sim_init(t_sim *sim)
{
	(*sim).onthemove = 1;
	pthread_mutex_init(&(*sim).log_mutex, NULL);
	pthread_mutex_init(&(*sim).time_mutex, NULL);
	pthread_cond_init(&(*sim).stop, NULL);
}

int	assign_args(t_thread **stack, t_dongle **dongles, t_pack *args, t_sim *sim)
{
	int	i;

	i = 0;
	sim_init(sim);
	while (i < (*args).coders)
	{
		(*stack)[i].pack = &(*args);
		(*stack)[i].sim = &(*sim);
		(*stack)[i].turn = 0;
		(*stack)[i].n = i + 1;
		(*dongles)[i].n = i;
		(*dongles)[i].queue = NULL;
		(*dongles)[i].state = 0;
		pthread_cond_init(&(*dongles)[i].cond, NULL);
		(*dongles)[i].cooldown = (*args).cooldown;
		pthread_mutex_init(&(*dongles)[i].mutex, NULL);
		(*stack)[i].left = &(*dongles)[i];
		(*stack)[i].right = &(*dongles)[i + 1];
		if (i == (*args).coders - 1)
			(*stack)[i].right = &(*dongles)[0];
		i++;
	}
	return (0);
}
