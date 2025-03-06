/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:33:52 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 01:28:23 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct data
{
	pthread_mutex_t	l_mutex;
	pthread_mutex_t	*r_mutex;
	pthread_mutex_t	*w_mutex;
	pthread_mutex_t	*t_mutex;
	pthread_t		id;
	pthread_t		id_2;
	int				dead;
	int				iseating;
	int				i;
	int				nbr;
	long			time_start;
	long			last_eat;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				time_must_eat;
}	t_data;

typedef struct s_env{
	pthread_mutex_t	w_mutex;
	pthread_mutex_t	t_mutex;
	t_data			*data;
}	t_env;
int		ft_atoi(const	char *str);
long	start_time(void);
long	get_time(long start);
void	action(t_data *data, char *str, int time);
int		philo_init(t_env *env, char **str);
int		check_die(t_env *env, int nphilo);
int		ft_strcmp(const char *s1, const char *s2);
int		error(char *str);
#endif
