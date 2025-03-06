/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:32:55 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 01:45:25 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_clear(t_env *env, int nphilo)
{
	int	n;

	n = -1;
	while (++n < nphilo)
		pthread_mutex_destroy(&env->data[n].l_mutex);
	pthread_mutex_destroy(&env->t_mutex);
	pthread_mutex_destroy(&env->w_mutex);
	free(env->data);
	return (1);
}

int	check_error(int ac, char **str)
{
	int	i;
	int	j;

	i = 0;
	if (ac < 5 || ac > 6)
		return (error("nombre d'argument invalide"));
	while (str[++i] != 0)
	{
		if (!ft_atoi(str[i]))
			return (error("seulement un entier positif > 0"));
		j = -1;
		while (str[i][++j] != 0)
			if (str[i][j] < 48 || str[i][j] > 57)
				return (error("seuleument un entier positif"));
	}
	return (0);
}

void	*ft_philo(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->i % 2 == 0)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&data->l_mutex);
		action(data, "has taken a fork", 0);
		pthread_mutex_lock(data->r_mutex);
		action(data, "has taken a fork", 0);
		data->last_eat = start_time();
		action(data, "is eating", data->time_eat);
		data->iseating++;
		pthread_mutex_unlock(data->r_mutex);
		pthread_mutex_unlock(&data->l_mutex);
		if (data->time_must_eat && data->time_must_eat <= data->iseating)
			break ;
		action(data, "is sleeping", data->time_sleep);
		action(data, "is thinking", 0);
	}
	return (NULL);
}

int	main(int ac, char **str)
{
	t_env	env;
	int		n;
	int		nphilo;

	nphilo = ft_atoi(str[1]);
	memset(&env, '\0', sizeof(t_env));
	if (check_error(ac, str))
		return (0);
	if (philo_init(&env, str))
		return (1);
	n = 0;
	while (n < nphilo)
	{
		pthread_create(&env.data[n].id, NULL, ft_philo, (void *)&env.data[n]);
		n++;
	}
	n = -1;
	while (++n < nphilo)
		pthread_detach(env.data[n].id);
	check_die(&env, nphilo);
	ft_clear(&env, nphilo);
}
