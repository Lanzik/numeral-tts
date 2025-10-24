#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *number_to_words(int number)
{
    char *units[] = {"", "یک", "دو", "سه", "چهار", "پنج", "شش", "هفت", "هشت", "نه", "ده", "یازده", "دوازده", "سیزده", "چهارده", "پانزده", "شانزده", "هفده", "هجده", "نوزده"};
    char *tens[] = {"", "", "بیست", "سی", "چهل", "پنجاه", "شصت", "هفتاد", "هشتاد", "نود"};
    char *hundreds[] = {"", "صد", "دویست", "سیصد", "چهارصد", "پانصد", "ششصد", "هفتصد", "هشتصد", "نهصد"};
    char *thousands[] = {"", "هزار", "میلیون", "میلیارد"};

    if (number == 0)
    {
        return strdup("صفر");
    }

    char *words = malloc(1000 * sizeof(char));
    words[0] = '\0';

    int groups[4];
    int i = 0;
    while (number > 0)
    {
        groups[i] = number % 1000;
        number /= 1000;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        int group = groups[j];
        if (group == 0)
        {
            continue;
        }
        char group_words[100] = "";

        int hundred = group / 100;
        if (hundred > 0)
        {
            strcat(group_words, hundreds[hundred]);
            if (group % 100 != 0)
                strcat(group_words, " و ");
            else
                strcat(group_words, " ");
        }

        int ten = (group % 100) / 10;
        int unit = group % 10;
        if (ten >= 2)
        {
            if (group % 10 == 0)
            {
                strcat(group_words, tens[ten]);
                strcat(group_words, " ");
            }
            else
            {
                strcat(group_words, tens[ten]);
                strcat(group_words, " و ");
            }
            if (unit > 0)
            {
                strcat(group_words, units[unit]);
                strcat(group_words, " ");
            }
        }
        else if (ten == 1)
        {
            strcat(group_words, units[10 + unit]);
            strcat(group_words, " ");
        }
        else if (unit > 0)
        {
            strcat(group_words, units[unit]);
            strcat(group_words, " ");
        }

        if (group_words[0] != '\0')
        {
            strcat(words, group_words);
            strcat(words, thousands[j]);
            if (j >= 1)
            {
                if (groups[0] == 0)
                    strcat(words, " ");
                else
                    strcat(words, " و ");
            }
        }
    }
    return words;
}

int main()
{
    while (1)
    {
        printf("please enter a number\n");
        long long int number;
        scanf("%lld", &number);
        char *num_s = number_to_words(number);
        printf("%s\n", num_s);
        free(num_s);
    }
    return 0;
}