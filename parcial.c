#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cuit(char, char *, char *);
int validar_tipo(char);
int validar_dni(char *);

int main(int argc, char *argv[])
{
    char DNI[20] = "";
    char ERROR[255] = "== ERROR ==";

    char dato = argv[1][0];

    int confirm = cuit(dato, argv[2], DNI);
    switch (confirm)
    {
    case 1:
        printf("%s \n El tipo de persona juridica no es valido, posibles valores M o F", ERROR);
        break;

    case 2:
        printf("%s \n El tipo de DNI no es valido", ERROR);
        break;
    case 3:
        printf("%s \n El tipo de persona juridica y DNI no son validos", ERROR);
        break;

    default:
        printf("%s", DNI);
        break;
    }

    return 0;
}

int cuit(char t, char *dni, char *cuit)
{
    int error = 0;
    int error2 = 0;
    switch (validar_tipo(t))
    {
    case 2:
        strcpy(cuit, "20-");
        break;
    case 1:
        strcpy(cuit, "27-");
        break;

    default:
        error = 1;
        break;
    }
    strcat(cuit, dni);

    if (validar_dni(cuit) == 1)
    {
        error2 = 1;
    }
    if (error == 1 && error2 == 1)
    {
        return 3;
    }
    else if (error2 == 1)
    {
        return 2;
    }

    return error;
}

int validar_tipo(char tipo)
{
    if (tipo == 'M' || tipo == 'm')
    {
        return 2;
    }
    else if (tipo == 'F' || tipo == 'f')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validar_dni(char *dni)
{

    int multi = 5;
    float sum = 0;
    int flag = 0;
    for (int i = 0; i < 11; i++)
    {
        if (*dni != '-')
        {
            int num = *dni - '0';
            if (*dni < '0' || *dni > '9')
            {
                if (!*dni)
                {
                    if (flag == 1)
                    {
                        return 1;
                    }
                    return 0;
                }
                return 1;
            }
            sum += (num * multi);
            if (multi == 2)
            {
                multi = 7;
            }
            else
            {
                multi--;
            }
        }
        else if (*dni == '-')
        {
            flag = 1;
        }
        dni++;
    }
    int result = (sum / 11) * 10;
    result = 11 - (result) % 10; // 20-87654321 suma = 160,     (160/11)%10 = 5 ejemplo
    char dato = result + '0';
    int bandera = 0;
    char dato2 = ' ';
    switch (dato) // dato == '9' + 1  (:)      dato == '9' + 2  (;)
    {
    case ':':
        dato = '1';
        dato2 = '0';
        break;
    case ';':
        dato = '1';
        dato2 = '1';
        break;
    default:
        break;
    }
    while (bandera != 1)
    {
        if (!*dni)
        {
            if (bandera == 2)
            {
                *dni = dato;
                bandera = 1;
            }
            else
            {
                if (bandera == 0)
                {
                    *dni = '-';
                    if (dato2 != ' ')
                    {
                        bandera = 3;
                    }
                    else
                    {
                        bandera = 2;
                    }
                }
                else if (bandera == 3)
                {
                    *dni = dato2;
                    bandera = 2;
                }
            }
        }
        dni++;
    }
    return 0;
}
