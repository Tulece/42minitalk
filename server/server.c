/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:47:53 by anporced          #+#    #+#             */
/*   Updated: 2024/03/15 12:01:30 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handle_signal(int sig, siginfo_t *siginfo, void *str)
{
	static int	i;
	static int	bit;

	(void)str;
	if (sig == SIGUSR1)
	{
		bit = bit | 1 << (7 - i);
		i++;
	}
	else
		i++;
	if (i == 8)
	{
		alloc_char(bit);
		i = 0;
		bit = 0;
	}
	usleep(50);
	kill(siginfo->si_pid, SIGUSR1);
}

void	alloc_char(char c)
{
	static char	*str = NULL;
	static int	i = 0;
	static int	capacity = REALLOC_SIZE;
	char		*new_str;

	if (!str)
	{
		str = (char *)malloc(capacity * sizeof(char));
		if (!str)
			exit(EXIT_FAILURE);
	}
	if (i >= capacity - 1)
	{
		capacity += REALLOC_SIZE;
		new_str = (char *)malloc(capacity * sizeof(char));
		if (!new_str)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(new_str, str, i);
		free(str);
		str = new_str;
	}
	str[i++] = c;
	if (c == '\0')
	{
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
		i = 0;
		capacity = REALLOC_SIZE;
	}
}
