/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:06:27 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/05/25 04:32:41 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_status	status;

	if (fd < 0)
		return (NULL);
	if (fd != status.fd)
	{
		status.current = 0;
		status.read_p = 0;
		status.read_ret = 0;
		status.fd = fd;
	}
	//printf("status.read_p:%lu status.current:%lu  BUFFER_SIZE:%d\n",status.read_p, status.current,  BUFFER_SIZE);
	return (read_file(&status));
}

char	*read_file(t_status *status)
{
	ssize_t	i;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		if (status->read_p <= status->current)
		{
			status->read_ret = read(status->fd, status->buffer, BUFFER_SIZE);
			status->read_p = status->read_ret + status->read_p;
			if (status->read_ret < 0)
				return (free(tmp), NULL);
		}
		i = status->current;
	//	printf("status->read_p:%lu status->current:%lu i:%lu tmp:%s BUFFER_SIZE:%d\n",status->read_p, status->current, i, tmp, BUFFER_SIZE);
		while (status->read_p > status->current)
		{
			if (status->buffer[status->current++] == '\n')
				return (output_line(i, *status, tmp));
		}
		tmp = output_line(i, *status, tmp);
		if (!tmp || status->read_ret == 0)
			return (tmp);
	}
}

//like a substr + strjoin
char	*output_line(ssize_t i, t_status status, char *tmp)
{
	char	*ret;
	char	*tmp_2;

	if (!tmp)
		return (ft_strndup(&(status.buffer[i]), status.current - i));
	tmp_2 = ft_strndup(&(status.buffer[i]), status.current - i);
	if (!tmp_2)
	{
		free(tmp);
		return (NULL);
	}
	ret = ft_strjoin(tmp, tmp_2);
	free(tmp);
	free(tmp_2);
	return (ret);
}

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int	fd;

	fd = open("./test.txt", O_RDONLY,755);
	printf("your result:%s\n",get_next_line(fd));
	printf("your result:%s\n",get_next_line(fd));
	printf("your result:%s\n",get_next_line(fd));
	close(fd);
}
