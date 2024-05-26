/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:06:27 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/05/26 23:42:22 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_status	status_lst = {.fd = -2, .next = NULL};
	t_status		*status;
	char			*ret;

	if (fd < 0)
	{
		ft_free_list(&status_lst);
		return (NULL);
	}
	status = get_status(fd, &status_lst);
	if (!status)
	{
		ft_free_list(&status_lst);
		return (NULL);
	}
	ret = read_file(status);
	if (!ret)
	{
		remove_status(fd, &status_lst);
		return (NULL);
	}
	return (ret);
}

t_status	*get_status(int fd, t_status *lst)
{
	t_status	*current_status;
	t_status	*new_status;

	current_status = lst;
	while (current_status)
	{
		if (current_status->fd == fd)
			return (current_status);
		if (!current_status->next)
			break ;
		current_status = current_status->next;
	}
	new_status = malloc(sizeof(t_status));
	if (!new_status)
		return (NULL);
	current_status->next = new_status;
	new_status->current = 0;
	new_status->read_ret = 0;
	new_status->fd = fd;
	new_status->bf_size = BUFFER_SIZE;
	new_status->next = NULL;
	return (new_status);
}

char	*read_file(t_status *status)
{
	ssize_t	i;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		if (status->read_ret <= status->current)
		{
			status->read_ret = read(status->fd, status->buffer, BUFFER_SIZE);
			if (status->read_ret < 0)
				return (free(tmp), NULL);
			status->current = 0;
		}
		i = status->current;
		while (status->read_ret && status->read_ret > status->current)
		{
			if (status->buffer[status->current++] == '\n')
				return (output_line(i, *status, tmp));
		}
		if (status->read_ret)
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
	ssize_t	len;

	if (status.current - i > status.bf_size)
	{
		len = status.current - i - status.bf_size;
		if (len > status.bf_size)
			len = status.bf_size;
	}
	else
		len = status.current - i;
	if (!tmp)
		return (ft_strndup(&(status.buffer[i]), len));
	tmp_2 = ft_strndup(&(status.buffer[i]), len);
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

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	int		fd1;
// 	char	*ret0;
// 	//char	*ret1;

// 	fd = open("./test.txt", O_RDONLY, 755);
// 	fd1 = open("./test2.txt", O_RDONLY, 755);
// 	while ((ret0 = get_next_line(fd)) != NULL)
// 	{
// 		printf("your result:%s\n",ret0);
// 		fflush(stdout);
// 		free(ret0);
// 		ret0 = NULL;
// 		ret0 = get_next_line(fd1);
// 		if (ret0 != NULL) {
// 			printf("your result from text2: %s\n", ret0);
// 			fflush(stdout);
// 			free(ret0);
// 			ret0 = NULL;
// 		}
// 	}
// 	close(fd);
// 	close(fd1);
// }
// __attribute__((destructor))
// static void	a(void)
// {
// 	system("leaks -q a.out");
// }
