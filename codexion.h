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

typedef struct s_pack		t_pack;
typedef struct s_sim		t_sim;
typedef struct s_dongle		t_dongle;
typedef struct s_thread		t_thread;
typedef struct s_coder		t_coder;
typedef struct s_monitor	t_monitor;

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

typedef struct s_sim
{
	int				onthemove;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	time_mutex;
	// pthread_mutex_t	dongle_mutex;
	struct timeval	start;
	pthread_cond_t	stop;
}		t_sim;

typedef struct s_dongle
{
	int				n;
	int				state;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_coder			*queue;
	int				cooldown;
	struct timeval	last;
}		t_dongle;

typedef struct s_thread
{
	pthread_t		th;
	int				n;
	int				turn;
	t_pack			*pack;
	t_sim			*sim;
	struct timeval	last;
	t_dongle		*left;
	t_dongle		*right;
}		t_thread;

typedef struct s_coder
{
	t_thread	*coder;
	t_coder		*next;
}		t_coder;

typedef struct s_monitor
{
	pthread_t	th;
	int			on;
	t_thread	**stack;
}		t_monitor;

//starting.c
int			prologue(char **argv, t_pack *args, t_thread **stack,
				t_dongle **dongles);
int			assign_args(t_thread **stack, t_dongle **dongles, t_pack *args,
				t_sim *sim);

//gearing.c
int			gearing(t_thread **threads);
void		join_all(t_thread **stack, t_monitor *monitor);
void		clean_all(t_thread **stack);

//routine.c
void		*thread_routine(void *arg);

//dongle.c
void		takedongle(t_thread *thread);
void		rtakedongle(t_thread *thread);

//monitor.c
void		*monitor_routine(void *arg);

//check_args.c
int			is_valid(char **args);
t_pack		check_args(char **args);

//queue.c
void		add_to_lqueue(t_thread **thread);
void		add_to_rqueue(t_thread **thread);
void		rm_to_lqueue(t_thread *thread);
void		rm_to_rqueue(t_thread *thread);

//helper.c
char		*need_args(void);
int			timediff(struct timeval *start, struct timeval *end);
void		free_queue(t_thread *thread);
int			check_length(t_dongle **dongle);
int			is_walking(t_thread	**thread);

//scheduler.c
void		fifol(t_thread *thread);
void		fifor(t_thread *thread);
void		edfl(t_thread *thread);
void		edfr(t_thread *thread);

#endif
