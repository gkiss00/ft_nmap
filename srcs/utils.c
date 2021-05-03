#include "./../ft_nmap.h"

static char			**liberer(char **tab, int j)
{
	--j;
	while (j >= 0)
	{
		free(tab[j]);
		--j;
	}
	return (0);
}

static int			separation(char c, char charset)
{
	if (c == charset)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int			count_word(char *str, char charset)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && separation(str[i], charset) == 1)
		{
			++i;
		}
		if (str[i] != '\0' && separation(str[i], charset) == 0)
		{
			++k;
			while (str[i] != '\0' && separation(str[i], charset) == 0)
				++i;
		}
	}
	return (k);
}

static char			*mot(char *str, char charset)
{
	char	*mot;
	int		i;

	i = 0;
	while (str[i] != '\0' && separation(str[i], charset) == 0)
	{
		++i;
	}
	if (!(mot = malloc(sizeof(char*) + (i + 1))))
	{
		return (0);
	}
	i = 0;
	while (str[i] != '\0' && separation(str[i], charset) == 0)
	{
		mot[i] = str[i];
		++i;
	}
	mot[i] = '\0';
	return (mot);
}

char				**ft_split(const char *str, char charset)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == 0)
		return (0);
	if (!(tab = malloc(sizeof(char*) * (count_word((char*)str, charset) + 1))))
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && separation(str[i], charset) == 1)
			++i;
		if (str[i] != '\0' && separation(str[i], charset) == 0)
		{
			if ((tab[j] = mot((char*)&str[i], charset)) == 0)
				return (liberer(tab, j));
			++j;
			while (str[i] != '\0' && separation(str[i], charset) == 0)
				++i;
		}
	}
	tab[count_word((char*)str, charset)] = NULL;
	return (tab);
}


int tab_length(char **tab) {
    int i = 0;

    while(tab[i]) {
        ++i;
    }
    return i;
}

void free_tab(char **tab) {
    int i = 0;

    while(tab[i]) {
        free(tab[i]);
        ++i;
    }
    free(tab);
}

int ft_strlen(char *str) {
    int i = 0;

    while(str && str[i]) {
        ++i;
    }
    return i;
}

char		*ft_strjoin(char *s1, char *s2)
{
	unsigned int		i;
	unsigned int		last;
	char				*str;

	i = 0;
	last = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1 && s1[i] != '\0')
	{
	    str[i] = s1[i];
		++i;
	}
	while (s2 && s2[last] != '\0')
	{
		str[last + i] = s2[last];
		++last;
	}
	str[last + i] = '\0';
    free(s1);
	return (str);
}