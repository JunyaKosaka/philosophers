/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 16:47:41 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  check if eat count reached must_eat_cnt  */
static void	check_eat_cnt(t_man *man)
{
	if (man->my_eat_cnt == man->must_eat_cnt)
	{
		pthread_mutex_lock(man->done_persons);
		*(man->done_persons_cnt) += 1;
		pthread_mutex_unlock(man->done_persons);
	}
	if (*(man->done_persons_cnt) == man->num_of_phils)
	{
		*(man->sim_done) = true;
	}
}

void	*loop_thread(void *p)
{
	t_man	*man;

	man = p;
	while (*(man->sim_done) == false)
	{
		phil_eat(man);
		phil_sleep(man);
		phil_think(man);
		check_eat_cnt(man);
	}
	return (NULL);
}

void	launcher(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_phils)
		pthread_create(&info->men[i].thread, NULL, &loop_thread, \
						(void *)&info->men[i]);
	i = -1;
	while (++i < info->num_of_phils)
		pthread_join(info->men[i].thread, NULL);
}

int	solo_philo(int time_to_die)
{
	long long	time;
	int			id;

	time = get_millisec();
	id = 1;
	printf("%lld %d %s\n", time, id, FORK_MSG);
	usleep(time_to_die * 1000);
	printf("%lld %d %s\n", time + time_to_die, id, DIED_MSG);
	return (1);
}
