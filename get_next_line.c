/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:06:27 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/05/25 02:02:30 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_status	status;

	if (fd < 0)
		return (NULL);
	if (fd != status.fd)
	{
		status.current = 0;
		status.read_p = 0;
		status.fd = fd;
	}
	return (read_file(fd, status));
}

char	*read_file(int fd, t_status status)
{
	ssize_t	i;
	char	*tmp;

	if (status.read_p == 0)
		tmp = NULL;
	if (status.read_p <= status.current)
	{
		status.read_p = read(status.fd, status.buffer, BUFFER_SIZE);
		if (status.read_p < 0)
		{
			free(tmp);
			return (NULL);
		}
	}
	i = status.current;
	while (status.read_p != 0 && status.read_p > status.current)
	{
		if (status.buffer[status.current++] == '\n')
			return (output_line(i, status, tmp));
	}
	tmp = output_line(i, status, tmp);
	if (!tmp)
		return (NULL);
}

//like a substr + strjoin
char	*output_line(ssize_t i, t_status status, char *tmp)
{
	char	*ret;

	if (!tmp)
		return (ft_strndup(status.buffer[i], status.current - i));
	ret = ft_strjoin(tmp, ft_strndup(status.buffer[i], status.current - i));
	if (!ret)
	{
		free(tmp);
		return (NULL);
	}
	return (ret);
}

#include <fcntl.h>
int	main(void)
{
	int	fd;

	open("./test.txt", O_RDONLY,755);

}