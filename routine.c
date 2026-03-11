/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 10:33:42 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/11 10:33:45 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	codetime(int ms)
{
	usleep(ms);
	return (0);
}

int	debugtime(int ms)
{
	usleep(ms);
	return (0);
}

int	refactortime(int ms)
{
	usleep(ms);
	return (0);
}

void	*thread_routine(void *arg)
{
	codetime(arg);
}