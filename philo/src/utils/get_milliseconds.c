/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_milliseconds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:20:18 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 18:32:49 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  get current time in milli seconds  */
long long	get_millisec(void)
{
	struct timeval	time;
	long long		millisec;

	gettimeofday(&time, NULL);
	millisec = (long long)time.tv_sec * 1000 + time.tv_usec / 1000;
	return (millisec);
}
