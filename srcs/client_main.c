/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:33:41 by me                #+#    #+#             */
/*   Updated: 2021/12/08 07:46:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sigusr_handler()
{
	ft_putstr("Message Received!\n");
}

int	ft_send_bit(char c, int pid)
{
	int	i;

	i = 0;
//	printf("sending bit: %c\n", c);
	while (i < 8)
	{
//		printf("in the send bit loop\n");
		if (c & 1<<i)
		{
			if ((kill(pid, SIGUSR1)) == -1)
				return (ft_error_msg_fd("Error, bad PID\n", 0, 0));
				// Should i say error signal or bad pid?
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
	int		i;
	int		pid;
	struct sigaction	sa;

	if (ac != 3)
		return (ft_error_msg_fd("Error, expected arguments: <PID> <Message>\n", 0, 0));

	sa.sa_handler = &ft_sigusr_handler;
	// secure this, nope
	sigaction(SIGUSR1, &sa, NULL);

	if (!ft_str_isdigit(av[1]))
		return (ft_error_msg_fd("Error, PID must be a number\n", 0, 0));
	if (!ft_str_isprint(av[2]))
		return (ft_error_msg_fd("Error, Message is not fully printable.\n", 0, 0));
	pid = ft_atoi(av[1]);
	i = 0;
	while (av[2][i])
	{
		if (!ft_send_bit(av[2][i], pid))
			return (0);
		++i;
	}
	ft_send_bit('\0', pid);
	return (0);
}
