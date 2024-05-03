// Hotel Booking Mangement System
#include <iostream>
#include <string>
using namespace std;

class Login
{
protected:
    string userId;
    int password;

public:
    virtual bool login() = 0; // Virtual function for login
};

class ManagerLogin : public Login
{
public:
    bool login()
    {
        cout << "Enter your UserId: ";
        cin >> userId;
        cout << "Enter Password: ";
        cin >> password;

        if ((userId == "1234") && (password == 123))
        {
            cout << endl
                 << "Login Successful!!" << endl
                 << endl;
            return true;
        }

        else
        {
            cout << "Wrong Id or Password!!" << endl
                 << endl;
            return false;
        }
    }
};

class AdminLogin : public Login
{
public:
    bool login()
    {
        cout << "Enter your UserId: ";
        cin >> userId;
        cout << "Enter Password: ";
        cin >> password;

        if ((userId == "123") && (password == 123))
        {
            cout << endl
                 << "Login Successful!!" << endl
                 << endl;
            return true;
        }

        else
        {
            cout << "Wrong Id or Password!!" << endl
                 << endl;
            return false;
        }
    }
};

class Customer
{
private:
    string name;
    string address;
    string phone;
    int days = 0;
    float payment_advance;
    double bill = 0;
    int booking_id;
    int room;
    int status;

public:
    Customer()
    {
        days = 0;
        payment_advance = 0;
        bill = 0;
        booking_id = 0;
        status = 0;
        room = 0;
    }

    void accept()
    {
        cout << endl;
        cout << "Enter customer name: ";
        cin >> name;
        cout << "Enter Customer address: ";
        cin >> address;
        cout << "Enter mobile number: ";
        cin >> phone;
    }

    void display()
    {
        cout << endl
             << booking_id << "\t" << name << "\t" << phone << "\t" << address << "\t" << room << "\t";
        if (status == 1)
        {
            cout << "-" << endl;
        }
        else
        {
            cout << "CHECKED OUT." << endl;
        }
    }

    friend class room;
    friend class Hotel;
};

class Room
{
private:
    char type;      // Comfort Suite or Normal type Room
    char stype;     // Big or Small size room
    char ac;        // AC or Non-AC room
    int roomNumber; // Room number
    double rent;    // Rent per day
    int status = 0; // Room is booked or not

public:
    friend class Hotel;

    Room() // default Constructor
    {
        type = '\0';
        stype = '\0';
        ac = '\0';
        roomNumber = 0;
        rent = 0;
        status = 0;
    }

    void acceptroom(int rno)
    {
        roomNumber = rno;
        cout << "\nType AC/Non-AC Room (A/N) : ";
        cin >> ac;
        while (ac != 'A' && ac != 'N')
        {
            cout << "Please Re-Enter Type: AC/Non-AC (A/N) : ";
            cin >> ac;
        }
        cout << "Type Comfort Suite or Normal (S/N) : ";
        cin >> type;
        while (type != 'S' && type != 'N')
        {
            cout << "Please Re-enter Type Comfort Suite or Normal (S/N) : ";
            cin >> type;
        }
        cout << "Type Room Size Big/Small (B/S) : ";
        cin >> stype;
        while (stype != 'B' && stype != 'S')
        {
            cout << "Please Re-enter Type Size Big or Small (B/S) : ";
            cin >> stype;
        }
        cout << "Enter daily Rent of the room: ";
        cin >> rent;
        while (rent < 0 || rent > 80000)
        {
            cout << "\nPlease enter valid rent.";
            cin >> rent;
        }
        status = 0;
        cout << "\n\nRoom Added Successfully!" << endl;
    }

    void displayroom()
    {
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "  "
             << "Room number "
             << "  "
             << "AC/Non-AC "
             << "  "
             << "Type "
             << "   "
             << "Room Size    "
             << "Rent" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "   " << roomNumber << "         " << ac << "           " << type << "       " << stype << "           " << rent << endl;
        if (status == 0)
        {
            cout << "\n The Room is Available :)" << endl;
        }
        else
        {
            cout << "\n SORRY!! The Room is Booked :(" << endl;
        }
        cout << endl;
    }
};

class Hotel
{
private:
    Room a[100];
    Customer c[100];
    int nroom = 0; // NROOM IS USED TO RECORD FOR NUMBER OF CUSTOMERS
    int ncust = 0; // NCUST IS USED TO RECORD FOR NUMBER OF CUSTOMERS
public:
    void addRooms()
    {
        int rno;
        cout << "Enter number of rooms you want to add: ";
        cin >> nroom;
        while (nroom <= 0)
        {
            cout << "Invalid. Enter valid number of rooms.";
            cin >> nroom;
        }
        for (int i = 0; i < nroom; i++)
        {
            cout << "\n\nROOM " << (i + 1) << endl;
        flag:
            cout << endl
                 << "Enter room number : ";
            cin >> rno;
            if (rno <= 0)
            {
                cout << endl
                     << "This room number is invalid! Please Re-enter the room number : ";
                goto flag;
            }
            for (int i = 0; i < nroom; i++)
            {
                if (a[i].roomNumber == rno)
                {
                    cout << "Invalid. Repetitive room numbers." << endl;
                    goto flag;
                }
            }
            a[i].acceptroom(rno); // Calling accept function from class Room
        }
    }

