/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:20:07 by trhee             #+#    #+#             */
/*   Updated: 2021/06/15 18:20:11 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t				ft_strlen(const char *s)
{
	size_t			len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t				ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t			i;

	if (!dst && !src)
		return (0);
	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < n - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

size_t				ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t			i;
	size_t			len_dst;
	size_t			len_src;

	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (n <= len_dst)
		return (len_src + n);
	while (src[i] && i < n - len_dst - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len1;
	size_t			len2;
	char			*ret;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ret = malloc(len1 + len2 + 1)))
		return (0);
	ft_strlcpy(ret, s1, len1 + 1);
	ft_strlcat(ret, s2, len1 + len2 + 1);
	return (ret);
}

char				*ft_strdup(const char *s1)
{
	char			*ret;
	size_t			len;
	size_t			i;

	i = 0;
	len = ft_strlen(s1);
	if (!(ret = malloc(len + 1)))
		return (0);
	while (i < len)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
