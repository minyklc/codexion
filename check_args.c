/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:23:44 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/08 17:23:46 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_valid(char **args)
{
	char	c;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < 8)
	{
		while (args[i][j])
		{
			c = args[i][j];
			if (!(c >= '0' && c <= '9'))
				return (1);
			j++;
		}
		if (atoi(args[i]) < 0)
			return (1);
		j = 0;
		i++;
	}
	if (strcmp(args[i], "fifo") != 0 && strcmp(args[i], "edf") != 0)
		return (1);
	return (0);
}

t_pack	check_args(char **args)
{
	t_pack	data;
	int			i;

	i = 0;
	data.coders = atoi(args[++i]);
	data.burnout = atoi(args[++i]);
	data.compile = atoi(args[++i]);
	data.debug = atoi(args[++i]);
	data.refactor = atoi(args[++i]);
	data.compile_times = atoi(args[++i]);
	data.cooldown = atoi(args[++i]);
	data.scheduler = args[++i];
	return (data);
}
