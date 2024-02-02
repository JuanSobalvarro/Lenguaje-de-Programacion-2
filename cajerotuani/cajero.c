#include "cajero.h"

/*
    Get accounts from a csv file and 
    returns an array of ACCOUNT pointers
*/
static inline ACCOUNT **getACCOUNTS(FILE *fp, int *numAccounts)
{
    ACCOUNT **array;
    int arrlen = 0;
    char buffer[100];
    char *data;

    array = realloc(NULL, sizeof(ACCOUNT**) * arrlen);

    // get token headers
    if(!fgets(buffer, sizeof(buffer), fp))
    {
        printf("ERROR: READING BUFFER FROM CSV FILE\n");
        return NULL;
    }
    printf("Accounts csv opened with headers: %s\n", buffer);
    while (fgets(buffer, sizeof(buffer), fp))
    {
        ACCOUNT *a = malloc(sizeof(ACCOUNT));
        printf("Buffer : %s\n", buffer);
        
        data = strtok(buffer, ",");
        copymemory(a->id, data, 5);
        //printf("test = %s with last %c", a->id, a->id[4]);

        data = strtok(NULL, ",");
        copymemory(a->pin, data, 5);

        data = strtok(NULL, ",");
        copymemory(a->name, data, 10);

        data = strtok(NULL, ",");
        a->balance = strtof(data, NULL);

        array[arrlen++] = a;
        array = realloc(array, sizeof(ACCOUNT**) * arrlen);
    }

    *numAccounts = arrlen;

    return array;
}

/*
    Initiate session searching for a account
*/
static inline ACCOUNT *initSession(ACCOUNT **accounts, int size)
{
    ACCOUNT *a;
    char cid[5];
    char cpin[5];
    int pass = 0;
    int tries = 3;

    while(!pass)
    {
        // first get id and pin
        //system("cls");
        printf("======================ATM======================\n");
        printf("Ingrese su ID: ");
        scanf("%s", cid);
        printf("Ingrese su pin: ");
        pinInput(cpin, '*', 4);

        for (int i = 0; i < size; i++)
        {
            // check for a account that matches the id
            printf("\nA: %sa?: %s\n", accounts[i]->id, cid);
            if (strcmp(cid, accounts[i]->id) == 0)
            {
                printf("ACCOUNT FOUND\n");
                a = accounts[i];
                if (strcmp(cpin, accounts[i]->pin) != 0)
                {
                    system("cls");
                    printf("Pin incorrecto. Intentos restantes: %d\n", --tries);
                    break;
                }
                pass = 1;
                break;
            }
        }
        if (tries == 0)
        {
            return NULL;
        }
    }

    return a;
}

/*
    Initialize cajero
*/
CAJERO *initCAJERO(char *accPATH, char *movPATH)
{
    CAJERO *c;
    c = malloc(sizeof(CAJERO));
    if (c == NULL)
    {
        printf("LA CAGASTE HEAVY\n");
    }
    c->accountsPath = accPATH;
    c->movementsPath = movPATH;

    FILE *accf = fopen(accPATH, "r");
    if (accf == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE at %s\n", accPATH);
        return NULL;
    }

    FILE *movf = fopen(movPATH, "r");
    if (movf == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE at %s\n", movPATH);
        return NULL;
    }

    int accSize;
    ACCOUNT **array = getACCOUNTS(accf, &accSize);

    //printf("Cuenta 1: %s id %s\n", array[accSize-1]->name, array[accSize-1]->id);

    if (array == NULL)
    {
        printf("ERROR: COULDNT LOAD ACCOUNTS ARRAY OR THERE IS NO ACCOUNTS REGISTER\n");
    }
    
    // once initialized the accounts init session asking the user
    c->account = initSession(array, accSize);
    if (c->account == NULL)
    {
        printf("CAJERO BLOQUEADO\n");
        c = NULL;
    }

    fclose(accf);
    fclose(movf);
    return c;
}

/*
    Save movement in some format
*/
void saveMovement(CAJERO *c, int amount, char *type)
{
    time_t raw = time(NULL);
    local *loc = localtime(&raw);
    char *mov;
    mov = malloc(sizeof(char) * 100);
    int check = snprintf(mov, 100, "%d.%d.%d,%d:%d:%d,%s,%s,%d\n", 
                            loc->tm_mday, loc->tm_mon + 1, loc->tm_year + 1900, 
                            loc->tm_hour, loc->tm_min, loc->tm_sec, 
                            c->account->id, type, amount);
    mov = realloc(mov, sizeof(char) * check);

    FILE *movementsFile = fopen(c->movementsPath, "a");

    if (movementsFile == NULL)
    {
        printf("ERROR:saveMovement: COULDNT OPEN FILE.");
    }
    fwrite(mov, check, 1, movementsFile);

    fclose(movementsFile);
}

void updateAccount(ACCOUNT *account)
{
    
}

static inline void key2Exit()
{
    printf("\nPresione cualquier tecla para continuar");
    getchar();
    getchar();
}

// ACTIONS PART

static inline void consult(CAJERO *c)
{
    system("cls");
    printf("====================CONSULT====================\n");

    printf("AccountID: %s\n", c->account->id);
    printf("Name: %s\n", c->account->name);
    printf("Balance: $%f\n", c->account->balance);

    key2Exit();
}

static inline void deposit(CAJERO *c)
{
    int deposit;
    system("cls");
    

    while (deposit%100 != 0)
    {
        printf("====================DEPOSIT====================\n");
        printf("Cuanto desea depositar (multiplo de 100)?\n");
        scanf("%d", &deposit);

        if (deposit%100 != 0)
        {
            printf("Numero no valido. Ingrese de nuevo\n");
        }
    }

    updateAccount(c->account);
    saveMovement(c, deposit, "DEPOSIT");

    key2Exit();
}

static inline void retire(CAJERO *c)
{
    system("cls");
    printf("====================RETIRE====================\n");

    key2Exit();
}

static inline void movements(CAJERO *c)
{
    system("cls");
    printf("====================MOVEMENTS====================\n");

    key2Exit();
}

void selectAction(CAJERO *cajero, int selection)
{
    void (*fptr[])(CAJERO*) = {consult, deposit, retire, movements};

    fptr[selection - 1](cajero);
}

// ACTIONS FINISH

/*
    Execute cajero 
*/
void *execCAJERO(CAJERO *caj)
{
    int selection = -1;
    ACCOUNT *acc;
    acc = caj->account;

    while (1)
    {
        system("cls");
        do
        {
            if (selection != -1)
            {
                printf("Numero no valido\n");
            }
            // 1. Print main menu
            printf("===================Cajero Automatico===================\n");
            printf("Bienvenido usuario %s. Seleccione que desea realizar.\n", acc->name);
            printf("1. Consulta\n2. Deposito\n3. Retiro\n4. Movimientos\n5. Salir\n");
            printf("=======================================================\n");

            scanf("%d", &selection);
        } while(selection < 1 || selection > 5);
        // 2. Select action
        if (selection == 5)
        {
            printf("SALIENDO UWUNYA FINISHED\n");
            break;
        }
        selectAction(caj, selection);
    }
}