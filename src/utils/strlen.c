int	ft_strlen(const char *str)
{
	int	a;

	a = 0;
	while(str && *(str + a))
		a++;
	return (a);
}
