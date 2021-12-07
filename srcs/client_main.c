/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:33:41 by me                #+#    #+#             */
/*   Updated: 2021/12/07 11:00:15 by me               ###   ########.fr       */
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
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		++i;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;
	char	*msg;
	struct sigaction	sa;

	(void)av;
	if (ac != 3)
		return (ft_error_msg_fd("Error, expected arguments: <PID> <Message>\n", 0, 0));

	sa.sa_handler = &ft_sigusr_handler;
	sigaction(SIGUSR1, &sa, NULL);

	pid = ft_atoi(av[1]);
	msg = ft_strdup(av[2]);
	i = 0;
	while (msg[i])
	{
//		printf("main sending bits loop\n");
		ft_send_bit(msg[i], pid);
		++i;
	}
	ft_send_bit('\0', pid);

	// works but not what we want to do.
/*	kill(pid, SIGUSR1);
	usleep(100);
	kill(pid, SIGUSR2);
	usleep(100);
	kill(pid, SIGUSR2);
	usleep(100);
	kill(pid, SIGUSR1);
	usleep(100);
*/
//	kill(pid, SIGINT);
	free(msg);

	return (0);
}
