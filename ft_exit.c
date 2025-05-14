
#include "builtins.h"

long long    ft_atoll(const char *str)
{
    int            i;
    int            sign;
    long long    result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = 10 * result + (str[i] - 48);
        i++;
    }
    return (result * (long long)sign);
}

static bool isnumber(char *str)
{
	int i = 0;
	while(str && str[i])
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		if (!ft_isdigit(str[i]) && i > 0)
			return(false);
		i++;
	}
	if (ft_atoll(str) > (INT64_MAX) || ft_atoll(str) < (INT64_MIN))
		return (false);
	return (true);
}

int ft_exit(char **str) //prototypage qui sera changer par la suite
{
	long long int nb;

	nb = 0;
	if (str[1])
	{
		if (isnumber(str[1]))
		{
			nb = ft_atoll(str[1]);
			if (str[2])
			{
				printf("bash: exit: too many arguments\n");
				return(-12);
			}
			return (nb);
		}
		printf("bash: exit: %s: numeric argument required\n", str[1]);
		return (2);
	}
	return (errno);
}




/* 1er cas : "exit jhdsjhfdsjhf dsjhfdsjfjdsfhds"
bash: exit: jhdsjhfdsjhf: numeric argument required
echo $? =2
*/

/* 2eme cas : "exit 15 fdfds"
exit
bash: exit: too many arguments 
N'EXIT PAS
*/

/* 3eme cas : "exit [nbr]"
exit
echo $? = [nbr]
*/

//9223372036854775807 = int64_MAX
/*4eme cas : exit [nbr > 64-bit signed integer ou nbr < 64-bit signed integer]
exit
bash: exit: 4444444444444444444444444444: numeric argument required
echo $? = 2
*/

/*5eme cas : exit
exit
echo $? = 0
*/

/*Si le 1er argument n'est pas numerique (qu'importe le nombre d'argument total) alors bash executera comme le 1er cas*/
/*Si le 1er argument est numerique MAIS QUE LE NBR D'ARGUMENT EST >= 2 alors bash executera comme le 2eme cas 
(peu importe ce que le 2eme argument represente)*/