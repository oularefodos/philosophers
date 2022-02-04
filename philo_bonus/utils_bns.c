/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:49:56 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 01:52:42 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bns.h"
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	n;

	i = 0;
	n = 1;
	result = 0;
	if (str == 0)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		n *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * n);
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

	sem_wait(data->write_sem);
	end = get_time(data->time_start);
	printf ("%ld %i %s\n", end, data->i, str);
	sem_post(data->write_sem);
	usleep(time);
}

void	*check_die(void *arg)
{
	long	time;
	t_data	*data;
	int		n;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->die_sem);
		if (start_time() - data->last_eat > data->time_die)
		{
			time = get_time(data->time_start);
			sem_wait (data->write_sem);
			printf ("%ld %d die\n", time, data->i);
			n = -1;
			data->dead = 1;
			ft_die_clean(data);
			exit (0);
			sem_post(data->write_sem);
		}
		sem_post(data->die_sem);
		if (data->time_must_eat && data->time_must_eat <= data->iseating)
			break ;
	}
	return (0);
}
