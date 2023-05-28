#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


struct item
{
    int productno;
    char productname[10];
    int quantity;
    int price;
} item;


struct customer
{
    int productno;
    char productname[10];
    int quantity;
    int price;
    int amount;
} cst;


int n=0;
int grandtotal=0;
int totalquan=0;


void create()
{
    int i=0;

    FILE *fp;
    fp=fopen("records.csv","a+");
    if(fp==NULL)
    {
        printf("Error\n");
    }

    printf("\t");
    printf("Enter the Number of Records:");
    scanf("%d",&n);
    printf("\n");

    while(i<n)
    {
        printf("\t");
        printf("Enter Product Code:");
        scanf("%d",&item.productno);

        printf("\t");
        printf("Enter Product Name:");
        scanf("%s",item.productname);

        printf("\t");
        printf("Enter Inventory:");
        scanf("%d",&item.quantity);

        printf("\t");
        printf("Enter Price:");
        scanf("%d",&item.price);

        printf("\n");
        i++;
        fprintf(fp,"%d, %s, %d, %d\n",item.productno,item.productname,item.quantity,item.price);
    }

    fclose(fp);

    printf("\t");
    printf("Records are Created............");
    printf("\n");
    printf("\n");
    fclose(fp);
}


int display()
{
        FILE *fp;
        fp=fopen("records.csv", "r");
        if (fp == NULL) {
            perror("Error opening file");
            return 0;
        }

        printf("_____________________________________________________________________________________________\n");
        printf("\tPROD_ID\t\tNAME\t\t\tINVENTORY\t\tPRICE\n");
        printf("---------------------------------------------------------------------------------------------\n");

        char buffer[1024];
        while (fgets(buffer, 1024, fp) != NULL)
        {
            char *field;

            field = strtok(buffer, ",");
            item.productno = atoi(field);

            field = strtok(NULL, ",");
            strcpy(item.productname, field);

            field = strtok(NULL, ",");
            item.quantity = atoi(field);

            field = strtok(NULL, ",");
            item.price = atoi(field);

            printf("%14d\t\t%8s\t\t%8d\t\t%d\n", item.productno, item.productname, item.quantity, item.price);

        }

        printf("_____________________________________________________________________________________________\n");
        fclose(fp);
        return 0;
}


