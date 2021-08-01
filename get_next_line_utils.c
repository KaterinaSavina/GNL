#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while ('\0' != s[i])
		i++;
	return ((int)i);
}

char	*ft_s2(char *s2, const char *s, unsigned int start, size_t len)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = ((char *)s)[start++];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
		str[i++] = (unsigned char)c;
	return (b);
}

char	*ft_strchr(const char *s, int c)

{
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(*s1) * (ft_strlen((char *) s1) + 1));
	if (!(s2))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
