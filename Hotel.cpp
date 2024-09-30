#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Hotel
{
    char Name[40];
    char Address[50];
    long long int Mob;
};

struct User
{
    int UserID = 1000;
    char Name[20];
    long long int Adhar;
    long long int Mob;
    char Food_option;
    char Bed_option;
    char AC_option;
    int Days;
    int Date;
    double Totelprice;
};

int SRP, DRP, FP, NSRP, NDRP;

int SRooms = 0;
int DRooms = 0;

struct Price
{

    int DisplayPrice(char B, char F, char AC, int day)
    {
        double price = 0;

        if (F == 'y' || F == 'Y')
        {
            price += FP;
        }

        if (AC == 'a' || AC == 'A')
        {
            if (B == 's' || B == 'S')
            {
                price += SRP;
            }
            else
            {
                price += DRP;
            }
        }
        else
        {
            if (B == 's' || B == 'S')
            {
                price += NSRP;
            }
            else
            {
                price += NDRP;
            }
        }
        price *= day;

        return price;
    }
};

void HotelDetalis()
{
    Hotel hotel;
    Price price;

    cout << "Enter Hotel Name : ";
    cin.get();
    cin.getline(hotel.Name, 40);
    cout << "Enter Address : ";
    cin.get();
    cin.getline(hotel.Address, 50);
    cout << "Enter Custumer Care Mob No. : ";
    cin >> hotel.Mob;
    cout << "Number of Single Bedrooms : ";
    cin >> SRooms;
    cout << "Number of Couples OR Double Bedrooms : ";
    cin >> DRooms;
    cout << "Enter Additional Food Price :";
    cin >> FP;
    cout << "Enter  Single & Double AC Bedroom's Price : ";
    cin >> SRP >> DRP;
    cout << "Enter  Single & Double Non-AC Bedroom's Price : ";
    cin >> NSRP >> NDRP;

    ofstream file;
    file.open("HotelDetails.txt", ios::app);

    file << "\n"
         << hotel.Name << "\n"; // write in file
    file << hotel.Address << "\n";
    file << hotel.Mob << "\n";
    // file << SRooms << "\n";
    // file << DRooms << "\n";

    ofstream File;
    File.open("Room.txt", ios::app);
    File << SRooms << "\n";
    File << DRooms << "\n";
    File.close();

    file << FP << "\n";
    file << SRP << "\n";
    file << DRP << "\n";
    file << NSRP << "\n";
    file << NDRP << "\n";

    file.close();
    cout << "\n\n Data Saved Successfully ! " << endl;
}

void ViewHotelDetails()
{
    Hotel hotel;
    Price price;

    ifstream file;
    file.open("HotelDetails.txt");
    file >> hotel.Name; // read from file
    file >> hotel.Address;
    file >> hotel.Mob;
    // file >> SRooms;
    // file >> DRooms;
    ifstream File;
    File.open("Room.txt");
    File >> SRooms;
    File >> DRooms;
    File.close();

    file >> FP;
    file >> SRP;
    file >> DRP;
    file >> NSRP;
    file >> NDRP;

    cout << "Hotel Name : " << hotel.Name << endl;
    cout << "Address : " << hotel.Address << endl;
    cout << "Custumer Care Mob No. : " << hotel.Mob << endl;
    cout << "Number of Single Bedrooms : " << SRooms << endl;
    cout << "Number of Couples OR Double Bedrooms : " << DRooms << endl;
    cout << "Additional Food Price : " << FP << endl;
    cout << "Single & Double AC Bedroom's Price : " << SRP << " , " << DRP << endl;
    cout << "Non-AC Single & Double Non-AC Bedroom's Price : " << NSRP << " , " << NDRP << endl;

    file.close();
}

