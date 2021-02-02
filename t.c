#include <stdlib.h>
#include <stdio.h>
extern int e;
int		ft_atoi(char *str)
{
	int				i;
	int				sign;
	size_t			result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		sign = (str[i] == 45) ? -1 : 1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	if (result > 9223372036854775807 && sign == 1)
		return (-1);
	else if (result > 9223372036854775807 && sign == -1)
		return (0);
	return ((int)result * sign);
}

int		main()
{
	// int i = 0;
	// while (i < 3)
	// 	printf("%d\n", i++);

	// printf("%s\n", NULL[6000]);

	// // printf("%d\n", ft_atoi("2147483647"));
	// // printf("%d\n", ft_atoi("2147483648"));
	// // printf("%d\n", ft_atoi("2147483644449"));
	// // printf("%d\n", ft_atoi("214748364444444444448"));
	// // printf("%d\n", ft_atoi("214748364654321985640032168984212165498498461612315616164444444448"));


	int a = 0;
	int c[4] = {1, 2, 3, 4};
	int d[] = {5, 6, 7, 8};
	int	**b = malloc(3 * sizeof(int *));

// 	assigning
	while (a < 3)
	{
		b[a] = malloc(4 * sizeof(int));
		a++;
	}
	a = 0;
	while (a < 4)
	{
		b[0][a] = c[a];
		a++;
	}
	a = 0;
	while (a < 4)
	{
		b[1][a] = d[a];
		a++;
	}
	a = 0;
	while (a < 4)
	{
		b[2][a] = d[a] + c[a];
		a++;
	}

// printing
	a = 0;
	while (a < 4)
	{
		printf("%d\n", b[2][a]);
		a++;
	}

//	freeing
	a = 0;
	while (a < 3)
	{
		free(b[a]);
		a++;
	}
	free(b);
}