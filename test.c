#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Values
#define MAX_LENGTH 256
char READL[MAX_LENGTH];
const char acts[10][19] ={
    "Hiking","Golfing","Scuba Diving",
    "Jet Skiing","Horse Backing","Kayaking",
    "Boat Tours","Forest Trails","Yoga on the Beach",
    "Spa-day on the reff"};
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


// Function to read a specific line from a file using fseek
int read_line_at(FILE *fp, long line_number) {
    char buffer[MAX_LENGTH];
    long current_line = 0;
    long pos = 0;

    // Rewind to start of file
    rewind(fp);

    // Loop until we reach the desired line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (current_line == line_number) {
            printf("Line %ld: %s", line_number, buffer);
            return 1; // Success
        }
        current_line++;
        //pos = ftell(fp); // Save position after reading
    }

    return 0; // Line not found
}

int main() {
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
                        //fprintf(IN_Bookings,"\nUID;%d%d\n",Hold,entry_counter);
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
        }
    }
    return 0;
}



//ClearScreen
/*void ClearScreen() {
    system("cls");//Windows command to clear screen
    printf("\033[2J\033[H");//ANSI Escape code to clear screen
    fflush(stdout);//flush output stream
    //THe two clear are done for compatibility with my complier
}*/