void Booking()
{

    User user;
    Price price;

    user.UserID++;

    // cout<< "Enter User ID : ";
    // cin >> user.UserID;
    cout << "Enter Your Name : ";
    cin.ignore();
    cin.getline(user.Name, 20);
    cout << "Enter Your Addhar No. : ";
    cin >> user.Adhar;
    cout << "Enter Mob No. : ";
    cin >> user.Mob;
    cout << "Do you want Additional Food (Y/N): ";
    cin >> user.Food_option;
    cout << "Which Bedroom Do you like to Book Single or Double Bedroom (S/D) : ";
    cin >> user.Bed_option;
    cout << "Which Bedroom Do you like to Book AC or Non-Ac (A/N) : ";
    cin >> user.AC_option;
    cout << "Enter Days to Stay here! : ";
    cin >> user.Days;
    cout << "Enetr Booking Date : ";
    cin >> user.Date;

    cout << "\n\nThank You For Booking ..\n\n";
    cout << "Your User ID  : " << user.UserID << endl;

    user.Totelprice = price.DisplayPrice(user.Bed_option, user.Food_option, user.AC_option, user.Days);
    cout << "Totel Price : " << user.Totelprice;
    cout << "\n\n\nPlease Remember Your User ID." << endl;
    ifstream File1;
    File1.open("Room.txt");

    File1 >> SRooms;
    File1 >> DRooms;

    int s, d;
    s = SRooms;
    d = DRooms;

    if (user.Bed_option == 's' || user.Bed_option == 'S')
    {
        SRooms = int(s - 1);
    }
    else
    {
        DRooms = int(d - 1);
    }

    ofstream tempFile;
    tempFile.open("temp.txt", ios::app);
    tempFile << SRooms << "\n";
    tempFile << DRooms << "\n";

    File1.close();
    tempFile.close();
    remove("Room.txt");
    rename("temp.txt", "Room.txt");

    ofstream file;
    file.open("UserData.txt", ios::app);

    file << "\n"
         << user.UserID << "\n";
    file << user.Name << "\n";
    file << user.Adhar << "\n";
    file << user.Mob << "\n";
    file << user.Food_option << "\n";
    file << user.Bed_option << "\n";
    file << user.AC_option << "\n";
    file << user.Days << "\n";
    file << user.Date << "\n";
    file << user.Totelprice << "\n";

    file.close();
}

void DisplayAllUser()
{
    ifstream file;
    User user;

    file.open("UserData.txt");

    while (!file.eof())
    {

        int n = 1;

        file >> user.UserID;
        file >> user.Name;
        file >> user.Adhar;
        file >> user.Mob;
        file >> user.Food_option;
        file >> user.Bed_option;
        file >> user.AC_option;
        file >> user.Days;
        file >> user.Date;
        file >> user.Totelprice;

        cout << "\n Costomer -> " << n << "\n";
        cout << "\tID : " << user.UserID << endl;
        cout << "\tName : " << user.Name << endl;
        cout << "\tAdhar No. : " << user.Adhar << endl;
        cout << "\tMob No. : " << user.Mob << endl;
        cout << "\tFood Option : " << user.Food_option << endl;
        cout << "\tBed Option : " << user.Bed_option << endl;
        cout << "\tAc or Non Ac option : " << user.AC_option << endl;
        cout << "\tDays : " << user.Days << endl;
        cout << "\tBooking Date : " << user.Date << endl;
        cout << "\tTotel Price : " << user.Totelprice << endl;

        n++;
    }
    file.close();
}

