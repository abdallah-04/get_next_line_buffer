/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:59:52 by amufleh           #+#    #+#             */
/*   Updated: 2025/09/21 13:15:14 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_words(int fd, char *words_read)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		if (ft_strchr(words_read, '\n'))
			break;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(words_read);
			return (NULL);
		}
		if (bytes == 0)
			break;
		buffer[bytes] = '\0';
		words_read = ft_strjoin(words_read, buffer);
	}
	free(buffer);
	return (words_read);
}

char	*write2endl(char *words_read)
{
	char	*line;
	int		i;

	if (!words_read || !*words_read)
		return (NULL);
	i = 0;
	while (words_read[i] && words_read[i] != '\n')
		i++;
	line = malloc(i + (words_read[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (words_read[i] && words_read[i] != '\n')
	{
		line[i] = words_read[i];
		i++;
	}
	if (words_read[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*final_words(char *words_read)
{
	char	*leftover;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!words_read)
		return (NULL);
	while (words_read[i] && words_read[i] != '\n')
		i++;
	if (!words_read[i])
	{
		free(words_read);
		return (NULL);
	}
	i++;
	leftover = malloc(ft_strlen(words_read + i) + 1);
	if (!leftover)
	{	free(words_read);
		return (NULL);
	}
	while (words_read[i])
		leftover[j++] = words_read[i++];
	leftover[j] = '\0';
	free(words_read);
	return (leftover);
}

char *get_next_line(int fd)
{
	static char *words_read;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	words_read = fill_words(fd, words_read);
	if (!words_read)
		return (NULL);
	line = write2endl(words_read);
	words_read = final_words(words_read);
	if (!line)
	{
		free(line);
		free(words_read);
		return (NULL);
	}
	return (line);
}
// int 	main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	// printf("%s",get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
