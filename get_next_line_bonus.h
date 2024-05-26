/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:06:45 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/05/26 23:12:19 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_status
{
	char			buffer[BUFFER_SIZE];
	ssize_t			current;
	int				fd;
	ssize_t			read_ret;
	ssize_t			bf_size;
	struct s_status	*next;
}	t_status;

char		*get_next_line(int fd);
t_status	*get_status(int fd, t_status *lst);
char		*read_file(t_status *status);
char		*output_line(ssize_t i, t_status status, char *tmp);

size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strndup(char *s, size_t len);
void		ft_free_list(t_status *status_lst);
void		remove_status(int fd, t_status *lst);

#endif