void ApproveRoom()
{
    int UserID;
    cout << "\nEnter Costomer ID : ";
    cin >> UserID;

    ifstream file;
    User user;
    bool found = false;

    file.open("UserData.txt");

    while (!file.eof())
    {
        file >> user.UserID;
        file >> user.Name;
        file >> user.Adhar;
        file >> user.Food_option;
        file >> user.Bed_option;
        file >> user.AC_option;
        file >> user.Days;
        file >> user.Date;
        file >> user.Totelprice;

        if (user.UserID == UserID)
        {
            found = true;
            cout << "\n\n-----------------------------------------------------------------";
            cout << "\n                             RECORD                                ";
            cout << "\n\n------------------------------------------------------------------\n\n";

            cout << "Customer Information - \n\n";

            cout << " Name : " << user.Name << endl;
            cout << " Adhar No. : " << user.Adhar << endl;
            cout << " Food Option : " << user.Food_option << endl;
            cout << " Bed Option (S-Single / D-Double Bed ): " << user.Bed_option << endl;
            cout << " AC or Non-AC option : " << user.AC_option << endl;
            cout << " Days : " << user.Days << endl;
            cout << " Date : " << user.Date << endl;
            cout << " Totel Price : " << user.Totelprice << endl;

            ofstream File;
            File.open("Allotment.txt", ios::app);
            if (!File.is_open())
            {
                cout << "\n\nError opening file. " << endl;
            }
            else
            {
                int RoomNo;
                cout << "\nEnter Room No. to Allotment : " << endl;
                cin >> RoomNo;
                cout << "Room Alloted Successfully ! " << endl;

                File << "\n"
                     << RoomNo << " \n";
                File << user.UserID << "\n ";
                File << user.Name << " \n";
                File << user.Totelprice << " \n ";
                File << user.Bed_option << "\n"; //--------------new add---------//
            }
            File.close();
        }
    }

    if (!found)
    {

        cout << "\n\nRecord with User ID  " << UserID << " not found." << endl;
    }

    file.close();
}

void CheckBooking()
{
    User user;
    ifstream file;
    file.open("Allotment.txt");

    int UserID;
    cout << "Enter Your User ID : ";
    cin >> UserID;

    while (!file.eof())
    {
        int RoomNo;
        file >> RoomNo;
        file >> user.UserID;
        file >> user.Name;
        file >> user.Totelprice;
        file >> user.Bed_option;

        if (user.UserID == UserID)
        {
            cout << "Great ! Your Room is alloted . \n"
                 << endl;
            cout << "Room No . : " << RoomNo << endl;
            cout << "Totel Price : " << user.Totelprice << endl;
        }
        else
        {
            cout << "Invaild User ID or Your Appliction is pending.. " << endl;
            break;
        }
    }
    file.close();
}

void SearchUser()
{
    int UserID;
    cout << "\nEnter Costomer ID : ";
    cin >> UserID;

    ifstream file;
    User user;
    bool found = false;

    file.open("UserData.txt");

    while (!file.eof())
    {
        file >> user.UserID;
        file >> user.Name;
        file >> user.Adhar;
        file >> user.Food_option;
        file >> user.Bed_option;
        file >> user.AC_option;
        file >> user.Days;
        file >> user.Date;
        file >> user.Totelprice;

        if (user.UserID == UserID)
        {
            found = true;
            cout << "\n\n-----------------------------------------------------------------------------------";
            cout << "\n                                        RECORD                                       ";
            cout << "\n\n-----------------------------------------------------------------------------------\n\n";

            cout << "Customer Information - \n\n";

            cout << " Name : " << user.Name << endl;
            cout << " Adhar No. : " << user.Adhar << endl;
            cout << " Food Option : " << user.Food_option << endl;
            cout << " Bed Option (S-Single / D-Double Bed ): " << user.Bed_option << endl;
            cout << " AC or Non-AC option : " << user.AC_option << endl;
            cout << " Days : " << user.Days << endl;
            cout << " Date : " << user.Date << endl;
            cout << " Totel Price : " << user.Totelprice << endl;
        }
    }
    if (!found)
    {

        cout << "\n\nRecord with User ID  " << UserID << " not found." << endl;
    }

    file.close();
}

