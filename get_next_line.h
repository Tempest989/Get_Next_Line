/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:37:37 by druth             #+#    #+#             */
/*   Updated: 2021/09/19 19:37:37 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int		ft_checking(char *str, int flag);
int		ft_reconfig(char **buffer, int fd, char *reader, int checker);
char	*get_next_line(int fd);
char	*ft_freemanstuff(char **buffer, int fd, char *output, char *reader);
char	*ft_assigning(char **buffer, int fd, int checker);
char	*ft_oneline(char **buffer, int fd, int checker);
char	*ft_adding(char *reader, ssize_t size, char *output);
char	*ft_end_of_the_line_for_you_bucko(char **buffer, int fd, char *output,
			int track);
char	*ft_loop(char **buffer, int fd, char *output, char *reader);
char	*ft_nonull(char **buffer, int fd, char *output, char *reader);
#endif
