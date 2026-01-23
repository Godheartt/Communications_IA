#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//Logins
const char  Default_Admin_Username[]    = "Admin";
const char  Default_Admin_Password[]    = "Private";
const char  Default_Employee_Username[] = "Employee";
const char  Default_Employee_Password[] = "Operator";

//Values
#define MAX_LENGTH 256

char READL[MAX_LENGTH];//Variable used for store the contents of a line to be used later

struct Booking_Data {
    int  Activity;
    char FName[MAX_LENGTH];
    char LName[MAX_LENGTH];
    int  Age;
    char Phone_Num[MAX_LENGTH];
    char Email[MAX_LENGTH];
    int  Participants;
    char Date[MAX_LENGTH];
    char Time[MAX_LENGTH];
}Booking_data;


const char acts[10][19] ={
    "Hiking","Golfing","Scuba Diving",
    "Jet Skiing","Horse Backing","Kayaking",
    "Boat Tours","Forest Trails","Yoga on the Beach",
    "Spa-day on the reef"};
//Displays
const char  Top_Tile[]    = "\t\t    Welcome to sister island's\n";
const char  Top_Subtile[] = "\t\t\t  Booking System\n";
const char  Top_divider[] = "********************************************************************************\n";
const char  TAB_divider[] = "--------------------------------------------------------------------------------\n"
                            "------------------------------------NEW--TAB------------------------------------\n"
                            "--------------------------------------------------------------------------------\n\n";
//Screen layouts :
const char  Emp_Screen[]  = "\t\t\t1---Create Booking\n\t\t\t2---View Current Bookings\n\t\t\t3---Cancel Booking"
                            "\n\t\t\t4---EXIT\n";
const char  Adm_Screen[]  = "\t\t\t1---View Reports\n\t\t\t2---View Current Bookings\n\t\t\t3---Create Employee Accounts"
                            "\n\t\t\t4---EXIT\n";
const char  BC_Subtile[]  = "\t\t\t  Booking Creation\n";

//Functions
int Read_Line(FILE *file,double Line_Num);
int createBookings();
void BookingCosting(int UID);
int GrabBookings(int UID,int Fetch_type);
int Login();

int main(void) {
    int Account = 0;
    //Account = Login();
    printf("%d\n",GrabBookings(32,0));

    //FILES
    FILE *IN_Bookings = fopen("Bookings.txt", "a");
    fclose(IN_Bookings);

    //Variables
    char In1[] = "Enter :-",Store[50];
    int Hold= 0,
    Checked = 1,
    Running= 1;
    while (Running == 1) {
        Checked = 1;
        if (Account == 0) {
            printf("%s%s%s%s",
                Top_Tile,Top_Subtile,Top_divider,Emp_Screen);
            while (Checked ==1) {
                Hold =0;
                printf("%s",In1);
                scanf("%s",Store);
                sscanf(Store, "%d", &Hold);
                switch (Hold) {
                    case 1:
                        BookingCosting(createBookings());
                        Checked = 0;
                        break;
                    case 2:
                        Checked = 0;
                        break;
                    case 3:
                        Checked = 0;
                        break;
                    case 4://ends Program
                        Running = 0;
                        Checked = 0;
                        break;
                    default:
                        printf("Error Value Invalid -- Only numbers (1-3)\n");
                        break;
                }
            }
        }else {
            printf("%s%s%s%s",
                Top_Tile,Top_Subtile,Top_divider,Adm_Screen);
            while (Checked ==1) {
                Hold =0;
                printf("%s",In1);
                scanf("%s",Store);
                sscanf(Store, "%d", &Hold);
                switch (Hold) {
                    case 1:
                        Checked = 0;
                        break;
                    case 2:
                        Checked = 0;
                        break;
                    case 3:
                        Checked = 0;
                        break;
                    case 4://ends Program
                        Running = 0;
                        Checked = 0;
                        break;
                    default:
                        printf("Error Value Invalid -- Only numbers (1-3)\n");
                        break;
                }
            }
        }
    }

    Sleep(2000);
    return 0;
}


