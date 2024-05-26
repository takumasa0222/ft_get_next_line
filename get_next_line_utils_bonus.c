/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:06:47 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/05/26 23:42:46 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	char			*ret;
	char			*cpy_s1;
	char			*cpy_s2;

	cpy_s1 = (char *)s1;
	cpy_s2 = (char *)s2;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (*cpy_s1)
		*ret++ = *cpy_s1++;
	while (*cpy_s2)
		*ret++ = *cpy_s2++;
	*ret = '\0';
	return (ret - (s1_len + s2_len));
}

size_t	ft_strlen(const char *s)
{
	size_t			len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strndup(char *s, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	ft_free_list(t_status *status_lst)
{
	t_status	*current;
	t_status	*tmp;

	current = status_lst;
	while (current->next)
	{
		tmp = current;
		current = current->next;
		if (tmp->fd != -2)
		{
			free(tmp);
			tmp = NULL;
		}
	}
}

void	remove_status(int fd, t_status *lst)
{
	t_status	*current_status;
	t_status	*prev_status;

	current_status = lst;
	prev_status = NULL;
	while (current_status)
	{
		if (current_status->fd == fd)
		{
			if (prev_status)
				prev_status->next = current_status->next;
			free(current_status);
			return ;
		}
		prev_status = current_status;
		current_status = current_status->next;
	}
}
