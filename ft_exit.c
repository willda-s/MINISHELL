
#include "builtins.h"


#define INT64_MAX_STR "9223372036854775807"
#define INT64_MIN_STR "9223372036854775808"

long long ft_atoll(const char *str)
{
    int i = 0;
    int sign = 1;
    long long result = 0;

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
        result = 10 * result + (str[i] - '0');
        i++;
    }
    return (result * sign);
}
bool check_isdigit(const char *nb) /// verifie que c'est bien un digit 
{

	int j;
	j = 0;
	while(nb[j]) 
	{
		if (!ft_isdigit(nb[j]))
			return false;
		j++;
	}
	return true;
}
bool isnumber(const char *str) //////// A NORMER
{
    int i;
    int sign;
    const char *nb;

    i = 0;
    sign = 1;

    if (!str || !*str) //// securiter de str NULL
        return false;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) /// skip  des white spaces
        i++;
    if (str[i] == '-' || str[i] == '+') /// comme dans atoll si + ou - ... 
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    nb = &str[i];
    while (*nb == '0') ///// gere les 0 au debut du nombre et les skip
        nb++;
    int nb_count;
	nb_count = 0;
    while (ft_isdigit(nb[nb_count]))//// calcule la len de nb
        nb_count++;
    if (nb_count == 0) /// si la len de nb vaut 0, alors return false
        return (false);
    if (nb_count > 19) /// si elle est supprerieur a 19 alors elle overflow
        return (false);
    if (nb_count == 19) /// si elle est egale a 19 alors, on verifie que le nombre noverflow pas en int max et int min 
    {
        if (sign == 1 && ft_strncmp(nb, INT64_MAX_STR, 19) > 0) /// si le int et positif alors, on vefie que elle noverflow pas en la comparant au int64 max
            return (false);
        if (sign == -1 && ft_strncmp(nb, INT64_MIN_STR, 19) > 0)/// si le int et negatif alors, on vefie que elle noverflow pas en la comparant au int64 min
            return (false);
    }
	return (check_isdigit(nb));
}

int ft_exit(char **args)
{
    long long nb = 0;

    if (args[1])
    {
        if (isnumber(args[1]))
        {
            nb = ft_atoll(args[1]);
            if (args[2])
            {
                printf("bash: exit: too many arguments\n");
                return (-12);
            }
            return (nb); // comportement bash : exit code = n % 256
        }
        printf("bash: exit: %s: numeric argument required\n", args[1]);
        return (2);
    }
    return (errno); // ou 0 selon ton design
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