void CancelBooking()
{
    User user;
    ifstream file;

    file.open("Allotment.txt");

    int UserID;
    cout << "Enter Your User ID : ";
    cin >> UserID;

    while (!file.eof())
    {
        int RoomNo;
        file >> RoomNo;
        file >> user.UserID;
        file >> user.Name;
        file >> user.Totelprice;
        file >> user.Bed_option;
        if (user.UserID == UserID)

        {
            char name[20];
            cout << "Verify Yourself .. \n\n";
            cout << "Enter Yoour Name : ";
            cin.get();
            cin.getline(name, 20);

            if (name == user.Name)
            {
                char opt;
                cout << "Do You Want to Cancel Your Booking ? (Y/N) : ";
                cin >> opt;
                if (opt == 'y' || opt == 'Y')
                {
                    char reason[100];

                    cout << "Reason for Cancel Booking : ";
                    cin.get();
                    cin.getline(reason, 100);

                    ofstream File;
                    File.open("CancelData.txt", ios::app);

                    ifstream File1;
                    File1.open("Room.txt");

                    File1 >> SRooms;
                    File1 >> DRooms;

                    int s, d;
                    s = SRooms;
                    d = DRooms;

                    if (user.Bed_option == 's' || user.Bed_option == 'S')
                    {
                        SRooms = int(s - 1);
                    }
                    else
                    {
                        DRooms = int(d - 1);
                    }

                    ofstream tempFile;
                    tempFile.open("temp.txt", ios::app);
                    tempFile << SRooms << "\n";
                    tempFile << DRooms << "\n";

                    File1.close();
                    tempFile.close();
                    remove("Room.txt");
                    rename("temp.txt", "Room.txt");

                    char Cancel[7] = "Cancel";

                    File << RoomNo << "\n";
                    File << user.UserID << "\n";
                    File << user.Name << "\n";
                    File << Cancel << "\n";
                    File.close();
                }
                else
                {
                    cout << "Thanks Again ..." << endl;
                }
            }
            else
            {
                cout << "Invaild User Name !" << endl;
            }
        }
        else
        {
            cout << "Invaild User ID !" << endl;
        }
    }
    file.close();
}

void CkeckCancelList()
{
    ifstream file;
    User user;
    int RoomNo;
    char Cancel[7];

    file.open("CancelData.txt");

    while (!file.eof())
    {

        int n = 1;

        file >> RoomNo;
        file >> user.UserID;
        file >> user.Name;
        file >> Cancel;

        cout << "\n Costomer -> " << n << "\n";
        cout << "\tID : " << user.UserID << endl;
        cout << "\tName : " << user.Name << endl;
        if (Cancel == "")
        {
            cout << "\tCancel or Not : Not " << endl;
        }
        else
        {
            cout << "\tCancel or Not : " << Cancel << endl;
        }

        n++;
    }
    file.close();
}

void LeaveHotel()
{

    int UserID;
    cout << "\nEnter Costomer ID : ";
    cin >> UserID;

    ifstream file;
    User user;
    bool found = false;

    file.open("UserData.txt");

    while (!file.eof())
    {
        file >> user.UserID;
        file >> user.Name;
        file >> user.Adhar;
        file >> user.Food_option;
        file >> user.Bed_option;
        file >> user.AC_option;
        file >> user.Days;
        file >> user.Date;
        file >> user.Totelprice;

        if (user.UserID == UserID)
        {
            found = true;

            cout << "Customer Information - \n\n";

            cout << " Name : " << user.Name << endl;
            cout << " Adhar No. : " << user.Adhar << endl;
            cout << " Days : " << user.Days << endl;
            cout << " Date : " << user.Date << endl;
            cout << " Totel Price : " << user.Totelprice << endl;

            int date;
            cout << "Enter Date of Leaving : ";
            cin >> date;

            ofstream File;
            File.open("LeaveData.txt", ios::app);
            File << user.UserID << "\n";
            File << user.Name << "\n";
            File << user.Totelprice << "\n";
            File << user.Days << "\n";
            File << user.Date << "\n";
            File << date << "\n";

            File.close();

            ifstream File1;
            File1.open("Room.txt");

            File1 >> SRooms;
            File1 >> DRooms;

            int s, d;
            s = SRooms;
            d = DRooms;

            if (user.Bed_option == 's' || user.Bed_option == 'S')
            {
                SRooms = int(s - 1);
            }
            else
            {
                DRooms = int(d - 1);
            }

            ofstream tempFile;
            tempFile.open("temp.txt", ios::app);
            tempFile << SRooms << "\n";
            tempFile << DRooms << "\n";

            File1.close();
            tempFile.close();
            remove("Room.txt");
            rename("temp.txt", "Room.txt");
        }
    }
    if (!found)
    {

        cout << "\n\nRecord with User ID  " << UserID << " not found." << endl;
    }

    file.close();
}

