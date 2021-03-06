/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:25:23 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/24 13:22:05 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  philosopher takes the first fork  */
static void	first_fork(t_man *man)
{
	if (man->id & 1)
		pthread_mutex_lock(man->left_fork);
	else
		pthread_mutex_lock(man->right_fork);
	print_log(man, FORK_MSG);
}

/*  philosopher takes the second fork  */
static void	second_fork(t_man *man)
{
	if (man->id & 1)
		pthread_mutex_lock(man->right_fork);
	else
		pthread_mutex_lock(man->left_fork);
	print_log(man, FORK_MSG);
}

void	take_two_forks(t_man *man)
{
	first_fork(man);
	second_fork(man);
}

void	unlock_two_forks(t_man *man)
{
	pthread_mutex_unlock(man->left_fork);
	pthread_mutex_unlock(man->right_fork);
}
