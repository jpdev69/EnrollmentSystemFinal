#include <iostream>             // library use for the implementation of "input and output" at terminal
#include <chrono>               // library use to represent 'time'
#include <thread>               // library use for sleep function - loadingAnimation
#include <string>               // libary use for integer conversion to string

#include "sysMainFinal.h"        // custom library, use to implement function as 'global'
using namespace std;            // explicitly indicate the use of STANDARD LIBRARY(std) in C++ compiler

// global variable
int userID=0;                   // initialize to zero - use for userID login
char selectedSection='a';       // declare - 'homepage controller'
string enteredCourse="";           // monitors enteredCourse - BSIS, BSCS, BSIT(2 Specialize), BLIS
static string enrolledSubject="";         // declare - determine enrolled Subject

bool paid=false;                // tuition hasn't been paid yet - default - FALSE
float accountBalance=0.00f;     // bank accountBalance

void banner() {
    string display = " _______ _______ ______ _______ _____   _____   _______ _______ _______ _______      _______ ___ ___ _______ _______ _______ _______\n"
                "|    ___|    |  |   __ |       |     |_|     |_|   |   |    ___|    |  |_     _|    |     __|   |   |     __|_     _|    ___|   |   |\n"
                "|    ___|       |      |   -   |       |       |       |    ___|       | |   |      |__     |\\     /|__     | |   | |    ___|       |\n"
                "|_______|__|____|___|__|_______|_______|_______|__|_|__|_______|__|____| |___|      |_______| |___| |_______| |___| |_______|__|_|__|\n"
                "                                                                                                                                      \n"
                "                                       College of Computing Studies, Computer Science                                                 \n"
                "                                       Programmer: CHRISTIAN JOSHUA B. PARTIDO, BSCS 1-1                                              \n"
                "                                                                                                                                      \n"
                "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n";
    

    cout<<display;
}

// feature Function - animation for loadingScreen
void loadingAnimation(string text) {   
    for(char c:text) {                                          // iterate and display each character from a given text
        cout<<c;                                                
        this_thread::sleep_for(chrono::milliseconds(1));        // uses a sleep function featured from 'thread', to stop the execution per sey; given time(milliseconds)
    }                                            
}

// STEP 1: webPage function
void webPage() {

    bool selected=false;
    while(!selected) {
        cout<<"CREATE AN ACCOUNT TO PROCEED.\n"
            "ENTER [R] for REGISTER\n";

        char ask;
        cin>>ask;               // reads input for 'Register'
        ask=toupper(ask);

        switch(ask) {
            case 'R':
                selected=true;
                createAccount();
            default:
                cout<<"ERROR! TRY AGAIN.\n";
                continue;
        }
    }
}

// STEP 3: personalInfo function
void personalInfo(string firstName, string lastName, string age, string contactNumber) {

    cout<<"=========================================================================================================================\n"
        "   PERSONAL INFORMATION                                                                                                  \n"
        "=========================================================================================================================\n"
        "   FIRST NAME: "<<firstName<<"                                  LAST NAME: "<<lastName<<"                                \n"
        "                                                                                                                         \n"
        "_________________________________________________________________________________________________________________________\n"
        "   AGE: "<<age<<"                                              CONTACT NUMBER: "<<contactNumber<<"                       \n"
        "                                                                                                                         \n"
        "=========================================================================================================================\n";
    
    bool identityConfirmed=false;             // identityConfirmed is necessary to verify user authenticity
    while(!identityConfirmed) {               // assumes identity is not yet confirmed
        cout<<"Confirm identity?[Y/N]: ";

        char ask;
        cin>>ask;                             // reads identityConfirmation 
        ask=toupper(ask);                     // simplest method to convert character(char) to upperCase

        switch(ask) {
        case 'Y':
            identityConfirmed=true;          // set as 'true' - identity is confirmed
            login();                         // proceed to login
            break;
        case 'N':                       
            createAccount();                  // re-input request for personalInformation
            break;
        default:
            cout<<"INVALID!!\n";
            continue;
        }
    }
}

// STEP 2: createAccount function
void createAccount() {

    cout<<"Kindly Indicate First Name: ";
    string firstName;                         
    cin>>firstName;                           // reads firstName

    cout<<"Including Your Last Name: ";
    string lastName;        
    cin>>lastName;                            // reads lastName

    cout<<"Input your age: ";
    string age;                               // uses string instead, to represent 'nominal' - identification
    cin>>age;

    cout<<"Input contact number: +63 ";       // uses string as well, to represent 'nominal' - identification
    string contactNumber;
    cin>>contactNumber;

    // creates userID from completeName
    int calculatedName, calculatedAge;                        // use given variable to create userID
    string completeName=firstName +""+lastName;               // adds firstName & lastName to create completeName
    for(int i=0;i<completeName.length();i++) {                // iterate from all characters at completeName to find total length
        calculatedName+=i;
        for(int j=0;j<age.length();j++) {                     // iterate from all characters at age to find total length
            calculatedAge+=j;
        }
    }
    userID=calculatedName*calculatedAge;                      // multiply together to create a userID - UPDATES global variable userID
    cout<<"YOUR GIVEN USER ID IS: "<<userID<<"\n";

    personalInfo(firstName, lastName, age, contactNumber);    // validates input to confirm identity

}

// STEP 4: login
void login() {
    while(true) {
        cout<<"TO GAIN ACCESS, ENTER YOUR GIVEN USERID: ";

        int ask;                               
        cin>>ask;                             // reads password input

        if(ask==userID) {
            homepageSection();
        } else {
            cout<<"INVALID!! TRY AGAIN.\n";
            continue;
        }
    }
}

// STEP 5: homepageSection >> REVIEWPAGE SECTION
void homepageSection() {
    bool sectionSelected=false;
    while(!sectionSelected) {
        
        cout<<"[A]    VIEW ENROLLMENT STATUS\n"
            "[B]    VIEW AVAILABLE COURSES\n"
            "[C]    ENROLL A PROGRAM SEMESTER\n"
            "[D]    EXIT\n";

        char ask;
        cin>>ask;                   // reads input for sectionSelected
        ask=toupper(ask);

        switch(ask) {
            case 'A':                   // enrollmentStatus()
                sectionSelected=true;
                selectedSection='a';
                enrollmentStatus();
            case 'B':                   // courses() - either viewCourses or enrollCourse
                sectionSelected=true;
                selectedSection='b';            
                courses();              // thisFunction is dependent to coursesFunctions : bsis(),bscs(),bsitWMAD(),bsitNAS(),blis()
            case 'C':                   // courses() - either viewCourses or enrollCourse
                sectionSelected=true;
                selectedSection='c';
                courses();              // thisFunction is dependent to coursesFunctions : bsis(),bscs(),bsitWMAD(),bsitNAS(),blis()
            case 'D':                   // exit the program
                sectionSelected=true;
                selectedSection='d';
                exit(1);
            default:
                cout<<"TRY AGAIN.\n";
                continue;
        }
    }
}



 // SECTION A   
void enrollmentStatus() {                        // checks wether you have enrolledSubject
    if(enrolledSubject.length()>0&&paid==true) {             // view enrolledSubject status
        cout<<"You are currently at these semester subjects: \n"<<enrolledSubject;
        bool answered=false;
        while(!answered){
            cout<<"PRESS [E] TO GET BACK TO HOMEPAGE\n";
            
            char ask;
            cin>>ask;                    // reads input to get back to homepage
            ask=toupper(ask);

            if(ask='E') {
                answered=true;
                homepageSection();
            } else {
                cout<<"TRY AGAIN.\n";
                continue;
            }
        }      
    } else {
        cout<<"You are not enrolled to any subject.\n";
        homepageSection();
    }
}

