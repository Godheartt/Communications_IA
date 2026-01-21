#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//Logins
char Default_Admin_Username[] =   "Admin";
char Default_Employee_Username[]= "Employee";
char  Default_Employee_Pass[] =   "operator";
char  Default_Admin_Pass[] =      "private";
//Values
#define MAX_LENGTH 256

char READL[MAX_LENGTH];
const char acts[10][19] ={
    "Hiking","Golfing","Scuba Diving",
    "Jet Skiing","Horse Backing","Kayaking",
    "Boat Tours","Forest Trails","Yoga on the Beach",
    "Spa-day on the reef"};
//Displays
const char  Top_Tile[]    = "\t\t    Welcome to sister island's\n";
const char  Top_Subtile[] = "\t\t\t  Booking System\n";
const char  Top_divider[] = "********************************************************************************\n";
const char  divider1[]    = "--------------------------------------------------------------------------------\n"
                            "------------------------------------NEW--TAB------------------------------------\n"
                            "--------------------------------------------------------------------------------\n\n";
//Screen layouts :
const char  Empscreen1[]    = "\t\t\t1---Create Booking\n\t\t\t2---View Current Bookings\n\t\t\t3---Cancel Booking\n";
const char  BC_Subtile[] = "\t\t\t  Booking Creation\n";

//Functions
int Read_Line(FILE *file,double Line_Num);
void createBookings();
int Login();

int main(void) {
    //FILES
    FILE *IN_Bookings = fopen("Bookings.txt", "a");
    fclose(IN_Bookings);

    //Variables
    char In1[] = "Enter :-",Store[50];
    int Hold = 0,Checked =1;
    printf("%s%s%s%s",
        Top_Tile,Top_Subtile,Top_divider,Empscreen1);
    while (Checked ==1) {
        printf("%s",In1);
        scanf("%s",Store);
        sscanf(Store, "%d", &Hold);
        switch (Hold) {
            case 1:
                createBookings();
                Checked = 0;
                break;
            case 2:
                Checked = 0;
                break;
            case 3:
                Checked = 0;
                break;
            default:
                printf("Error Value Invalid -- Only numbers (1-3)\n");
                break;
        }
    }



    Sleep(2000);
    return 0;
}

// Functions
void createBookings() {
    //Check entries
    char entry_checks[MAX_LENGTH];
    int entry_counter=0;
    FILE *Ed_Bookings = fopen("Bookings.txt", "r+");
    if ((Read_Line(Ed_Bookings, 0))!=0) {
        sprintf(entry_checks, "%s", READL);
        entry_checks[strcspn(entry_checks, "\n")] = '\0';// Removes the \n in the str

        printf("%s\n",entry_checks);


        if (strcmp(entry_checks,"\0")==0) {
            entry_counter++;
        }else {
            sscanf(entry_checks, "%d", &entry_counter);
            if (entry_counter == 0) {
                printf("Error failed to create UID");
            }
            else {
                entry_counter++;
            }
        }
    }
    else {
        entry_counter++;
        fprintf(Ed_Bookings,"0\n");
    }
    fclose(Ed_Bookings);


    // variables
    FILE *IN_Bookings = fopen("Bookings.txt", "a");
    int Hold =0,Querying=1;
    char Storage[MAX_LENGTH];
    char Questions[9][35] ={"Enter Activity No.#","Frist Name:","Last Name:","Person's age:","Phone No.#","Email Address :"
        ,"Number of persons Booking for:","Date in (dd/mm/yyyy) :","Time in (23:00):~"};

    printf("%s%s%s%sActivities\n1--%s\t   2--%s\t\t3--%s\n"
           "4--%s\t   5--%s\t6--%s\n7--%s\t   8--%s\t9--%s\n\t       10--%s\n\nEnter clients Info:\n",
        divider1,Top_Tile,BC_Subtile,Top_divider,acts[0],acts[1],acts[2],acts[3],acts[4],acts[5],acts[6]
        ,acts[7],acts[8],acts[9]);


    //Booking entries
    for (int i = 0 ; i < 9 ; i++) {
        Querying = 1;
        while (Querying ==1) {
            printf("%s",Questions[i]);
            scanf("%s",Storage);
            switch (i) {
                case 0:sscanf(Storage, "%d", &Hold);
                    if (Hold != 0 && Hold < 11) {
                        Querying = 0;
                        sprintf(Storage, "%s", acts[Hold-1]);// makes the booking number the word
                        fprintf(IN_Bookings,"\nUID;%d%d\n",Hold,entry_counter);
                        //Creates UID Using the activity number and
                        //how many bookings were entered
                    }else{printf("Error Not an Valid Entry\n");}
                    break;

                case 1://Names can be anything so no check need
                case 2:
                case 4://While phones numbers are simply too strange to be able to check at my skill level
                    Querying = 0;
                    break;
                case 5:
                    //check to see if (@) and(.) are present
                    if (strchr(Storage,'@')!=NULL&&strchr(Storage,'.')!=NULL) {
                        Querying = 0;
                    }
                    else {printf("Error please enter a valid email\n");}
                    break;
                case 3:
                case 6:
                    sscanf(Storage, "%d", &Hold);//changes string to int and if it can't set the value to 0
                    if (Hold != 0) {//checks if the change is succesful
                        Querying = 0;
                    }else {printf("Error Not an Valid Entry\n");}
                    break;
                case 7:
                    //check the text to see if it has Two(/) like in the format
                    if (strchr(Storage,'/')!=NULL) {
                        Storage[strcspn(Storage, "/")] = '@';
                        if (strchr(Storage,'/')!=NULL) {
                            Storage[strcspn(Storage, "@")] = '/';
                            Querying = 0;
                        }else {printf("Error Not an Valid Entry\n");}
                    }else {printf("Error Not an Valid Entry\n");}
                    break;
                case 8:
                    //check the text to see if it has (:) like in the format
                    if (strchr(Storage,':')!=NULL) {
                        Querying = 0;
                    }else {printf("Error Not an Valid Entry\n");}
                    break;
                default:break;
            }


            if (Querying == 0 ) {
                fprintf(IN_Bookings, "%s\n",Storage);
            }


        }
    }
    fclose(IN_Bookings);
    Ed_Bookings = fopen("Bookings.txt", "r+");
    sprintf(entry_checks, "%d", entry_counter );
    fseek(Ed_Bookings, 0, SEEK_SET);
    fputs(entry_checks, Ed_Bookings);
    fclose(Ed_Bookings);
}

int Read_Line(FILE *file,double Line_Num) {
    char FILE_Storage[MAX_LENGTH];
    double Current_Position = 0;
    rewind(file);
    //Find the line
    while (fgets(FILE_Storage,sizeof(FILE_Storage), file) != NULL) {
        if (Current_Position == Line_Num) {
            sprintf(READL, "%s", FILE_Storage);
            return 1;
        }
        Current_Position++;
    }
    return 0;
}

int Login() {
    //Variables
    char Default_Admin_Username[]={"admin",""};
};