int bill(int n)
{
    int items, i, prod_id, quan, amt, rem_inv, j, k, cash, change;
    char billno[10];

    sprintf(billno, "billno_%d.csv", n);

    FILE *fpt;
    fpt=fopen(billno, "a+");
    if (fpt == NULL) {
        perror("Error opening file");
        return 0;
    }

    FILE *fp;
    fp=fopen("records.csv", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    FILE *fp1;
    fp1=fopen("records1.csv", "a+");
    if (fp1 == NULL) {
        perror("Error opening file");
        return 0;
    }

        printf("\n\tEnter the product id: ");
        scanf("%d", &prod_id);

        char buffer[1024];
        while (fgets(buffer, 1024, fp) != NULL)
        {
            char *field;

            field = strtok(buffer, ",");
            item.productno = atoi(field);

            field = strtok(NULL, ",");
            strcpy(item.productname, field);

            field = strtok(NULL, ",");
            item.quantity = atoi(field);

            field = strtok(NULL, ",");
            item.price = atoi(field);

            rem_inv = item.quantity;

            if (prod_id != item.productno)
            {
                rem_inv=item.quantity;
            }

            if (prod_id == item.productno)
            {
                printf("\tProduct Name: %s\n", item.productname);
                printf("\tThe price is: %d\n", item.price);
                printf("\tEnter quantity to be purchased: ");
                scanf("%d", &quan);
                printf("\n");

                if(item.quantity<quan)
                {
                    printf("\tOut Of Stock Item\n\n");
                    printf("The stock is: %d", item.quantity);
                    break;
                }

                rem_inv=item.quantity-quan;
                //item.quantity=quan;
                amt = quan*item.price;

                fprintf(fpt,"%d,%s, %d, %d, %d\n",item.productno,item.productname,quan,item.price, amt);
            }

            fprintf(fp1, "%d,%s, %d, %d\n", item.productno, item.productname, rem_inv, item.price);

        }

        fclose(fp1);
        fclose(fp);
        fclose(fpt);

        remove("records.csv");
        if (rename("records1.csv", "records.csv") != 0)
        {
            perror("Error renaming file");
        }

    return 0;
}


int invoice(int n)
{
        char billno[10];

        sprintf(billno, "billno_%d.csv", n);

        FILE *fp;
        fp=fopen(billno, "r");
        if (fp == NULL) {
            perror("Error opening file");
            return 0;
        }

        printf("_______________________________________________________________________________________________________\n");
        printf("\tPROD_ID\t\tNAME\t\t\tQUANTITY\t\tPRICE\t\tAMOUNT\n");
        printf("-------------------------------------------------------------------------------------------------------\n");

        char buffer[1024];
        while (fgets(buffer, 1024, fp) != NULL)
        {
            char *field;

            field = strtok(buffer, ",");
            cst.productno = atoi(field);

            field = strtok(NULL, ",");
            strcpy(cst.productname, field);

            field = strtok(NULL, ",");
            cst.quantity = atoi(field);

            field = strtok(NULL, ",");
            cst.price = atoi(field);

            field = strtok(NULL, ",");
            cst.amount = atoi(field);

            totalquan=totalquan+cst.quantity;
            grandtotal=grandtotal+cst.amount;
            printf("%14d\t\t%8s\t\t%8d\t\t%8d\t\t%d\n", cst.productno, cst.productname, cst.quantity, cst.price, cst.amount);

        }

        printf("_____________________________________________________________________________________________________\n");

        printf("\n\tTOTAL QUANTITY: %d", totalquan);
        printf("\n\n\tGRAND TOTAL: %d", grandtotal);
        printf("\n_____________________________________________________________________________________________________\n");

        grandtotal = 0;
        totalquan = 0;

        fclose(fp);

        return 0;
}


int delete(int n)
{
    char billno[10];

    sprintf(billno, "billno_%d.csv", n);
    remove(billno);
    printf("\n\tBILL DELETED SUCCESSFULLY.........\n\n");

}


int inventory(int prod_id)
{
    int i, rem_inv, inv_add;
    char buffer1[1024];

    FILE *fp;
    fp=fopen("records.csv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    FILE *fp1;
    fp1=fopen("records1.csv", "a+");
    if (fp1 == NULL)
    {
        perror("Error opening file");
        return 0;
    }

        while (fgets(buffer1, 1024, fp) != NULL)
        {
            char *field;

            field = strtok(buffer1, ",");
            item.productno = atoi(field);

            field = strtok(NULL, ",");
            strcpy(item.productname, field);

            field = strtok(NULL, ",");
            item.quantity = atoi(field);

            field = strtok(NULL, ",");
            item.price = atoi(field);

            if (prod_id != item.productno)
            {
                rem_inv=item.quantity;
            }

            if (prod_id == item.productno)
            {
                printf("Product Name: %s\n", item.productname);
                printf("Enter inventory to be added: ");
                scanf("%d", &inv_add);
                printf("\n");
                rem_inv=item.quantity+inv_add;
            }

            fprintf(fp1, "%d,%s, %d, %d\n", item.productno, item.productname, rem_inv, item.price);

        }

        fclose(fp1);
        fclose(fp);
        remove("records.csv");

        if (rename("records1.csv", "records.csv") != 0)
        {
            perror("Error renaming file");
        }

        printf("\nInventory Updated Successfully.............\n\n");
    return 0;


}


int remove_prod(int prod_id)
{
    FILE *fp;
    fp=fopen("records.csv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    FILE *fp1;
    fp1=fopen("records1.csv", "a+");
    if (fp1 == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    char buffer1[1024];
    while (fgets(buffer1, 1024, fp) != NULL)
        {
            char *field;

            field = strtok(buffer1, ",");
            item.productno = atoi(field);
            //printf("Hello");

            field = strtok(NULL, ",");
            strcpy(item.productname, field);

            field = strtok(NULL, ",");
            item.quantity = atoi(field);

            field = strtok(NULL, ",");
            item.price = atoi(field);

            //rem_inv = item.quantity;

            if (prod_id == item.productno)
            {
                printf("Product Name: %s\n", item.productname);
                printf("Product deleted successfully...........\n");
                continue;
            }

            fprintf(fp1, "%d,%s, %d, %d\n", item.productno, item.productname, item.quantity, item.price);

        }

        fclose(fp1);
        fclose(fp);
        remove("records.csv");

        if (rename("records1.csv", "records.csv") != 0)
        {
            perror("Error renaming file");
        }

        return 0;

}


int main()
{
    char ch,password[10],q[10]="admin";
    int prod_id, bill_no, items;
    int s=0;
    int y=0;
    int i;

    printf("\n");
    q: printf("\n\t");
    printf("\n\n\n");

    printf("\t");
    printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");
    printf("\n");
    printf("\t\t\t");
    printf("JAYPEE SUPERMARKET");
    printf("\n");
    printf("\t");
    printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");

    printf("\t * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");
    printf("\n");
    printf("\t");
    printf("Please Select an Option: ");
    printf("\n");
    printf("\t");
    printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");
    printf("\n");
    printf("\t");
    printf("01. ADMINISTRATOR");
    printf("\n\t");
    printf("02. CUSTOMER");
    printf("\n\t");
    printf("03. EXIT");
    printf("\n");
    printf("\n\t");
    printf("Please Enter an Option: ");
    scanf("%d",&s);


        if(s==1)
        {
              printf("\tEnter Password:\t");
              for(i=0;i<5;i++)
              {
              ch = getch();
              password[i] = ch;
              ch = '*' ;
               printf("%c",ch);
              }
              password[i]='\0';
              if(strcmp(password,q))
              {
                  printf("\n\t");
              printf("Wrong Password Please Try Again");
              printf("\n\n");
              goto q;
             }
               else
               goto l3;
               l3: printf("\n\t");
               printf("Access Granted\n");
               printf("\n\n");
               printf("\t");
               printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");
               printf("\n");
               printf("\t");
               printf("Please Select an Option: ");
               printf("\n");
               printf("\t");
               printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");
               printf("\n\t");
               printf("01.INCREASE PRODUCTS IN DATABASE");
               printf("\n\t");
               printf("02.DELETE PRODUCT FROM DATABASE");
               printf("\n\t");
               printf("03.INCREASE INVENTORY");
               printf("\n\t");
               printf("04.DISPLAY ALL PRODUCTS");
               printf("\n\t");
               printf("05.FETCH AN OLD BILL");
               printf("\n\t");
               printf("06.DELETE AN OLD BILL");
               printf("\n\t");
               printf("07.MAIN MENU");
               printf("\n");
               printf("\n");
               printf("\t");
               printf("Please Enter an Option: ");
                scanf("%d",&y);
                //switch(y)
                //{
                    if (y==1)
                    {
                            create();
                            goto q;
                    }

                    else if(y==2)
                    {
                            printf("Enter product id of the product to be deleted: ");
                            scanf("%d", &prod_id);
                            remove_prod(prod_id);
                            goto q;
                    }

                    else if(y==3)
                    {
                            printf("Enter product ID whose inventory is to be added: ");
                            scanf("%d", &prod_id);
                            inventory(prod_id);
                            goto q;
                    }

                    else if (y==4)
                    {
                            display();
                            goto q;
                    }

                    else if (y==5)
                    {
                            printf("\tBillno:");
                            scanf("%d", &bill_no);
                            invoice(bill_no);
                            goto q;
                    }

                    else if (y==6)
                    {
                            printf("\tBillno:");
                            scanf("%d", &bill_no);
                            delete(bill_no);
                            goto q;
                    }

                    else if(y==7)
                    {
                            goto q;
                    }

                    else
                    {
                            printf("error\n");
                            goto q;
                    }
            }



        else if(s==2){

                            FILE *fp;
                            fp=fopen("billstorage.txt", "r");
                            if (fp == NULL) {
                                perror("Error opening file");
                                return 0;
                            }

                            fscanf(fp, "%d", &bill_no);
                            //printf("%d", billno);
                            fclose(fp);

                            bill_no++;

                            FILE *fpt;
                            fpt=fopen("billstorage.txt", "w");
                            if (fpt == NULL) {
                                perror("Error opening file");
                                return 0;
                            }

                            fprintf(fpt, "%d", bill_no);
                            //printf("%d", billno);
                            fclose(fpt);

                            printf("\t\tBILL NO. : %d\n", bill_no);
                            printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * ");

                            printf("\n\tEnter number of items to be added in the bill: ");
                            scanf("%d", &items);

                            //remove("bill.csv");

                            for (i=0;i<items;i++)
                            {
                                bill(bill_no);
                            }

                            printf("\n\n");
                            invoice(bill_no);
                             goto q;
                        }


    else if(s==3)
    {
        printf("\tExiting...\n");
        return 0;
    }

    else 
    {
        printf("error\n");
        goto q;
    }
      return 0;
    }
