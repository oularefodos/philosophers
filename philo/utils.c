/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:49:56 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 02:39:40 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	all_eat(t_env *env)
{
	int	n;
	int	p;

	n = 0;
	p = env->data[0].time_must_eat;
	while (p && p == env->data[n].iseating)
	{
		pthread_mutex_lock(env->data[n].t_mutex);
		n++;
		if (n == env->data[0].nbr)
			return (1);
		pthread_mutex_unlock(env->data[n].t_mutex);
	}
	return (0);
}

long	start_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_time(long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - start);
}

void	action(t_data *data, char *str, int time)
{
	long	end;

	pthread_mutex_lock(data->w_mutex);
	end = get_time(data->time_start);
	printf ("%ld %i %s\n", end, data->i, str);
	pthread_mutex_unlock(data->w_mutex);
	usleep(time);
}

int	check_die(t_env *env, int nphilo)
{
	int		n;
	long	time;

	while (1)
	{
		n = -1;
		while (++n < nphilo)
		{
			pthread_mutex_lock(env->data[n].t_mutex);
			if (start_time() - env->data[n].last_eat > env->data[n].time_die)
			{
				pthread_mutex_lock(&env->w_mutex);
				time = get_time(env->data[n].time_start);
				printf ("%ld %d die\n", time, env->data[n].i);
				env->data[n].dead = 1;
				return (1);
				pthread_mutex_unlock(&env->w_mutex);
			}
			pthread_mutex_unlock(env->data[n].t_mutex);
		}
		if (all_eat(env))
			return (1);
	}
	return (0);
}
