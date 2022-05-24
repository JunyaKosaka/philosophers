/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/24 14:35:56 by jkosaka          ###   ########.fr       */
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
		pthread_mutex_lock(man->baton);
		*(man->sim_done) = true;
		pthread_mutex_unlock(man->baton);
	}
}

void	*loop_thread(void *p)
{
	t_man	*man;

	man = p;
	if (man->num_of_phils & 1 && man->id == man->num_of_phils)
		phil_wait(man, 2 * man->time_to_eat);
	if (man->id & 1 == 0)
		usleep(200);
	while (*(man->sim_done) == false)
	{
		phil_eat(man);
		phil_sleep(man);
		phil_think(man);
		check_eat_cnt(man);
		if (man->num_of_phils & 1)
			phil_wait(man, 2 * man->time_to_eat - man->time_to_sleep - 1);
	}
	return (NULL);
}

void	*monitor_thread(void *p)
{
	t_info		*info;
	long long	cur_time;
	int			i;

	info = p;
	while (info->sim_done == false)
	{
		cur_time = get_millisec();
		i = -1;
		while (++i < info->num_of_phils)
		{
			if (info->time_to_die <= cur_time - info->men[i].last_eat_time)
			{
				print_log(&(info->men[i]), DIED_MSG);
			}
		}
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
	pthread_create(&info->monitor, NULL, &monitor_thread, info);
	pthread_join(info->monitor, NULL);
	i = -1;
	while (++i < info->num_of_phils)
		pthread_join(info->men[i].thread, NULL);
}

/*  solo philosopher cannot survive  */
int	solo_philo(int time_to_die)
{
	long long	time;
	int			id;

	time = get_millisec();
	id = 1;
	printf("%lld %d %s\n", time, id, FORK_MSG);
	usleep(time_to_die * 1000);
	printf("%lld %d %s\n", time + time_to_die, id, DIED_MSG);
	return (0);
}
