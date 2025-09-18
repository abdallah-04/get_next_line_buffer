/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:59:52 by amufleh           #+#    #+#             */
/*   Updated: 2025/09/18 12:12:35 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(const char *s1)
{
	size_t	size;
	size_t	i;
	char	*copy;

	size = ft_strlen(s1);
	i = 0;
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (i < size)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	j = 0;
	new_str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)(s + i));
	return (NULL);
}
char *fill_words(int fd, char *words_read)
{
	char *str;
	int bytes;

	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(words_read, '\n'))
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes <=0)
		{
			free(str);
			return (NULL);
		}
		str[bytes] = '\0';
		words_read = ft_strjoin(words_read, str);
	}
	free(str);
	return (words_read);
}
char	*write2endl(char *words_read)
{
	char *line;
	int	i;

	i = 0;
	while(words_read[i] && words_read[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while(words_read[i] && words_read[i] != '\n')
	{
		line[i] = words_read[i];
		i++;
	}
	if (words_read[i] == '\n')
	{
		line[i] = words_read[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
char	*final_words(char *words_read)
{
	int		i = 0;
	int		j = 0;
	char	*leftover;

	while (words_read[i] && words_read[i] != '\n')
		i++;
	if (!words_read[i])
	{
		free(words_read);
		return (NULL);
	}
	leftover = malloc(ft_strlen(words_read) - i - 1);
	if (!leftover)
		return (NULL);
	i++;
	while (words_read[i])
		leftover[j++] = words_read[i++];
	leftover[j] = '\0';
	free(words_read);
	return (leftover);
}

char *get_next_line(int fd)
{
	static char *words_read;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	words_read = fill_words(fd, words_read);
	if (!words_read)
		return (NULL);
	line = write2endl(words_read);
	words_read = final_words(words_read);
	return (line);
}

int 	main()
{
	int fd = open("text.txt", O_RDONLY | O_CREAT, 0777);
	char *line;

	while ((line = get_next_line(fd))) {
	printf("%s", line);
	free(line);
}
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));
	// printf("%s",get_next_line(fd));a
	close(fd);
	return (0);
}
