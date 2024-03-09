/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:28:45 by ftemori           #+#    #+#             */
/*   Updated: 2023/08/10 00:28:51 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"	

static char	*nl_finder(int fd, char *chunk, char *archive)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != '\0')
	{
		if ((archive) && (ft_strchr (archive, '\n')))
			break ;
		read_line = read(fd, chunk, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		chunk[read_line] = '\0';
		if (!archive)
			archive = ft_strdup("");
		char_temp = archive;
		archive = ft_strjoin(char_temp, chunk);
		free(char_temp);
		char_temp = NULL;
	}
	return (archive);
}

static int	nl_counter(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

static char	*before_nl(char *line)
{
	char	*befline;
	int		i;
	int		k;

	k = nl_counter(line);
	i = 0;
	befline = malloc(k + 1);
	while (i <= k)
	{
		befline[i] = line[i];
		i++;
	}
	befline[k] = '\0';
	free(line);
	line = NULL;
	return (befline);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*archive;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (0);
	archive = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*archive == '\0')
	{
		free(archive);
		archive = NULL;
	}
	line[count + 1] = '\0';
	return (archive);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*chunk;
	static char	*archive[FOPEN_MAX];
	char		*retline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	chunk = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chunk)
		return (0);
	line = nl_finder(fd, chunk, archive[fd]);
	free(chunk);
	chunk = NULL;
	if (!line)
		return (NULL);
	archive[fd] = extract(line);
	retline = before_nl(line);
	return (retline);
}
