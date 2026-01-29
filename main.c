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
    int  Hours;
}Booking_data;

struct Receipts_Data {
    int    Hours;
    int    Participants;
    int    Cost;
    char   Discount[MAX_LENGTH];
    double Total_Cost;
    char   Payment_status[MAX_LENGTH];
}Receipts_data;

const char acts[9][19] ={
    "Hiking","Golfing","Scuba Diving",
    "Jet Skiing","Horse Backing","Kayaking",
    "Boat Tours","Forest Trails","Yoga on the Beach",};

const int act_cost[10]={//each correlates to the price of activities in acts per(session/hour)
    125,150,100,100,75,125,150,175,75};

//Displays
const char  Top_Tile[]    = "\t\t    Welcome to sister island's\n";
const char  Top_Subtitle[] = "\t\t\t  Booking System\n";
const char  Top_divider[] = "********************************************************************************\n";
const char  View_divider[]= "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
const char  TAB_divider[] = "--------------------------------------------------------------------------------\n"
                            "------------------------------------NEW--TAB------------------------------------\n"
                            "--------------------------------------------------------------------------------\n\n";
//Screen layouts :
const char  Emp_Screen[]  = "\t\t\t1---Create Booking\n\t\t\t2---View Current Bookings\n\t\t\t3---Cancel Booking"
                            "\n\t\t\t4---EXIT\n";
const char  Adm_Screen[]  = "\t\t\t1---View Reports\n\t\t\t2---View Current Bookings\n\t\t\t3---Create Employee Accounts"
                            "\n\t\t\t4---EXIT\n";
const char  BC_Subtitle[] = "\t\t\t  Booking Creation\n";
const char  BCP_Subtitle[]= "\t\t\t  Booking Pricing\n";
const char  CB_Subtitle[] = "\t\t\t Current Bookings\n";

//Functions
int Login();
int Create_Bookings();
void Activity_View();
void Booking_Costing(int UID,int Hours);
int Grab_Bookings(int UID,int Fetch_type);
int Read_Line(FILE *file,double Line_Num);
void Change_status(int UID);

//to make
int Cancel_Booking(int UID);
void Create_Employees_logins();
void Reports();

