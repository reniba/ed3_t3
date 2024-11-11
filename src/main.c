/* Estrutura de Dados III - SCC0607
 * Prof. Anderson Canale
 *
 * Segundo trabalho prático
 *
 * Grupo 31
 *
 * Alunos:
 * Rafael Borecki Guimarães de Carvalho - 14604271
 * Renan Correia Monteiro Soares - 14605661
 *
 * Porcentagem de participação
 * Rafael - 100%
 * Renan - 100%
 *
 */

#include "../headers/func_1.h"
#include "../headers/func_10.h"
#include "../headers/func_11.h"
#include "../headers/func_2.h"
#include "../headers/func_3.h"
#include "../headers/func_4.h"
#include "../headers/func_5.h"
#include "../headers/func_6.h"
#include "../headers/func_7.h"
#include "../headers/func_8.h"
#include "../headers/func_9.h"
//#include "../headers/func_12.h"
//#include "../headers/func_13.h"
//#include "../headers/func_14.h"
#include "../headers/messages.h"
#include "../headers/readInput.h"

int main()
{
    /*
     * input1 = string that has 'command' + \0
     * input2 = second string separated by ' ' or '\n'
     * input3 = third string separated by ' ' or '\n'
     */
    char input1[MAX_STR_LEN], input2[MAX_STR_LEN], input3[MAX_STR_LEN];

    ReadInput(input1, input2, input3);

    // printf("%s %ld", input1, strlen(input1));

    if (!strcmp("1", input1))
    {
        // CREATE TABLE funcionality
        funcionality1(input2, input3);
    }
    else if (!strcmp("2", input1))
    {
        // SELECT FROM funcionality
        funcionality2(input2);
    }
    else if (!strcmp("3", input1))
    {
        // SELECT WHERE funcionality
        funcionality3(input2, input3);
    }
    else if (!strcmp("4", input1))
    {
        // REMOVE funcionality
        funcionality4(input2, input3);
    }
    else if (!strcmp("5", input1))
    {
        // INSERT INTO funcionality
        funcionality5(input2, input3);
    }
    else if (!strcmp("6", input1))
    {
        // COMPACT funcionality
        funcionality6(input2);
    }
    else if (!strcmp("7", input1))
    {
        // CREATE_INDEX funcionality
        funcionality7(input2, input3);
    }
    else if (!strcmp("8", input1))
    {
        // SELECT funcionality
        funcionality8(input2, input3);
    }
    else if (!strcmp("9", input1))
    {
        // INSERT funcionality
        funcionality9(input2, input3);
    }
    else if (!strcmp("10", input1))
    {
        //  INSERT funcionality
        funcionality10(input2);
    }
    else if (!strcmp("11", input1))
    {
        // INSERT funcionality
        funcionality11(input2, input3);
    }
    else if (!strcmp("12", input1))
    {
        // INSERT funcionality
        // funcionality12(input2, input3);
    }
    else if (!strcmp("13", input1))
    {
        // funcionality13(input2, input3);
    }
    else if (!strcmp("14", input1))
    {
        // funcionality14(input2, input3);
    }
    else
    {
        msg_default_error();
    }

    return 0;
}
