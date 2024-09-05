/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:56:21 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/10 10:56:33 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	word_count(char *str, char *charset)
{
	int	i;
	int	word;
	int	count;

	if (!str)
		return (0);
	i = 0;
	word = 0;
	count = 0;
	while (str && str[i])
	{
		if (!is_separator(str[i], charset) && word == 0)
		{
			count++;
			word = 1;
		}
		else if (is_separator(str[i], charset))
			word = 0;
		i++;
	}
	return (count + 1);
}

static int	len(char *str, char *charset)
{
	int	i;

	i = 0;
	while (!is_separator(str[i], charset) && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strdup(char *dest, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) malloc(sizeof(1) * (len + 1));
	while (i < len)
	{
		str[i] = dest[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_ssplit(char *str, char *charset)
{
	int		i;
	int		j;
	int		word;
	char	**ans;

	i = -1;
	j = 0;
	word = 0;
	ans = malloc(sizeof(char *) * (word_count(str, charset)));
	if (str == NULL || ans == NULL)
		return (NULL);
	while (str[++i])
	{
		if (!is_separator(str[i], charset) && word == 0)
		{
			word = 1;
			ans[j] = ft_strdup(&str[i], len(&str[i], charset));
			j++;
		}
		else if (is_separator(str[i], charset))
			word = 0;
	}
	ans[j] = NULL;
	return (ans);
}
