#include <stdio.h>
#include <string.h> // used this to perform string library function
#include <ctype.h>  // used this to lowercase a character
#include <conio.h>  // used this header for getch()
#include <time.h>   // used this to generate date and time

struct menu
{
    int compare;
    char *string_from_menu;         // String literal. can't change any element between any index. Stored here menu name.
    char string_from_database[200]; // stored here menu name from txt file.
} menu_string[50];                  // menu data type array. can store upto 50 stack of items here. But we stored 25 stack of items here.

struct calculation_part
{
    double sum, total;
    int quantity, input, limit;
    char string[200], name[100];
} sum_calculation, sum[50], receipt_string[50], loop, name; // loop.limit is used in "for loop" limit for void calculation() function, it stored the input limit from user
// sum[50].sum = stored all the available foods individual sum [ which consists of (sum[50].sum * sum[50].quantity)]   sum[50].sum--->array type
// name.name[50] = stored customers name
// sum_calculation.input = takes input the number given in menu
// sum_calculation.total = all sum of sum[50].sum

FILE *ptr1, *ptr2; // declared FILE pointer globally

time_t currentTime; // special types of data_type "time_h" for time header, declared currentTime variable

void menu_string_store(); // function prototype
void menu_display();      // for menu display
void calculation();       // for calculation
void receipt();           // generating reciept
void sub_total();         // for total sum without vat and service charge

int main()
{
    char input;
    printf("*********************************************************************************************************************************************************\n");
    printf("*\t\t\t\t\t\t\t\tWelcome to \"CHILLS RESTAURANT\"\t\t\t\t\t\t\t\t*\n");
    printf("*********************************************************************************************************************************************************\n");
    printf("\n\n\n\t\t\t*** Press 'Y' to display the menu to progress further and press 'N' to close the application. ***\n\n");
start:
    printf("Press (Y/N):\t");
    scanf("%c", &input);
    fflush(stdin);
    if (tolower(input) == 'y') // can input either y or Y
    {
        menu_string_store();
        menu_display();
        calculation();

        if (loop.limit == 0)
        {
            ;
        }
        else
        {
            printf("\t\t\t\t\t\t\t\t*** Receipt is given below: ***");
            receipt();
        }
        printf("\n\n\n\t\t\t\t\t\t\t\t*** Have a nice day! ***\n\n\t\t\t\t\t\t\t\t(Press any button to exit)");
    }
    else if (tolower(input) == 'n') // can input either n or N
    {
        printf("\n\n\n\t\t\t\t\t\t\t\t*** Have a nice day! ***\n\n\t\t\t\t\t\t\t\t(Press any button to exit)");
    }
    else
    {
        printf("*** Invalid keyword! Press 'Y' to display the menu to progress further and press 'N' to close the application. ***\n\n");
        goto start; // if user press any keyword except y or n..goto will send the code in start lebel(in 41 no line)
    }
    getch(); // it will give some time
    return 0;
}

void sub_total()
{
    for (int i = 0; i < loop.limit; i++)
    {
        sum_calculation.total += sum[i].sum; // simply summation of all sum[50].sum....see calculation()
    }
}

