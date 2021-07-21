/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:11:17 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/21 12:45:42 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
	Performs the following:
	(i) Cycle through string passed to check for '\n'
	(ii) If '\n' found, fill buffer of characters after '\n', and NUL terminate
	(iii) Returns index integer (including 0) if '\n' found, else return (-1)
*/
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
	// NUL terminates if (i) no more chars in buffer
	buffer[j] = '\0';
	return (-1);
}

/*
	(i) Calculates length of characters in lst, and concatenate to string
	(ii) Returns string to user
*/
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

/*
	1. Reads from either buffer or file descriptor (fd)
	- Reads from buffer if buffer[0] has value. 
	  Value may be 0 if:
		- initial calloc in process_gnl
		- NUL terminated by check_newline when no more chars in buffer
	- Reads from fd
	2. Fills char_tmp buffer
	- malloc sizeof can be dynamic because it will be freed by end of single gnl execution
	3. Appends to end of list using ft_lstadd_back
*/
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
	// if error noted
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

/*
	(i) Checks if file descriptor exists, else calloc with sizeof(BUFFER_SIZE)
	(ii) Loop until '\n' is found:
		- add_str appends string to end of list from (a) buffer or (b) file descriptor
		- check_newline - checks if '\n' exists in read string, updates and NUL terminates buff
			- if '\n' found or index == 0, (a) concatenate list, (b) update **line user input, (c) free list 
			- else repeat loop
	(iii) If read return value (index) is 0 (file fully read) or -1
	- free buff[fd] and important to assign NULL subsequently
*/
int	process_gnl(int fd, char **line, char **buff)
{
	int			index;
	char		*char_tmp;
	t_list		*lst;

	index = -1;
	lst = NULL;
	if (!buff[fd])
		buff[fd] = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	while (index)
	{
		index = add_str(fd, buff[fd], &lst, &char_tmp);
		if (index == -1)
			break ;
		else if (check_newline(char_tmp, buff[fd]) >= 0 || index == 0)
		{
			*line = concat_lst(lst, ft_linesize(lst));
			ft_lstclear(&lst, free);
			if (!index)
				break ;
			return (1);
		}
	}
	free(buff[fd]);
	buff[fd] = NULL;
	return (index);
}

/*
	Uses array of static (char *) replicating a key-item array.
	Keys are represented by file descriptors (fd) passed by users
	if fd is negative integer or less than OPEN_MAX, function ends, 
	Else, proceed processing via func process_gnl.
*/
int	get_next_line(int fd, char **line)
{
	int			index;
	static char	*buff[OPEN_MAX + 1];

	index = -1;
	if (fd >= 0 && fd <= OPEN_MAX)
		index = process_gnl(fd, line, buff);
	return (index);
}
