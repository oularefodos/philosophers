/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:33:52 by foulare           #+#    #+#             */
/*   Updated: 2022/02/04 01:30:42 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_H
# define PHILO_BNS_H
# include <semaphore.h>
# include <unistd.h>

typedef struct data
{
	pid_t		pid;
	sem_t		*write_sem;
	pthread_t	id;
	int			dead;
	int			iseating;
	int			i;
	int			nbr;
	long		time_start;
	long		last_eat;
	int			time_eat;
	sem_t		*die_sem;
	sem_t		*fork_sem;
	int			time_die;
	int			time_sleep;
	int			time_must_eat;
}	t_data;

typedef struct s_env{
	sem_t	*fork_sem;
	sem_t	*write_sem;
	sem_t	*die_sem;
	t_data	*data;
}	t_env;
int		ft_atoi(const	char *str);
int		ft_clear(t_env *env, int nphilo, int status);
long	start_time(void);
long	get_time(long start);
void	action(t_data *data, char *str, int time);
int		philo_init(t_env *env, char **str);
void	*check_die(void	*arg);
int		error(char *str);
int		ft_die_clean(t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
#endif
