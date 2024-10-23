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
    int Days;
    int Date;
    double Totelprice;
};

int DP, SP, FP;

int SRooms = 0;
int DRooms = 0;

struct Price
{

    int DisplayPrice(char B, char F, int day)
    {
        double price = 0;

        if (F == 'y' || F == 'Y')
        {
            price += FP;
        }
        if (B == 'D' || B == 'd')
        {
            price += DP;
        }
        else
        {
            price += SP;
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
    fflush(stdin);
    cin.getline(hotel.Name, 40);
    cout << "Enter Address : ";
    fflush(stdin);
    cin.getline(hotel.Address, 50);
    cout << "Enter Custumer Care Mob No. : ";
    cin >> hotel.Mob;
    cout << "Number of Deluxe Bedrooms : ";
    cin >> DRooms;
    cout << "Number of Suites Bedrooms : ";
    cin >> SRooms;
    cout << "Enter Food Service Price :";
    cin >> FP;
    cout << "Enter  Deluxe and Suite room Price : ";
    cin >> DP >> SP;

    ofstream file;
    file.open("HotelDetails.txt", ios::app);

    file << "\n"
         << hotel.Name << "\n"; // write in file
    file << hotel.Address << "\n";
    file << hotel.Mob << "\n";

    ofstream File;
    File.open("Room.txt", ios::app);
    File << DRooms << "\n";
    File << SRooms << "\n";
    File.close();

    file << FP << "\n";
    file << DP << "\n";
    file << SP << "\n";

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

    ifstream File;
    File.open("Room.txt");
    File >> DRooms;
    File >> SRooms;
    File.close();

    file >> FP;
    file >> DP;
    file >> SP;

    cout << "Hotel Name : " << hotel.Name << endl;
    cout << "Address : " << hotel.Address << endl;
    cout << "Custumer Care Mob No. : " << hotel.Mob << endl;
    cout << "Number of Deluxe Bedrooms : " << DRooms << endl;
    cout << "Number of Suite Bedrooms : " << SRooms << endl;
    cout << "Food Service Price : " << FP << endl;
    cout << "Deluxe and Suite Bedroom's Price : " << DP << " , " << SP << endl;

    file.close();
}

void Booking()
{

    User user;
    Price price;

    user.UserID++;

    cout << "Enter Your Name : ";
    fflush(stdin);
    cin.getline(user.Name, 20);
    cout << "Enter Your Addhar No. : ";
    cin >> user.Adhar;
    cout << "Enter Mob No. : ";
    cin >> user.Mob;
    cout << "Food Service Food (Y/N): ";
    cin >> user.Food_option;
    cout << "Deluxe Or Suite Bedroom (D/S) : ";
    cin >> user.Bed_option;
    cout << "Enter Days to Stay here! : ";
    cin >> user.Days;
    cout << "Enetr Booking Date : ";
    cin >> user.Date;

    cout << "\n\nThank You For Booking ..\n\n";
    cout << "Your User ID  : " << user.UserID << "\n\n";

    user.Totelprice = price.DisplayPrice(user.Bed_option, user.Food_option, user.Days);
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
    file << user.Days << "\n";
    file << user.Date << "\n";
    file << user.Totelprice << "\n";

    file.close();
}

void DisplayAllUser()
{
    ifstream file;
    User user;

    file.open("UserData.txt", ios::in);
    if (!file.good())
    {
        cout << " No Data Available ... ";
    }
    else
    {

        while (!file.eof())
        {

            int n = 1;

            file >> user.UserID;
            file >> user.Name;
            file >> user.Adhar;
            file >> user.Mob;
            file >> user.Food_option;
            file >> user.Bed_option;
            file >> user.Days;
            file >> user.Date;
            file >> user.Totelprice;

            cout << "\n Costomer -> " << n << "\n";
            cout << "\tID : " << user.UserID << endl;
            cout << "\tName : " << user.Name << endl;
            cout << "\tAdhar No. : " << user.Adhar << endl;
            cout << "\tMob No. : " << user.Mob << endl;
            cout << "\tFood Option : " << user.Food_option << endl;
            cout << "\tBed Option ( Deluxe / Suite ) : " << user.Bed_option << endl;
            cout << "\tDays : " << user.Days << endl;
            cout << "\tBooking Date : " << user.Date << endl;
            cout << "\tTotel Price : " << user.Totelprice << endl;

            n++;
        }
        file.close();
    }
}

void ApproveRoom()
{
    int UserID;
    cout << "\nEnter Costomer ID : ";
    cin >> UserID;

    ifstream file;
    User user;
    bool found = false;

    file.open("UserData.txt", ios::in);
    if (!file.good())
    {
        cout << " No Data Available ... ";
    }
    else
    {

        while (!file.eof())
        {
            file >> user.UserID;
            file >> user.Name;
            file >> user.Adhar;
            file >> user.Mob;
            file >> user.Food_option;
            file >> user.Bed_option;
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
                cout << " Mob No. : " << user.Mob << endl;
                cout << " Food Option : " << user.Food_option << endl;
                cout << " Bed Option ( Deluxe / Suite ): " << user.Bed_option << endl;
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
                    File << user.Bed_option << "\n";
                    break;
                }
                File.close();
            }
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
    file.open("Allotment.txt", ios::in);

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
            break;
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

    file.open("UserData.txt", ios::in);
    if (!file.good())
    {
        cout << " No Data Available ... ";
    }
    else
    {

        while (!file.eof())
        {
            file >> user.UserID;
            file >> user.Name;
            file >> user.Adhar;
            file >> user.Mob;
            file >> user.Food_option;
            file >> user.Bed_option;
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
                cout << " Mob No. : " << user.Mob << endl;
                cout << " Food Option : " << user.Food_option << endl;
                cout << " Bed Option ( Deluxe / Suite ): " << user.Bed_option << endl;
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
            cout << "Enter Yoour Name : ";
            fflush(stdin);
            cin.getline(name, 20);

            char opt;
            cout << "Do You Want to Cancel Your Booking ? (Y/N) : ";
            cin >> opt;
            if (opt == 'y' || opt == 'Y')
            {
                char reason[100];

                cout << "Reason for Cancel Booking : ";
                fflush(stdin);
                cin.getline(reason, 100);

                ofstream File;
                File.open("CancelData.txt", ios::app);

                ifstream File1;
                File1.open("Room.txt");

                File1 >> DRooms;
                File1 >> SRooms;

                int s, d;
                s = SRooms;
                d = DRooms;

                if (user.Bed_option == 'd' || user.Bed_option == 'D')
                {
                    DRooms = int(d - 1);
                }
                else
                {
                    SRooms = int(s - 1);
                }

                ofstream tempFile;
                tempFile.open("temp.txt", ios::app);
                tempFile << DRooms << "\n";
                tempFile << SRooms << "\n";

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

                cout << "Booking Cancel Successfully ";
                break;
            }
            else
            {
                cout << "Thanks Again ..." << endl;
            }

            break;
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

    file.open("CancelData.txt", ios::in);
    if (!file.good())
    {
        cout << " No Data Available ... ";
    }
    else
    {

        while (!file.eof())
        {

            int n = 1;

            file >> RoomNo;
            file >> user.UserID;
            file >> user.Name;
            file >> Cancel;

            cout << "\n Costomer -> " << n << "\n";
            cout << "\tRoom No. : " << RoomNo << endl;
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
}

void AvailableRooms()
{
    ifstream file;
    file.open("Room.txt");

    file >> DRooms;
    file >> SRooms;

    cout << "Available Rooms :- \n\n";
    cout << "Deluxe Rooms : " << DRooms << endl;
    cout << "Suite Rooms : " << SRooms << endl;

    file.close();
}

int main()
{
    /*This project is developed by Priyaranjan and team. The project name is Hotel Booking Management Application created using C++. For access to the source code and further details, please visit my GitHub profile: www.github.com/csepriyaranjan   */

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
                cout << " 06. Exit \n\n\n";
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

                else if (option1 > 6)
                {
                    cout << "Select Right Option ! ";
                }

                cin.clear();
                fflush(stdin);
                cin.get();
                system("cls");

            } while (option1 != 6);
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
                cout << " 06. EXIT \n\n";
                cout << " 07. RESET YOUR SYSTEM \n\n";
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
                    cout << "Exiting....";
                }
                else if (option2 == 7)
                {
                    cout << "< Factory Reset >\n\n";
                    char yes;
                    cout << "Do You Want To Reset Your System ? (y/n) : ";
                    cin >> yes;
                    if (yes == 'y' || yes == 'Y')
                    {
                        remove("HotelDetails.txt");
                        remove("Allotment.txt");
                        remove("UserData.txt");
                        remove("Room.txt");
                        remove("CancelData.txt");

                        cout<<"Reset Succeffully... \n\n";
                    }
                    else
                        cout << "Reset revoked. \n\n";

                    cin.get();
                    exit(EXIT_FAILURE);
                }
                else if (option2 > 7)
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
