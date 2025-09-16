/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:59:52 by amufleh           #+#    #+#             */
/*   Updated: 2025/09/16 12:59:57 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list *head = NULL;
	char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fill_list(&head, fd);
	// printf("\nafter the fill\n");
	// ft_lstiter(head, print);
	str = write2endl(&head);
	// printf("\nafter writefun\n");
	// ft_lstiter(head, print);
	final_list(&head);
	// printf("\nafter final_list\n");
	// ft_lstiter(head, print);

	printf("-> %s",str);
	return (str);
}

int 	main()
{
	int fd = open("text.txt", O_RDONLY | O_CREAT, 0777);

	get_next_line(fd);

	//printf("%s\n",get_next_line(fd));
	close(fd);
	return (0);
}
