/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:53:45 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 02:28:34 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bns.h"
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_clear(t_env *env, int nphilo, int status)
{
	int	n;

	n = -1;
	status = 1;
	if (status == 1)
		while (++n < nphilo)
			kill(env->data[n].pid, 15);
	free(env->data);
	sem_close(env->fork_sem);
	sem_close(env->write_sem);
	sem_close(env->die_sem);
	sem_unlink("/fork");
	sem_unlink("/write");
	sem_unlink("/die_sem");
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
				return (error("seulement un entier positif"));
	}
	return (0);
}

void	ft_philo(t_data *data)
{
	if (pthread_create(&data->id, 0, check_die, data))
		error ("erreur de thread\n");
	if (data->i % 2 == 0)
		usleep(15000);
	while (1)
	{
		sem_wait(data->fork_sem);
		action(data, "has taken a fork", 0);
		sem_wait(data->fork_sem);
		action(data, "has taken a fork", 0);
		data->last_eat = start_time();
		action(data, "is eating", data->time_eat);
		data->iseating++;
		sem_post(data->fork_sem);
		sem_post(data->fork_sem);
		if (data->time_must_eat && data->time_must_eat <= data->iseating)
			break ;
		action(data, "is sleeping", data->time_sleep);
		action(data, "is thinking", 0);
	}
	pthread_join(data->id, NULL);
	usleep(15000);
	ft_die_clean(data);
	exit (0);
}

int	main(int ac, char **str)
{
	t_env	env;
	int		n;
	int		nphilo;
	int		status;

	nphilo = ft_atoi(str[1]);
	memset(&env, '\0', sizeof(t_env));
	if (check_error(ac, str))
		return (0);
	if (philo_init(&env, str))
		return (1);
	n = 0;
	while (n < nphilo)
	{	
		env.data[n].pid = fork();
		if (env.data[n].pid < 0)
			error ("error fork\n");
		if (env.data[n].pid == 0)
			ft_philo(&env.data[n]);
		n++;
	}
	waitpid (-1, &status, 0);
	ft_clear(&env, nphilo, status);
}