void LeaveHotelList()
{
    ifstream file;
    User user;
    int RoomNo;
    int date;

    file.open("LeaveData.txt");

    while (!file.eof())
    {

        int n = 1;

        file >> user.UserID;
        file >> user.Name;
        file >> user.Totelprice;
        file >> user.Days;
        file >> user.Date;
        file >> date;

        cout << "\n Costomer -> " << n << "\n";
        cout << "\tID : " << user.UserID << endl;
        cout << "\tName : " << user.Name << endl;
        cout << "\tTotel Price : " << user.Totelprice << endl;
        cout << "\tDays : " << user.Days << endl;
        cout << "\tIn Date : " << user.Date << endl;
        cout << "\tLeaving Date : " << date << endl;

        n++;
    }
    file.close();
}

void AvailableRooms()
{
    ifstream file;
    file.open("Room.txt");

    file >> SRooms;
    file >> DRooms;

    cout << "Available Rooms :- \n\n";
    cout << "Single Rooms : " << SRooms << endl;
    cout << "Double or Couple Rooms : " << DRooms << endl;

    file.close();
}

int main()
{
    /*This project is developed by Priyaranjan and team. The project name is Hotel Booking Management Application created using C++. For access to the source code and further details, please visit my GitHub profile: www.github.com/@csepriyaranjan   */
  
    User user;
    Hotel hotel;
    int option, option1, option2;

    system("cls");

    char setup_opt;

    cout << "------------------------------------------------\n";
    cout << "            Hotel Booking Application           \n";
    cout << "------------------------------------------------\n\n";

    cout << " Have You Already Setup Your Hotel ? (Y/N) : ";
    cin >> setup_opt;

    if (setup_opt == 'y' || setup_opt == 'Y')
    {
        goto Jump;
    }

    else
    {

        cout << "\n\nSETUP YOUR HOTEL  \n\n";
        HotelDetalis();
        cin.get();
    }
Jump:
    do
    {

        system("cls");

        cout << "------------------------------------------------\n";
        cout << "            Hotel Booking Application           \n";
        cout << "------------------------------------------------\n\n";
        cout << " 01. USER DASHBOARD \n\n";
        cout << " 02. HOTEL DASHBOARD \n\n";
        cout << " 03. EXIT \n\n\n";
        cout << " Select an option : ";
        cin >> option;

        if (option == 1)
        {
            system("cls");

            do
            {
                cout << "------------------------------------------------\n";
                cout << "                USER DASHBOARD                   \n";
                cout << "------------------------------------------------\n\n";

                cout << " 01. VIEW HOTEL DETAILS \n\n";
                cout << " 02. AVAILABLE ROOMS \n\n";
                cout << " 03. BOOK HERE ! \n\n";
                cout << " 04. CHECK STATUS OF BOOKING \n\n";
                cout << " 05. CANCEL YOUR BOOKING \n\n";
                cout << " 06. LEAVE HOTEL \n\n";
                cout << " 07. Exit \n\n\n";
                cout << " Select an option >> ";
                cin >> option1;

                if (option1 == 1)
                {

                    cout << "------------------------------------------------\n";
                    cout << "                  HOTEL DETAILS                 \n";
                    cout << "------------------------------------------------\n\n";

                    ViewHotelDetails();
                    cin.get();
                }
                else if (option1 == 2)
                {

                    cout << "------------------------------------------------\n";
                    cout << "                AVAILABLE ROOMS                 \n";
                    cout << "------------------------------------------------\n\n";

                    AvailableRooms();
                    cin.get();
                }
                else if (option1 == 3)
                {

                    cout << "------------------------------------------------\n";
                    cout << "                BOOKING DASBOARD                \n";
                    cout << "------------------------------------------------\n\n";

                    Booking();
                    cin.get();
                }
                else if (option1 == 4)
                {
                    cout << "------------------------------------------------\n";
                    cout << "                STATUS OF BOOKING               \n";
                    cout << "------------------------------------------------\n\n";

                    CheckBooking();
                    cin.get();
                }
                else if (option1 == 5)
                {
                    cout << "------------------------------------------------\n";
                    cout << "                CANCEL DASBOARD                 \n";
                    cout << "------------------------------------------------\n\n";
                    CancelBooking();
                    cin.get();
                }
                else if (option1 == 6)
                {
                    cout << "------------------------------------------------\n";
                    cout << "                LEAVING DASBOARD                \n";
                    cout << "------------------------------------------------\n\n";

                    LeaveHotel();
                    cin.get();
                }
                else if (option1 > 7)
                {
                    cout << "Select Right Option ! ";
                }

                cin.clear();
                fflush(stdin);
                cin.get();
                system("cls");

            } while (option1 != 7);
        }

        else if (option == 2)
        {
            system("cls");

            do
            {
                cout << "------------------------------------------------\n";
                cout << "                HOTEL DASBOARD                  \n";
                cout << "------------------------------------------------\n\n";

                cout << " 01. CHECK BOOKING LIST ! " << "\n\n";
                cout << " 02. CHECK AVILABLE ROOMS " << "\n\n";
                cout << " 03. APPROVE AND ALLOT ROOM  " << "\n\n";
                cout << " 04. DISPLAY CUSTOMER DETAILS " << "\n\n";
                cout << " 05. CHECK CANCEL BOOKING LIST \n\n";
                cout << " 06. CHECK LEAVING USER LIST \n\n";
                cout << " 07. EXIT \n\n";
                cout << " Select an option >> ";
                cin >> option2;

                if (option2 == 1)
                {
                    cout << "---------------------------------------------------------\n";
                    cout << "                       BOOKING LIST                      \n";
                    cout << "---------------------------------------------------------\n\n";

                    DisplayAllUser();
                    cin.get();
                }
                else if (option2 == 2)
                {
                    cout << "---------------------------------------------------------\n";
                    cout << "                       AVILABLE ROOMS                    \n";
                    cout << "---------------------------------------------------------\n\n";

                    AvailableRooms();
                    cin.get();
                }
                else if (option2 == 3)
                {
                    cout << "---------------------------------------------------------\n";
                    cout << "                  APPROVE AND ALLOT ROOM                 \n";
                    cout << "---------------------------------------------------------\n\n";

                    ApproveRoom();
                    cin.get();
                }
                else if (option2 == 4)
                {
                    cout << "---------------------------------------------------------\n";
                    cout << "                    CUSTOMER DETAILS                     \n";
                    cout << "---------------------------------------------------------\n\n";

                    SearchUser();
                    cin.get();
                }
                else if (option2 == 5)
                {
                    cout << "---------------------------------------------------------\n";
                    cout << "                  CANCEL BOOKING LIST                    \n";
                    cout << "---------------------------------------------------------\n\n";

                    CkeckCancelList();
                    cin.get();
                }
                else if (option2 == 6)
                {
                    cout << "---------------------------------------------------------\n";
                    cout << "                    LEAVING USER LIST                    \n";
                    cout << "---------------------------------------------------------\n\n";

                    LeaveHotelList();
                    cin.get();
                }
                else if (option1 > 7)
                {
                    cout << "Select Right Option ! ";
                }
                cin.clear();
                fflush(stdin);
                cin.get();
                system("cls");
            } while (option2 != 7);
        }

        else
        {
            cout << "Select Right Option ! ";
        }

        cin.clear();
        fflush(stdin);
        cin.get();
        system("cls");

    } while (option != 3);

    return 0;
}