/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:11:17 by jkhong            #+#    #+#             */
/*   Updated: 2021/05/13 23:00:17 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_newline(char *str)
{	
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++; 
	}
	return (-1);
}

char	*concat_lst(t_list *lst, int len)
{
	char	*tmp;
	int		i_tmp;
	int		i_lst;

	tmp = malloc(sizeof(char) * ((len * BUFFER_SIZE) + 1));
	i_tmp = 0;
	while (lst)
	{	
		i_lst = 0;
		while ((lst->content)[i_lst])
			tmp[i_tmp++] = (lst->content)[i_lst++];
		lst = lst->next;
	}
	tmp[i_tmp] = '\0';
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1]; // why + 1?
	int			index;
	char		*char_tmp;
	t_list		*lst;
	int			nl_index;
	int			lst_len;

	index = 1;
	lst_len = 0;
	char_tmp = NULL;
	lst = NULL;
	while(index)
	{	
		char_tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		index = read(fd, char_tmp, BUFFER_SIZE);
		if (index == 0 || index == -1)
			free(char_tmp);
		if (index == 0)
			return (0);
		if (index == -1)
			return (1);
		char_tmp[index] = '\0';
		ft_lstadd_back(&lst, char_tmp);
		lst_len++;
		nl_index = check_newline(char_tmp);
		if (nl_index != -1)
		{	
			// print_lst(lst);
			*line = concat_lst(lst, lst_len);
			ft_lstclear(&lst, free);
			return (1);
		}
	}
}