/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:06:45 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/05/25 04:00:39 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_status
{
	char	buffer[BUFFER_SIZE];
	ssize_t	current;
	ssize_t	read_p;
	ssize_t	fd;
	ssize_t	read_ret;
}	t_status;

char	*read_file(t_status *status);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(char *s, size_t len);
char	*output_line(ssize_t i, t_status status, char *tmp);

#endif