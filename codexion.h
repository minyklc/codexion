/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:24:07 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/08 21:24:09 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_package
{
	char	*scheduler;
	int		nb_coders;
	int		burnout;
	int		compile;
	int		debug;
	int		refactor;
	int		compile_times;
	int		cooldown;
}		t_package;

typedef struct s_dongle
{
	int	n;
	int	cooldown;
}		t_dongle;

typedef struct s_thread
{
	pthread_t	th;
	int			n;
	t_dongle	*left;
	t_dongle	*right;
}		t_thread;

typedef struct s_mutex
{
	pthread_mutex_t	lock1;
	int				count;
}		t_mutex;

void	*thread_create(void *arg);
void	*thread_routine(void *arg);

#endif