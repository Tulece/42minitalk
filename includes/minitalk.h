/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:29:49 by anporced          #+#    #+#             */
/*   Updated: 2024/03/15 12:01:54 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/includes/libft.h"
# include <signal.h>

# define REALLOC_SIZE 64

void	handle_signal(int sig, siginfo_t *siginfo, void *str);
void	alloc_char(char c);

#endif