void receipt()
{
    time(&currentTime); // passing address through time library function of time.h
    int i;
    double service_charge, vat;
    printf("\n\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tChills Restaurant\n");
    printf("\t\t\t\t\t\t\t\t\t-----------------\n");
    printf("\t\t\t\t\t\t%s", ctime(&currentTime)); // ctime library function prints current time and date in a string with a newline.
    printf("\t\t\t\t\t\tCustomer Name: %s\n", name.name);
    printf("\t\t\t\t\t\t-----------------------------------------------------------\n");
    printf("\t\t\t\t\t\tItems\t\t\t\tQty\t\tTotal\n");
    printf("\t\t\t\t\t\t-----------------------------------------------------------\n\n");
    for (i = 0; i < loop.limit; i++)
    {
        if (strlen(receipt_string[i].string) <= 15)
        {
            if (sum[i].sum == 0)
                continue;
            else
                printf("\t\t\t\t\t\t%s\t\t\t%d\t\t%.2lf\n", receipt_string[i].string, sum[i].quantity, sum[i].sum);
        }
        else if (strlen(receipt_string[i].string) > 15 && strlen(receipt_string[i].string) <= 22)
        {
            if (sum[i].sum == 0)
                continue;
            else
                printf("\t\t\t\t\t\t%s\t\t%d\t\t%.2lf\n", receipt_string[i].string, sum[i].quantity, sum[i].sum);
        }

        else
        {
            if (sum[i].sum == 0)
                continue;
            else
                printf("\t\t\t\t\t\t%s\t%d\t\t%.2lf\n", receipt_string[i].string, sum[i].quantity, sum[i].sum);
        }
    }
    printf("\n\t\t\t\t\t\t-----------------------------------------------------------\n");

    printf("\t\t\t\t\t\tSub Total\t\t\t\t\t");
    sub_total();
    printf("%.2lf\n", sum_calculation.total);
    printf("\t\t\t\t\t\t---------\n");
    service_charge = .1 * sum_calculation.total;
    printf("\t\t\t\t\t\tService Charge (10%)\t\t\t\t%.2lf\n", service_charge);
    vat = .15 * sum_calculation.total;
    printf("\t\t\t\t\t\tValue Added Tax (15%)\t\t\t\t%.2lf\n", vat);
    printf("\t\t\t\t\t\t-----------------------------------------------------------\n");
    printf("\t\t\t\t\t\tGrand Total\t\t\t\t\t%.2lf\n", sum_calculation.total + service_charge + vat);
    printf("\t\t\t\t\t\t-----------------------------------------------------------\n");

    // storing all receipts in file which is for the owners

    ptr2 = fopen("C:\\Users\\Rifat\\Desktop\\Project\\Owners Database\\Receipt List.txt", "a");

    fprintf(ptr2, "\n\n\n--------------------------------------------------------------------------------------------------------\n");
    fprintf(ptr2, "\t\t\tChills Restaurant\n");
    fprintf(ptr2, "\t\t\t-----------------\n");
    fprintf(ptr2, "%s", ctime(&currentTime)); // ctime library function prints current time and date in a string with a newline.
    fprintf(ptr2, "Customer Name: %s\n", name.name);
    fprintf(ptr2, "------------------------------------------------------------------------------\n");
    fprintf(ptr2, "Items\t\t\t\tQty\t\tTotal\n");
    fprintf(ptr2, "------------------------------------------------------------------------------\n\n");
    for (i = 0; i < loop.limit; i++)
    {
        if (strlen(receipt_string[i].string) <= 15)
        {
            if (sum[i].sum == 0)
                continue;
            else
                fprintf(ptr2, "%s\t\t\t%d\t\t%.2lf\n", receipt_string[i].string, sum[i].quantity, sum[i].sum);
        }
        else if (strlen(receipt_string[i].string) > 15 && strlen(receipt_string[i].string) <= 22)
        {
            if (sum[i].sum == 0)
                continue;
            else
                fprintf(ptr2, "%s\t\t%d\t\t%.2lf\n", receipt_string[i].string, sum[i].quantity, sum[i].sum);
        }

        else
        {
            if (sum[i].sum == 0)
                continue;
            else
                fprintf(ptr2, "%s\t%d\t\t%.2lf\n", receipt_string[i].string, sum[i].quantity, sum[i].sum);
        }
    }
    fprintf(ptr2, "\n---------------------------------------------------------------------------\n");

    fprintf(ptr2, "Sub Total\t\t\t\t\t");
    fprintf(ptr2, "%.2lf\n", sum_calculation.total);
    fprintf(ptr2, "---------\n");
    fprintf(ptr2, "Service Charge (10%)\t\t\t\t%.2lf\n", service_charge);
    fprintf(ptr2, "Value Added Tax (15%)\t\t\t\t%.2lf\n", vat);
    fprintf(ptr2, "------------------------------------------------------------------------------\n");
    fprintf(ptr2, "Grand Total\t\t\t\t\t%.2lf\n", sum_calculation.total + service_charge + vat);
    fprintf(ptr2, "------------------------------------------------------------------------------\n");
    fclose(ptr2);
}

