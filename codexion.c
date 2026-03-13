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

int	assign_args(t_thread **stack, t_dongle **dongles, t_pack args)
{
	int	i;
	int	r;
	
	i = 0;
	while (i < args.coders)
	{
		(*stack)[i].n = i + 1;
		(*dongles)[i].n = i;
		(*dongles)[i].taken = 0;
		(*dongles)[i].cooldown = args.cooldown;
		(*stack)[i].left = &(*dongles)[i];
		(*stack)[i].right = &(*dongles)[i + 1];
		if (i == args.coders - 1)
			(*stack)[i].right = &(*dongles)[0];
		r = pthread_create(&(*stack)[i].th, NULL,
			thread_create, (void*)&(*stack)[i].n);
		if (r)
			return (printf("not enough ressources for new thread"), 1);
		i++;
	}
	i = -1;
	while (++i < args.coders)
		pthread_join((*stack)[i].th, NULL);
	return (0);
}

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

int	main(int argc, char *argv[])
{
	t_thread		*stack;
	t_pack			args;
	t_dongle		*dongles;

	if (argc != 9 || prologue(argv, &args, &stack, &dongles))
		return (printf("%s", need_args()), 1);
	if (assign_args(&stack, &dongles, args))
		return (1);
	print_helper(args.coders, stack);
	free(stack);
	free(dongles);
	return (0);
}
