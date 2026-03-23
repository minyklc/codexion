/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:51:29 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/16 08:51:33 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char *argv[])
{
	t_thread		*stack;
	t_pack			args;
	t_dongle		*dongles;

	if (argc != 9 || prologue(argv, &args, &stack, &dongles))
		return (printf("%s", need_args()), 1);
	if (assign_args(&stack, &dongles, &args))
		return (free(stack), free(dongles), 1);
	if (gearing(&stack))
		return (free(stack), free(dongles), 1);
	// print_helper(args.coders, stack); // trash after
	free(stack);
	free(dongles);
	return (0);
}
