/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:33:41 by me                #+#    #+#             */
/*   Updated: 2021/12/10 09:19:16 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error_handler(int sig)
{
	(void)sig;
	ft_putstr("Server Error\n");
	exit(0);		// do i want this?
}

void	ft_confirmation_handler(int sig)
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
				return (ft_error_msg_fd("Error, bad PID\n", 0, 0));
		}
		else
		{
			if ((kill(pid, SIGUSR2)) == -1)
				return (ft_error_msg_fd("Error, bad PID\n", 0, 0));
		}
		usleep(100);
		++i;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int					i;
	int					pid;
	struct sigaction	s1;
	struct sigaction	s2;

	if (ac != 3)
		return (ft_error_msg_fd("Error, expected args: <PID> <Msg>\n", 0, 0));
	s1.sa_handler = &ft_confirmation_handler;
	sigaction(SIGUSR1, &s1, NULL);
	s2.sa_handler = &ft_error_handler;
	sigaction(SIGUSR2, &s2, NULL);
	if (!ft_str_isdigit(av[1]))
		return (ft_error_msg_fd("Error, PID must be a number\n", 0, 0));
	if (!ft_str_isprint(av[2]))
		return (ft_error_msg_fd("Error, Message is not printable.\n", 0, 0));
	pid = ft_atoi(av[1]);
	i = 0;
	while (av[2][i])
	{
		if (!ft_send_bit(av[2][i], pid))
			return (0);
		++i;
	}
	usleep(5000000);
	ft_send_bit('\0', pid);
	return (0);
}