int main(void) {
    int Account = 0;
    //Account = Login();
    Cancel_Booking(12);

    //FILES
    FILE *IN_Bookings = fopen("Bookings.txt", "a");
    fclose(IN_Bookings);
    FILE *IN_Receipts = fopen("Receipts.txt", "a");
    fclose(IN_Receipts);

    //Variables
    char In1[] = "Enter :-",Store[50];
    int Hold= 0,UID,
    Checked = 0,
    Running= 1;
    while (Running == 1) {
        Checked = 1;
        if (Account == 0) {
            printf("%s%s%s%s",
                Top_Tile,Top_Subtitle,Top_divider,Emp_Screen);
            while (Checked ==1) {
                Hold =0;
                printf("%s",In1);
                scanf("%s",Store);
                sscanf(Store, "%d", &Hold);
                switch (Hold) {
                    case 1:
                        UID = Create_Bookings();//runs the create booking function
                        Booking_Costing(UID,Booking_data.Hours);//runs the Booking cost function
                        Checked = 0;
                        break;
                    case 2:
                        Checked = 0;
                        Activity_View();
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
                Top_Tile,Top_Subtitle,Top_divider,Adm_Screen);
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

    return 0;
}


// Functions
int Create_Bookings() {
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
    int Num_Hold =0,Querying=0,
    UID,activity = 1;
    char Storage[MAX_LENGTH];
    char FStorage[MAX_LENGTH*9];
    char Questions[9][35] ={"Enter Activity No.#","Frist Name:","Last Name:","Person's age:","Phone No.#","Email Address :"
        ,"Number of persons Booking for:","Booking Date (dd/mm/yyyy) :","Time in (23:00):~"};

    printf("%s%s%s%sActivities\n1--%s\t   2--%s\t\t3--%s\n"
           "4--%s\t   5--%s\t6--%s\n7--%s\t   8--%s\t9--%s\n\nEnter clients Info:\n",
        TAB_divider,Top_Tile,BC_Subtitle,Top_divider,acts[0],acts[1],acts[2],acts[3],acts[4],acts[5],acts[6]
        ,acts[7],acts[8]);
    //print the screen along with activities


    //Booking entries
    for (int i = 0 ; i < 9 ; i++) {
        Querying = 1;
        while (Querying ==1) {
            printf("%s",Questions[i]);
            scanf("%s",Storage);
            switch (i) {
                case 0:sscanf(Storage, "%d", &Num_Hold);
                    if (Num_Hold != 0 && Num_Hold < 10) {
                        Querying = 0;
                        sprintf(FStorage, "%d%d", Num_Hold,entry_counter);//Creates UID Using the activity number
                        sscanf(FStorage, "%d", &UID);//and how many bookings were entered
                        sprintf(FStorage, "\nUID;%d",UID);//copies UID
                        sprintf(Storage, "%s", acts[Num_Hold-1]);// makes the booking number the word
                        activity = Num_Hold;

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
    if (activity != 1 && activity != 7 && activity != 8) {
        Querying = 1;
        while (Querying == 1) {
            printf("How many hour to be booked");
            if (activity > 8) {
                printf(" (5-Hours MAX):-\n");
            }else {
                printf(" (3-Hours MAX):-\n");
            }
            scanf("%s",Storage);
            sscanf(Storage, "%d", &Num_Hold);
            if (Num_Hold > 0 && Num_Hold < 6 && activity > 8 || Num_Hold > 0 && Num_Hold < 4 ) {
                Booking_data.Hours = Num_Hold;
                Querying = 0;
            }
        }

    }else {
        Booking_data.Hours = 1;

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
    printf("%s%s%sENTER LOGIN CREDENTIALS\n",Top_Tile,Top_Subtitle,Top_divider);
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


int Grab_Bookings(int UID,int Fetch_type) {
    //Fetch_type 0-reads information on amount of person and activity
    //type       1-reads the Fullname, date and phone number, along with info from type 0
    //type       2-reads ALL Information for booking including Cost, discount and Payment status
    //type       3-reads Report data
    //the Information is stored in Booking_data

    //variables
    FILE *READ_Bookings = fopen("Bookings.txt","r");
    FILE *READ_Receipts;
    double line_num = 2;//UID start 3 line away from the top
    double Receipts_line_Num=0;
    double Holder;
    int found = 0,
    Hold = 1;
    char Storage[MAX_LENGTH],
    str_end ='\0';//ends the string deleting all chars to the right

    while (found == 0) {
        if (Read_Line(READ_Bookings, line_num)!=0) {
            sprintf(Storage, "%s",READL);
            Storage[strcspn(Storage, "U")] = '0';
            Storage[strcspn(Storage, "I")] = '0';
            Storage[strcspn(Storage, "D")] = '0';
            Storage[strcspn(Storage, ";")] = '0';
            Storage[strcspn(Storage, "\n")] = '\0';//remove \n and UID; from the str
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
            case 2:
                READ_Receipts= fopen("Receipts.txt","r");
                while (Read_Line(READ_Receipts,Receipts_line_Num)!=0) {
                    sprintf(Storage, "%s",READL);
                    Storage[strcspn(Storage, "\n")] = '\0';//remove \n and UID; from the str
                    sscanf(Storage,"%d",&Hold);
                    if (Hold == UID) {
                        break;
                    }
                    Receipts_line_Num = Receipts_line_Num +8;
                }
                //gets info for Total
                Read_Line(READ_Receipts,Receipts_line_Num+5);
                sscanf(READL, "%lf",&Holder);
                Receipts_data.Total_Cost = Holder;
                //gets info for Discount
                Read_Line(READ_Receipts,Receipts_line_Num+4);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Receipts_data.Discount,"%s",Storage);
                //gets info for Payment_status
                Read_Line(READ_Receipts,Receipts_line_Num+6);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Receipts_data.Payment_status,"%s",Storage);
                //close the file
                fclose(READ_Receipts);


                //gets info for Age
                Read_Line(READ_Bookings,line_num+4);
                sscanf(READL, "%d",&Hold);
                Booking_data.Age = Hold;
                //gets info for Time
                Read_Line(READ_Bookings,line_num+9);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Booking_data.Time,"%s",Storage);
                //gets info for Email
                Read_Line(READ_Bookings,line_num+6);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Booking_data.Email,"%s",Storage);
            case 1:
                Hold = 0;

                //gets info for FName
                Read_Line(READ_Bookings,line_num+2);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Booking_data.FName,"%s",Storage);
                //gets info for LName
                Read_Line(READ_Bookings,line_num+3);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Booking_data.LName,"%s",Storage);
                //gets info for Date
                Read_Line(READ_Bookings,line_num+8);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Booking_data.Date,"%s",Storage);
                //gets info for Phone Number
                Read_Line(READ_Bookings,line_num+5);
                sprintf(Storage, "%s",READL);
                Storage[strcspn(Storage, "\n")] = '\0';
                sprintf(Booking_data.Phone_Num,"%s",Storage);

            case 0:
                Hold = 0;

                //gets info for activity
                sprintf(Storage,"%d",UID);
                Storage[1] = str_end;
                sscanf(Storage, "%d",&Hold);
                Booking_data.Activity = Hold;
                Hold = 0;

                //gets info for Participants
                Read_Line(READ_Bookings,line_num+7);
                sscanf(READL, "%d",&Hold);
                Booking_data.Participants = Hold;

                /*printf("%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n",
                    Booking_data.Activity,Booking_data.Participants,Booking_data.Age,Booking_data.FName,Booking_data.LName
                    ,Booking_data.Date,Booking_data.Time,Booking_data.Email,Booking_data.Phone_Num);*/
                break;
            default:break;

        }
    }
    fclose(READ_Bookings);
    return found;
}

void Booking_Costing(int UID,int Hours) {
    printf("%s%s%s%s",TAB_divider,Top_Tile,BCP_Subtitle,Top_divider);
    double Price;
    int paid = 1;
    char percent_sign = '%',store[1],Discount[50];
    Grab_Bookings(UID,0);
    if (Booking_data.Participants > 5) {//25% Discount
        printf("BOOKING COST:\n\t Hours :%d\n\t Participants :%d\n\t = %d x %d x Cost",
            Hours,Booking_data.Participants,Hours,Booking_data.Participants);
        Price = Hours * Booking_data.Participants ;
        printf("\n\t = %.0lf x Cost\n\t Cost = $%d \n\t SubTotal = %.0lf x $%d",
            Price,act_cost[Booking_data.Activity-1],Price,act_cost[Booking_data.Activity-1]);
        Price = Price * act_cost[Booking_data.Activity-1];
        printf("\n\t SubTotal = $%.2lf \n\t Total = $%.2lf - (25%c--DISCOUNT)",Price,Price,percent_sign);
        Price = Price * 0.85;
        printf("\n\t TOTAL = $%.2lf\n\n",Price);
        sprintf(Discount,"%s","Discounted--25%");

    }else if (Booking_data.Participants > 2) {//10% Discount
        printf("BOOKING COST:\n\t Hours :%d\n\t Participants :%d\n\t = %d x %d x Cost",
            Hours,Booking_data.Participants,Hours,Booking_data.Participants);
        Price = Hours * Booking_data.Participants ;
        printf("\n\t = %.0lf x Cost\n\t Cost = $%d \n\t SubTotal = %.0lf x $%d",
            Price,act_cost[Booking_data.Activity-1],Price,act_cost[Booking_data.Activity-1]);
        Price = Price * act_cost[Booking_data.Activity-1];
        printf("\n\t SubTotal = $%.2lf \n\t Total = $%.2lf - (10%c--DISCOUNT)",Price,Price,percent_sign);
        Price = Price * 0.9;
        printf("\n\t TOTAL = $%.2lf\n\n",Price);
        sprintf(Discount,"%s","Discounted--10%");

    }else {//No Discount
        printf("BOOKING COST:\n\t Hours :%d\n\t Participants :%d\n\t = %d x %d x Cost",
            Hours,Booking_data.Participants,Hours,Booking_data.Participants);
        Price = Hours * Booking_data.Participants ;
        printf("\n\t = %.0lf x Cost\n\t Cost = $%d \n\t Total = %.0lf x $%d",
            Price,act_cost[Booking_data.Activity-1],Price,act_cost[Booking_data.Activity-1]);
        Price = Price * act_cost[Booking_data.Activity-1];
        printf("\n\t TOTAL = $%.2lf\n\n",Price);
        sprintf(Discount,"%s","NO-Discount");
    }

    printf("\tConfirm Payment Status\n\t1--PAYMENT PAID\n\t2--PENDING PAYMENT");
    while(TRUE) {
        printf("\n ENTER...");
        scanf("%s",store);
        sscanf(store,"%d",&paid);
        if (paid > 0 && paid < 3) {
            FILE *IN_Receipts = fopen("Receipts.txt", "a");
            fprintf(IN_Receipts, "%d\n",UID);
            fprintf(IN_Receipts, "Hours :%d\n",Hours);
            fprintf(IN_Receipts, "Participants :%d\n",Booking_data.Participants);
            fprintf(IN_Receipts, "Cost :$%d\n",act_cost[Booking_data.Activity-1]);
            fprintf(IN_Receipts, "%s\n",Discount);
            fprintf(IN_Receipts, "%.2lf\n",Price);
            if (paid == 1) {
                fprintf(IN_Receipts, "PAID\n\n");
            }else {
                fprintf(IN_Receipts, "PENDING\n\n");
            }
            fclose(IN_Receipts);
            break;
        }
    }
}

void Activity_View() {

    //variables
    FILE *READ_Bookings = fopen("Bookings.txt","r");
    int line_num = 2//UID start 3 line away from the top
    , UID = 1,Hold,running = 1;
    char Storage[MAX_LENGTH];

    printf("%s%s%s%s\n",
                TAB_divider,Top_Tile,CB_Subtitle,Top_divider);

    while (Read_Line(READ_Bookings, line_num)!=0) {
        if (line_num != 2) {//for better looking GUI
            printf("%s",View_divider);
        }
        //Get UID
        sprintf(Storage, "%s",READL);
        Storage[strcspn(Storage, "U")] = '0';
        Storage[strcspn(Storage, "I")] = '0';
        Storage[strcspn(Storage, "D")] = '0';
        Storage[strcspn(Storage, ";")] = '0';
        Storage[strcspn(Storage, "\n")] = '\0';//remove \n and UID; from the str
        sscanf(Storage,"%d",&UID);

        //Get Some Booking Data
        Grab_Bookings(UID,1);
        if (Booking_data.Activity == 9) {
            printf("%s \t\t UID;%d\n",acts[Booking_data.Activity-1],UID);
        }else {
            printf("%s \t\t\t\t UID;%d\n",acts[Booking_data.Activity-1],UID);
        }
        printf(" %s %s , %s , %s\n",Booking_data.FName,Booking_data.LName,Booking_data.Phone_Num,Booking_data.Date);

        line_num = line_num +11;
    }
    printf("\n%s",Top_divider);
    if (line_num == 2) {
        printf("Sorry no Bookings Found...\n");
        Sleep(500);
    }else {

        while (TRUE) {
            printf("Enter (-1) to EXIT\n");
            printf(" Enter booking ID...");
            scanf("%s",Storage);
            sscanf(Storage,"%d",&UID);
            if (UID == -1) {
                printf("Closing Program...\n");
                Sleep(500);
                break;
            }
            if (UID != 0){
                if (Grab_Bookings(UID,2) != 0) {
                    printf("%s\n",Top_divider);
                    if (Booking_data.Activity == 9) {
                        printf("Event Booked : %s \t Booking Details \nBooking UID# %d ",
                               acts[Booking_data.Activity-1],UID);
                    }else{
                        printf("Event Booked : %s \t\t\t Booking Details \nBooking UID# %d ",
                               acts[Booking_data.Activity-1],UID);}

                    printf("\t\t\t ---------------\n---------------");
                    printf("\t\t\t\t Name: %s %s  \nPress : 1--Confirm Payment \t\t Age: %d\n\t2--Cancel \t\t\t No.# %s \n\t"
                           "3--Exit \t\t\t Participants : %d  \n",
                           Booking_data.FName,Booking_data.LName,Booking_data.Age,Booking_data.Phone_Num,Booking_data.Participants);
                    printf("\t\t\t\t\t Date : %s \n\t\t\t\t\t Time : %s\n",
                           Booking_data.Date,Booking_data.Time);
                    printf("\t\t\t\t\t Payment Status : %s \n\t\t\t\t\t %s \n\t\t\t\t\t Total Cost :$%0.2lf\n",
                           Receipts_data.Payment_status,Receipts_data.Discount,Receipts_data.Total_Cost);

                    running = 1;
                    while (running == 1) {
                        printf("Enter...");
                        scanf("%s",Storage);
                        sscanf(Storage,"%d",&Hold);
                        switch (Hold) {
                            case 1:
                                Change_status(UID);
                                running = 0;
                                break;
                            case 2:
                                Cancel_Booking(UID);
                                running = 0;
                                break;
                            case 3:
                                running = 0;
                                printf("Closing Program...\n");
                                break;
                            default:
                                printf("Invalid Entry\n");
                                break;

                        }
                    }

                }else{
                    printf("Error UID Not Found\n");
                }
            }
        }
    }

    fclose(READ_Bookings);
    printf("%s",TAB_divider);
}

int Cancel_Booking(int UID) {
    //variables
    FILE *ED_Bookings = fopen("Bookings.txt", "r");
    FILE *Temp_file = fopen("temp.txt", "w");

    int line_Num = 2,
    Current_line = 0,
    Hold;
    char Storage[MAX_LENGTH];

    /*char entry_checks[MAX_LENGTH];
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
    fclose(Ed_Bookings);*/



    while (Read_Line(ED_Bookings,line_Num)!=0) {
        sprintf(Storage, "%s",READL);
        Storage[strcspn(Storage, "U")] = '0';
        Storage[strcspn(Storage, "I")] = '0';
        Storage[strcspn(Storage, "D")] = '0';
        Storage[strcspn(Storage, ";")] = '0';
        Storage[strcspn(Storage, "\n")] = '\0';//remove \n and UID; from the str
        sscanf(Storage,"%d",&Hold);

        if (Hold == UID) {
            break;
        }

        line_Num = line_Num +11;
    }
    if (Read_Line(ED_Bookings,line_Num+11 )==0) {//check if this is the last entry and pushes the pointer back
        line_Num--;                              //to aviod formating issues
    }

    rewind(ED_Bookings); // puts the pointer back to the start
    // copy all contents to the temporary file other except specific line
    while (!feof(ED_Bookings))
    {
        strcpy(Storage, "\0");//empty's the var
        fgets(Storage, MAX_LENGTH, ED_Bookings);//gets contents of file

        if (!feof(ED_Bookings))
        {

            if (Current_line >= line_Num  && Current_line <= (line_Num + 10 ))
            {
                printf("1");
            }
            else
            {
                fprintf(Temp_file, "%s", Storage);

            }
            Current_line++;
        }
    }
    fclose(ED_Bookings);
    fclose(Temp_file);
    remove("Bookings.txt");
    rename("temp.txt", "Bookings.txt");
    printf("Booking Updated successfully...\n");
    printf("%s\n",Top_divider);
    Sleep(600);
    return 0;
}

void Change_status(int UID) {
    //variables
    FILE *ED_Receipts = fopen("Receipts.txt", "r");
    FILE *Temp_file = fopen("temp.txt", "w");

    int line_Num = 0,
    Current_line = 0,
    Hold;
    char Storage[MAX_LENGTH];
    char New_data[MAX_LENGTH] ="80";

    printf("    <<Change Payment Status>>\n\t1--PAYMENT PAID\n\t2--PENDING PAYMENT");
    while (TRUE) {
        printf("\n ENTER...");
        scanf("%s",Storage);
        sscanf(Storage,"%d",&Hold);
        if (Hold > 0 && Hold < 3) {
            if (Hold == 1) {
                sprintf(New_data, "%s","PAID\n");
                break;
            }else {
                sprintf(New_data, "%s","PENDING\n");
                break;
            }
        }
    }


    while (Read_Line(ED_Receipts,line_Num)!=0) {
        sprintf(Storage, "%s",READL);
        Storage[strcspn(Storage, "\n")] = '\0';//remove \n and UID; from the str
        sscanf(Storage,"%d",&Hold);

        if (Hold == UID) {
            break;
        }
        line_Num = line_Num +8;
    }
    rewind(ED_Receipts); // puts the pointer back to the start
    line_Num = line_Num + 6 ; //gets contents of file

    // copy all contents to the temporary file other except specific line
    while (!feof(ED_Receipts))
    {
        strcpy(Storage, "\0");//empty's the var
        fgets(Storage, MAX_LENGTH, ED_Receipts);//gets contents of file

        if (!feof(ED_Receipts))
        {
            if (Current_line != line_Num)
            {
                fprintf(Temp_file, "%s", Storage);
            }
            else
            {
                fprintf(Temp_file, "%s", New_data);
            }
            Current_line++;
        }
    }
    fclose(ED_Receipts);
    fclose(Temp_file);
    remove("Receipts.txt");
    rename("temp.txt", "Receipts.txt");
    printf("Booking Updated successfully...\n");
    printf("%s\n",Top_divider);
    Sleep(600);
}