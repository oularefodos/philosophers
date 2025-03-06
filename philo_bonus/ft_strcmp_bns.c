/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:06:48 by foulare           #+#    #+#             */
/*   Updated: 2022/02/03 22:10:07 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bns.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	int				p;

	i = 0;
	p = 0;
	while ((s1[i] || s2[i]) && p == 0)
	{
		if (s1[i] != s2[i])
			p = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (p);
}
