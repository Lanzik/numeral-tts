#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "audio_files.h"

#define MAX_LENGTH 1000

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
                strcat(group_words, "و ");
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
                strcat(group_words, "و ");
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
                    strcat(words, "و ");
            }
        }
    }
    return words;
}

const char *replaceWord(const char *word)
{
    for (int i = 0; i < 60; i++)
    {
        if (strcmp(word, searchWords[i]) == 0)
        {
            return alternativeWords[i];
        }
    }
    return word;
}

void mergeAudioFiles(const char *audioFiles, const char *outputFile)
{
    FILE *outFile = fopen(outputFile, "wb");
    if (outFile == NULL)
    {
        printf("Failed to open output file for writing.\n");
        return;
    }

    char *fileNamesCopy = strdup(audioFiles);
    char *token = strtok(fileNamesCopy, " ");
    while (token != NULL)
    {
        FILE *inFile = fopen(token, "rb");
        if (inFile == NULL)
        {
            printf("Failed to open input file: %s\n", token);
            fclose(outFile);
            remove(outputFile);
            free(fileNamesCopy);
            return;
        }

        int c;
        while ((c = fgetc(inFile)) != EOF)
        {
            fputc(c, outFile);
        }

        fclose(inFile);
        token = strtok(NULL, " ");
    }

    fclose(outFile);
    free(fileNamesCopy);
    printf("Audio files merged successfully.\n");
}

int main(int argc, char *argv[])
{
    printf("\nplease enter a number: \n");
    long long int number;
    //scanf("%lld", &number);
    number = strtol(argv[1], NULL, 0);
    char *result_str = number_to_words(number);
    char convertedText[MAX_LENGTH] = "";
    char word[MAX_LENGTH] = "";

    int i = 0;
    int j = 0;
    while (result_str[i] != '\0')
    {

        if (result_str[i] == ' ')
        {
            word[j] = '\0';
            strcat(convertedText, replaceWord(word));
            strcat(convertedText, " ");
            j = 0;
        }
        else
        {
            word[j] = result_str[i];
            j++;
        }
        i++;
    }

    word[j] = '\0';
    strcat(convertedText, replaceWord(word));
    free(result_str);
    const char *outputFile = "output.mp3";

    mergeAudioFiles(convertedText, outputFile);

    return 0;
}
