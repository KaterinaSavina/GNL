#include "get_next_line.h"

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*new_line;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(len + 1);
	if (!(s3))
		return (NULL);
	new_line = s3;
	while (*s1)
	{
		*s3 = *s1;
		s3++;
		s1++;
	}
	while (*s2)
	{
		*s3 = *s2;
		s3++;
		s2++;
	}
	*s3 = '\0';
	return (new_line);
}

static char	*ft_swap_buff(int fd, char *trans_buf, char *swap_buff)
{
	char		read_buff[BUFFER_SIZE + 1];
	ssize_t		ret;

	while (!ft_strchr(swap_buff, '\n'))
	{
		ft_memset(read_buff, 0, BUFFER_SIZE + 1);
		ret = read(fd, read_buff, BUFFER_SIZE);
		if (!swap_buff)
			swap_buff = ft_strdup(read_buff);
		else
		{
			trans_buf = ft_strdup(swap_buff);
			free(swap_buff);
			if (ret == 0)
				swap_buff = ft_strdup(trans_buf);
			else
				swap_buff = ft_strjoin(trans_buf, read_buff);
			free(trans_buf);
		}
		if (!ret)
			break ;
	}
	return (swap_buff);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start)
	{
		s2 = (char *)malloc(sizeof(char));
		if (!s2)
			return (NULL);
		s2[0] = '\0';
		return (s2);
	}
	if (start + len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s) - start;
	s2 = (char *)malloc((sizeof(char)) * (len + 1));
	if (!(s2))
		return (NULL);
	return (ft_s2(s2, s, start, len));
}

static int	find_len(const char *source)
{
	int	len;

	len = 0;
	while (source[len])
	{
		if (source[len] == '\n')
			return (len);
		len++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*trans_buf;
	char		*swap_buff;

	swap_buff = NULL;
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read
		(fd, trans_buf, 0))
		return (-1);
	if (trans_buf)
	{
		swap_buff = ft_strdup(trans_buf);
		free(trans_buf);
	}
	swap_buff = ft_swap_buff(fd, trans_buf, swap_buff);
	if (ft_strchr(swap_buff, '\n'))
	{
		*line = ft_substr(swap_buff, 0, find_len(swap_buff));
		trans_buf = ft_substr(swap_buff, find_len(swap_buff) + 1, BUFFER_SIZE);
		free(swap_buff);
		return (1);
	}
	*line = ft_strdup(swap_buff);
	free(swap_buff);
	trans_buf = NULL;
	return (0);
}
