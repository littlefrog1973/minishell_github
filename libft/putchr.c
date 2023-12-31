/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 00:07:45 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/02/24 11:11:28 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	putchr(int c, int fd)
{
	return (write(fd, &c, 1));
}
