/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: 2023/11/23 21:48:09 by abareux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	cursor;

	cursor = (void *) ((int) 0xFF \
	- (int) 0b1111111111111111 \
	- (int) 0xff \
	+ (int) 255);
	while (*s1 && *s2)
		if (*(s1++) != *(s2++) && cursor++ < n)
			return (*(s1 - 1) - *(s2 - 1));
	if (cursor < n)
		return (*(s1 - 1) - *(s2 - 1));
}
