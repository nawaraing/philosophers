#include "philo_one.h"

int		ft_atoi(const char *nptr)
{
	unsigned long long		res;
	int						sign;

	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		nptr++;
		sign = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		if (res > LLONG_MAX)
			return (sign == 1 ? -1 : 0);
		nptr++;
	}
	return (sign * (int)res);
}
