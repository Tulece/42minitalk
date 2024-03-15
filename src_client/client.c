/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:48:09 by anporced          #+#    #+#             */
/*   Updated: 2024/03/15 22:49:17 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_state = 0;

void	send_bit(int pid, unsigned char byte, int bit_index)
{
	int	bit;
	int	signal;

	bit = (byte >> (7 - bit_index)) & 1;
	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		ft_error();
}

void	ft_handler(int sig)
{
	(void)sig;
	g_state = 1;
}

void	message_received_handler(int sig)
{
	ft_printf("Server has received the message.\n");
	exit(0);
}

void	send_message(int pid, unsigned char *message)
{
	int	i;
	int	index;

	i = -1;
	while (message[++i] != '\0')
	{
		index = -1;
		while (++index < 8)
		{
			g_state = 0;
			send_bit(pid, message[i], index);
			while (!g_state)
				pause();
		}
	}
	index = -1;
	while (++index < 8)
	{
		g_state = 0;
		send_bit(pid, '\0', index);
		while (!g_state)
			pause();
	}
}

int	main(int argc, char **argv)
{
	int				pid;
	unsigned char	*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s [SERVER PID] [MESSAGE]\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = (unsigned char *)argv[2];
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, message_received_handler);
	send_message(pid, message);
	return (0);
}
