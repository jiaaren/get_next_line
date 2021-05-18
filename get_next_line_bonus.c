/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:11:17 by jkhong            #+#    #+#             */
/*   Updated: 2021/05/18 12:17:45 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_newline(char *str, char *buffer)
{	
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			while (str[i + j + 1])
			{
				buffer[j] = str[i + j + 1];
				j++;
			}
			buffer[j] = '\0';
			return (i);
		}
		i++;
	}
	buffer[j] = '\0';
	return (-1);
}

char	*concat_lst(t_list *lst, int len)
{
	char	*tmp;
	int		i_tmp;
	int		i_lst;

	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	i_tmp = 0;
	while (lst)
	{
		i_lst = 0;
		while ((lst->content)[i_lst] && (lst->content)[i_lst] != '\n')
			tmp[i_tmp++] = (lst->content)[i_lst++];
		lst = lst->next;
	}
	tmp[i_tmp] = '\0';
	return (tmp);
}

int	add_str(int fd, char *buffer, t_list **lst, char **str)
{
	int		index;
	char	*char_tmp;

	index = 0;
	char_tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer[0])
	{	
		while (buffer[index])
		{
			char_tmp[index] = buffer[index];
			index++;
		}
	}
	else
		index = read(fd, char_tmp, BUFFER_SIZE);
	if (index == -1)
	{	
		free(char_tmp);
		return (-1);
	}
	char_tmp[index] = '\0';
	*str = char_tmp;
	ft_lstadd_back(lst, char_tmp);
	return (index);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff[1024];
	int			index;
	char		*char_tmp;
	t_list		*lst;

	index = 1;
	char_tmp = NULL;
	lst = NULL;
	if (!buff[fd])
		buff[fd] = calloc((BUFFER_SIZE + 1), sizeof(char));
	while (index)
	{
		index = add_str(fd, buff[fd], &lst, &char_tmp);
		if (index == -1)
		{
			free(buff[fd]);
			return (-1);
		}
		else if (check_newline(char_tmp, buff[fd]) >= 0 || index == 0)
		{
			*line = concat_lst(lst, ft_linesize(lst));
			ft_lstclear(&lst, free);
			if (!index)
			{
				free(buff[fd]);
				return (0);
			}
			return (1);
		}
	}
	return (0);
}
