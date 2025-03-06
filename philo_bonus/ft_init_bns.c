/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:43:29 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 02:10:34 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_bns.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

int	ft_die_clean(t_data *data)
{
	int	n;

	n = data->i - 1;
	while (n-- > 0)
		data--;
	n = -1;
	while (++n > data[0].nbr)
		kill (data[n].pid, 15);
	sem_unlink("/fork");
	sem_unlink("/write");
	sem_unlink("/die_sem");
	free(data);
	return (0);
}

int	error(char *str)
{
	printf ("erreur: %s\n", str);
	exit (1);
}

int	ft_mutex_init(t_env *env, int n, char **str)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		memset(&env->data[i], '\0', sizeof(t_data));
		env->data[i].time_start = start_time();
		env->data[i].last_eat = env->data[i].time_start;
		env->data[i].nbr = ft_atoi(str[1]);
		env->data[i].time_die = ft_atoi(str[2]);
		env->data[i].time_eat = ft_atoi(str[3]) * 1000;
		env->data[i].time_sleep = ft_atoi(str[4]) * 1000;
		if (str[5])
				env->data[i].time_must_eat = ft_atoi(str[5]);
		else
			env->data[i].time_must_eat = 0;
	}
	sem_unlink("/fork");
	sem_unlink("/write");
	sem_unlink("/die_sem");
	env->fork_sem = sem_open("/fork", O_CREAT, S_IRWXU, n);
	env->write_sem = sem_open("/write", O_CREAT, S_IRWXU, 1);
	env->die_sem = sem_open("/die_sem", O_CREAT, S_IRWXU, 1);
	return (0);
}

int	philo_init(t_env *env, char **str)
{
	int	nphilo;
	int	n;

	nphilo = ft_atoi(str[1]);
	n = -1;
	env->data = malloc(sizeof(t_data) * nphilo);
	if (env->data == NULL)
		return (error("echec d'allocation"));
	if (ft_mutex_init(env, nphilo, str))
		return (error("error: initialisation mutex"));
	while (++n < nphilo)
	{
		env->data[n].dead = 0;
		env->data[n].die_sem = env->die_sem;
		env->data[n].write_sem = env->write_sem;
		env->data[n].fork_sem = env->fork_sem;
		env->data[n].i = n + 1;
		env->data[n].iseating = 0;
	}
	return (0);
}
