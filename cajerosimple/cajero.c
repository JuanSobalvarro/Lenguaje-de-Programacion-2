#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// define for different SO, the code needs an implementation for replace conio.h, so it cannot be used for linux
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef const struct tm local;

int main()
{
    int exit = 1;
    // billetes de 1000, 500, 200, 100
    int billval[] = {1000, 500, 200, 100};
    int billetes[] = {5, 5, 5, 5};
    float cuentas[] = {1000.0, 2000.0, 3000.0};
    char **movimientos; // format: DD.MM.YY HH.MM.SS IDCUENTA MOVEMENTTYPE QUANTITY
    int movnum = 0;
    int cuenta_select = -1;
    int countpass = 0;
    int equal;

    movimientos = realloc(NULL, sizeof(*movimientos) * movnum);

    if (!movimientos)
    {
        printf("COULDNT REALLOCATE MEMORY UWUNYA\n");
        return -1;
    }

    printf("===================Cajero Automatico===================\n");
    printf("Ingrese su numero de cuenta(1-3): ");
    scanf("%d", &cuenta_select);
    if (!(cuenta_select >= 1 && cuenta_select <= 3))
    {
        printf("Cuenta no valida\n");
        return 0;
    }
    cuenta_select--;
    getchar();

    do
    {
        equal = 1;
        char pin[5] = "1234";
        char check[5];
        printf("\nIngrese pin de la cuenta: ");
        for (int i = 0; i < 4; i++)
        {  
            check[i] = getch();
            putchar('*');
            if (check[i] != pin[i])
            {
                equal = 0;
            }
        }
        check[4] = '\0';
        if(!equal)
        {
            countpass++;
            if (countpass < 3)
            {
                printf("\nPin incorrecto. Intente otra vez.");
            }
            else
            {
                printf("\nPor seguridad la cuenta ha sido bloqueada\n");
                return 0;
            }
        }
        printf("\n");
    } while (!equal);
    

    while (exit == 1)
    {   
        system(CLEAR);
        int select;
        printf("===================Cajero Automatico===================\n");
        printf("1. Consulta\n2. Deposito\n3. Retiro\n4. Movimientos\n5. Salir\n");
        printf("=======================================================\n");

        scanf("%d", &select);

        switch (select)
        {
        case 1:
            system(CLEAR);
            printf("===================Cajero Automatico===================\n");
            printf("CONSULTA\n");
            printf("Su saldo actual es de: %f\n", cuentas[cuenta_select]);
            printf("=======================================================\n");
            printf("\nPresione cualquier tecla para continuar\n");
            getchar();
            getchar();
            break;
        
        case 2:
            system(CLEAR);
            float deposit;
            printf("===================Cajero Automatico===================\n");
            printf("DEPOSITO\n");
            printf("Cuanto desea depositar?\n");
            scanf("%f", &deposit);
            cuentas[cuenta_select] += deposit;
            printf("Depositado correctamente %f\n", deposit);

            // save movement
            time_t raw = time(NULL);
            local *loc = localtime(&raw);
            char *mov;
            mov = malloc(sizeof(char) * 100);
            int check = snprintf(mov, 100, "%d.%d.%d %d:%d:%d AccountID: %d DEPOSITO %f", 
                                    loc->tm_mday, loc->tm_mon + 1, loc->tm_year + 1900, 
                                    loc->tm_hour, loc->tm_min, loc->tm_sec, 
                                    cuenta_select, deposit);
            mov = realloc(mov, sizeof(char) * check);
            if (check >= 0 && check < 100)
            {
                //printf("Movimiento guardado: %s", mov);
            }
            movimientos[movnum++] = mov;
            movimientos = realloc(movimientos, sizeof(*movimientos) * movnum);


            if (!movimientos)
            {
                printf("COULDNT REALLOCATE MEMORY UWUNYA\n");
                return -1;
            }

            printf("\nPresione cualquier tecla para continuar\n");
            getchar();
            getchar();
            break;

        case 3:
            system(CLEAR);
            int retire;
            printf("===================Cajero Automatico===================\n");
            printf("RETIRO\n");
            printf("Cuanto desea retirar(multiplos de 100)?\n");
            scanf("%d", &retire);

            //printf("\ntotal%d\n", retire);

            //float total = 0;
            //int retire2 = retire;
            if (cuentas[cuenta_select] - retire >= 0)
            {
                if (retire%100 == 0)
                {
                    int retireBill[] = {0, 0, 0, 0};
                    int tran = 1;
                    for (int i = 0; i < 4; i++)
                    {
                        retireBill[i] = (int)retire/billval[i];
                        retire -= retireBill[i] * billval[i];
                        //printf("\nretirando:%d de %d", retireBill[i], billval[i]);
                        if (retireBill[i] > billetes[i])
                        {
                            printf("\nNo hay billetes suficientes en el cajero para la transaccion\n");
                            tran = 0;
                            break;
                        }
                    }
                    
                    if (tran)
                    {   
                        int total_retirado = 0;
                        for (int i = 0; i < 4; i++)
                        {
                            int sum = retireBill[i] * billval[i];
                            printf("Billetes de %d: %d\n", billval[i], retireBill[i]);
                            billetes[i] -= retireBill[i];
                            //printf("\nVariable sum: %d de tama;o %d\n", sum, sizeof(int));
                            total_retirado += sum;
                        }
                        cuentas[cuenta_select] -= total_retirado;
                        printf("\nSe retiraron exitosamente %d\n", total_retirado);
                        printf("Saldo actual: %f\n", cuentas[cuenta_select]);

                        // save movement
                        time_t raw = time(NULL);
                        local *loc = localtime(&raw);
                        char *mov;
                        mov = malloc(sizeof(char) * 100);
                        int check = snprintf(mov, 100, "%d.%d.%d %d:%d:%d AccountID: %d RETIRO %d.00", 
                                                loc->tm_mday, loc->tm_mon + 1, loc->tm_year + 1900, 
                                                loc->tm_hour, loc->tm_min, loc->tm_sec, 
                                                cuenta_select, total_retirado);
                        mov = realloc(mov, sizeof(char) * check);

                        if (check >= 0 && check < 100)
                        {
                            //printf("Movimiento guardado: %s ==== check: %d\n", mov, check);
                        }
                        
                        movimientos[movnum++] = mov;
                        movimientos = realloc(movimientos, sizeof(*movimientos) * movnum);


                        if (!movimientos)
                        {
                            printf("COULDNT REALLOCATE MEMORY UWUNYA\n");
                            return -1;
                        }
                    }
                }
                else
                {
                    printf("\nNumero ingresado no valido\n");
                }
            }
            else
            {
                printf("\nFONDOS NO SUFICIENTES\n");
            }

            printf("\nPresione cualquier tecla para continuar\n");
            getchar();
            getchar();
            break;

        case 4:
            system(CLEAR);
            printf("===================Cajero Automatico===================\n");
            printf("===============HISTORIAL DE MOVIMIENTOS================\n\n");

            char **head = movimientos;
            for (int i = 0; i < movnum; i++)
            {
                //printf("adress %p: ", head);
                printf("MOV %d %s\n", i+1, head[i]);
            }

            printf("\nPresione cualquier tecla para continuar\n");
            getchar();
            getchar();
            break;

        default:
            printf("\nSALIENDO\n");
            exit = 0;
            break;
        }
    }

    // free MEMORY
    while (movimientos)
    {
        free(*(movimientos++));
    }
    free(movimientos);

    return 0;
}