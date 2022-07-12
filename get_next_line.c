/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:37:30 by druth             #+#    #+#             */
/*   Updated: 2021/09/19 19:37:30 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_adding(char *reader, ssize_t size, char *output)
{
	ssize_t	track;
	char	*temp;

	track = 0;
	if (output == NULL && size == 0)
		return (NULL);
	while (output != NULL && output[track] != '\0')
		track++;
	temp = (char *)malloc(sizeof(char) * (track + size + 1));
	if (temp == NULL)
		return (NULL);
	track = 0;
	while (output != NULL && output[track] != '\0')
	{
		temp[track] = output[track];
		track++;
	}
	size = -1;
	while (reader[++size] != '\0')
		temp[track + size] = reader[size];
	temp[track + size] = '\0';
	free(output);
	output = NULL;
	return (temp);
}

char	*ft_end_of_the_line_for_you_bucko(char **buffer, int fd, char *output,
		int track)
{
	char	*temp;

	if (output[track] == '\n')
		track++;
	temp = (char *)malloc(sizeof(char) * (track + 1));
	if (temp == NULL)
		return (ft_freemanstuff(buffer, fd, output, temp));
	temp[track] = '\0';
	track = -1;
	while (output[++track] != '\n' && output[track] != '\0')
		temp[track] = output[track];
	if (output[track] == '\n')
		temp[track++] = '\n';
	track = ft_reconfig(buffer, fd, output, track);
	if (track == -1)
		return (ft_freemanstuff(buffer, fd, output, temp));
	if (buffer[fd][0] == '\0' && track == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	free(output);
	return (temp);
}

char	*ft_loop(char **buffer, int fd, char *output, char *reader)
{
	ssize_t	track;
	int		check;

	check = -10;
	track = -12;
	reader = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (reader == NULL)
		return (ft_freemanstuff(buffer, fd, output, reader));
	while (check != -1 && track != 0)
	{
		track = read(fd, reader, BUFFER_SIZE);
		if (track == -1)
			return (ft_freemanstuff(buffer, fd, output, reader));
		reader[track] = '\0';
		output = ft_adding(reader, track, output);
		if (output == NULL)
			return (ft_freemanstuff(buffer, fd, output, reader));
		check = ft_checking(reader, 1);
	}
	free(reader);
	reader = NULL;
	track = 0;
	while (output[track] != '\n' && output[track] != '\0')
		track++;
	return (ft_end_of_the_line_for_you_bucko(buffer, fd, output, track));
}

char	*ft_nonull(char **buffer, int fd, char *output, char *reader)
{
	int		track;

	track = 0;
	while (buffer[fd][track] != '\0')
		track++;
	if (track > 0)
	{
		output = (char *)malloc(sizeof(char) * (track + 1));
		if (output == NULL)
			return (ft_freemanstuff(buffer, fd, output, reader));
		track = -1;
		while (buffer[fd][++track] != '\0')
			output[track] = buffer[fd][track];
		output[track] = '\0';
		free(buffer[fd]);
	}
	buffer[fd] = NULL;
	return (ft_loop(buffer, fd, output, reader));
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*reader;
	int			checker;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	checker = -1;
	if (buffer[fd] != NULL)
		checker = ft_checking(buffer[fd], 0);
	if (checker > 0)
		return (ft_oneline(buffer, fd, checker));
	reader = NULL;
	output = NULL;
	if (buffer[fd] == NULL)
		return (ft_loop(buffer, fd, output, reader));
	return (ft_nonull(buffer, fd, output, reader));
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	// int		fd2;
	// int		fd3;
	fd1 = open("test.txt", O_RDONLY);
	// fd2 = open("test2.txt", O_RDONLY);
	// fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 4)
	{
		// printf("entering\n");
		line = get_next_line(fd1);
		// printf("entering!?\n");
		printf("\n\nline [%02d]:%s:\n", i, line);
		// printf("problem? :%s:\n", line);
		free(line);
		// printf("nope not at all\n");
		// line = get_next_line(fd2);
		// printf("line [%02d]:%s:\n", i, line);
		// free(line);
		// line = get_next_line(fd3);
		// printf("line [%02d]:%s:\n", i, line);
		// free(line);
		i++;
	}
	close(fd1);
	// close(fd2);
	// close(fd3);
	return (0);
}*/
