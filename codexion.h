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
	int		start;
}		t_pack;

typedef struct s_dongle
{
	int				n;
	int				state;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				cooldown;
}		t_dongle;

typedef struct s_thread
{
	pthread_t		th;
	int				n;
	int				turn;
	t_pack			*pack;
	struct timeval	start;
	struct timeval	last;
	pthread_mutex_t	*print_m;
	t_dongle		*left;
	t_dongle		*right;
}		t_thread;

typedef struct	s_sim
{
	pthread_mutex_t	print_mutex;
	pthread_cond_t	cond;
}		t_sim;

//codexion
int			prologue(char **argv, t_pack *args, t_thread **stack, t_dongle **dongles);
int			assign_args(t_thread **stack, t_dongle **dongles, t_pack *args);
int			gearing(t_thread **threads);
int			check_compile_time(t_thread **threads);
void		*thread_create(void *arg);
void		*thread_routine(void *arg);
int			is_valid(char **args);
t_pack		check_args(char **args);
char		*need_args(void);
int 		timediff(struct timeval *start, struct timeval *end);

//delete after finish part
void	print_helper(int limit, t_thread *stack);

#endif