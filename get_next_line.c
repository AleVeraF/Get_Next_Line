/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:08:18 by alvera-f          #+#    #+#             */
/*   Updated: 2024/10/15 12:08:21 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	if (size > 0)
	{
		while (src[src_len] != '\0' && src_len < size -1)
		{
			dest[src_len] = src[src_len];
			src_len++;
		}
		dest[src_len] = '\0';
	}
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	return (src_len);
}

char	*concat_store(char **store, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*store, buffer);
	free(*store);
	//free(buffer);
	return (temp);
}

char	*extrac_line(char **store)
{
	char	*new_line;
	size_t	line_len;
	char	*line;
	char	*new_store;

	new_line = ft_strchr(*store, '\n');
	if (new_line)
		line_len = (new_line - *store) + 1;
	else
		line_len = ft_strlen(*store);
	line = (char *) malloc(line_len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *store, line_len + 1);
	if (new_line)
	{
		new_store = ft_strdup(new_line + 1);
		free(*store);
		*store = new_store;
	}
	else
	{
		free(*store);
		*store = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char	*buffer;
	ssize_t			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		if (store == NULL)
			store = ft_strdup(buffer);
		else
			store = concat_store(&store, buffer);
		if (ft_strchr(store, '\n'))
			break;
	}

	if (bytes_read < 0)
	{
		free(buffer);
		free(store);
		store = NULL;
		return NULL;
	}

	if (bytes_read == 0 && (store == NULL || *store == '\0'))
	{
		free(buffer);
		free (store); // liberamos la memoria si no hay datos
		store = NULL; // restablecemos store
		return NULL;
	}
	free(buffer);
	return extrac_line(&store);// función para extraer cada linea
}

#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

    // Abrimos el archivo en modo solo lectura
    fd = open("ale.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error abriendo archivo");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
	close(fd);

    return (0);
}