    void searchroom()
    {
        if (nroom == 0)
        {
            cout << "Please add rooms." << endl;
            return;
        }
        int flag = 0;
        char ac1, type1, stype1;
        cout << "Do you want AC or Non-AC? (A/N): " << endl;
        cin >> ac1;
        cout << "Do you want suite or normal room?" << endl;
        cin >> type1;
        cout << "Size? (B/S)" << endl;
        cin >> stype1;
        for (int i = 0; i < nroom; i++)
        {
            if (a[i].ac == ac1 && a[i].type == type1 && a[i].stype == stype1)
            {
                flag = 1;
                cout << "Room found" << endl;
                a[i].displayroom();
            }
        }
        if (flag == 0)
        {
            cout << "No such room is available." << endl;
        }
    }

    void CheckIn()
    {
        if (nroom == 0)
        {
            cout << "Please add rooms." << endl;
            return;
        }
        int i, rno;
        if (ncust <= nroom)
        {
            c[ncust].booking_id = ncust + 1;
        flag:
            int flag1 = 0;
            cout << "Enter room number=";
            cin >> rno;
            for (i = 0; i < nroom; i++)
            {
                if (rno == a[i].roomNumber)
                {
                    flag1 = 1;
                    break;
                }
            }
            if (flag1 == 0)
            {
                cout << "Invalid room number. Please Enter again.\n";
                goto flag;
            }
            if (a[i].status == 0) // Checking if room is occupied
            {
                char ch2;
                cout << "Room available." << endl;
                a[i].displayroom();
                cout << "Do you wish to continue? Press(Y/y)";
                cin >> ch2;
                if (ch2 == 'Y' || ch2 == 'y')
                {
                    c[ncust].accept();
                    cout << "Enter number of days of stay: ";
                    cin >> c[ncust].days;
                    c[ncust].bill = c[ncust].days * a[i].rent; // generating bill. bill= No. of days * rent per day.
                    cout << "Your total bill will approx be Rs." << (c[ncust].bill) << "." << endl
                         << "Min adv payment = " << c[ncust].bill / 4 << " What will you be paying? ";
                    cin >> c[ncust].payment_advance;
                    while (c[ncust].payment_advance < c[ncust].bill / 4 || c[ncust].payment_advance > c[ncust].bill)
                    {
                        cout << "Enter valid amount.";
                        cin >> c[ncust].payment_advance;
                    }
                    cout << "Thank you. Booking confirmed." << endl;
                    cout << "--------------------------------------------------------------" << endl;
                    cout << "Booking Id: " << c[ncust].booking_id << endl
                         << "Name: " << c[ncust].name << endl
                         << "Room no.: " << rno;
                    a[i].status = 1; // changing room status to booked
                    c[ncust].room = rno;
                    c[ncust].status = 1;
                    ncust++;
                }
                else // if needs to change room number
                {
                    goto flag;
                }
            }
            else // if room is occupied
            {
                cout << "Room Occupied. Please choose another room." << endl;
            }
        }
        else // if all roomes are occupied
        {
            cout << "Sorry! Hotel is Full." << endl;
        }
    }

    void searchcust() // Seach if a customer is staying in the hotel
    {
        int id, flag = 0;
        cout << "Enter booking id of customer.";
        cin >> id;
        for (int i = 0; i <= ncust; i++) // Searching for customer
        {
            if (c[i].booking_id == id)
            {
                cout << "\t\t\t Name";
                cout << "\t\t\t Phone";
                cout << "\t\t\t Address";
                cout << "\t\t\tRoom no: ";
                c[i].display();
                flag = 1;
            }
        }
        if (flag == 0) // case not found
        {
            cout << "No customer found." << endl;
        }
    }

    void availability() // check availability of room
    {
        if (nroom == 0)
        {
            cout << "Please add rooms." << endl;
            return;
        }
        cout << "The list of all available rooms:" << endl;
        cout << "| Room No.\tAC/Non-AC\tType\tStype\tRent\tAvailability" << endl;
        for (int i = 0; i < nroom; i++)
        {
            a[i].displayroom();
        }
    }

