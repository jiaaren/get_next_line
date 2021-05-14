/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:11:17 by jkhong            #+#    #+#             */
/*   Updated: 2021/05/14 11:43:14 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_newline(char *str, char *buffer)
{	
	int i;
	int j;
	int index;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			while (str[i + j + 1]) // + 1 to skip the newline
			{
				buffer[j] = str[i + j + 1];
				j++;
			}
			buffer[j] = '\0'; // realised that i is returned without ending j
			return (i); // return where is the ending
		}
		i++; 
	}
	buffer[j] = '\0'; // need to shift j here
	return (-1);
	/*
		Make sure to fill buffer with '\0' if nothing
	*/
}

char	*concat_lst(t_list *lst, int len, int nl_index)
{
	char	*tmp;
	int		i_tmp;
	int		i_lst;
	int		start;

	start = 0;
	while ((lst->content)[start] && lst->next != NULL) // double check that we are not iterating through if this is the last node. 
		start++;										// makes sure not to run this if lst len is 1
	if (start > 0 && start < BUFFER_SIZE)
		len -= (BUFFER_SIZE - start);
	if (nl_index != -1)
		len -= (BUFFER_SIZE - nl_index);
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

int		add_str(int fd, char *buffer, t_list **lst, char **str)
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
	char_tmp[index] = '\0';
	*str = char_tmp;
	ft_lstadd_back(lst, char_tmp);
	return (index);
}


int		get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1]; // why + 1?
	int			index;
	char		*char_tmp;
	t_list		*lst;
	int			lst_len;
	int			nl_index;

	index = 1;
	lst_len = 0;
	char_tmp = NULL;
	lst = NULL;
	while(index)
	{
		index = add_str(fd, buff, &lst, &char_tmp);
		lst_len++;
		nl_index = check_newline(char_tmp, buff);
		if (nl_index != -1 || index == 0)
		{
			*line = concat_lst(lst, lst_len * BUFFER_SIZE, nl_index);
			ft_lstclear(&lst, free);
			if (!index)
				return (0);
			return (1);
		}
	}
	if (index == 0)
		return (0);
	if (index == -1)
		return (1);
}