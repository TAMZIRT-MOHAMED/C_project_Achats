// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <time.h>
// #include <string.h>
// #include "header_PRODUIT.h"
// FILE * PDM ;            // PDM : PRODUCT DETAIL MANAGMENT //

// FILE * CDM ;         // CRM : CREDIT CARD DETAIL MANAGMENT //

// typedef struct {     // date_card_credit information   //
//    char year[3] ;
//     char month[3];
// }date_card ;

// typedef struct {       // PRODUCT  information   //
//    char product_name[30];
//    int category ;
//    int quantity ;
//    float price ;
// }produit_info;   

// typedef struct credit_card_details {     // CREDIT CARD  INFORMATION   //
//   int client_id ;
//   char client_name[30];
//   char card_number [50];
//   date_card expiry_date ;
// }CCD  ;    // CCD : CREDIT CARD  DETAIL

// void add_credit_card (int id_client , char * name_client){   // AFTER TESTING THE CLIENT HAS an account //
       
//     time_t t = time(NULL);   // Get the current time
    
//     struct tm * current_time = localtime(&t); // Convert to local time structure

//     int current_year = current_time->tm_year + 1900; // Extract the current year
//    CDM = fopen ("CREDIT_CARD.dat" , "ab");
//    if (CDM == NULL){
//     printf("Le fichier not existe !!!");
//     exit(0);
//    }
//    int i = -1 , int valid = 0 ;
//    CCD A ;  
//    A.client_id = id_client ;
//    A.client_name = name_client ;
//    printf(" %s , Please Entre your Credit card information (typically 13-19 digits ) : \n" , name_client );
//    do{
//    printf("Entre you Card Credit Number : ");
//    scanf("%s" ,A.card_number);
//            valid = 1;
//         for (int i = 0; i < strlen(A.card_number); i++) {
//             if (!isdigit(A.card_number[i])) {
//                 valid = 0;
//                 break;
//             }
//         }
//         if (strlen(A.card_number) < 13 || strlen(A.card_number) > 16) {
//             valid = 0;
//         }

//         if (!valid) {
//             printf("\nPlease enter a valid number between 13-19 digits\n");
//         }
//     } while (!valid);

//    printf("\n************** Entre The expiry date  ************** \n");
//    do{
//    printf("Entre the date like this MM/YY (e.g , 02/27) : ");
//    scanf("%2s/%2s" ,A.expiry_date.month , A.expiry_date.year);
//    int month, year;
//    if ( (sscanf(A.expiry_date.month ,"%2d" , &month) == 1) && (sscanf(A.expiry_date.year ,"%2d" , &year) == 1) ){
//         if(month > 12 || month <= 0 ){
//          c_textcolor(4);
//          printf("\nInvalid mont !!!\n");
//          break;
//         }
//         if ( year < (current_year - 2000) ){
//          c_textcolor(4);
//          printf("\nInvalid year\n");
//          break;
//         }
//       i = -1 ;
//    }
//    }while (i == 0 );
// printf("month = %d , year = %d " ,month , year );
// fwrite(&A ,sizeof(CCD) , 1 , CDM);
// fclose(CDM);
// }




#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "conio.h"
#include "header_PRODUIT.h"

FILE *CDM;  // CRM : CREDIT CARD DETAIL MANAGEMENT

typedef struct {     // Date card credit information
    char year[3];
    char month[3];
} date_card;

typedef struct credit_card_details {     // Credit Card Information
    int client_id;
    char client_name[30];
    char card_number[50];
    date_card expiry_date;
} CCD;    // CCD : CREDIT CARD DETAIL

void add_credit_card(int id_client, char *name_client) {
    time_t t = time(NULL);   // Get the current time
    struct tm *current_time = localtime(&t); // Convert to local time structure
    int current_year = current_time->tm_year + 1900; // Extract the current year

    // Open the file in append binary mode
    CDM = fopen("CREDIT_CARD.dat", "ab");
    if (CDM == NULL) {
        printf("File does not exist!\n");
        return;  // Exit without terminating the program
    }

    CCD A;
    A.client_id = id_client;
    strncpy(A.client_name, name_client, sizeof(A.client_name) - 1);
    A.client_name[sizeof(A.client_name) - 1] = '\0';  // Ensure null termination

    printf(" \n%s, please enter your credit card information (typically 13-19 digits): \n", name_client);

    int valid = 0;
    do {
        printf("Enter your credit card number: ");
        scanf("%s", A.card_number);

        // Check if card number contains only digits and has valid length
        valid = 1;
        for (int i = 0; i < strlen(A.card_number); i++) {
            if (!isdigit(A.card_number[i])) {
                valid = 0;
                break;
            }
        }
        if (strlen(A.card_number) < 13 || strlen(A.card_number) > 16) {
            valid = 0;
        }

        if (!valid) {
            printf("\nPlease enter a valid number between 13-19 digits\n");
        }
    } while (!valid);

    printf("\n************** Enter The Expiry Date **************\n");

    valid = 0;
    int month, year;
    do {
        printf("Enter the expiry date as MM/YY (e.g., 02/27): ");
        scanf("%2s/%2s", A.expiry_date.month, A.expiry_date.year);

        // Parse and validate month and year
        if ((sscanf(A.expiry_date.month, "%2d", &month) == 1) && (sscanf(A.expiry_date.year, "%2d", &year) == 1)) {
            if (month > 0 && month <= 12 && year >= (current_year - 2000)) {
                valid = 1;
            } else {
                c_textcolor(4); // Assuming c_textcolor changes text color
                printf("\nInvalid month or year!\n");
                c_textcolor(7); // Reset color (assuming 7 is the reset color code)
            }
        } else {
            printf("Invalid format. Please enter MM/YY\n");
        }
    } while (!valid);

    printf("Month = %d, Year = %d\n", month, year+2000);

    // Write to file and close
    fwrite(&A, sizeof(CCD), 1, CDM);
    fclose(CDM);
}
