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

    int confirm = 0;

    if (argc == 1)
    { // si no se ingresa nada
        confirm = 3;
    }
    else if (argc == 2)
    { // si se ingresa solo el tipo de persona
        char dato = argv[1][0];

        if (validar_tipo(dato) == 2 || validar_tipo(dato) == 1)
        { // en caso de que el tipo este bien solo salta error de dni
            confirm = 2;
        }
        else
        { // en caso contrario saltan ambos
            confirm = 3;
        }
    }
    else if (argc == 3)
    { // en caos de estar todos los datos ingresados correctamente sigue a la confirmacion
        char dato = argv[1][0];

        confirm = cuit(dato, argv[2], DNI);
    }

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

    switch (validar_tipo(t)) // llamamos a validar_tipo para verificar si es hombre o mujer
    {
    case 2:
        strcpy(cuit, "20-"); // en caso de ser hombre
        break;
    case 1:
        strcpy(cuit, "27-"); // en caso de ser mujer
        break;

    default:
        error = 1; // en caso de error, colocamos error = 1
        break;
    }

    if (validar_dni(dni) == 1) // llamamos a dni para verificar si esta bien
    {
        error2 = 1; // en caso de que no, colocamos error2 = 1
    }
    if (error == 1 && error2 == 1) // si esta mal el tipo de persona como dni devolvemos un 3
    {
        return 3;
    }
    else if (error2 == 1) // si solo esta mal el dni devolvemos un 2
    {
        return 2;
    }
    else if (error == 1)
    { // si solo esta mal la persona juridica devuelve un 1
        return 1;
    }

    if (error2 == 0 && error == 0) // en caso de que no surgieran errores
    {
        strcat(cuit, dni); // concatenamos el dni al cuit
        int sum = 0;
        int multi = 5;
        for (int i = 0; i < 11; i++) // hacemos un for recorriendo 11 posiciones del cuit contando el '-'
        {
            if (*cuit != '-') // en caso de que no sea '-'
            {
                int num = *cuit - '0'; // restamos al char del cuit el char '0' para que me quede el valor ASCII de forma numerica
                sum += (num * multi);  // realizamos la cuenta
                if (multi == 2)        // si llego a 2 multi vuelve a 7
                {
                    multi = 7;
                }
                else // en caso de que no llegue se sigue restando
                {
                    multi--;
                }
            }
            cuit++;
        }
        int result = (sum * 10) / 11;
        result = 11 - (result) % 10; // 20-87654321 suma = 160,     (160/11)%10 = 5 ejemplo
        char dato = result + '0';    // sumamos el numero a '0' para conseguir el numero en ASCII
        int bandera = 0;
        char dato2 = ' '; // inicializamos dato2
        switch (dato)     // dato == '9' + 1  (:)      dato == '9' + 2  (;)
        {
        case ':': // si dato es : lo guardamos en 2 char para separar el numero en 10
            dato = '1';
            dato2 = '0';
            break;
        case ';': // si dato es ; lo guardamos en 2 char para separar el numero en 11
            dato = '1';
            dato2 = '1';
            break;
        default:
            break;
        }
        if (dato2 != ' ') // si es : o ;
        {
            *cuit = '-';
            cuit++;
            *cuit = dato;
            cuit++;
            *cuit = dato2; // sumamos ambos char al string del cuit
        }
        else
        {
            *cuit = '-';
            cuit++;
            *cuit = dato; // sumamos el numero al tring del cuit
            cuit++;
        }
    }

    return error; // devuelvo el error
}

int validar_dni(char *dni)
{
    if (dni)
    {
        int cuenta = 0;
        while (*dni) // mientras exista char en dni
        {

            if (cuenta > 8) // en caso de que supere los 8 char devuelve error
            {
                return 1;
            }
            if (*dni < '0' || *dni > '9') // verifica que sean numeros
            {
                return 1;
            }
            dni++;
            cuenta++;
        }
        if (cuenta != 8) // en caso de ser distinto de 8 devuelve error
        {
            return 1;
        }
        else
        {
            return 0; // en caso de que no surgiera ningun error devuelve 0
        }
    }
    else
    {
        return 1;
    }
}

int validar_tipo(char tipo)
{
    if (tipo == 'M' || tipo == 'm') // si es hombre devuelve 2
    {
        return 2;
    }
    else if (tipo == 'F' || tipo == 'f') // si es mujer devuelve 1
    {
        return 1;
    }
    else
    {
        return 0; // si no es ninguno devuelve error
    }
}