    void CheckOut()
    {
        int rno, i, j;
        cout << "Enter room number= ";
        cin >> rno;
        for (j = 0; j < nroom; j++)
        {
            if (rno == a[j].roomNumber)
            {
                break;
            }
        }
        if (a[j].status == 0) // If room is not occupied
        {
            cout << "Invalid." << endl;
        }
        for (i = 0; i < ncust; i++) // Checking customer details
        {
            if (c[i].room == rno)
            {
                cout << "CHECKING OUT." << endl;
                c[i].display();
                cout << "Your total bill is " << c[i].bill << endl;
                cout << "Adv payment: " << c[i].payment_advance;
                cout << endl
                     << "Hence, pending payment= Rs." << c[i].bill - c[i].payment_advance; // Pending Payment
                cout << endl
                     << "Thank you! Visit Again :)" << endl;
                a[j].status = 0; // Change status to unoccupied
                c[i].status = 0; // Checked out
                break;
            }
        }
    }

    void Summary()
    {
        if (nroom == 0)
        {
            cout << "No customers as yet." << endl;
            return;
        }
        cout << "Guest Summary:" << endl;
        cout << "|Id  ";
        cout << "| Name      ";
        cout << "| Phone     ";
        cout << "| Address    ";
        cout << "| Room no    ";
        cout << "| Status\t|" << endl;
        for (int i = 0; i < ncust; i++)
        {
            c[i].display();
        }
    }
};

void welcome()
{
    cout << "              |-------------------------------------------------------|" << endl;
    cout << "              |                                                       |" << endl;
    cout << "              |                       WELCOME                         |" << endl;
    cout << "              |                 Hotel Booking System                  |" << endl;
    cout << "              |                                                       |" << endl;
    cout << "              |-------------------------------------------------------|" << endl;
}

int main()
{
    Hotel h;
    char ch;
    Login *managerLogin = new ManagerLogin;
    Login *adminLogin = new AdminLogin;

log:
    welcome();
    do
    {
        cout << endl
             << "---------------------------------------------------------------------" << endl;
        cout << "MENU:" << endl;
        cout << "1. OPERATE AS MANAGER" << endl;
        cout << "2. OPERATE AS ADMIN" << endl;
        cout << "3. EXIT" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case '1':
        {
            bool isManagerLoggedIn = managerLogin->login();
            if (!isManagerLoggedIn)
            {
                cout << "You don't have permission to access this option." << endl;
                break;
                goto m_menu;
            }

            int ch1;
        m_menu:
            cout << "-------------------------- MANAGER ----------------------------" << endl;
            cout << "To Add database of rooms in the hotel" << endl;
            cout << "View Records of all customers" << endl;
            cout << "LogOut" << endl;
            cout << "Enter your choice here: ";
            cin >> ch1;
            cout << endl;
            switch (ch1)
            {
            case 1:
            {
                cout << "Add database of rooms in the hotel" << endl;
                h.addRooms();
                cout << "Database updated......" << endl
                     << endl;
                break;
            }
            case 2:
            {
                cout << "Here is the record of all customers\n\n";
                h.Summary();
                break;
            }
            case 3:
                goto log;
            }
            cout << "Going back to menu." << endl;
            goto m_menu;
        }

        case '2':
        {
            bool isAdminLoggedIn = adminLogin->login();
            if (!isAdminLoggedIn)
            {
                cout << "You don't have permission to access this option." << endl;
                break;
            }

            char ch3;
            do
            {
                cout << endl;
                cout << "------------------------------ ADMINISTRATOR ------------------------------" << endl;
                cout << "Menu:" << endl;
                cout << "1. Check Availability of rooms" << endl;
                cout << "2. Search Room" << endl;
                cout << "3. Check In" << endl;
                cout << "4. Search Customer" << endl;
                cout << "5. Guest Summary" << endl;
                cout << "6. Checkout." << endl;
                cout << "7. Logout" << endl;
                cout << "8. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> ch3;

                switch (ch3)
                {
                case '1':
                {
                    h.availability();
                    break;
                }
                case '2':
                {
                    h.searchroom();
                    break;
                }
                case '3':
                {
                    h.CheckIn();
                    break;
                }
                case '4':
                {
                    h.searchcust();
                    break;
                }
                case '5':
                {
                    h.Summary();
                    break;
                }
                case '6':
                {
                    h.CheckOut();
                    break;
                }
                case '7':
                    goto log;
                case '8':
                    goto Exit;
                default:
                    cout << "Invalid Choice." << endl;
                    break;
                }
            } while (ch3 != '7');
            break;
        }

        case '3':
        {
            cout << "Thank you!";
            break;
        }

        default:
        {
            cout << "Invalid Choice." << endl;
            break;
        }
        }
    } while (ch != '3');
    // Free the allocated memory for Login pointers
    delete managerLogin;
    delete adminLogin;
Exit:
    return 0;
}