// SECTION B
void viewCourses(string fiYearfiSem, string fiYearsSem, string sYearfSem, string sYearsSem, string tYearfSem,
    string tYearsSem, string foYearfSem, string foYearsSem, string mYear) {

    if(enteredCourse=="BSIS"||"BSCS"||"WMAD"||"NAS"||"BLIS") {                  // review enteredCourse from course() function: display all
    cout<<fiYearfiSem<<fiYearsSem<<sYearfSem<<sYearsSem<<tYearfSem<<tYearsSem<<foYearfSem<<foYearsSem<<mYear;
    
        while(true) {
            cout<<"PRESS [E] TO GET BACK TO HOMEPAGE\n";

            char ask;
            cin>>ask;                   // reads input to get back to homepage
            ask=toupper(ask);           

            if(ask=='E') {
                homepageSection();
            } else {
                cout<<"Try Again.\n";
                continue;
            }
        }
    }
}

// SECTION C
void enrollCourse(string fiYearfiSem, string fiYearsSem, string sYearfSem, string sYearsSem, string tYearfSem, 
    string tYearsSem, string foYearfSem, string foYearsSem, string mYear) {    // proceed to enroll a semester

    while(true) {
        cout<<"Indicate YEAR LEVEL:\n";
        cout<<"Enter [first]   for FIRST  YEAR\n"
            "Enter [second]  for SECOND YEAR\n" 
            "Enter [third]   for THIRD  YEAR\n"
            "Enter [fourth]  for FOURTH YEAR\n";
    
        string ask;
        cin>>ask;                             // reads input for yearLevel

        cout<<"Indicate the SEMESTER you want to enroll.\n"
            "   [FIRSTSEM] [SECONDSEM] [MIDYEAR]\n";

        string pick;
        cin>>pick;                            // reads input for semesters


        // IMPLEMENTS NESTED IF-ELSE CONDITION
        if(ask=="first") {                    // Eliminate needs for midYear in firstYear - only firstSem, secondSem
            if(pick=="FIRSTSEM") {
                cout<<fiYearfiSem;
                enrolledSubject=fiYearfiSem;
                bankSystem();
                break;
            } else if(pick=="SECONDSEM") {
                cout<<fiYearsSem;
                enrolledSubject=fiYearsSem;
                bankSystem();
                break;
            } else {
                cout<<"INVALID!!\n";
                continue;
            }
        } else if(ask=="second") {            // Requires the inclusion of midYear in thirdYear
            if(pick=="FIRSTSEM") {
                cout<<sYearfSem;
                enrolledSubject=sYearfSem;
                bankSystem();
                break;
            } else if(pick=="SECONDSEM") {
                cout<<sYearsSem;
                bankSystem();
                enrolledSubject=sYearsSem;
                break;
            } else if(pick=="MIDYEAR") {      
                while(mYear.length()>0) {     // assumes midYear contains value, then display midYear
                    cout<<mYear;
                    enrolledSubject=mYear;
                    bankSystem();
                    break;
                }
                break;
            } else {
                cout<<"INVALID!!\n";
                continue;
            }
        } else if(ask=="third") {
            if(pick=="FIRSTSEM") {
                cout<<tYearfSem;
                enrolledSubject=tYearfSem;
                bankSystem();
                break;
            } else if(pick=="SECONDSEM") {
                cout<<tYearsSem;
                enrolledSubject=tYearsSem;
                bankSystem();
                break;
            } else if(pick=="MIDYEAR") {      
                while(mYear.length()>0) {     // assumes midYear contains value, then display midYear
                    cout<<mYear;
                    enrolledSubject=mYear;
                    bankSystem();
                    break; 
                }
                break;
            } else {
                cout<<"INVALID!!\n";
                continue;
            }
        } else if(ask=="fourth") {
            if(pick=="FIRSTSEM") {
                cout<<foYearfSem;
                enrolledSubject=foYearfSem;
                bankSystem();
                break;
            } else if(pick=="SECONDSEM") {
                cout<<foYearsSem;
                enrolledSubject=foYearsSem;
                bankSystem();
                break;
            } else if(pick=="MIDYEAR") {      
                while(mYear.length()>0) {     // assumes midYear contains value, then display midYear
                    cout<<mYear;
                    enrolledSubject=mYear;
                    bankSystem();
                    break; 
                }        
                break;
            } else {
                cout<<"INVALID!!\n";
                continue;
            }
        } else {
            cout<<"INVALID!!\n";
            continue;
        }
    }         
}


