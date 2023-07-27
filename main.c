/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebbaill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:18:53 by sebbaill          #+#    #+#             */
/*   Updated: 2020/02/04 19:38:35 by sebbaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

static void		ft_putstr(const char *s)
{
	int i;

	i = 0;
	if (!s || !*s)
		return ;
	while (s[i] != '\0')
		ft_putchar(s[i++]);
}

static void		ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		n /= 10;
		ft_putnbr(n);
		ft_putchar('8');
	}
	else if ((n >= 0) && (n <= 9))
		ft_putchar(n + '0');
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(n * (-1));
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	char		*line = NULL;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	ft_putstr("BUFFER_SIZE = ");
	ft_putnbr(BUFFER_SIZE);
	ft_putchar('\n');
//	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	if (argc > 2)
	{
		printf("Too many arguments.\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		ret = get_next_line(fd, &line);
		ft_putstr("RET = ");
		ft_putnbr(ret);
		ft_putchar('\n');
		ft_putstr(line);
		ft_memdel((void**)(&line));
		if (ret == 0)
			return (0);
		if (ret == -1)
				return (-1);
		i++;
	}
	return (0);
}