void calculation()
{
    char input; // local variable,takes only single character

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t**** Press 'Y' to continue ordering items from the menu and press 'N' to finish ordering from the menu. ****\n\n");
    printf("Please enter the customer name:\t");
    fflush(stdin);   // if there is any newline character comes through this library function converts this '\n' to NULL to avoid buffer
    gets(name.name); // customer name
    printf("\n\n");
    for (loop.limit = 0; loop.limit < 50; loop.limit++)
    {
    again:
        printf("Press (Y/N):\t");
        fflush(stdin);
        scanf("%c", &input);
        printf("\n");
        if (tolower(input) == 'y')
        {
        again_menu:
            printf("Please enter the item number:\t");
            fflush(stdin);
            scanf("%d", &sum_calculation.input);
            switch (sum_calculation.input)
            {
            case 1:
                if (menu_string[0].compare == 0) // see in void menu_display() function
                {
                quantity_again1:
                    printf("Please enter the quantity:\t");
                    fflush(stdin); // again if \n exists it terminates with or converts with NULL
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0) // if greater than 0 then it will run normally
                    {
                        fflush(stdin);
                        sum[loop.limit].sum = 180.0 * sum[loop.limit].quantity;                     // normal calculation with price and stored in sum[50].sum
                        strcpy(receipt_string[loop.limit].string, menu_string[0].string_from_menu); // copied our string menu no 1 to receipt_string[50].string[200],see in void menu_string_store() function
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again1; // if not greeater than 0, code will jump here from 155 no line and run its code again
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again; // if the menu is unavailable code will jump to line no 139
                }

            case 2:
                if (menu_string[1].compare == 0)
                {
                quantity_again2:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 200.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[1].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again2;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 3:
                if (menu_string[2].compare == 0)
                {
                quantity_again3:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 225.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[2].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again3;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 4:
                if (menu_string[3].compare == 0)
                {
                quantity_again4:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 230.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[3].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again4;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 5:
                if (menu_string[4].compare == 0)
                {
                quantity_again5:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 250.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[4].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again5;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 6:
                if (menu_string[5].compare == 0)
                {
                quantity_again6:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 320.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[5].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again6;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 7:
                if (menu_string[6].compare == 0)
                {
                quantity_again7:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 380.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[6].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again7;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 8:
                if (menu_string[7].compare == 0)
                {
                quantity_again8:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 430.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[7].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again8;
                    }
                }
                else
                {
                    printf("***This item is not available. Please select another available item from the menu.***\n\n");
                    goto again;
                }
            case 9:
                if (menu_string[8].compare == 0)
                {
                quantity_again9:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 680.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[8].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again9;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 10:
                if (menu_string[9].compare == 0)
                {
                quantity_again10:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 180.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[9].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again10;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 11:
                if (menu_string[10].compare == 0)
                {
                quantity_again11:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 200.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[10].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again11;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 12:
                if (menu_string[11].compare == 0)
                {
                quantity_again12:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 225.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[11].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again12;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 13:
                if (menu_string[12].compare == 0)
                {
                quantity_again13:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 230.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[12].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again13;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 14:
                if (menu_string[13].compare == 0)
                {
                quantity_again14:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 250.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[13].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again14;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 15:
                if (menu_string[14].compare == 0)
                {
                quantity_again15:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 320.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[14].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again15;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 16:
                if (menu_string[15].compare == 0)
                {
                quantity_again16:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 380.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[15].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again16;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 17:
                if (menu_string[16].compare == 0)
                {
                quantity_again17:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 430.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[16].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again17;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 18:
                if (menu_string[17].compare == 0)
                {
                quantity_again18:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 680.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[17].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again18;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 19:
                if (menu_string[18].compare == 0)
                {
                quantity_again19:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 120.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[18].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again19;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu.*** \n\n");
                    goto again;
                }
            case 20:
                if (menu_string[19].compare == 0)
                {
                quantity_again20:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 130.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[19].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again20;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 21:
                if (menu_string[20].compare == 0)
                {
                quantity_again21:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 180.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[20].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again21;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 22:
                if (menu_string[21].compare == 0)
                {
                quantity_again22:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 140.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[21].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again22;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 23:
                if (menu_string[22].compare == 0)
                {
                quantity_again23:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 140.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[22].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again23;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu.*** \n\n");
                    goto again;
                }
            case 24:
                if (menu_string[23].compare == 0)
                {
                quantity_again24:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 160.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[23].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again24;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            case 25:
                if (menu_string[24].compare == 0)
                {
                quantity_again25:
                    printf("Please enter the quantity:\t");
                    fflush(stdin);
                    scanf("%d", &sum[loop.limit].quantity);
                    if (sum[loop.limit].quantity > 0)
                    {
                        sum[loop.limit].sum = 170.0 * sum[loop.limit].quantity;
                        strcpy(receipt_string[loop.limit].string, menu_string[24].string_from_menu);
                        printf("\n\n");
                        break;
                    }
                    else
                    {
                        printf("*** Invalid quantity! Please enter quantity greater than 0. ***\n\n");
                        goto quantity_again25;
                    }
                }
                else
                {
                    printf("*** This item is not available. Please select another available item from the menu. ***\n\n");
                    goto again;
                }
            default:
                printf("*** Invalid menu number! Please enter valid menu number. ***\n\n");
                goto again_menu;
            }
        }
        else if (tolower(input) == 'n')
        {
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        }
        else
        {
            printf("*** Invalid keyword! Please press 'Y' to continue ordering items from the menu and press 'N' to finish ordering from the menu. ***\n\n");
            fflush(stdin);
        }
    }
}

void menu_string_store()
{ // in this function we stored serially menu items, these are string literals
    menu_string[0].string_from_menu = "1. BEEF BURGER";
    menu_string[1].string_from_menu = "2. BEEF BURGER WITH CHEESE";
    menu_string[2].string_from_menu = "3. BEEF SMOKY BBQ CHEESE";
    menu_string[3].string_from_menu = "4. BEEF WITH BACON";
    menu_string[4].string_from_menu = "5. BEEF WITH SAUSAGE";
    menu_string[5].string_from_menu = "6. BEEF CHEESE BLAST";
    menu_string[6].string_from_menu = "7. BEEF SIGNATURE";
    menu_string[7].string_from_menu = "8. GIGANTO BEEF";
    menu_string[8].string_from_menu = "9. BINGE BEEF";
    menu_string[9].string_from_menu = "10. CHICKEN BURGER";
    menu_string[10].string_from_menu = "11. CHICKEN BURGER WITH CHEESE";
    menu_string[11].string_from_menu = "12. CHICKEN SMOKY BBQ CHEESE";
    menu_string[12].string_from_menu = "13. CHICKEN WITH BACON";
    menu_string[13].string_from_menu = "14. CHICKEN WITH SAUSAGE";
    menu_string[14].string_from_menu = "15. CHICKEN CHEESE BLAST";
    menu_string[15].string_from_menu = "16. CHICKEN SIGNATURE";
    menu_string[16].string_from_menu = "17. GIGANTO CHICKEN";
    menu_string[17].string_from_menu = "18. BINGE CHICKEN";
    menu_string[18].string_from_menu = "19. FRENCH FRIES";
    menu_string[19].string_from_menu = "20. CHICKEN FINGERS (10 PCS)";
    menu_string[20].string_from_menu = "21. NAGA DRUMS (3 PCS)";
    menu_string[21].string_from_menu = "22. COLD COFFEE";
    menu_string[22].string_from_menu = "23. MUNCH";
    menu_string[23].string_from_menu = "24. OREO";
    menu_string[24].string_from_menu = "25. NUTELLA";
}

void menu_display()
{
    int i = 0, j = 0, len;
    ptr1 = fopen("C:\\Users\\Rifat\\Desktop\\Project\\Owners Database\\Food Availibility.txt", "r"); // file location (change it in your computer)
    char store[200];
    while (fgets(menu_string[i].string_from_database, sizeof(menu_string[i].string_from_database), ptr1))
    { // fgets reads strings with a new line and to terminate the new line , used loop and replaces the last element with NULL
        len = strlen(menu_string[i].string_from_database);
        menu_string[i].string_from_database[len - 1] = 0;
        i++;
    }
    menu_string[i - 1].string_from_database[len - 1] = 'A'; // but fgets doesnt read new line for the last line string of file, so here i assigned the last element as A ,because 25. NUTELLA, here added A in last element

    for (j = 0; j < i; j++)
    { // compares the string of menu and string from database and stored in menu_string[j].compare
        menu_string[j].compare = strcmp(menu_string[j].string_from_menu, menu_string[j].string_from_database);
    }

    printf("***********************************************************************************************************************************************************\n");
    printf("*\t\t\t\t\t\t\t\t\tCHILLS RESTAURANT\t\t\t\t\t\t\t\t  *\n");
    printf("***********************************************************************************************************************************************************\n");
    printf("\n");

    printf("\t\tBEEF BURGERS\t\t\t");
    printf("|\t\t  CHICKEN BURGERS\t\t\t|\t\t\tSIDES\n");
    printf("\t\t------------\t\t\t|\t\t  ---------------\t\t\t|\t\t\t-----\n");

    // for display purposes
    if (menu_string[0].compare == 0)
        printf("%s\t\t\t| 180 TK |", menu_string[0].string_from_menu);
    else
        printf("%s(U/A)\t\t| 180 TK |", menu_string[0].string_from_menu);

    printf("\t");

    if (menu_string[9].compare == 0)
        printf("|%s\t\t\t| 180 TK |", menu_string[9].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 180 TK |", menu_string[9].string_from_menu);

    printf("\t");

    if (menu_string[18].compare == 0)
        printf("|%s\t\t\t| 120 TK |\n", menu_string[18].string_from_menu);
    else
        printf("|%s(U/A)\t\t\t| 120 TK |\n", menu_string[18].string_from_menu);

    printf("   (Beef Patty, Special Sauce)\t\t\t|   (Chicken Patty, Special Sauce)\t\t\t|\n\t\t\t\t\t\t|\t\t\t\t\t\t\t");

    if (menu_string[19].compare == 0)
        printf("|%s\t\t| 130 TK |\n", menu_string[19].string_from_menu);
    else
        printf("|%s(U/A)\t| 130 TK |\n", menu_string[19].string_from_menu);

    if (menu_string[1].compare == 0)
        printf("%s\t| 200 TK |", menu_string[1].string_from_menu);
    else
        printf("%s(U/A)\t| 200 TK |", menu_string[1].string_from_menu);

    printf("\t");

    if (menu_string[10].compare == 0)
        printf("|%s\t\t| 200 TK |", menu_string[10].string_from_menu);
    else
        printf("|%s(U/A)\t| 200 TK |", menu_string[10].string_from_menu);

    printf("\t|\n");
    printf("   (Beef Patty, Cheese, Special \t\t|   (Chicken Patty, Cheese, Special\t\t\t");

    if (menu_string[20].compare == 0)
        printf("|%s\t\t\t| 180 TK |", menu_string[20].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 180 TK |", menu_string[20].string_from_menu);

    printf("\n    Sauce)\t\t\t\t\t|    Sauce)\t\t\t\t\t\t|\n\t\t\t\t\t\t|\t\t\t\t\t\t\t|\n");

    if (menu_string[2].compare == 0)
        printf("%s\t| 225 TK |", menu_string[2].string_from_menu);
    else
        printf("%s(U/A)\t| 225 TK |", menu_string[2].string_from_menu);

    printf("\t");

    if (menu_string[11].compare == 0)
        printf("|%s\t\t| 225 TK |", menu_string[11].string_from_menu);
    else
        printf("|%s(U/A)\t| 225 TK |", menu_string[11].string_from_menu);

    printf("\t|\t\t\tSHAKES\n");
    printf("   (BBQ Sauce Cooked Beef Patty,\t\t|   (BBQ Sauce Cooked Beef Patty,\t\t\t|\t\t\t------\n    Cheese)\t\t\t\t\t|    Cheese)\t\t\t\t\t\t");

    if (menu_string[21].compare == 0)
        printf("|%s\t\t\t| 140 TK |", menu_string[21].string_from_menu);
    else
        printf("|%s(U/A)\t\t\t| 140 TK |", menu_string[21].string_from_menu);

    printf("\n\t\t\t\t\t\t|\t\t\t\t\t\t\t|\n");

    if (menu_string[3].compare == 0)
        printf("%s\t\t| 230 TK |", menu_string[3].string_from_menu);
    else
        printf("%s(U/A)\t\t| 230 TK |", menu_string[3].string_from_menu);

    printf("\t");

    if (menu_string[3].compare == 0)
        printf("|%s\t\t\t| 230 TK |", menu_string[12].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 230 TK |", menu_string[12].string_from_menu);

    printf("\t");

    if (menu_string[22].compare == 0)
        printf("|%s\t\t\t\t| 140 TK |\n", menu_string[22].string_from_menu);
    else
        printf("|%s(U/A)\t\t\t\t| 140 TK |\n", menu_string[22].string_from_menu);

    printf("   (Beef Patty, Beef Bacon)\t\t\t|   (Chicken Patty, Beef Bacon)\t\t\t\t|\n\t\t\t\t\t\t|\t\t\t\t\t\t\t");

    if (menu_string[23].compare == 0)
        printf("|%s\t\t\t\t| 160 TK |\n", menu_string[23].string_from_menu);
    else
        printf("|%s(U/A)\t\t\t\t| 160 TK |\n", menu_string[23].string_from_menu);

    if (menu_string[4].compare == 0)
        printf("%s\t\t| 250 TK |", menu_string[4].string_from_menu);
    else
        printf("%s(U/A)\t| 250 TK |", menu_string[4].string_from_menu);

    printf("\t");

    if (menu_string[13].compare == 0)
        printf("|%s\t\t| 250 TK |", menu_string[13].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 250 TK |", menu_string[13].string_from_menu);

    printf("\t|\n");
    printf("   (Beef Patty, 2x Chicken \t\t\t|   (Chicken Patty, 2x Chicken \t\t\t\t");

    if (menu_string[24].compare == 0)
        printf("|%s\t\t\t\t| 170 TK |", menu_string[24].string_from_menu);
    else
        printf("|%s(U/A)\t\t\t| 170 TK |", menu_string[24].string_from_menu);

    printf("\n    Sausage, Cheese)\t\t\t\t|    Sausage, Cheese)\n\t\t\t\t\t\t|\n");

    if (menu_string[5].compare == 0)
        printf("%s\t\t| 320 TK |", menu_string[5].string_from_menu);
    else
        printf("%s(U/A)\t| 320 TK |", menu_string[5].string_from_menu);

    printf("\t");

    if (menu_string[14].compare == 0)
        printf("|%s\t\t| 320 TK |\n", menu_string[14].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 320 TK |\n", menu_string[14].string_from_menu);

    printf("   (2x Melted Cheese inside a \t\t\t|   (2x Melted Cheese inside a \n    Double Sized Beef Patty & \t\t\t|    Double Sized Chicken Patty & \n    Cheese outside)\t\t\t\t|    Cheese outside)\n\t\t\t\t\t\t|\n");

    if (menu_string[6].compare == 0)
        printf("%s\t\t| 380 TK |", menu_string[6].string_from_menu);
    else
        printf("%s(U/A)\t\t| 380 TK |", menu_string[6].string_from_menu);

    printf("\t");

    if (menu_string[15].compare == 0)
        printf("|%s\t\t\t| 380 TK |\n", menu_string[15].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 380 TK |\n", menu_string[15].string_from_menu);

    printf("   (2x Beef Patty, 2x Cheese, \t\t\t|   (2x Chicken Patty, 2x Cheese, \n    Beef Pastrami, Poached Egg)\t\t\t|    Chicken Pastrami, Poached Egg)\n\t\t\t\t\t\t|\n");

    if (menu_string[7].compare == 0)
        printf("%s\t\t\t| 430 TK |", menu_string[7].string_from_menu);
    else
        printf("%s(U/A)\t\t| 430 TK |", menu_string[7].string_from_menu);

    printf("\t");

    if (menu_string[16].compare == 0)
        printf("|%s\t\t\t| 430 TK |\n", menu_string[16].string_from_menu);
    else
        printf("|%s(U/A)\t\t| 430 TK |\n", menu_string[16].string_from_menu);

    printf("   (2x Beef Patty, 2x Cheese, \t\t\t|   (2x Chicken Patty, 2x Cheese, \n    Double Beef Bacon,BBQ Sauce)\t\t|    Double Beef Bacon,BBQ Sauce)\n\t\t\t\t\t\t|\n");

    if (menu_string[8].compare == 0)
        printf("%s\t\t\t| 680 TK |", menu_string[8].string_from_menu);
    else
        printf("%s(U/A)\t\t| 680 TK |", menu_string[8].string_from_menu);

    printf("\t");

    if (menu_string[17].compare == 0)
        printf("|%s\t\t\t| 680 TK |", menu_string[17].string_from_menu);
    else
        printf("|%s(U/A)\t\t\t| 680 TK |", menu_string[17].string_from_menu);

    printf("\t|* If any food item is unavailable, it will show up\n");

    printf("   (2x Giant Beef Patty, Smoked \t\t|   (2x Giant Chicken Patty, Smoked\t\t\t|\tnext to the food item (U/A)\n    Chicken, Chicken Ham, 3x \t\t\t|    Chicken, Chicken Ham, 3x \t\t\t\t|\n    Cheese)\t\t\t\t\t|    Cheese)\t\t\t\t\t\t|* Service Charge(10%) and VAT(15%) excluded\n\n");
    fclose(ptr1);
}
