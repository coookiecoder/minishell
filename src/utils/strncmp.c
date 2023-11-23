/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   NOOT NOOT MOTHER FUCKER                      :#:  :#:         :#:  :#:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: the-day-it-was updated by UwU                                   */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, int len)
{
	int	cursor;

	cursor = 0;
	while (*(s1 + cursor) && *(s2 + cursor) && cursor < len)
	{
		if (*(s1 + cursor) != *(s2 + cursor))
			return (*(s1 + cursor) - *(s2 + cursor));
		cursor++;
	}
	if (cursor < len)
		return (*(s1 + cursor) - *(s2 + cursor));
	return (0);
}

/*

int ft_strncmp(const char *s1, const char *s2, int len)
{
	int	a;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	a = 0;
	while (a < len - 1 && s1[a] && s2[a])
	{
		if (s1[a] != s2[a])
			return (s1[a] - s2[a]);
		a++;
	}
	return (s1[a] - s2[a]);
}

*/
