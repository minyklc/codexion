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
# include <string.h>

typedef struct s_pack
{
	char	*scheduler;
	int		coders;
	int		burnout;
	int		compile;
	int		debug;
	int		refactor;
	int		compile_times;
	int		cooldown;
}		t_pack;

typedef struct s_dongle
{
	int	n;
	int	taken;
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

//codexion
void		*thread_create(void *arg);
void		*thread_routine(void *arg);
int			is_valid(char **args);
t_pack		check_args(char **args);
char		*need_args(void);

//delete after finish part
void	print_helper(int limit, t_thread *stack);

#endif