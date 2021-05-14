/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 21:17:55 by jkhong            #+#    #+#             */
/*   Updated: 2021/05/14 00:22:17 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 40
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int		get_next_line(int fd, char **line);
void	ft_lstadd_back(t_list **lst, char *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
char	*ft_strdup(const char *str);
void	print_lst(t_list *lst);

#endif