// REVIEW PAGE SECTION - 'important to access our database: courses'
void reviewPageSection(string firstYearFSem, string firstYearSSem, string secondYearFSem, string secondYearSSem, string thirdYearFSem, 
    string thirdYearSSem, string fourthYearFSem, string fourthYearSSem, string midYear) {

        bool answered=false;
        while(!answered) {
            if(selectedSection=='a') {          // DONE - enrollmentStatus
                answered=true;
                enrollmentStatus();          
            } else if(selectedSection=='b') {   // DONE - viewCourses
                answered=true;
                viewCourses(firstYearFSem, firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
            } else if(selectedSection=='c') {   // DONE - enrollCourse
                answered=true;
                enrollCourse(firstYearFSem, firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
            } else if(selectedSection=='d') {   // DONE - exitProgram
                string e="This program will exit..";
                loadingAnimation(e);
                exit(0);
            } else {
                cout<<"ERROR!!";
                continue;
            }
        }
}


void bsis() { // none
    string firstYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 4           |       Purposive Communication        |  3   |       3      |              |       None        |\n"
                "|      GEC 5           |       Art Appreciation               |  3   |       3      |              |       None        |\n"
                "|      IS 111          |       Introduction to Computing      |  3   |       2      |      1       |       None        |\n"
                "|      IS 112          |       Computer Programming 1         |  3   |       2      |      1       |       None        |\n"
                "|      IS GEC Elec 1   |       Health and Wellness Science    |  3   |       3      |              |       None        |\n"
                "|      IS GE Elec 2    |       Multicultural Education        |  3   |       3      |              |       None        |\n"
                "|      PE 1            |       Physical Activity Towards      |  2   |       2      |              |       None        |\n"
                "|                      |       Health Fitness                 |      |              |              |       None        |\n"
                "|                      |       (Movement Patterns)            |      |              |              |       None        |\n"
                "|      NSTP 1          |       CWTS/LTS/MS 1                  | (3)  |       3      |              |       None        |\n"
                "|                      |                        Total Units   | 20.0 |      18      |      2       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string firstYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 1           |       Understanding the Self         |  3   |       3      |              |       None        |\n"
                "|      GEC 2           |       readings in Philippine History |  3   |       3      |              |       None        |\n"
                "|      GEC 3           |       Mathematics in Modern World    |  3   |       3      |              |       None        |\n"
                "|      IS GEC Elec 2   |       Gender and Society             |  3   |       3      |              |       None        |\n"
                "|      IS INST 1       |       Climate Change and Disaster    |  2   |       2      |              |       None        |\n"
                "|                      |       Risk Management                |      |              |              |       None        |\n"
                "|      IS 121          |       Fundamentals of Information    |  3   |       3      |              |       IS 111      |\n"
                "|                      |       Systems                        |      |              |              |                   |\n"
                "|      IS 122          |       Computer Programming 2         |  3   |       2      |      1       |       IS 112      |\n"
                "|      PE 2            |       Physical Activity Towards      |  2   |       2      |              |       PE 1        |\n"
                "|                      |       Fitness II(Exercise Program)   |      |              |              |                   |\n"
                "|      NSTP 2          |       CWTS/LTS/MS 2                  | (3)  |       3      |              |       NSTP 1      |\n"
                "|                      |                       Total Units    | 22.0 |      21      |      1       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 6           |       Science, Techonology, Society  |  3   |       3      |              |       None        |\n"
                "|      GEC 8           |       The Contemporary World         |  3   |       3      |              |       None        |\n"
                "|      IS INST 2       |       Creative and Critical Thinking |  2   |       1      |      1       |       None        |\n"
                "|      IS 211          |       Data Structures and Algorithms |  3   |       2      |      1       |       IS 112      |\n"
                "|      IS 212          |       Professional Issues in         |  3   |       3      |              |   IS 111, IS 121  |\n"
                "|                      |       Information Systems            |      |              |              |                   |\n"  
                "|      IS 213          |       IT Infrastructure and Network  |  3   |       2      |      1       |   IS 111, IS 121  |\n"
                "|                      |       Technologies                   |      |              |              |                   |\n"
                "|      PE 3            |       Physical Activity Towards      |  2   |       2      |              |   PE 1, PE 2      |\n"
                "|                      |       Health Fitness III(Dance,      |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|      IS BPO 211      |       Business Communicaiton for BPO |  3   |       3      |              |       GEC 4       |\n"
                "|                      |                        Total Units   | 25.0 |      22      |      3       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 7           |       Ethics                         |  3   |       3      |              |       None        |\n"
                "|      GEC 9           |       Life and Works of Rizal        |  3   |       3      |              |       None        |\n"
                "|      IS GE Elec 1    |       Entrepreneurial Mind           |  3   |       3      |              |       None        |\n"
                "|      IS 221          |       Systems Analysis and Design    |  3   |       2      |      1       | 2nd Year Standing |\n"
                "|      IS 222          |       Financial Management           |  3   |       3      |              |       IS 214      |\n"
                "|      IS Elec 1       |       IT Audit and Controls          |  3   |       2      |      1       | 2nd Year Standing |\n"
                "|                      |       Systems                        |      |              |              |                   |\n"
                "|      PE 4            |       Physical Activity Towards      |  2   |       2      |              | PE 1, PE 2, PE 3  |\n"
                "|                      |       Health Fitness IV(Dance,       |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|      IS BPO 221      |       Service Culture                |  3   |       2      |      1       |    IS BPO 211     |\n"
                "|                      |                       Total Units    | 23.0 |      20      |      3       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      IS 311          |       Information Management         |  3   |       2      |      1       |       IS 211      |\n"
                "|      IS 312          |       Enterprise Architecture        |  3   |       2      |      1       |       IS 213      |\n"
                "|      IS 313          |       Business Process Management    |  3   |       3      |              |       IS 222      |\n"
                "|      IS 314          |       Quantitative Methods           |  3   |       3      |              | 3rd Year Standing |\n"
                "|      IS Elec 2       |       Data Mining                    |  3   |       2      |      1       | 3rd Year Standing |\n"
                "|      IS BPO 311      |       Fundamentals of Business       |  3   |       2      |      1       |     IS BPO 211,   |\n"  
                "|                      |       Process Outsourcing 101        |      |              |              |     IS BPO 221    |\n"
                "|      IS BPO 312      |       Principles of Systems Thinking |  3   |       3      |              |     IS BPO 211,   |\n"
                "|                      |                                      |      |              |              |     IS BPO 221    |\n"
                "|                      |                        Total Units   | 21.0 |      17      |      4       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      IS GEC Elec 3   |       Foreign Language 1             |  3   |       3      |              |       None        |\n"
                "|      IS 321          |       IS Project Management 1        |  3   |       3      |              |       IS 221      |\n"
                "|      IS 322          |       Evaluation of Business         |  3   |       3      |              |       IS 313      |\n"
                "|                      |       Performance                    |      |              |              |                   |\n"
                "|      IS 323          |       Capstone Project 1             |  3   |       2      |      1       | 3rd Year Standing |\n"
                "|      IS Elec 3       |       IT Security and Risk Management|  3   |       2      |      1       | 3rd Year Standing |\n"
                "|      IS GE Elec 3    |       Leadership and Management in   |  3   |       3      |              |       None        |\n"
                "|                      |       the Profession                 |      |              |              |                   |\n"
                "|      IS BPO 321      |       Fundamentals of Business       |  3   |       2      |      1       |     IS BPO 211    |\n"
                "|                      |       Process Outsourcing 102        |      |              |              |     IS BPO 221,   |\n"
                "|                      |                                      |      |              |              |     IS BPO 311    |\n"
                "|                      |                       Total Units    | 21.0 |      18      |      3       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      IS 411          |       IS Strategy, Management, and   |  3   |       3      |              | 4th Year Standing |\n"
                "|                      |       Acquisition                    |      |              |              |                   |\n"
                "|      IS 412          |       Applications Development and   |  3   |       2      |      1       | 4th Year Standing |\n"
                "|                      |       Emerging Technologies          |      |              |              |                   |\n"
                "|      IS 413          |       Capstone Project 2             |  3   |       2      |      1       |       IS 323      |\n"
                "|      IS Elec 4       |       IS Innovations and             |  3   |       2      |      1       | 4th Year Standing |\n"
                "|                      |       New Technologies               |      |              |              |                   |\n"
                "|      IS FOR 411      |       Foreign Language               |  3   |       3      |              |       None        |\n"
                "|                      |                        Total Units   | 15.0 |      12      |      3       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      IS 421          |       Practicum for Information       |  9  |       9      |              | 4th Year Standing |\n"
                "|                      |       Systems/Internship Program      |     |              |              |                   |\n"
                "|                      |       (486 hours)                     |     |              |              |                   |\n"
                "|                      |                       Total Units     |  9  |       9      |              |                   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |              TOTAL NUMBER OF UNITS    |156.0|              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string midYear="";

    reviewPageSection(firstYearFSem, firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
}
void bscs() { // mid year - third year
    string firstYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 1           |       Understanding the Self         |  3   |       3      |              |       None        |\n"
                "|      GEC 4           |       Purposive Communication        |  3   |       3      |              |       None        |\n"
                "|      GEC 3           |       Mathematics in Modern World    |  3   |       3      |              |       None        |\n"
                "|      CS 111          |       Introduction to Computing      |  3   |       2      |      1       |       None        |\n"
                "|      CS 112          |       Fundamentals of Programming    |  3   |       2      |      1       |       None        |\n"
                "|      GE Elec CS 1    |       health and Wellness Science    |  3   |       3      |              |       None        |\n"
                "|      PE 1            |       Physical Activity Towards      |  2   |       2      |              |       None        |\n"
                "|                      |       Health Fitness I               |      |              |              |       None        |\n"
                "|                      |       (Movement Patterns)            |      |              |              |       None        |\n"
                "|      NSTP 1          |       CWTS/LTS/MS 1                  |   3  |       3      |              |       None        |\n"
                "|                      |                        Total Units   | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string firstYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 2           |       Readings in Philippine History |  3   |       3      |              |       None        |\n"
                "|      GEC 8           |       The Contemporary World         |  3   |       3      |              |       None        |\n"
                "|      GEC Elec CS 2   |       Gender and Society             |  3   |       3      |              |       None        |\n"
                "|      GEC Elec CS 3   |       Foreign Language 1             |  3   |       3      |              |       None        |\n"
                "|      CS 121          |       Discrete Structures 1          |  3   |       3      |              |       None        |\n"
                "|      CS Inst 1       |       Climate Change and Disaster    |  2   |       2      |              |       None        |\n"
                "|                      |       Risk Management                |      |              |              |                   |\n"
                "|      CS 1 22         |       intermediate Programming       |  3   |       2      |      1       |       CS 112      |\n"
                "|      PE 2            |       Physical Activity Towards      |  2   |       2      |              |       PE 1        |\n"
                "|                      |       Fitness II(Exercise Program)   |      |              |              |                   |\n"
                "|      NSTP 2          |       CWTS/LTS/MS 2                  |  3   |       3      |              |       NSTP 1      |\n"
                "|                      |                       Total Units    | 25   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 6           |       Science, Techonology, Society  |  3   |       3      |              |       None        |\n"
                "|      GEC 7           |       Ethics                         |  3   |       3      |              |       None        |\n"
                "|      GEC 5           |       Art Appreciation               |  3   |       3      |              |       None        |\n"
                "|      CS 211          |       Discrete Structures 2          |  3   |       3      |              |       CS 121      |\n"
                "|      CS 212          |       Object-Oriented Programming    |  3   |       2      |      1       |       CS 122      |\n"
                "|      CS 213          |       Data Structures and Algorithms |  3   |       2      |      1       |       CS 122      |\n"
                "|                      |       Technologies                   |      |              |              |                   |\n"
                "|      CS 214          |       Calculus withAnalytic Geometry |  3   |       3      |              | 2nd Year Standing |\n"
                "|      PE 3            |       Health Fitness III(Dance,      |  2   |       2      |              |       PE 2        |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|                      |                        Total Units   | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      CS GE Elec 1    |       Entrepreneurial Mind           |  3   |       3      |              |       None        |\n"
                "|      CS GE Elec 4    |       Technical Writing              |  3   |       3      |              |       None        |\n"
                "|      CS 221          |       Algorithms and Complexity      |  3   |       3      |              |   CS 213, CS 211  |\n"
                "|      CS 222          |       Information Management         |  3   |       2      |      1       |       CS 112      |\n"
                "|      CS Elec 1       |       CS Elective 1                  |  3   |       2      |      1       | 2nd Year Standing |\n"
                "|      PE 4            |       Physical Activity Towards      |  2   |       2      |              | PE 1, PE 2, PE 3  |\n"
                "|                      |       Health Fitness IV(Dance,       |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|      CS DM 1         |       Statistical methods for Data   |  3   |       2      |      1       | 2nd Year Standing |\n"
                "|                      |       Analysis and Inference         |      |              |              |                   |\n"
                "|      CSDM 2          |       Data Preparation and Analysis  |  3   |       2      |      1       | 2nd Year Standing |\n"
                "|                      |                       Total Units    | 23.0 |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      CS 311          |       Automata Theory and Formal     |  3   |       3      |      0       |       CS 221      |\n"
                "|                      |       Languages                      |      |              |              |                   |\n"
                "|      CS 312          |       Architecture and Organization  |  3   |       2      |      1       |   CS 213, CS 121  |\n"
                "|      CS 313          |       Information Assurance and      |  3   |       2      |              |       CS 222      |\n"
                "|                      |       Security                       |      |              |              |                   |\n"
                "|      CS 314          |       Software Engineering 1         |  3   |       2      |      1       |   CS 222, CS 212  |\n"
                "|      CS 315          |       Social and Professional Issues |  3   |       3      |              |Co-requisite CS 314|\n"
                "|      CS DM 3         |       Data Mining Techniques Tools   |  3   |       2      |      1       | 3rd Year Standing |\n"  
                "|                      |       Process Outsourcing 101        |      |              |              |     IS BPO 221    |\n"
                "|      CS DM 4         |       Data Mining Applications       |  3   |       2      |      1       | 3rd Year Standing |\n"
                "|                      |                                      |      |              |              |     IS BPO 221    |\n"
                "|                      |                        Total Units   | 21   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      CS 321          |      CS Thesis Writing                |  3   |      2      |      1       |CS 313,CS GELEC 4  |\n"	
                "|      CS 324          |      Programming Languages            |  3   |      2      |      1       |     CS 213        |\n"	
                "|      CS 322          |      Software Engineering 2           |  3   |      2      |      1       |     CS 314        |\n"	
                "|      CS 323          |      Application Development and      |  3   |      2      |      1       |     CS 222        |\n"	
                "|                      |      Emerging Technologies            |      |             |              |                   |\n"	
                "|      CS ELEC 2       |      CS Elective 2                    |  3   |      2      |      1       | 3rd Year Standing |\n"	
                "|                      |                                       |      |             |              |                   |\n"	
                "|      CS DM 5         |      Algorithms for Data Mining       |  3   |      2      |      1       |    CS DM 3 & 4    |\n"	
                "|                      |                                       |      |             |              |                   |\n"	
                "|      CS DM 6         |      Data Mining Methodology          |  3   |      2      |      1       |    CS OM 3 & 4    |\n"
                "|                      |                        Total Units    | 21   |             |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string midYear="________________________________________________________________________________________________________________________\n"
                "                                                       THIRD YEAR                                                       \n"
                "MIDYEAR                                                                                                                 \n"
                "________________________________________________________________________________________________________________________\n"
                "|      CS GE Elec 2    |      Multicultural Education          |  3   |      3      |              |        None       |\n"	
                "|      GEC 9           |      The Life and Words of Rizal      |  3   |      3      |              |        None       |\n"	
                "|      CS GE Elec 3    |      Leadership and Management in     |  3   |      3      |              |        None       |\n"	
                "|                      |                        Total Units    |  9   |             |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      CS 412          |      Human Computer Interaction      |  3   |      2       |      1       |       CS 122      |\n"	
	            "|      CS 413          |      Network and Communications      |  3   |      2       |      1       |       CS 213      |\n"
	            "|      CS 414          |      Operating Systems               |  3   |      2       |      1       |       CS 213      |\n"	
	            "|      CS 411          |      CS Thesis Writing               |  3   |      2       |      1       |       CS 321      |\n"	
	            "|      CS ELEC 3       |      CS Elective 3                   |  3   |      2       |              | 4th Year Standing |\n"	
	            "|                      |                       Total Units    | 15   |              |              |                   |\n"	
                "________________________________________________________________________________________________________________________\n";
    string fourthYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      CS 421          |      Practicum(486 hours)            |  9   |              |              | 4th Year Standing |\n"
                "|                      |              TOTAL NUMBER OF UNITS   |169.0 |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";

    reviewPageSection(firstYearFSem,firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
}
void bsitWMAD() { // midyear - second year
    string firstYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 1           |       Understanding the Self         |  3   |       3      |              |       None        |\n"
                "|      GEC 4           |       Purposive Communication        |  3   |       3      |              |       None        |\n"
                "|      GEC 3           |       Mathematics in Modern World    |  3   |       3      |              |       None        |\n"
                "|      GEC ELEC IT 1   |       Health and Wellness            |  3   |       3      |              |       None        |\n"
                "|      CS 111          |       Introduction to Computing      |  3   |       2      |      1       |       None        |\n"
                "|      CS 112          |       Computer Programming 1         |  3   |       2      |      1       |       None        |\n"
                "|      PE 1            |       Physical Activity Towards      |  2   |       2      |              |       None        |\n"
                "|                      |       Health Fitness                 |      |              |              |       None        |\n"
                "|                      |       (Movement Patterns)            |      |              |              |       None        |\n"
                "|      NSTP 1          |       CWTS/LTS/MS 1                  | (3)  |       3      |              |       None        |\n"
                "|                      |                        Total Units   | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string firstYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 2           |       Readings in Philippine History |  3   |       3      |              |       None        |\n"
                "|      GEC 8           |       The Contemporary World         |  3   |       3      |              |       None        |\n"
                "|      GEC ELEC IT 2   |       Foreign Language               |  3   |       3      |              |       None        |\n"
                "|      IT 121          |       Computer Programming 2         |  3   |       2      |      1       |       IT 112      |\n"
                "|      IT 122          |       Human Computer Interaction 1   |  3   |       2      |      1       |       IT 112      |\n"
                "|      IT 123          |       Discrete Mathematics           |  3   |       3      |              |       GEC 3       |\n"
                "|      PE 2            |       Physical Activity Towards      |  2   |       2      |              |       PE 1        |\n"
                "|                      |       Fitness II(Exercise Program)   |      |              |              |                   |\n"
                "|      NSTP 2          |       CWTS/LTS/MS 2                  | (3)  |       3      |              |       NSTP 1      |\n"
                "|                      |                       Total Units    | 22.0 |      21      |      1       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 6           |       Science, Techonology, Society  |  3   |       3      |              |       None        |\n"
                "|      GEC 7           |       Ethics                         |  3   |       3      |              |       None        |\n"
                "|      GEC 5           |       Art Appreciation               |  3   |       3      |              |       None        |\n"
                "|      IS 211          |       Data Structures and Algorithms |  3   |       2      |      1       |       IT 121      |\n"
                "|      IS ELEC 1       |       Platform Technologies          |  3   |       2      |      1       |       IT 121      |\n"
                "|                      |       Information Systems            |      |              |              |                   |\n"  
                "|      IT ELEC 2       |       Object-Oriented Programming    |  3   |       2      |      1       |       IT 121      |\n"
                "|      IT BPO 1        |       Business Communication         |  3   |       3      |              |       None        |\n"
                "|      PE 3            |       Physical Activity Towards      |  2   |       2      |              |    PE 1, PE 2     |\n"
                "|                      |       Health Fitness III(Dance,      |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|                      |                        Total Units   | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      IT INST 1       |       Climate Change and             |  2   |       2      |              |       None        |\n"
                "|                      |       Disaster Risk Management       |      |              |              |       None        |\n"
                "|      GE ELEC IT 3    |       Foreign Language 2             |  3   |       3      |              |       None        |\n"
                "|      IT 221          |       Information Management         |  3   |       2      |      1       |       IT 121      |\n"
                "|      IT 222          |       Networking 1                   |  3   |       2      |      1       |     IT Elec 1     |\n"
                "|      IT 223          |       Quantitative Methods(including |  3   |       3      |              |  IT 211, IT 123   |\n"
                "|                      |       Modeling and Simulation)       |      |              |              |                   |\n"
                "|      IT 224          |       Integrative Programming and    |  3   |       2      |      1       |     IT Elec 1,    |\n"
                "|                      |       Techonologies                  |      |              |              |     IT Elec 2     |\n"
                "|      IT 225          |       Accounting for Information     |  3   |       3      |              |       None        |\n"
                "|                      |       Techonology                    |      |              |              |                   |\n"
                "|      IT APPDEV 1     |       Fundamental ofMobile Technology|  3   |       2      |      1       | IT Elec1,IT Elec2 |\n"
                "|      PE 4            |       Physical Activity Towards      |  2   |       2      |              | PE 1, PE 2, PE 3  |\n"
                "|                      |       Health Fitness IV(Dance,       |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|                      |                       Total Units    | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string midYear="________________________________________________________________________________________________________________________\n"
                "                                                       SECOND YEAR                                                       \n"
                "|MIDYEAR                                                                                                               |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      IT 226          |      Applications Development and     |  3   |      2      |      1       |        IT 221     |\n"	
                "|                      |      Emerging Technologies            |      |             |              |                   |\n"	
                "|      IT ELEC 3       |      Web Systems and Technologies     |  3   |      2      |      1       |        None       |\n"	
                "|                      |                        Total Units    |  6   |             |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      IT GE ELEC 1    |       The Entrepreneurial Mind       |  3   |       3      |      0       |       None        |\n"
                "|      IT 311          |       Advance Database Systems       |  3   |       2      |      1       |       IT 221      |\n"
                "|      IT 312          |       Networking 2                   |  3   |       2      |      1       |       IT 222      |\n"
                "|      IT 313          |       System Integration and         |  3   |       2      |      1       |       IT 224      |\n"
                "|                      |       Architecture                   |      |              |              |                   |\n"
                "|      IT 314          |       Information Assurance and      |  3   |       2      |      1       |       IT 224      |\n"
                "|                      |       Security                       |      |              |              |                   |\n"
                "|      IT APPDEV 2     |       Web Applications               |  3   |       2      |      1       |     IT Elec 3     |\n"
                "|      IT APPDEV 3     |       Mobile Applications            |  3   |       2      |      1       |    IT APPDEV 1    |\n"
                "|                      |                        Total Units   | 21   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 9           |      The Life and Works of Rizal      |  3   |      3      |              |       None        |\n"	
                "|      IT GE ELEC 2    |      Multicultural Education          |  3   |      3      |              |       None        |\n"	
                "|      IT 321          |      Information Assurance and        |  3   |      2      |      1       |       IT 314      |\n"
                "|                      |      Security 2                       |      |             |              |                   |\n"
                "|      IT 322          |      Social and Professional Issues   |  3   |      3      |              |       GEC 5       |\n"	
                "|      IT 323          |      Capstone Project and Research 1  |  3   |      2      |      1       |   IT 226, IT 314  |\n"	
                "|      IT APPDEV 4     |      Game Development                 |  3   |      2      |      1       |    IT APPDEV 2,   |\n"
                "|                      |                                       |      |             |              |    IT APPDEV 3    |\n"	
                "|      IT APPDEV 5     |      Cloud Computing                  |  3   |      2      |      1       |    IT APPDEV 2,   |\n"	
                "|                      |                                       |      |             |              |    IT APPDEV 3    |\n"	
                "|                      |                        Total Units    | 21   |             |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      IT GE ELEC 3    |      Leadership and Management in    |  3   |      3       |              |       None        |\n"	
	            "|                      |      the Profession                  |      |              |              |                   |\n"
	            "|      IT 411          |      System Administration and       |  3   |      2       |      1       |       IT 321      |\n"
	            "|                      |      Maintenance                     |      |              |              |                   |\n"
	            "|      IT ELEC 4       |      Human-Computer Interaction 2    |  3   |      2       |      1       |       IT 122      |\n"	
	            "|      IT 412          |      Capstone Project and            |  3   |      2       |      1       |       IT 323      |\n"	
	            "|                      |                       Total Units    | 12   |              |              |                   |\n"	
                "________________________________________________________________________________________________________________________\n";
    string fourthYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "SECOND SEMESTER                                                                                                         \n"
                "________________________________________________________________________________________________________________________\n"
                "|      IT 421          |      Practicum(486 hours)            |  9   |              |              | 4th Year Standing |\n"
                "|                      |              TOTAL NUMBER OF UNITS   | 163  |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";

    reviewPageSection(firstYearFSem,firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
}
void bsitNAS() { // midyear - second year
    string firstYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 1           |       Understanding the Self         |  3   |       3      |              |       None        |\n"
                "|      GEC 4           |       Purposive Communication        |  3   |       3      |              |       None        |\n"
                "|      GEC 3           |       Mathematics in Modern World    |  3   |       3      |              |       None        |\n"
                "|      GEC ELEC IT 1   |       Health and Wellness            |  3   |       3      |              |       None        |\n"
                "|      CS 111          |       Introduction to Computing      |  3   |       2      |      1       |       None        |\n"
                "|      CS 112          |       Computer Programming 1         |  3   |       2      |      1       |       None        |\n"
                "|      PE 1            |       Physical Activity Towards      |  2   |       2      |              |       None        |\n"
                "|                      |       Health Fitness                 |      |              |              |       None        |\n"
                "|                      |       (Movement Patterns)            |      |              |              |       None        |\n"
                "|      NSTP 1          |       CWTS/LTS/MS 1                  | (3)  |       3      |              |       None        |\n"
                "|                      |                        Total Units   | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string firstYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 2           |       Readings in Philippine History |  3   |       3      |              |       None        |\n"
                "|      GEC 8           |       The Contemporary World         |  3   |       3      |              |       None        |\n"
                "|      GEC ELEC IT 2   |       Foreign Language               |  3   |       3      |              |       None        |\n"
                "|      IT 121          |       Computer Programming 2         |  3   |       2      |      1       |       IT 112      |\n"
                "|      IT 122          |       Human Computer Interaction 1   |  3   |       2      |      1       |       IT 112      |\n"
                "|      IT 123          |       Discrete Mathematics           |  3   |       3      |              |       GEC 3       |\n"
                "|      PE 2            |       Physical Activity Towards      |  2   |       2      |              |       PE 1        |\n"
                "|                      |       Fitness II(Exercise Program)   |      |              |              |                   |\n"
                "|      NSTP 2          |       CWTS/LTS/MS 2                  | (3)  |       3      |              |       NSTP 1      |\n"
                "|                      |                       Total Units    | 22.0 |      21      |      1       |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 6           |       Science, Techonology, Society  |  3   |       3      |              |       None        |\n"
                "|      GEC 7           |       Ethics                         |  3   |       3      |              |       None        |\n"
                "|      GEC 5           |       Art Appreciation               |  3   |       3      |              |       None        |\n"
                "|      IS 211          |       Data Structures and Algorithms |  3   |       2      |      1       |       IT 121      |\n"
                "|      IS ELEC 1       |       Platform Technologies          |  3   |       2      |      1       |       IT 121      |\n"
                "|      IT ELEC 2       |       Object-Oriented Programming    |  3   |       2      |      1       |       IT 121      |\n"
                "|      IT BPO 1        |       Business Communication         |  3   |       3      |              |       None        |\n"
                "|      PE 3            |       Physical Activity Towards      |  2   |       2      |              |    PE 1, PE 2     |\n"
                "|                      |       Health Fitness III(Dance,      |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|                      |                        Total Units   | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      IT INST 1       |       Climate Change and             |  2   |       2      |              |       None        |\n"
                "|                      |       Disaster Risk Management       |      |              |              |       None        |\n"
                "|      GE ELEC IT 3    |       Foreign Language 2             |  3   |       3      |              |       None        |\n"
                "|      IT 221          |       Information Management         |  3   |       2      |      1       |       IT 121      |\n"
                "|      IT 222          |       Networking 1                   |  3   |       2      |      1       |     IT Elec 1     |\n"
                "|      IT 223          |       Quantitative Methods(including |  3   |       3      |              |  IT 211, IT 123   |\n"
                "|                      |       Modeling and Simulation)       |      |              |              |                   |\n"
                "|      IT 224          |       Integrative Programming and    |  3   |       2      |      1       |     IT Elec 1,    |\n"
                "|                      |       Techonologies                  |      |              |              |     IT Elec 2     |\n"
                "|      IT 225          |       Accounting for Information     |  3   |       3      |              |       None        |\n"
                "|                      |       Techonology                    |      |              |              |                   |\n"
                "|      IT NS 1         |       Cybersecurity Principles and   |  3   |       2      |      1       | IT Elec1, IT 222  |\n"
                "|                      |       Emerging Challenges            |      |              |              |                   |\n"
                "|      PE 4            |       Physical Activity Towards      |  2   |       2      |              | PE 1, PE 2, PE 3  |\n"
                "|                      |       Health Fitness IV(Dance,       |      |              |              |                   |\n"
                "|                      |       Sports, Group Exercise,        |      |              |              |                   |\n"
                "|                      |       Outdoor Adventure Activities)  |      |              |              |                   |\n"
                "|                      |                       Total Units    | 25   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string midYear="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|MIDYEAR                                                                                                               |\n"
                "|      IT 226          |      Applications Development and     |  3   |      2      |      1       |        IT 221     |\n"	
                "|                      |      Emerging Technologies            |      |             |              |                   |\n"	
                "|      IT ELEC 3       |      Web Systems and Technologies     |  3   |      2      |      1       |        None       |\n"	
                "|                      |                        Total Units    |  6   |             |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      IT GE ELEC 1    |       The Entrepreneurial Mind       |  3   |       3      |      0       |       None        |\n"
                "|      IT 311          |       Advance Database Systems       |  3   |       2      |      1       |       IT 221      |\n"
                "|      IT 312          |       Networking 2                   |  3   |       2      |      1       |       IT 222      |\n"
                "|      IT 313          |       System Integration and         |  3   |       2      |      1       |       IT 224      |\n"
                "|                      |       Architecture                   |      |              |              |                   |\n"
                "|      IT 314          |       Information Assurance and      |  3   |       2      |      1       |       IT 224      |\n"
                "|                      |       Security                       |      |              |              |                   |\n"
                "|      IT NS 2         |       Virtual Systems and Services   |  3   |       2      |      1       |       IT 222      |\n"
                "|                      |                        Total Units   | 18   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 9           |      The Life and Works of Rizal      |  3   |      3      |              |       None        |\n"	
                "|      IT GE ELEC 2    |      Multicultural Education          |  3   |      3      |              |       None        |\n"	
                "|      IT 321          |      Information Assurance and        |  3   |      2      |      1       |       IT 314      |\n"
                "|                      |      Security 2                       |      |             |              |                   |\n"
                "|      IT 322          |      Social and Professional Issues   |  3   |      3      |              |       GEC 5       |\n"	
                "|      IT 323          |      Capstone Project and Research 1  |  3   |      2      |      1       |   IT 226, IT 314  |\n"	
                "|      IT NS 3         |      Applied Networks                 |  3   |      2      |      1       |  IT 312, IT NS 2  |\n"
                "|      IT NS 4         |      Internet of Things               |  3   |      2      |      1       |    IT APPDEV 2,   |\n"	
                "|                      |                                       |      |             |              |  IT 312, IT NS 2  |\n"	
                "|                      |                        Total Units    | 21   |             |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      IT GE ELEC 3    |      Leadership and Management in    |  3   |      3       |              |       None        |\n"	
	            "|                      |      the Profession                  |      |              |              |                   |\n"
	            "|      IT 411          |      System Administration and       |  3   |      2       |      1       |       IT 321      |\n"
	            "|                      |      Maintenance                     |      |              |              |                   |\n"
	            "|      IT ELEC 4       |      Human-Computer Interaction 2    |  3   |      2       |      1       |       IT 122      |\n"	
	            "|      IT 412          |      Capstone Project and            |  3   |      2       |      1       |       IT 323      |\n"
	            "|      IT NS 5         |      Introduction to Network         |  3   |      3       |      0       | 4th Year Standing |\n"	
	            "|                      |                       Total Units    | 15   |              |              |                   |\n"	
                "________________________________________________________________________________________________________________________\n";
    string fourthYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "SECOND SEMESTER                                                                                                         \n"
                "________________________________________________________________________________________________________________________\n"
                "|      IT 421          |      Practicum(486 hours)            |  9   |              |              | 4th Year Standing |\n"
                "|                      |              TOTAL NUMBER OF UNITS   | 163  |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";

    reviewPageSection(firstYearFSem,firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
}
void blis() { // none
    string firstYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 1           |       Understanding the Self         |  3   |       3      |              |       None        |\n"
                "|      GEC 4           |       Purposive Communication        |  3   |       3      |              |       None        |\n"
                "|      GEC 7           |       Ethics                         |  3   |       3      |              |       None        |\n"
                "|      GEC 10          |       Kontekstwalisadong Komunikasyon|  3   |       3      |              |       None        |\n"
                "|                      |       sa Filipino                    |      |              |              |       None        |\n"
                "|      LIS 111         |       Introduction to Library and    |  3   |       3      |              |       None        |\n"
                "|                      |       Information Science            |      |              |              |       None        |\n"
                "|      LIS Elec 1      |       School/Academic Librarianship  |  3   |       3      |              |       None        |\n"
                "|      LIS ICT 111     |       Information Processing and     |  3   |       2      |      3       |       None        |\n"
                "|                      |       Hnadling in Libraries and      |      |              |              |       None        |\n"
                "|                      |       Information Centers            |      |              |              |       None        |\n"
                "|      PE 1            |       Physical Education 1           |  2   |       2      |              |       None        |\n"
                "|      NSTP 1          |       Civic Welfare Training Service |  3   |       3      |              |       None        |\n"
                "|                      |       MS, LTS                        |      |              |              |       None        |\n"
                "|                      |                        Total Units   | 26   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string firstYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FIRST YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 2           |       Readings in Philippine History |  3   |       3      |              |       None        |\n"
                "|      GEC 3           |       Mathematics in Modern World    |  3   |       3      |              |       None        |\n"
                "|      GEC 11          |       Filipino sa Iba't Ibang        |  3   |       3      |              |       GEC 10      |\n"
                "|                      |       Disiplina                      |      |              |              |       None        |\n"
                "|      INST 1          |       Climate Change and Disaster    |  3   |       3      |              |       None        |\n"
                "|                      |       Risk Management                |  3   |       3      |              |                   |\n"
                "|      LIS 121         |       Collection Management of       |  3   |       3      |              |       LIS 111     |\n"
                "|                      |       Information Resources          |      |              |              |       None        |\n"
                "|      LIS Elec 2      |       Special/Public Librarianship   |  3   |       3      |              |       None        |\n"
                "|      LIS ICT 121     |       Web Technologies in Libraries  |  3   |       2      |      3       |    LIS ICT 111    |\n"
                "|                      |       and Information Science        |      |              |              |       None        |\n"
                "|      PE 2            |       Physical Activity Towards      |  2   |       2      |              |       PE 1        |\n"
                "|                      |       Fitness II(Exercise Program)   |      |              |              |                   |\n"
                "|      NSTP 2          |       CWTS/LTS/MS 2                  |  3   |       3      |              |       NSTP 1      |\n"
                "|                      |                       Total Units    | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 6           |       Science, Technology, Society   |  3   |       3      |              |       None        |\n"
                "|      GEC 7           |       The Contemporary World         |  3   |       3      |              |       None        |\n"
                "|      LIS GE Elec 1   |       The Entrepreneurial Mind       |  3   |       3      |              |       None        |\n"
                "|      LIS 211         |       Information Resources and      |  3   |       3      |              |  LIS 111, LIS 121 |\n"
                "|                      |       Services                       |      |              |              |                   |\n"
                "|      LIS 212         |       Organization of Information    |  3   |       3      |              |  LIS 111, LIS 121 |\n"
                "|                      |       Resources                      |      |              |              |                   |\n"
                "|      LIS Elec 3      |       Preservation of Information    |  3   |       3      |              | 2nd Year Standing |\n"
                "|                      |       Reources                       |      |              |              |                   |\n"
                "|      LIS ICT 211     |       Digital Libraries and Resources|  3   |       2      |      3       |    LIS ICT 121    |\n"
                "|      PE 3            |       Physical Education 3           |  2   |       2      |              |       PE 2        |\n"
                "|                      |                        Total Units   | 26   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string secondYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       SECOND YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      GEC 5           |       Art Appreciation               |  3   |       3      |              |       None        |\n"
                "|      LIS GE Elec 2   |       Leadership and Management in   |  3   |       3      |              |       None        |\n"
                "|                      |       the Profession                 |      |              |              |                   |\n"
                "|      LIS 221         |       Information Resources and      |  3   |       3      |              |       LIS 211     |\n"
                "|                      |       Services II                    |      |              |              |                   |\n"
                "|      LIS 222         |       Organization of Information    |  3   |       3      |              |       LIS 212     |\n"
                "|                      |       Resources                      |      |              |              |                   |\n"
                "|      LIS 223         |       Library Materials for Children |  3   |       3      |              |       LIS 121     |\n"
                "|                      |       and Young Adults               |      |              |              |                   |\n"
                "|      LIS ICT 221     |       Programming Fundamentals       |  3   |       2      |      3       |    LIS ICT 211    |\n"
                "|                      |       Risk Management                |  3   |       3      |              |                   |\n"
                "|      LIS Elec 4      |       Philosophies and Principles of |  3   |       3      |              | 2nd Year Standing |\n"
                "|                      |       Teaching                       |      |              |              |       None        |\n"
                "|      PE 4            |       Physical Education 4           |  2   |       2      |              |       PE 3        |\n"
                "|                      |                       Total Units    | 23   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      GEC 9           |       Life and Works of Rizal        |  3   |       3      |              |       None        |\n"
                "|      LIS GE Elec 3   |       Environmental Science          |  3   |       3      |              |       None        |\n"
                "|      LIS 311         |       Indexing and Abstracting       |  3   |       3      |              |  LIS 212, LIS 222 |\n"
                "|      LIS 312         |       Introduction to Records        |  3   |       3      |              |       None        |\n"
                "|                      |       Management and Archives        |      |              |              |                   |\n"
                "|      LIS 313         |       Library and Information        |  3   |       3      |              |  LIS 221, LIS 222 |\n"
                "|                      |       Management  Academic Libraries |      |              |              |                   |\n"
                "|      LIS ICT 311     |       System Analysis and Design in  |  3   |       2      |      3       | 3rd Year Standing |\n"
                "|                      |       and Information Centers        |      |              |              |                   |\n"
                "|      LIS Elec 5      |       Educational Technology         |  3   |       3      |              | 3rd Year Standing |\n"
                "|      LIS Elec 6      |       Indigenous Knowledge and       |  3   |       3      |              | 3rd Year Standing |\n"
                "|                      |       Multiculturalism               |      |              |              |                   |\n"
                "|                      |                        Total Units   | 24   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string thirdYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       THIRD YEAR                                                     |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      LIS 321         |       Management of Libraries and    |  3   |       3      |              | LIS 111 - LIS 311 |\n"
                "|                      |       Information Centers            |      |              |              |                   |\n"
                "|      LIS 322         |       Information Literacy           |  3   |       3      |              | LIS 111, LIS 211, |\n"
                "|                      |                                      |      |              |              | LIS 221, LIS 212, |\n"
                "|                      |                                      |      |              |              |                   |\n"
                "|                      |                                      |      |              |              |                   |\n"
                "|      LIS 323         |       Information Sources and        |  3   |       3      |              |       LIS 313     |\n"
                "|                      |       Services in Academic           |      |              |              |                   |\n"
                "|                      |       Librarianship                  |      |              |              |                   |\n"
                "|      LIS ICT 321     |       Database Design for Libraries  |  3   |       2      |      3       |    LIS ICT 311    |\n"
                "|      LIS ICT 322     |       Introduction to Data Science   |  3   |       2      |      3       |    LIS ICT 311    |\n"
                "|      LIS Elec 7      |       Seminar in Library and         |  3   |       3      |              | 3rd Year Standing |\n"
                "|                      |       Information Science            |      |              |              |                   |\n"
                "|      LIS Elec 8      |       Foreign Language               |  3   |       3      |              | 3rd Year Standing |\n"
                "|                      |                       Total Units    | 21   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearFSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"

                "|FIRST SEMESTER                                                                                                        |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      Course No.      |             Course Title             | Unit |         No. of Units        |   Pre-requisite   |\n"
                "________________________________________________________________________________________________________________________\n"
                "|                      |                                      |      |   Lecture    |  Laboratory  |                   |\n"
                "|      LIS 411         |       Research Methods in Library    |  3   |       2      |      3       |  LIS 111-LIS 312  |\n"
                "|                      |       Information Science            |      |              |              |   LIS ICT 111 -   |\n"
                "|                      |                                      |      |              |              |    LIS ICT 322    |\n"
                "|                      |                                      |      |              |              |    LIS Elec 1 -   |\n"
                "|                      |                                      |      |              |              |    LIS Elec 7     |\n"
                "|      LIS 412         |       Library Practice I(200 hours)  |  3   |              |      9       | LIS 111 - LIS 323 |\n"
                "|      ICT LIS 411     |       Internet Technologies and      |  3   |       2      |      3       | 4th Year Standing |\n"
                "|                      |       Services                       |      |              |              |                   |\n"
                "|      INST 2          |       Course Audit 1                 |  6   |       6      |              | 4th Year Standing |\n"
                "|                      |                        Total Units   | 15   |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string fourthYearSSem="________________________________________________________________________________________________________________________\n"
                "|                                                       FOURTH YEAR                                                    |\n"
                "|SECOND SEMESTER                                                                                                       |\n"
                "________________________________________________________________________________________________________________________\n"
                "|      LIS 421         |       Thesis/Research Writing        |  3   |       2      |      3       |      LIS 411      |\n"
                "|                      |       Information Centers            |      |              |              |                   |\n"
                "|      LIS 422         |       Library Practice II(200 hours) |  3   |              |      9       |      LIS 412      |\n"
                "|      INST 3          |       Course Audit 2                 |  6   |       6      |              |       INST 2      |\n"
                "|                      |                       Total Units    | 170  |              |              |                   |\n"
                "________________________________________________________________________________________________________________________\n";
    string midYear="";

    reviewPageSection(firstYearFSem,firstYearSSem, secondYearFSem, secondYearSSem, thirdYearFSem, thirdYearSSem, fourthYearFSem, fourthYearSSem, midYear);
}

void courses() {

    bool answered=false;                                  // implicitly assigns 'false' as value
    while(!answered) {                                    // implements bool as 'loop switch' - since invoking a function passes program execution
        
        cout<<"View Program From Our Available Courses\n"
            "    [BSIS] [BSCS] [BSIT] [BLIS]\n";

        cin>>enteredCourse;                            // reads input for available courses - BSIT, BSCS, BSIT(2 Specialize), BLIS

        string pick;                                   // input declaration outside conditional structure
        
        if(enteredCourse=="BSIS") {
            answered=true;
            bsis();
        } else if(enteredCourse=="BSCS") {
            answered=true;
            bscs();
        } else if(enteredCourse=="BSIT") {
            cout<<"Select From Two Specialization\n"
                "       [WMAD] or [NAS]\n";

            cin>>pick;                      // reads input for BSIT Specialization - WMAD or NAS 
            
            if(pick=="WMAD") {
                answered=true;
                enteredCourse=pick;        // store new input into global variable - "WMAD" string
                bsitWMAD();
            } else if(pick=="NAS") {
                answered=true;
                enteredCourse=pick;        // store new input into global variable - "NAS" string
                bsitNAS();
            } else {
                cout<<"INVALID!!\n";
                continue;
            }
        } else if(enteredCourse=="BLIS") {
            answered=true;
            blis();
        } else {
            cout<<"Try again.\n";
            continue;
        }
    }
}



// BANKING SYSTEM
void bankSystem() {
    bool home=false;                          // while home is not chosen - program continues running

    const float tuition=4485.00;
    int deposit;

    cout<<"TO ENROLL THIS COURSE YOU WILL HAVE TO PAY FOR THE SEMESTER SUBJECTS.\n";    // inform
    do {
        cout<<"Press [A] to view your account balance.\n"
            "Press [B] to increase your balance.\n"
            "Press [C] to pay.\n"
            "Press [E] to HOMEPAGE.\n"; 

        char in;
        cin>>in;
        in=toupper(in);                       // ensure the input is in upperCase; prevent case sensitivity
        switch(in) {
            case 'A':
                cout<<"You currently have "<<accountBalance<<" available balance in your account.\n";
                break;
            case 'B':
                cout<<"How much would you like to deposit into your account?\n";

                cin>>deposit;                // reads how much is your deposit
                accountBalance+=deposit;

                cout<<deposit<<" has been added to your account. \n"
                    "Your new available balance is: "<<accountBalance<<"\n";
                break;
            case 'C':                       // IMPLEMENTS NESTED IF-ELSE INSIDE A SWITCH LOOP
                if(paid) { cout<<"YOU HAVE ALREADY PAID THE TUITION.\n"; } else {}  // assumes tuition is PAID - RUN IF TRUE

                while(!paid&&enrolledSubject.length()>0) {                                                      // assumes tuition is NOT YET PAID&&HAVEN'T CHOSE ANY SUBJECT - WON'T RUN IF TRUE
                    cout<<"Would you like to pay your tuition fee?[YES/NO]: ";

                    string ans;
                    cin>>ans;               // ask user confirmation to pay tuition

                    if(ans=="YES") { 
                            cout<<"You are about to pay an amount of "<<tuition<<". CONTINUE?[Y/N]: ";

                            char chosen;
                            cin>>chosen;                                                    
                            chosen=toupper(chosen);                                 // convert input character into upperCase

                            if(accountBalance>tuition) {                            // checks if available balance is enough to pay tuition
                                switch(chosen) {
                                    case 'Y':
                                        accountBalance-=tuition;
                                        paid=true;                                  // set tuition has been paid - TRUE
                                        cout<<tuition<<" has been deducted in your account.\n"
                                            "Your new balance now is: "<<accountBalance<<"\n";
                                        break;
                                    case 'N':
                                        cout<<"Try again.\n";
                                        break;
                                    default:
                                        cout<<"INVALID!!\n";
                                        continue;
                                    }
                            } else if(accountBalance<tuition&&chosen=='Y') {
                                cout<<"YOU HAVE INSUFFICIENT BALANCE IN YOUR ACCOUNT!\n";
                            } else if(chosen=='N') {
                                cout<<"Payment cancelled.\n";
                            } else {
                                cout<<"INVALID!!\n";
                            }
                        break;
                    } else if(ans=="NO") {
                        cout<<"Payment cancelled.\n";
                        break;
                    } else {
                        cout<<"INVALID!!\n";
                        continue;
                    }
                }
                break;
            case 'E':
                home=true;
                homepageSection();
                break;
            default:
                cout<<"INVALID!!\n";
                continue;                  // reloads the page
        }
    }while(!home);
}

// 'main' function - RUN THE PROGRAM.
int main() {
    banner();       // invoke function to view 'enrollmentSystem' banner;
    webPage();
    return 0;
}