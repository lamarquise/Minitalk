/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:33:41 by me                #+#    #+#             */
/*   Updated: 2021/12/09 07:53:39 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sigusr_handler(int sig)
{
	(void)sig;
	ft_putstr("Message Received!\n");
}

int	ft_send_bit(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 1 << i)
		{
			if ((kill(pid, SIGUSR1)) == -1)
				return (ft_error_msg_fd("Error, bad PID U1\n", 0, 0));
		}
		else
		{
			if ((kill(pid, SIGUSR2)) == -1)
				return (ft_error_msg_fd("Error, bad PID U2\n", 0, 0));
		}
		usleep(100);
		++i;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int					i;
	struct sigaction	sa;

	if (ac != 3)
		return (ft_error_msg_fd("Error, expected args: <PID> <Msg>\n", 0, 0));
	sa.sa_handler = &ft_sigusr_handler;
	sigaction(SIGUSR1, &sa, NULL);
	if (!ft_str_isdigit(av[1]) || !ft_str_isprint(av[2]))
		return (ft_error_msg_fd("Error, bad arguments\n", 0, 0));
	if (!ft_strcmp(av[2], "kill server"))
	{
		ft_putstr("Killing Server\n");
		kill(ft_atoi(av[1]), SIGINT);
		return (0);
	}
	i = 0;
	while (av[2][i])
	{
		if (!ft_send_bit(av[2][i], ft_atoi(av[1])))
			return (0);
		++i;
	}
	usleep(5000000);
	ft_send_bit('\0', ft_atoi(av[1]));
	return (0);
}