// Functions
int createBookings() {
    //Entry Check
    //Counts the amount of entries made by read and change a number at the top of the file
    char entry_checks[MAX_LENGTH];
    int entry_counter=0;
    FILE *Ed_Bookings = fopen("Bookings.txt", "r+");//opens file in both read and write mode
    if ((Read_Line(Ed_Bookings, 0))!=0) {//reads frist line

        sprintf(entry_checks, "%s", READL);//copies READL
        entry_checks[strcspn(entry_checks, "\n")] = '\0';// Removes the \n in the str

        sscanf(entry_checks, "%d", &entry_counter);
        if (entry_counter == 0){
            entry_counter++;
            printf("Creating counter....\n");
            Sleep(600);
        }
        else {
            entry_counter++;
        }

    }
    else {
        entry_counter++;
        fprintf(Ed_Bookings,"0\n");
        printf("Creating counter....\n");
        Sleep(600);
    }
    fclose(Ed_Bookings);


    // variables
    FILE *IN_Bookings = fopen("Bookings.txt", "a");
    int Num_Hold =0,Querying=0,UID;
    char Storage[MAX_LENGTH];
    char FStorage[MAX_LENGTH*9];
    char Questions[9][35] ={"Enter Activity No.#","Frist Name:","Last Name:","Person's age:","Phone No.#","Email Address :"
        ,"Number of persons Booking for:","Date in (dd/mm/yyyy) :","Time in (23:00):~"};

    printf("%s%s%s%sActivities\n1--%s\t   2--%s\t\t3--%s\n"
           "4--%s\t   5--%s\t6--%s\n7--%s\t   8--%s\t9--%s\n\t       10--%s\n\nEnter clients Info:\n",
        TAB_divider,Top_Tile,BC_Subtile,Top_divider,acts[0],acts[1],acts[2],acts[3],acts[4],acts[5],acts[6]
        ,acts[7],acts[8],acts[9]);
    //print the screen along with activities


    //Booking entries
    for (int i = 0 ; i < 9 ; i++) {
        Querying = 1;
        while (Querying ==1) {
            printf("%s",Questions[i]);
            scanf("%s",Storage);
            switch (i) {
                case 0:sscanf(Storage, "%d", &Num_Hold);
                    if (Num_Hold != 0 && Num_Hold < 11) {
                        Querying = 0;
                        sprintf(FStorage, "%d%d", Num_Hold,entry_counter);//Creates UID Using the activity number
                        sscanf(FStorage, "%d", &UID);//and how many bookings were entered
                        sprintf(FStorage, "\nUID;%d",UID);//copies UID
                        sprintf(Storage, "%s", acts[Num_Hold-1]);// makes the booking number the word


                    }else{printf("Error Not an Valid Entry\n");}
                    break;

                case 1://Names can be anything so no check need
                case 2:
                    Querying = 0;
                    break;

                case 3:
                case 4:
                case 6:
                    Num_Hold = 0;//clear var
                    sscanf(Storage, "%d", &Num_Hold);//changes string to int and if it can't set the value to 0
                    if (Num_Hold != 0) {//checks if the change is successful
                        Querying = 0;
                        if (i!=4) {//this trim incorrect entries to only the frist set of number but will not do that to phone numbers
                            sprintf(Storage, "%d",Num_Hold);
                        }
                    }else {printf("Error Not an Valid Entry\n");}
                    break;

                case 5:
                    //check to see if (@) and(.) are present
                    if (strchr(Storage,'@')!=NULL&&strchr(Storage,'.')!=NULL) {
                        Querying = 0;
                    }
                    else {printf("Error please enter a valid email\n");}
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
                sprintf(FStorage,"%s\n%s",FStorage,Storage);
            }
        }
    }


    fprintf(IN_Bookings, "%s\n",FStorage);//writes the whole entry at the end to avid possible errors with canceling
    fclose(IN_Bookings);//close the file.         the code while running
    Ed_Bookings = fopen("Bookings.txt", "r+");//reopens file in both read and write mode
    sprintf(entry_checks, "%d", entry_counter );//copies entry_counter
    fseek(Ed_Bookings, 0, SEEK_SET);//place the writer o the frist line
    fputs(entry_checks, Ed_Bookings);//writes the contents of entry_checks
    fclose(Ed_Bookings);//close the file.
    return UID;

}


int Read_Line(FILE *file,double Line_Num) {
    char FILE_Storage[MAX_LENGTH];
    double Current_Position = 0;
    rewind(file);
    //Find the line
    while (fgets(FILE_Storage,sizeof(FILE_Storage), file) != NULL) {
        if (Current_Position == Line_Num) {
            sprintf(READL, "%s", FILE_Storage);//changes READL
            return 1;//Success
        }
        Current_Position++;
    }
    return 0;//FAIL
}


int Login() {
    //Variables
    printf("%s%s%sENTER LOGIN CREDENTIALS\n",Top_Tile,Top_Subtile,Top_divider);
    int PASSED = 0;
    char Password[50],Username[50];
    while (PASSED == 0) {
        //INPUTS
        printf("\nPlease Enter Username:");
        scanf("%s",Username);
        printf("Please Enter Password:");
        scanf("%s",Password);

        //Defaults
        if (strcmp(Username,Default_Admin_Username)==0) {
            if (strcmp(Password,Default_Admin_Password)==0) {
                printf("Successful Login...\n");
                Sleep(600);
                printf("%s",TAB_divider);
                return 1;
            }
        }else if (strcmp(Username,Default_Employee_Username)==0) {
            if (strcmp(Password,Default_Employee_Password)==0) {
                printf("Successful Login...\n");
                Sleep(600);
                printf("%s",TAB_divider);
                PASSED = 1;
            }
        }



        if (PASSED == 0) {
            printf("ERROR Incorrect Username or Password\n");
        }
    }
    return 0;
}

void BookingCosting(int UID) {

}

int GrabBookings(int UID,int Fetch_type) {
    //Fetch_type 0-reads information on amount of person and activity
    //type       1-reads the Fullname, date and time, along with info from type 0
    //type       2-reads ALL Information
    //the Information is stored in Booking_data
    FILE *READ_Bookings = fopen("Bookings.txt","r");
    double line_num = 2;
    int found = 0;
    char Storage[MAX_LENGTH];
    int  Hold =1;
    while (found == 0) {
        if (Read_Line(READ_Bookings, line_num)!=0) {

            sprintf(Storage, "%s",READL);
            Storage[strcspn(Storage, "U")] = '0';
            Storage[strcspn(Storage, "I")] = '0';
            Storage[strcspn(Storage, "D")] = '0';
            Storage[strcspn(Storage, ";")] = '0';
            Storage[strcspn(Storage, "\n")] = '\0';//remove \n and UID; from the str
            printf("%c",Storage[4]);
            sscanf(Storage,"%d",&Hold);
            if (Hold == UID) {
                found = 1;
            }else {
                line_num = line_num +11;
            }
        }else {
            break;
        }
    }
    if (found == 1) {
        switch (Fetch_type) {
            case 0:
                Hold = 0;
                Storage[strcspn(Storage, )] = '0';
                Read_Line(READ_Bookings,line_num+7);
                sscanf(READL, "%d",&Hold);
                Booking_data.Participants = Hold;
                printf("%d",Booking_data.Participants);
                break;
            case 1:
            case 2:
                break;

        }
    }
    fclose(READ_Bookings);
    return found;
}