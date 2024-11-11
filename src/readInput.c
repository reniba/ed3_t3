#include "./../headers/readInput.h"

/* ReadInput
 * Read more inputs depending on the command passed on string1
 *
 * read one more string
 * cases 2 and 6
 *
 * read two more strings
 * cases 1, 3, 4, 5, 7, 8 and 9
 */
void ReadInput(char string1[], char string2[], char string3[])
{
    scanf("%s", string1);

    if (!strcmp("1", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }
    if (!strcmp("1", string1))
    {
        scanf("%s", string2);
    }
    if (!strcmp("3", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }

    if (!strcmp("4", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }
    if (!strcmp("5", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }
    if (!strcmp("6", string1))
    {
        scanf("%s", string2);
    }
    if (!strcmp("7", string1))
    {
        scanf("%s", string2);
    }
    if (!strcmp("8", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }
    if (!strcmp("9", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }
    if (!strcmp("10", string1))
    {
        scanf("%s", string2);
    }
    if (!strcmp("11", string1))
    {
        scanf("%s", string2);
        scanf("%s", string3);
    }
    if (!strcmp("12", string1))
    {
        scanf("%s", string2);
    }
    if (!strcmp("13", string1))
    {
        scanf("%s", string2);
    }
    if (!strcmp("14", string1))
    {
        scanf("%s", string2);
    }
}
