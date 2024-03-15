/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:48:41 by anporced          #+#    #+#             */
/*   Updated: 2024/03/15 22:29:12 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_add_char_to_buffer(char **buffer, char c, size_t *len)
{
	char	*new_buffer;

	new_buffer = malloc(*len + 2);
	if (!new_buffer)
	{
		ft_printf("Error: Allocation failed\n");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(new_buffer, *buffer, *len);
	new_buffer[*len] = c;
	(*len)++;
	new_buffer[*len] = '\0';
	free(*buffer);
	*buffer = new_buffer;
}

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int		bit_count = 0;
	static char		char_assembled = 0;
	static char		*msg_buffer = NULL;
	static size_t	msg_len = 0;

	(void)context;
	if (sig == SIGUSR1)
		char_assembled |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (char_assembled != '\0')
			ft_add_char_to_buffer(&msg_buffer, char_assembled, &msg_len);
		else
		{
			ft_printf("Message received: %s\n", msg_buffer);
			free(msg_buffer);
			msg_buffer = NULL;
			msg_len = 0;
			kill(info->si_pid, SIGUSR2);
		}
		bit_count = 0;
		char_assembled = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
