/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:37:57 by druth             #+#    #+#             */
/*   Updated: 2021/09/19 19:37:57 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_reconfig(char **buffer, int fd, char *reader, int checker)
{
	int		track;
	char	*temp;

	track = checker;
	while (reader[checker] != '\0')
		checker++;
	temp = (char *)malloc(sizeof(char) * (checker - track + 1));
	if (temp == NULL)
		return (-1);
	free(buffer[fd]);
	buffer[fd] = NULL;
	checker = 0;
	while (reader[track] != '\0')
		temp[checker++] = reader[track++];
	temp[checker] = '\0';
	buffer[fd] = temp;
	return (checker);
}

char	*ft_freemanstuff(char **buffer, int fd, char *output, char *reader)
{
	if (buffer[fd] != NULL)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	if (output != NULL)
	{
		free(output);
		output = NULL;
	}
	if (reader != NULL)
	{
		free(reader);
		reader = NULL;
	}
	return (NULL);
}

char	*ft_assigning(char **buffer, int fd, int checker)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (checker + 1));
	if (output == NULL)
		return (NULL);
	checker = -1;
	while (buffer[fd][++checker] != '\0' && buffer[fd][checker] != '\n')
		output[checker] = buffer[fd][checker];
	output[checker++] = '\n';
	output[checker] = '\0';
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (output);
}

char	*ft_oneline(char **buffer, int fd, int checker)
{
	int		track;
	char	*temp;
	char	*output;

	track = 0;
	output = NULL;
	while (buffer[fd][checker + track] != '\0')
		track++;
	if (track == 0)
		return (ft_assigning(buffer, fd, checker));
	temp = (char *)malloc(sizeof(char) * (track + 1));
	if (temp == NULL)
		return (ft_freemanstuff(buffer, fd, output, temp));
	track = -1;
	while (buffer[fd][checker + ++track] != '\0')
		temp[track] = buffer[fd][checker + track];
	temp[track] = '\0';
	output = ft_assigning(buffer, fd, checker);
	if (output == NULL)
		return (ft_freemanstuff(buffer, fd, output, temp));
	buffer[fd] = temp;
	return (output);
}

int	ft_checking(char *str, int flag)
{
	int	track;

	track = 0;
	while (str[track] != '\0' && str[track] != '\n')
		track++;
	if ((str[track] == '\n' && flag == 0) || (str[track] == '\0' && flag == 1))
		return (track + 1);
	return (-1);
}
