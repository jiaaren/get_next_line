/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:19:59 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/21 12:13:29 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
	Accepts a single linked list double pointer, and char *, represented by string.
	Creates new node and append to end of list.
	Note: Need double pointer in order to append to lst with len 0 
*/
void	ft_lstadd_back(t_list **lst, char *content)
{
	t_list	*new;
	t_list	*tmp;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = content;
	new->next = NULL;
	// for instances where len of lst is 0
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// Free all nodes within list, accepts list pointer and function pointer ('free' to be passed in)
void	ft_lstclear(t_list **lst, void (*del)(void *))
{	
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

// Returns length of list
int	ft_linesize(t_list *lst)
{
	int		len;
	char	*str;

	len = 0;
	while (lst)
	{
		str = lst->content;
		while (*str != '\n' && *str != '\0')
		{
			str++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_bzero(void *ptr, size_t num)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)ptr;
	while (i < num)
	{
		tmp[i] = 0;
		i++;
	}
}

// Used in conjunction with ft_bzero to mimic calloc, i.e. initialise memory to 0
void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
