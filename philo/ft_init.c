/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:43:31 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 02:40:45 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pthread.h>
#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	error(char *str)
{
	printf ("error: %s\n", str);
	return (1);
}

int	ft_mutex_init(t_env *env, int n, char **str)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		memset(&env->data[i], '\0', sizeof(t_data));
		if (pthread_mutex_init(&env->data[i].l_mutex, NULL))
			return (1);
		env->data[i].dead = 0;
		env->data[i].time_die = ft_atoi(str[2]);
		env->data[i].time_eat = ft_atoi(str[3]) * 1000;
		env->data[i].time_sleep = ft_atoi(str[4]) * 1000;
		if (str[5])
			env->data[i].time_must_eat = ft_atoi(str[5]);
		else
			env->data[i].time_must_eat = 0;
	}
	if (pthread_mutex_init(&env->w_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&env->t_mutex, NULL))
		return (1);
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
		env->data[n].r_mutex = &env->data[(n + 1) % nphilo].l_mutex;
		env->data[n].w_mutex = &env->w_mutex;
		env->data[n].t_mutex = &env->t_mutex;
		env->data[n].i = n + 1;
		env->data[n].iseating = 0;
		env->data[n].time_start = start_time();
		env->data[n].last_eat = env->data[n].time_start;
		env->data[n].nbr = ft_atoi(str[1]);
	}
	return (0);
}
