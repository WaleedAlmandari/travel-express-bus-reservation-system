#include <iostream>
#include<iomanip>
#include <conio.h>
#include<vector>
#include <algorithm>
#include<chrono>
#include <thread>
#include <sstream>
#include <fstream>
#include <regex>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;
using namespace sql;
sql::Connection* globalCon = nullptr;
sql::Connection* connection;
sql::Statement* statement;
sql::ResultSet* resultSet;
sql::PreparedStatement* pstmt;

void connectToDatabase();

void closeDatabaseConnection();

void executeInstruction(const string& instruction);

sql::ResultSet* executeQuery(const string& query);

void main_menu();

void login_page();

void registerUser();

void admin_menu(string, string);

void staff_menu(string, string);

void cust_menu(string, string);

bool doesIDExist(const string& id);

void admin_staff(string ac, string pw);

void admin_cust(string ac, string pw);

void admin_driver(string ac, string pw);

void admin_bus(string ac, string pw);

void report(string ac, string pw);

void admin_about_me(string ac, string pw);

void admin_trip(string ac, string pw);

void staff_trip(string ac, string pw);

void staff_cust(string ac, string pw);

void staff_driver(string ac, string pw);

void staff_bus(string ac, string pw);

void staff_about_me(string ac, string pw);

void about_me(string ac, string pw);

void booking(string custid, string pass);

void mybooking(string account, string password);

void add_trip(string ac, string pass);

void update_trip(string ac, string pass);

void delete_trip(string ac, string pass);

void trip_list();

void add_staff(string ac, string pass);

void update_staff(string ac, string pass);

void delete_staff(string ac, string pass);

void staff_list();

void admin_cust(string ac, string pw);

void displayTable(const vector<vector<string>>& table);

void bus_list();

void add_bus(string ac, string pass);

void update_bus(string ac, string pass);

void delete_bus(string ac, string pass);

void driver_list();

void add_driver(string ac, string pass);

void update_driver(string ac, string pass); 

void delete_driver(string ac, string pass);

void staff_add_trip(string ac, string pass);

void staff_update_trip(string ac, string pass);

void staff_delete_trip(string ac, string pass);

void staff_trip_list();

void staff_bus_list();

void staff_driver_list();

void staff_add_bus(string ac, string pass);

void staff_update_bus(string ac, string pass);

void staff_delete_bus(string ac, string pass);

void staff_add_driver(string ac, string pass);

void staff_update_driver(string ac, string pass);

void staff_delete_driver(string ac, string pass);

void cust_trip_list();

void payment_menu(string id, string ps, string tr);

void payment(string customerid, string password, string paymethod, string fl, string trip, string seat);

void online_payment(string ac, string pw, string paymethod, string fl, string trip, string seat);

string generatereceipt(const std::string& trip, const std::string& bd, const std::string& d, const std::string& st, const std::string& et, const std::string& du, const std::string& ds, const std::string de, const std::string& p, const std::string& seatnumber, const std::string& bid, const std::string& bdate, const std::string& pdate, const std::string& pid, const std::string& pmethod, const std::string& cid);

double discount(string a, string p, string trip);

string randomnumbercr(int previousNumber);

string randomnumberon(int previousNumber);

void monthly_report(string ac, string pass);

void selected_monthly_report(string ac, string pw, string month, string year, string monthname);

void annual_report(string ac, string pass);

void selected_annual_report(string ac, string pw, string year);

void date_report(string ac, string pass);

void selected_date_report(string ac, string pw, string start_date, string end_date);

void SearchForTrip(string custid, string pass);

void chart_report(string akaun, string pass);

void drawMonthlyBookingsChart(const string& ac, const string& pw, const string& year);

void drawDestinationBookingsChart(const string& ac, const string& pw, const string& year);

bool isValidEmail(const string& email);

bool isValidPhoneNumber(const string& phoneNumber);

bool isValidDate(const string& date);

void saveReceiptToFile(const string& receipt, const string& filename);


int main() {
   
    main_menu();


    return 0; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void connectToDatabase() {
    try {
        sql::Driver* driver = get_driver_instance();
        globalCon = driver->connect("tcp://127.0.0.1:3306", "root", "");
        globalCon->setSchema("workshop1"); // Replace with your database name
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void closeDatabaseConnection() {
    if (globalCon) {
        globalCon->close();
        delete globalCon;
        globalCon = nullptr;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void executeInstruction(const string& instruction) {
    try {
        if (globalCon == nullptr || globalCon->isClosed()) {
            connectToDatabase(); // Ensure connection is established
        }
        sql::Statement* stmt = globalCon->createStatement();
        stmt->execute(instruction);
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
sql::ResultSet* executeQuery(const string& query) {
    try {
        // Check if a valid connection exists and is open
        if (globalCon == nullptr || globalCon->isClosed()) {
            // Attempt to establish a connection
            connectToDatabase();
        }

        // Create a statement object for executing the query
        sql::Statement* stmt = globalCon->createStatement();

        // Execute the query and store the result set
        sql::ResultSet* rs = stmt->executeQuery(query);

        // Return the result set
        return rs;
    }
    catch (sql::SQLException& e) {
        // Handle any SQL exceptions that occur during query execution
        cerr << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
        return nullptr;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool doesIDExist(const string& id) {
    try {
        // Create a statement to query all tables for the given ID
        sql::Statement* stmt = globalCon->createStatement();
        string query = "SELECT COUNT(*) FROM admin WHERE admin_ID = '" + id + "'";
        query += " UNION ALL SELECT COUNT(*) FROM staff WHERE staff_ID = '" + id + "'";
        query += " UNION ALL SELECT COUNT(*) FROM customer WHERE customer_ID = '" + id + "'";

        // Execute the query
        sql::ResultSet* res = stmt->executeQuery(query);

        // Check if the ID exists in any of the tables
        int totalRows = 0;
        while (res->next()) {
            totalRows += res->getInt(1);
        }

        delete res;
        delete stmt;

        // Return true if any row exists, indicating that the ID is already in use
        return totalRows > 0;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
        // Return true to handle the error condition conservatively
        return true;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isValidEmail(const std::string& email) {
    // Define the regular expression for a valid email address
    const std::regex pattern(R"((\w+)(\.|\+)?(\w*)@(\w+)(\.(\w+))+)");

    return std::regex_match(email, pattern);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isValidPhoneNumber(const std::string& phoneNumber) {
    // Define the regex pattern for a valid phone number with 10 or 11 digits, starting with 0
    const regex pattern(R"(^0\d{9,10}$)");
    return regex_match(phoneNumber, pattern);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isValidDate(const string& date) {
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    int year, month, day;
    char dash1, dash2;
    istringstream dateStream(date);

    dateStream >> year >> dash1 >> month >> dash2 >> day;

    if (dateStream.fail() || dash1 != '-' || dash2 != '-') return false;
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) return false;
    
    return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main_menu() {
    string mmoption;

    cout << endl;
    cout << "\t\t\t+==============================+" << endl;
    cout << "\t\t\t|         TRAVEL EXPRESS       |" << endl;
    cout << "\t\t\t+==============================+" << endl;
    cout << "\t\t\t|                              |" << endl;
    cout << "\t\t\t|     1.  Login                |" << endl;
    cout << "\t\t\t|                              |" << endl;
    cout << "\t\t\t|     2.  Register             |" << endl;
    cout << "\t\t\t|                              |" << endl;
    cout << "\t\t\t|     3.  Exit                 |" << endl;
    cout << "\t\t\t+==============================+" << endl;
    cout << endl;

    cout << "Enter 1 to go to Login Page and 2 Register Page and 3 to Exit   \n";
    cout << endl;

    do {
        cout << "Option  :  ";
        getline(cin, mmoption);

        if (mmoption == "1") {
            system("cls");
            login_page();
        }
        else if (mmoption == "2") {
            system("cls");
            registerUser();
        }
        else if (mmoption == "3") {
            system("cls");
            cout << "\n\tThank you for Visiting! Exiting..." << endl;
            exit(0);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (mmoption != "1" && mmoption != "2" && mmoption != "3");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void login_page() {
    connectToDatabase();

    // Check if the database connection was successful
    if (!globalCon) {
        cerr << "Failed to connect to the database." << endl;
        return;
    }

    string username, password, userType;

    cout << "\n\n\t\t+============================+" << endl;
    cout << "\t\t|          LOGIN PAGE        |" << endl;
    cout << "\t\t+============================+" << endl;
    cout << endl;

    bool loggedIn = false;
    while (!loggedIn) {
        cout << "\tEnter Username : ";
        cin >> username;

        cout << "\tEnter Password : ";
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    // Remove the last character from the password and erase the '*' on the console
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        bool validUserType = false;
        while (!validUserType) {

            cout << "\tEnter User Type (Admin, Staff, or Customer) : ";
            cin>>userType;
            // Convert user type to lowercase
            transform(userType.begin(), userType.end(), userType.begin(), ::tolower);

            // Check if the user type is valid
            if (userType == "admin" || userType == "staff" || userType == "customer") {
                validUserType = true;
            }
            else {
                cout << "\n\tInvalid user type. Please enter 'Admin', 'Staff', or 'Customer'." << endl;
            }
        }

        string tableName = userType;

        // Prepare the SQL query with placeholders for username and password
        string query = "SELECT * FROM " + tableName + " WHERE " + tableName + "_ID = ? AND " + tableName + "_password = ?";
       
        sql::PreparedStatement* pstmt = globalCon->prepareStatement(query);
       
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        // Execute the query
        sql::ResultSet* resultSet = pstmt->executeQuery();

        // Check if the user exists and the password is correct
        if (resultSet->next()) {
            cout << "\n\tLogin successful! Welcome, " << resultSet->getString(tableName + "_name") << "!" << endl;

            
            if (userType == "admin") {
                admin_menu(username, password);
            }
            else if (userType == "staff") {
                staff_menu(username, password);
            }
            else if (userType == "customer") {
                cust_menu(username, password);
            }
            loggedIn = true; // Set loggedIn to true to exit the loop
        }
        else {
            char tryAgain;
            cout << "\n\tLogin failed. Invalid username or password." << endl;
            do {
                cout << "\tDo you want to try again? (Y/N): ";
                cin >> tryAgain;
                //toupper(tryAgain);
                if ( tryAgain == 'N' || tryAgain == 'n')
                {
                    main_menu();
                }
                else if (tryAgain == 'Y' || tryAgain == 'y')
                {
                    login_page();
                }
                else
                {
                     cout << "\n\tInvalid Input Please Enter (Y/N)\n";
                }
               } while (tryAgain != 'Y' && tryAgain != 'y' && tryAgain != 'N' && tryAgain != 'n');
           
            // Clear password for the next attempt
            password.clear();
            // Clean up
            delete resultSet;
            delete pstmt;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void registerUser() {
    // Call the function to connect to the database
    connectToDatabase();
   
    string account_id, name, email, phone, address, password, accountType , confirmPassword;

    cout << "\n\n\t\t+============================+" << endl;
    cout << "\t\t|        REGISTER PAGE       |" << endl;
    cout << "\t\t+============================+" << endl;
    cout << endl;
   // cin.ignore();
   
    bool uniqueID = false;
    while (!uniqueID) {
        cout << "\tEnter Username : ";
        getline(cin, account_id);

        // Check if the account ID already exists in any of the tables
        if (!doesIDExist(account_id)) {
            uniqueID = true;
        }
        else {
            cerr << "\n\tThis ID already exists. Please choose a different one." << endl;
        }
    }

    cout << "\tEnter Name       : ";
   // cin.ignore(); // Ignore the newline character left in the stream
    getline(cin, name);
    cout << endl;

    bool validEmail = false;
    while (!validEmail) {
        cout << "\tEnter Email : ";
       // cin.ignore();
        getline(cin, email);

        // Check if the account ID already exists in any of the tables
        if (isValidEmail(email)) {
            validEmail = true;
        }
        else {
            cerr << "\n\tThis is an Invalid Email , Please Enter a Valid One ." << endl;
        }
    }
    bool validPhoneNumber = false;
    while (!validPhoneNumber) {
        cout << "\tEnter Phone Number : ";
        getline(cin, phone);

        if (isValidPhoneNumber(phone)) {
            validPhoneNumber = true;
        }
        else {
            cerr << "\n\tThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
        }
    }

    cout << "\tEnter Address    : ";
    //cin.ignore(); // Ignore the newline character left in the stream
    getline(cin, address);
    cout << endl;

    do {
        cout << "\tEnter Password   : ";
        getline(cin, password);
        cout << "\tConfirm the new password : ";
        getline(cin, confirmPassword);

        if (password != confirmPassword) {
            cout << "\tPasswords do not match. Try again." << endl;
        }
    } while (password != confirmPassword);
    
    cout << endl;

    // Prompt for account type
    do {
        cout << "\tEnter Account Type (Admin, Staff, or Customer)   :  ";
       getline( cin,accountType);

        // Convert account type to lowercase
        transform(accountType.begin(), accountType.end(), accountType.begin(), ::tolower);

        // Check if the account type is valid
        if (accountType != "admin" && accountType != "staff" && accountType != "customer") {
            cerr << "\n\tInvalid account type. Please choose from Admin, Staff, or Customer." << endl;
        }
    } while (accountType != "admin" && accountType != "staff" && accountType != "customer");

    // Display the gathered information for verification
    cout << "\n\tPlease verify the following information:" << endl;
    cout << "\tAccount ID   : " << account_id << endl;
    cout << "\tName         : " << name << endl;
    cout << "\tEmail        : " << email << endl;
    cout << "\tPhone        : " << phone << endl;
    cout << "\tAddress      : " << address << endl;
    cout << "\tAccount Type : " << accountType << endl;

    // Confirm registration
    string confirm;
    string tryAgain;
    bool confirmed = false;
    do {
        cout << "\n\tIs the information correct? (Y/N): ";
        cin >> confirm;
        transform(confirm.begin(), confirm.end(), confirm.begin(), ::toupper);

        if (confirm == "Y") {
            confirmed = true;
        }
        else if (confirm == "N") {
            cout << "\n\tRegistration Failed. Please try again." << endl;
            do {
                cout << "\tDo you want to try again? (Y/N): ";
                cin >> tryAgain;

                if (tryAgain == "Y" || tryAgain == "y")
                {
                    cin.ignore();
                    registerUser();
                }
                else if (tryAgain == "N" || tryAgain == "n")
                {
                    cout << "\n\tThank you for registering! Exiting..." << endl;
                    exit(0); 
                }
                else 
                {
                    cout << "\n\tInvalid Input Please Enter (Y/N)\n";
                }
            } while (tryAgain != "Y" && tryAgain != "y" && tryAgain != "N" && tryAgain != "n");

          //  return;
        }
        else {
            cout << "\n\tInvalid input. Please enter Y or N." << endl;
        }
    } while (!confirmed);

    string tableName = "";
    if (accountType == "admin") {
        tableName = "admin";
    }
    else if (accountType == "staff") {
        tableName = "staff";
    }
    else if (accountType == "customer") {
        tableName = "customer";
    }

    // Execute the SQL query to insert the user into the database
    string insertQuery = "INSERT INTO " + tableName + " (";
    insertQuery += (tableName == "admin") ? "admin_ID, admin_name, admin_email, admin_phonenumber, admin_address, admin_password" :
        (tableName == "staff") ? "staff_ID, staff_name, staff_email, staff_phonenumber, staff_address, staff_password" :
        "customer_ID, customer_name, customer_email, customer_phonenumber, customer_address, customer_password";
    insertQuery += ") VALUES ('" + account_id + "', '" + name + "', '" + email + "', '" + phone + "', '" + address + "', '" + password + "')";

    try {
        executeInstruction(insertQuery);
        cout << "\n\tRegistration successful! Please login with your new credentials." << endl;

        // Prompt user if they want to login or exit
        string choice;
        bool validChoice = false;
        do {
            cout << "\n\tDo you want to login now? (Y/N): ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
            if (choice == "Y") {
               
                login_page();
                validChoice = true;
            }
            else if (choice == "N") {
                cout << "\n\tThank you for registering! Exiting..." << endl;
                validChoice = true;
            }
            else {
                cout << "\n\tInvalid choice. Please enter Y or N." << endl;
            }
        } while (!validChoice);
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_menu(string ak, string pss)
{
    // Connect to the database
    connectToDatabase();

    // Prepare SQL statement to check admin credentials
    string query = "SELECT * FROM admin WHERE admin_ID = '" + ak + "' AND admin_password = '" + pss + "'";
    executeInstruction(query);

   
    string amoption;
    cout << endl;
    cout << "\t\t\t+========================================+" << endl;
    cout << "\t\t\t|               ADMIN MENU               |" << endl;
    cout << "\t\t\t+========================================+" << endl;
    cout << "\t\t\t|                                        |" << endl;
    cout << "\t\t\t|      1. Trip Management                |" << endl;
    cout << "\t\t\t|      2. Staff Management               |" << endl;
    cout << "\t\t\t|      3. Customer Management            |" << endl;
    cout << "\t\t\t|      4. Driver Management              |" << endl;
    cout << "\t\t\t|      5. Bus Management                 |" << endl;
    cout << "\t\t\t|      6. Report Module                  |" << endl;
    cout << "\t\t\t|      7. User Profile                   |" << endl;
    cout << "\t\t\t|      8. Main Page                      |" << endl;
    cout << "\t\t\t|                                        |" << endl;
    cout << "\t\t\t+========================================+" << endl;

    cout << endl;


    do {
        cout << "Option : ";
        cin >> amoption;

        if (amoption == "1")
        {
            system("cls");
            admin_trip(ak, pss);
        }
        else if (amoption == "2")
        {
            system("cls");
            admin_staff(ak, pss);
        }
        else if (amoption == "3")
        {
            system("cls");
            admin_cust(ak, pss);
        }
        else if (amoption == "4")
        {
            system("cls");
            admin_driver(ak, pss);
        }
        else if (amoption == "5")
        {
            system("cls");
            admin_bus(ak, pss);
        }
        else if (amoption == "6")
        {
            system("cls");
            report(ak, pss);
        }
        else if (amoption == "7")
        {
            system("cls");
            admin_about_me(ak, pss);
        }
        else if (amoption == "8")
        {
            system("cls");
            main_menu();
        }
        else
        {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (amoption != "1" && amoption != "2" && amoption != "3" && amoption != "4" && amoption != "5" && amoption != "6" && amoption != "7" && amoption != "8");


    closeDatabaseConnection();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_menu(string ak, string pss)
{

    string smoption;
    cout << endl;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|         STAFF MANAGEMENT          |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|       1. Manage Trips             |" << endl;
    cout << "\t\t\t|       2. Manage Customers         |" << endl;
    cout << "\t\t\t|       3. Manage Drivers           |" << endl;
    cout << "\t\t\t|       4. Manage Buses             |" << endl;
    cout << "\t\t\t|       5. User Profile             |" << endl;
    cout << "\t\t\t|       6. Main Menu                |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    
    cout << endl;

      do {
       cout << endl;
       cout << "Option : ";
       cin >> smoption;
       cout << endl;
       if (smoption == "1")
       {
           system("cls");
           staff_trip(ak, pss);
       }
       else if (smoption == "2")
       {
           system("cls");
           staff_cust(ak, pss);
       }
       else if (smoption == "3")
       {
           system("cls");
           staff_driver(ak, pss);
       }
       else if (smoption == "4")
       {
           system("cls");
           staff_bus(ak, pss);
       }
       else if (smoption == "5")
       {
           system("cls");
           staff_about_me(ak, pss);
       }
       else if (smoption == "6")
       {
           system("cls");
           main_menu();
       }
       else
       {
           cout << endl;
           cout << "Incorrect" << endl;
       }
   } while (smoption != "1" && smoption != "2" && smoption != "3" && smoption != "4" && smoption != "5");

 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cust_menu(string accid, string psswd)
{
    string option;

    cout << "\n"; 

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|    TRAVEL EXPRESS BOOKING SYSTEM  |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|       1. User Profile             |" << endl;
    cout << "\t\t\t|       2. Search For a Trip        |" << endl;
    cout << "\t\t\t|       3. See All Trips            |" << endl;
    cout << "\t\t\t|       4. My Booking               |" << endl;
    cout << "\t\t\t|       5. Main Menu                |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;

    cout << endl;

    do {
        cout << "Option  :  ";
        cin >> option;

        if (option == "1")
        {
            system("cls");
            about_me(accid, psswd);
        }
        else if (option == "2")
        {
            system("cls");
            SearchForTrip(accid, psswd);
        }
        else if (option == "3")
        {
            system("cls");
            booking(accid, psswd);
        }
        else if (option == "4")
        {
            system("cls");
            mybooking(accid, psswd);
        }
        else if (option == "5")
        {
            system("cls");
            main_menu();
        }
        else { 
            cout << endl;
            cout << "Incorrect" << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4"); 

       closeDatabaseConnection();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_trip(string ac, string pw) {
    connectToDatabase();


    string option , bam;
    cout << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|          TRIP MANAGEMENT          |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Trip               |" << endl;
    cout << "\t\t\t|         2. Edit Trip              |" << endl;
    cout << "\t\t\t|         3. Delete Trip            |" << endl;
    cout << "\t\t\t|         4. View Trip List         |" << endl;;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;

    do {
        cout << "Option  : ";
        cin >> option;
        if (option == "1") {
            system("cls");
            add_trip(ac, pw);
        }
        else if (option == "2") {
            system("cls");
            update_trip(ac, pw);
        }
        else if (option == "3") {
            system("cls");
            delete_trip(ac, pw);
        }
        else if (option == "4") {
            system("cls");
            trip_list();
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;

                if (bam == "1") {
                    system("cls");
                    admin_trip(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5") {
            system("cls");
            admin_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    closeDatabaseConnection();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void admin_staff(string ac, string pw) 
{
    connectToDatabase();

   
    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|         STAFF MANAGEMENT          |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Staff              |" << endl;
    cout << "\t\t\t|         2. Edit Staff             |" << endl;
    cout << "\t\t\t|         3. Delete Staff           |" << endl;
    cout << "\t\t\t|         4. View Staff List        |" << endl;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    do {
        cout << "Option  : ";
        cin >> option;
        if (option == "1") {
            system("cls");
            add_staff(ac, pw);
        }
        else if (option == "2") {
            system("cls");
            update_staff(ac, pw);
        }
        else if (option == "3") {
            system("cls");
            delete_staff(ac, pw);
        }
        else if (option == "4") {
            string bam;
            system("cls");
            staff_list();
            cout << endl;
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;

                if (bam == "1") {
                    system("cls");
                    admin_staff(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5") {
            system("cls");
            admin_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");
    
    closeDatabaseConnection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_cust(string ac, string pw)
{
    connectToDatabase();

   

    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|        CUSTOMER MANAGEMENT        |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|       1. View Customer List       |" << endl;
    cout << "\t\t\t|       2. Back                     |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;
    do {
        cout << "Option  :  ";
        cin >> option;
        cout << endl;
        if (option == "1")
        {
            system("cls");
            try {
                connectToDatabase();

                // Execute the query
                ResultSet* res = executeQuery("SELECT * FROM customer");

                vector<vector<string>> table;
                vector<string> columnNames =
                {
                    "| Customer ID", "| Name", "| Email", "| Address", "| Phone Number"
                };

                // Add table headers with custom column names
                table.push_back(columnNames);

                while (res->next()) {
                    vector<string> rowData;
                    rowData.push_back(res->getString("customer_ID"));
                    rowData.push_back(res->getString("customer_name"));
                    rowData.push_back(res->getString("customer_email"));
                    rowData.push_back(res->getString("customer_address"));
                    rowData.push_back(res->getString("customer_phonenumber"));

                    table.push_back(rowData);
                }
                displayTable(table);

                
            }
            catch (sql::SQLException& e) {
                cout << "# ERR: " << e.what();
                cout << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            }
            string gbm;
            cout << endl;
            cout << "Enter 1 to Back " << endl;
            do {
                cout << "Option  :  ";
                cin >> gbm;

                if (gbm == "1")
                {
                    system("cls");
                    admin_menu(ac, pw);
                }
                else
                {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (gbm != "1");
        }
        else if (option == "2")
        {
            system("cls");
            admin_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2");

    closeDatabaseConnection();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void displayTable(const vector<vector<string>>& table)
{
    if (table.empty()) {
        cout << "No records found." << std::endl;
        return;
    }

    // Calculate the width for each column
    vector<size_t> columnWidths(table[0].size(), 0);
    for (const auto& row : table) {
        for (size_t i = 0; i < row.size(); ++i) {
            columnWidths[i] = max(columnWidths[i], row[i].length());
        }
    }

    // Print the table headers
    for (size_t i = 0; i < table[0].size(); ++i) {
        cout << setw(columnWidths[i]) << left << table[0][i] << " ";
    }
    cout << endl;

    // Print a horizontal line separating the headers and data
    for (size_t i = 0; i < columnWidths.size(); ++i) {
        cout << string(columnWidths[i], '-') << " ";
    }
    cout << endl;

    // Print the table data
    for (size_t i = 1; i < table.size(); ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            cout << setw(columnWidths[j]) << left << table[i][j] << " ";
        }
        cout << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_driver(string ac, string pw)
{
    connectToDatabase();


    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|         DRIVER MANAGEMENT         |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Driver             |" << endl;
    cout << "\t\t\t|         2. Edit Driver            |" << endl;
    cout << "\t\t\t|         3. Delete Driver          |" << endl;
    cout << "\t\t\t|         4. View Driver List       |" << endl;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;
    do {
        cout << "Option  : ";
        cin >> option;
        cout << endl;
        if (option == "1")
        {
            system("cls");
            add_driver(ac, pw);
        }
        else if (option == "2")
        {
            system("cls");
            update_driver(ac, pw);
        }
        else if (option == "3")
        {
            system("cls");
            delete_driver(ac, pw);
        }
        else if (option == "4")
        {
            string bam;
            system("cls");
            driver_list();
            cout << endl;
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;
                cout << endl;
                if (bam == "1")
                {
                    system("cls");
                    admin_driver(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5")
        {
            system("cls");
            admin_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    closeDatabaseConnection();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_bus(string ac, string pw)
{
    connectToDatabase();

    
    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|          BUS MANAGEMENT           |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Bus                |" << endl;
    cout << "\t\t\t|         2. Edit Bus               |" << endl;
    cout << "\t\t\t|         3. Delete Bus             |" << endl;
    cout << "\t\t\t|         4. View Bus List          |" << endl;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;
    do
    {
        cout << "Option  : ";
        cin >> option;
        cout << endl;
        if (option == "1")
        {
            system("cls");
            add_bus(ac, pw);
        }
        else if (option == "2")
        {
            system("cls");
            update_bus(ac, pw);
        }
        else if (option == "3")
        {
            system("cls");
            delete_bus(ac, pw);
        }
        else if (option == "4")
        {
            string bam;
            system("cls");
            bus_list();
            cout << endl;
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;
                cout << endl;
                if (bam == "1")
                {
                    system("cls");
                    admin_bus(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5")
        {
            system("cls");
            admin_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    closeDatabaseConnection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report(string ac, string pw)
{
    connectToDatabase();

    
    string option;

    cout << endl;
    cout << endl;

    cout << "\t\t\t+================================+" << endl;
    cout << "\t\t\t|             REPORT             |" << endl;
    cout << "\t\t\t+================================+" << endl;
    cout << "\t\t\t|                                |" << endl;
    cout << "\t\t\t|      1. Monthly Report         |" << endl;
    cout << "\t\t\t|      2. Yearly Report          |" << endl;
    cout << "\t\t\t|      3. Custom Date            |" << endl;
    cout << "\t\t\t|      4. Data Visualization     |" << endl;
    cout << "\t\t\t|      5. Back                   |" << endl; 
    cout << "\t\t\t|                                |" << endl;
    cout << "\t\t\t+================================+" << endl;

    cout << endl;
   // cout << "Enter 1 for Monthly, 2 for Yearly Report, 3 for Customize Date Report, 4 for Back option" << endl;
    cout << endl;
    do {
        cout << "\nEnter 1 for Monthly Report, 2 for Yearly Report, 3 for Customize Date Report, 4 for Data Visualization, 5  for Back option" << endl;
        cout << "\nOption  :  ";
        cin >> option;

        if (option == "1")
        {
            system("cls");
            monthly_report(ac, pw);
        }
        else if (option == "2")
        {
            system("cls");
            annual_report(ac, pw);
        }
        else if (option == "3")
        {
            system("cls");
            date_report(ac, pw);
        }
        else if (option == "4")
        {
            system("cls");
            chart_report(ac, pw);
        }
        else if (option == "5")
        {
            system("cls");
            admin_menu(ac, pw);
        }
        else
        {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    closeDatabaseConnection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin_about_me(string ac, string pw) {
    string dp, yon, choice, newValue, column, goback, newPassword, confirmPassword;

    try {
        connectToDatabase();

        string query = "SELECT * FROM admin WHERE admin_ID = ? AND admin_password = ?";
        sql::PreparedStatement* pstmt = globalCon->prepareStatement(query);
        pstmt->setString(1, ac);
        pstmt->setString(2, pw);

        sql::ResultSet* rs = pstmt->executeQuery();

        while (rs->next()) {
            cout << "\t\t\t                USER  PROFILE                " << endl;
            cout << "\t\t\t=============================================" << endl;
            cout << endl;
            cout << "\t\t\t   Username       : " << rs->getString("admin_ID") << endl;
            cout << endl;
            cout << "\t\t\t   Name           : " << rs->getString("admin_name") << endl;
            cout << endl;
            cout << "\t\t\t   Email          : " << rs->getString("admin_email") << endl;
            cout << endl;
            cout << "\t\t\t   Address        : " << rs->getString("admin_address") << endl;
            cout << endl;
            cout << "\t\t\t   Phone Number   : " << rs->getString("admin_phonenumber") << endl;
            cout << endl;
            cout << endl;

            cout << "Do you want to change your details?" << endl;
            do {
                cout << "Enter 1 for Update details, 2 for Back" << endl;
                cout << endl;

                cout << "Option  :  ";
                cin >> yon;

                if (yon == "1") {
                    do {
                        cout << endl;
                        cout << "Which detail do you want to update?" << endl;
                        cout << "1. Email" << endl;
                        cout << "2. Name" << endl;
                        cout << "3. Address" << endl;
                        cout << "4. Phone Number" << endl;
                        cout << "5. Password" << endl;
                        cout << "6. Back" << endl;
                        cout << endl;

                        cout << "Option: ";
                        cin >> choice;
                        cin.ignore();

                        if (choice == "6") {
                            system("cls");
                            this_thread::sleep_for(chrono::seconds(1));
                            admin_menu(ac, pw);
                            break;
                        }

                        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5") {
                            cout << "Invalid option. Please enter a number between 1 and 6." << endl;
                            continue;
                        }

                        if (choice == "5") {
                            do {
                                cout << "Enter the new password: ";
                                getline(cin, newPassword);
                                cout << "Confirm the new password: ";
                                getline(cin, confirmPassword);

                                if (newPassword != confirmPassword) {
                                    cout << "Passwords do not match. Try again." << endl;
                                }
                            } while (newPassword != confirmPassword);

                            column = "admin_password";
                            newValue = newPassword;
                        }
                        else {
                            cout << "Enter the new value: ";
                            if (choice == "1") {
                                column = "admin_email";
                                bool validEmail = false;
                                while (!validEmail) {
                                    getline(cin, newValue);

                                    if (isValidEmail(newValue)) {
                                        validEmail = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Email, Please Enter a Valid One." << endl;
                                    }
                                }
                            }
                            else if (choice == "2") {
                                column = "admin_name";
                                getline(cin, newValue);
                            }
                            else if (choice == "3") {
                                column = "admin_address";
                                getline(cin, newValue);
                            }
                            else if (choice == "4") {
                                column = "admin_phonenumber";
                                bool validPhoneNumber = false;
                                while (!validPhoneNumber) {
                                    getline(cin, newValue);

                                    if (isValidPhoneNumber(newValue)) {
                                        validPhoneNumber = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                                    }
                                }
                            }
                        }

                        connectToDatabase();
                        // Prepare and execute SQL statement to update admin details
                        query = "UPDATE admin SET " + column + " = ? WHERE admin_ID = ?";
                        sql::PreparedStatement* stmt = globalCon->prepareStatement(query);
                        stmt->setString(1, newValue);
                        stmt->setString(2, ac);
                        stmt->executeUpdate();

                        cout << endl;
                        cout << "\t\t-------------------------------" << endl;
                        cout << "\t\t|      Update Successfully     |" << endl;
                        cout << "\t\t-------------------------------" << endl;
                        cout << endl;

                        delete stmt;
                        this_thread::sleep_for(chrono::seconds(4));
                        system("cls");
                        admin_menu(ac, pw);
                    } while (choice != "6");
                }
                else if (yon == "2") {
                    system("cls");
                    this_thread::sleep_for(chrono::seconds(1));
                    admin_menu(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (yon != "1" && yon != "2");
        }

        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bus_list() {
    try {
        connectToDatabase();

        cout << endl << endl;
        cout << "    BUS  LIST" << endl;
        cout << "----------------" << endl;
        cout << endl << endl;

        // Execute SQL query to retrieve bus list
        ResultSet* res = executeQuery("SELECT * FROM bus");

        vector<vector<string>> table;
        vector<string> columnNames = {
            "|  Number Plate", "|  Capacity", "|  Type", "|  Brand", "|  Condition"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);

        // Fetch and display bus data
        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("number_plate"));
            rowData.push_back(res->getString("capacity"));
            rowData.push_back(res->getString("type"));
            rowData.push_back(res->getString("brand"));
            rowData.push_back(res->getString("condition"));

            table.push_back(rowData);
        }

        // Display the table
        displayTable(table);

        delete res;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_bus(string akaun, string pass) {
    try {
        connectToDatabase();

        string np, t, br, co, bo, aboption, choice;
        int ca;

        bus_list();
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back Menu or 2 to Add Bus" << endl;
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                admin_bus(akaun, pass);
            }
            else if (bo == "2") {
                cin.ignore();

                // Check if the bus already exists
                int count = 0;
                do {
                    cout << "\nEnter Bus Number Plate to Add: ";
                    getline(cin, np);

                    ResultSet* res = executeQuery("SELECT COUNT(*) FROM bus WHERE number_plate = '" + np + "'");

                    if (res->next()) {
                        count = res->getInt(1);
                        if (count > 0) {
                            cout << "Bus already exists." << endl;
                            do {
                                cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                cout << "Option  :  ";
                                cin >> choice;
                                if (choice == "1") {
                                    system("cls");
                                    add_bus(akaun, pass);
                                }
                                else if (choice == "2") {
                                    system("cls");
                                    admin_bus(akaun, pass);
                                }
                                else {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (choice != "1" && choice != "2");
                        }
                        delete res;
                    }
                } while (count > 0);

                cout << "Bus Capacity  : ";
                cin >> ca;
                cin.ignore();
                cout << "Bus Type  : ";
                getline(cin, t);
                cout << "Bus Brand  : ";
                getline(cin, br);
                cout << "Bus Condition : ";
                getline(cin, co);
                cout << "==========================================================" << endl;
                cout << endl;
                cout << "     Bus Number Plate    : " << np << endl;
                cout << "     Bus Capacity        : " << ca << endl;
                cout << "     Bus Type            : " << t << endl;
                cout << "     Bus Brand           : " << br << endl;
                cout << "     Bus Condition       : " << co << endl;
                cout << endl;
                cout << "==========================================================" << endl;
                cout << endl;
                cout << "Are you sure want to Add this Bus? (Y or N)" << endl;
                cout << "Enter Y for Yes, N for No" << endl;
                do {
                    cout << "Option  : ";
                    cin >> aboption;

                    if (aboption == "Y" || aboption == "y") {
                        string ab;
                        executeInstruction("INSERT INTO bus (number_plate, capacity, type, brand, `condition`) VALUES ('" + np + "', " + to_string(ca) + ", '" + t + "', '" + br + "', '" + co + "')");
                        cout << endl;
                        cout << "Bus added successfully." << endl;
                      /*  cout << "Press any key to continue..." << endl;
                        cin >> ab;*/
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        admin_bus(akaun, pass);
                    }
                    else if (aboption == "N" || aboption == "n") {
                        string bw;
                        cout << endl;
                        cout << "***  Bus not Added  ***" << endl;
                        cout << endl;
                        cout << "Press any key to continue..." << endl;
                        cin >> bw;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        add_bus(akaun, pass);
                    }
                    else {
                        cout << "Invalid Input , Please Enter Y for Yes, N for No " << endl;
                        cout << endl;
                    }
                } while (aboption != "Y" && aboption != "y" && aboption != "N" && aboption != "n");
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }

        } while (bo != "1" && bo != "2");

        closeDatabaseConnection();
    }
    catch (const std::exception& e) {
        // Handle the exception here
        cerr << "Exception caught: " << e.what() << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_bus(string akaun, string pass) {
    try {
        connectToDatabase();

        string bm, choice, column, c, b, numplate, condition;

        do {
            system("cls");
            bus_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Update Bus" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> bm;

            if (bm == "1") {
                system("cls");
                admin_bus(akaun, pass);
            }
            else if (bm == "2") {
                int count{};
                do {
                    cout << "\nEnter Bus Number Plate to Update: ";
                    cin >> numplate;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM bus WHERE number_plate = '" + numplate + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << "Bus does not exist." << endl << endl;

                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;

                            if (choice == "1") {
                                count = 0; // Reset count to allow retry
                                break; // Break out of the inner loop to allow re-entering the bus number plate
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_bus(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                system("cls");

                ResultSet* res = executeQuery("SELECT * FROM bus WHERE number_plate = '" + numplate + "'");

                while (res->next()) {
                    cout << "\t\t\t                 BUS DETAIL                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Bus Number Plate    : " << res->getString("number_plate") << endl;
                    cout << endl;
                    cout << "\t\t\t   Capacity            : " << res->getString("capacity") << endl;
                    cout << endl;
                    cout << "\t\t\t   Type                : " << res->getString("type") << endl;
                    cout << endl;
                    cout << "\t\t\t   Brand               : " << res->getString("brand") << endl;
                    cout << endl;
                    cout << "\t\t\t   Condition           : " << res->getString("condition") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Which column you want to update?" << endl;
                    cout << endl;
                    cout << "\t1. Condition        2. Back" << endl;
                    cout << endl;

                    do {
                        cout << "Option  :  ";
                        cin >> column;

                        if (column == "1") {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            cout << "Enter the condition for this Bus:  ";
                            cin.ignore();
                            getline(cin, condition);
                            cout << endl;
                            cout << endl;
                            cout << "Are you sure you want to change " << res->getString("condition") << " to " << condition << " ?" << endl;
                            cout << endl;
                            cout << "Enter Y for Yes, N for No" << endl;
                            cout << endl;
                            do {
                                cout << "Option  :  ";
                                cin >> c;

                                if (c == "Y" || c == "y") {
                                    executeInstruction("UPDATE bus SET `condition` = '" + condition + "' WHERE number_plate = '" + numplate + "'");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << "\t\t\t|      Bus Update Successfully     |" << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress anykey to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    admin_bus(akaun, pass);
                                }
                                else if (c == "N" || c == "n") {
                                    system("cls");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t***  Bus not Updated  ***" << endl;
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress anykey to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    update_bus(akaun, pass);
                                }
                                else {
                                    cout << "Invalid Input , Please Enter Y for Yes, N for No " << endl;
                                    cout << endl;
                                }
                            } while (c != "Y" && c != "y" && c != "N" && c != "n");
                        }
                        else if (column == "2") {
                            system("cls");
                            update_bus(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl;
                            cout << endl;
                        }
                    } while (column != "1" && column != "2");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (bm != "1" && bm != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_bus(string akaun, string pass) {
    try {
        connectToDatabase();

        string numplate, dboption, YorN, choice;

        do {
            system("cls");
            bus_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Bus" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dboption;

            if (dboption == "1") {
                //system("cls");
                admin_bus(akaun, pass);
            }
            else if (dboption == "2") {
                int count{};
                do {
                    cout << "\nEnter Bus Number Plate to Delete: ";
                    cin >> numplate;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM bus WHERE number_plate = '" + numplate + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Bus does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the bus number plate
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_bus(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM bus WHERE number_plate = '" + numplate + "'");
                while (res->next()) {
                    cout << "\t\t\t                 BUS DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Bus Number Plate    : " << res->getString("number_plate") << endl;
                    cout << endl;
                    cout << "\t\t\t   Capacity            : " << res->getInt("capacity") << endl;
                    cout << endl;
                    cout << "\t\t\t   Type                : " << res->getString("type") << endl;
                    cout << endl;
                    cout << "\t\t\t   Brand               : " << res->getString("brand") << endl;
                    cout << endl;
                    cout << "\t\t\t   Condition           : " << res->getString("condition") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure want to Delete this " << numplate << " Bus ?" << endl;


                    do {

                   
                        cout << "Enter Y to Delete N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete bus directly
                            executeInstruction("DELETE FROM bus WHERE number_plate = '" + numplate + "'");
                            cout << endl;
                            cout << "Bus deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            admin_bus(akaun, pass);
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Bus not Deleted  **" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            delete_bus(akaun, pass);
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dboption != "1" && dboption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void driver_list()
{
    connectToDatabase();

    cout << endl;
    cout << endl;
    cout << "    DRIVER  LIST" << endl;
    cout << "-------------------" << endl;
    cout << endl;
    cout << endl;

    try {
        connectToDatabase();

        
        ResultSet* res = executeQuery("SELECT * FROM driver");

        vector<vector<string>> table;
        vector<string> columnNames =
        {
            "|  Driver ID", "|  Name", "|  Address", "|  Phone Number"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);


        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("driver_ID"));
            rowData.push_back(res->getString("driver_name"));
            rowData.push_back(res->getString("driver_address"));
            rowData.push_back(res->getString("driver_phonenumber"));

            table.push_back(rowData);

        }
        displayTable(table);

        delete res;
        closeDatabaseConnection();

        
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_driver(string akaun, string pass)
{
    try {
        connectToDatabase();

        string did, dn, da, dp, bo, adoption, choice;
        

        driver_list();
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back Menu or 2 to Add Driver" << endl;
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                admin_driver(akaun, pass);
            }
            else if (bo == "2") {
                cin.ignore();

                // Check if the bus already exists
                int count = 0;
                do {
                    cout << "\nEnter Driver ID to Add: ";
                    getline(cin, did);

                    ResultSet* res = executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + did + "'");

                    if (res->next()) {
                        count = res->getInt(1);
                        if (count > 0) {
                            cout << "Driver ID already exist." << endl;
                            do {
                                cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                cout << "Option  :  ";
                                cin >> choice;
                                if (choice == "1") {
                                    system("cls");
                                    add_driver(akaun, pass);
                                }
                                else if (choice == "2") {
                                    system("cls");
                                    admin_driver(akaun, pass);
                                }
                                else {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (choice != "1" && choice != "2");
                        }
                        delete res;
                    }
                } while (count > 0);

                cout << "Driver Name  : ";
                getline(cin, dn);
                cout << endl;
                cout << "Driver Address  : ";
                getline(cin, da);
                cout << endl;
                cout << "Driver Phone Number  : ";
                
                bool validPhoneNumber = false;
                while (!validPhoneNumber) {
                    getline(cin, dp);

                    if (isValidPhoneNumber(dp)) {
                        validPhoneNumber = true;
                    }
                    else {
                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                    }
                }

               
                cout << endl;

                cout << "=======================================================================================" << endl;
                cout << endl;
                cout << "     Driver ID               : " << did << endl;
                cout << "     Driver Name             : " << dn << endl;
                cout << "     Driver Address          : " << da << endl;
                cout << "     Driver Phone Number     : " << dp << endl;
                cout << endl;
                cout << "=======================================================================================" << endl;
                cout << endl;
                cout << "Are you sure want to Add this Bus? (Y or N)" << endl;
                cout << "Enter Y for Yes, N for No" << endl;
                do {
                    cout << "Option  : ";
                    cin >> adoption;

                    if (adoption == "Y" || adoption == "y") {
                        string ad;
                        // Execute SQL insert statement to add bus directly
                        executeInstruction("INSERT INTO driver(driver_ID, driver_name, driver_address, driver_phonenumber) VALUES ('" + did + "', '" + dn + "', '" + da + "', '" + dp + "')");
                        cout << endl;
                        cout << "Driver Added Successfully." << endl;
                        /*  cout << "Press any key to continue..." << endl;
                          cin >> ad;*/
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        admin_driver(akaun, pass);
                    } 
                    else if (adoption == "N" || adoption == "n") {
                        string bw;
                        cout << endl;
                        cout << "***  driver not Added  ***" << endl;
                        cout << endl;
                        cout << "Press any key to continue..." << endl;
                        cin >> bw;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        add_driver(akaun, pass);
                    }
                    else {
                        cout << "Invalid Input , Please Enter Y for Yes, N for No " << endl;
                        cout << endl;
                    }
                } while (adoption != "Y" && adoption != "y" && adoption != "N" && adoption != "n");
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }

        } while (bo != "1" && bo != "2");

        closeDatabaseConnection();
    }
    catch (const std::exception& e) {
        // Handle the exception here
        cerr << "Exception caught: " << e.what() << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_driver(string akaun, string pass) {
    try {
        connectToDatabase();

        string dm, choice, column, c, b, driverID, newValue;

        do {
            system("cls");
            driver_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Update Driver" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dm;

            if (dm == "1") {
                system("cls");
                admin_driver(akaun, pass);
                return; // Exit the function
            }
            else if (dm == "2") {
                int count{};
                do {
                    cout << "\nEnter Driver ID to Update: ";
                    cin >> driverID;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + driverID + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << "Driver does not exist." << endl << endl;

                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;

                            if (choice == "1") {
                                count = 0; // Reset count to allow retry
                                break; // Break out of the inner loop to allow re-entering the driver ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_driver(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                system("cls");

                ResultSet* res = executeQuery("SELECT * FROM driver WHERE driver_ID = '" + driverID + "'");

                while (res->next()) {
                    cout << "\t\t\t                 DRIVER DETAIL                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Driver ID           : " << res->getString("driver_ID") << endl;
                    cout << endl;
                    cout << "\t\t\t   Name                : " << res->getString("driver_name") << endl;
                    cout << endl;
                    cout << "\t\t\t   Address             : " << res->getString("driver_address") << endl;
                    cout << endl;
                    cout << "\t\t\t   Phone Number        : " << res->getString("driver_phonenumber") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Which column do you want to update?" << endl;
                    cout << endl;
                    cout << "\t1. Name        2. Address        3. Phone Number        4. Back" << endl;
                    cout << endl;

                    do {
                        cout << "Option  :  ";
                        cin >> column;

                        if (column == "1" || column == "2" || column == "3") {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            if (column == "1") {
                                cout << "Enter the new name for this driver:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "2") {
                                cout << "Enter the new address for this driver:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "3") {
                              
                                cin.ignore();
                                cout << "Enter the new phone number for this driver:  ";

                                bool validPhoneNumber = false;
                                while (!validPhoneNumber) {

                                    getline(cin, newValue);

                                    if (isValidPhoneNumber(newValue)) {
                                        validPhoneNumber = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                                    }
                                }
                            }
                            
                            cout << endl;
                            cout << endl;
                            string oldValue = column == "1" ? res->getString("driver_name") : column == "2" ? res->getString("driver_address") : res->getString("driver_phonenumber");
                            cout << "Are you sure you want to change " << oldValue << " to " << newValue << "?" << endl;
                            cout << endl;
                            cout << "Enter Y for Yes, N for No" << endl;
                            cout << endl;
                            do {
                                cout << "Option  :  ";
                                cin >> c;

                                if (c == "Y" || c == "y") {
                                    string query;
                                    if (column == "1") {
                                        query = "UPDATE driver SET driver_name = '" + newValue + "' WHERE driver_ID = '" + driverID + "'";
                                    }
                                    else if (column == "2") {
                                        query = "UPDATE driver SET driver_address = '" + newValue + "' WHERE driver_ID = '" + driverID + "'";
                                    }
                                    else if (column == "3") {
                                        query = "UPDATE driver SET driver_phonenumber = '" + newValue + "' WHERE driver_ID = '" + driverID + "'";
                                    }
                                    executeInstruction(query);
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << "\t\t\t|      Driver Update Successfully     |" << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress any key to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    admin_driver(akaun, pass);
                                }
                                else if (c == "N" || c == "n") {
                                    system("cls");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t***  Driver not Updated  ***" << endl;
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress any key to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    update_driver(akaun, pass);
                                }
                                else {
                                    cout << "Invalid Input, Please Enter Y for Yes, N for No " << endl;
                                    cout << endl;
                                }
                            } while (c != "Y" && c != "y" && c != "N" && c != "n");
                        }
                        else if (column == "4") {
                            system("cls");
                            update_driver(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl;
                            cout << endl;
                        }
                    } while (column != "1" && column != "2" && column != "3" && column != "4");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dm != "1" && dm != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_driver(string akaun, string pass) {
    try {
        connectToDatabase();

        string driverID, dboption, YorN, choice;

        do {
            system("cls");
            driver_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Driver" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dboption;

            if (dboption == "1") {
                system("cls");
                admin_driver(akaun, pass);
            }
            else if (dboption == "2") {
                int count{};
                do {
                    cout << "\nEnter Driver ID to Delete: ";
                    cin >> driverID;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + driverID + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Driver does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the driver ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_driver(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM driver WHERE driver_ID = '" + driverID + "'");
                while (res->next()) {
                    cout << "\t\t\t                 DRIVER DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Driver ID           : " << res->getString("driver_ID") << endl;
                    cout << endl;
                    cout << "\t\t\t   Name                : " << res->getString("driver_name") << endl;
                    cout << endl;
                    cout << "\t\t\t   Address             : " << res->getString("driver_address") << endl;
                    cout << endl;
                    cout << "\t\t\t   Phone Number        : " << res->getString("driver_phonenumber") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure you want to delete this driver?" << endl;

                    do {
                        cout << "Enter Y to Delete, N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete driver directly
                            executeInstruction("DELETE FROM driver WHERE driver_ID = '" + driverID + "'");
                            cout << endl;
                            cout << "Driver deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            admin_driver(akaun, pass);
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Driver not Deleted  ***" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            delete_driver(akaun, pass);
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dboption != "1" && dboption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void trip_list()
{
    connectToDatabase();

    cout << endl;
    cout << endl;
    cout << "\t\t\t   TRIP  LIST" << endl;
    cout << "\t\t\t----------------" << endl;
    cout << endl;
    cout << endl;

    try {
        connectToDatabase();

        ResultSet* res = executeQuery("SELECT * FROM trip");

        vector<vector<string>> table;
        vector<string> columnNames =
        {
            "| Trip ID", "| Bus", "| Driver ID", "| Destination", "| Start Time", "| End Time", "| Duration", "| Date Start", "| Date End ", "| Price", "| Seat Available"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);

        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("trip_ID"));
            rowData.push_back(res->getString("number_plate"));
            rowData.push_back(res->getString("driver_ID"));
            rowData.push_back(res->getString("destination"));
            rowData.push_back(res->getString("start_time"));
            rowData.push_back(res->getString("end_time"));
            rowData.push_back(res->getString("duration"));
            rowData.push_back(res->getString("start_date"));
            rowData.push_back(res->getString("end_date"));
            rowData.push_back(res->getString("ticket_price"));
            rowData.push_back(res->getString("seat_available"));

            table.push_back(rowData);
        }
        displayTable(table);

        delete res;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_trip(string akaun, string pass) {
    try {
        connectToDatabase(); // Establish the database connection

        string tripId, numplate, drivid, dest, start, end, dur, dtstart, dtend, prc, atoption, bo, choice, choice1, choice2, choice3;
        int count = 0;
        int seat;

        trip_list();
        connectToDatabase();
        cout << endl << endl;
        cout << "Enter 1 to Back Menu or 2 to Add Trip" << endl;
        cout << endl;

        do {
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                admin_trip(akaun, pass);
                return; // Exit the function to avoid further execution
            }
            else if (bo == "2") {
                cin.ignore();

                try {
                    if (!globalCon) {
                        cerr << "Database connection is not established." << endl;
                        return; // Handle the error appropriately
                    }

                    unique_ptr<Statement> stmt(globalCon->createStatement()); // Use smart pointer to manage the statement's lifetime

                    int count1 = 0;

                    do {
                        cout << endl << "Enter Trip ID to add: ";
                        getline(cin, tripId);
                        cout << endl;
                        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*) FROM trip WHERE trip_ID = '" + tripId + "'"));

                        if (res->next()) {
                            count1 = res->getInt(1);
                            if (count1 > 0) {
                                cout << "Trip ID already exists." << endl << endl;
                                do {
                                    cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                    cout << "Option  :  ";
                                    cin >> choice;
                                    if (choice == "1") {
                                        system("cls");
                                        add_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else if (choice == "2") {
                                        system("cls");
                                        admin_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else {
                                        cout << "Incorrect" << endl << endl;
                                    }
                                } while (choice != "1" && choice != "2");
                            }
                        }
                    } while (count1 > 0);

                    do {
                        count = 0;

                        system("cls");
                        bus_list();
                        cout << endl;
                        cout << "Bus number plate for this trip: ";
                        getline(cin, numplate);

                        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*), capacity FROM bus WHERE number_plate = '" + numplate + "'"));

                        if (res->next()) {
                            count = res->getInt(1);
                            seat = res->getInt(2);

                            if (count == 0) {
                                cout << "Bus does not exist." << endl << endl;

                                do {
                                    cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                    cout << "Option: ";
                                    cin >> choice1;

                                    if (choice1 == "1") {
                                        cin.ignore();
                                        break;
                                    }
                                    else if (choice1 == "2") {
                                        system("cls");
                                        admin_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else {
                                        cout << "Incorrect" << endl << endl;
                                    }

                                } while (choice1 != "1" && choice1 != "2");
                            }
                        }

                    } while (count == 0);

                    do {
                        system("cls");
                        driver_list();
                        cout << endl;
                        cout << "Driver for this trip (Driver ID)  : ";
                        getline(cin, drivid);

                        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + drivid + "'"));

                        if (res->next()) {
                            count = res->getInt(1);
                            if (count == 0) {
                                cout << "Driver does not exist." << endl << endl;
                                do {
                                    cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                    cout << "Option  :  ";
                                    cin >> choice2;
                                    if (choice2 == "1") {
                                        cin.ignore();
                                        break;
                                    }
                                    else if (choice2 == "2") {
                                        system("cls");
                                        add_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else {
                                        cout << "Incorrect" << endl << endl;
                                    }
                                } while (choice2 != "1" && choice2 != "2");
                            }
                        }
                    } while (count == 0);

                    cout << endl;
                    cout << "Destination of this trip  : ";
                    getline(cin, dest);
                    cout << endl;
                    cout << "Start Time : ";
                    getline(cin, start);
                    cout << endl;
                    cout << "End Time  : ";
                    getline(cin, end);
                    cout << endl;
                    cout << "Duration : ";
                    getline(cin, dur);
                    cout << endl;
                    cout << "Start Date(YYYY-MM-DD)  : ";
                    
                    bool validsDate = false;

                    while (!validsDate) {
                        cin >> dtstart;
                        if (isValidDate(dtstart)) {
                            validsDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "Start Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    }
                   
                    cout << endl;
                    cout << "End Date(YYYY-MM-DD)  : ";
                    bool valideDate = false;

                    while (!valideDate) {
                        cin >> dtend;

                        if (isValidDate(dtend)) {
                            valideDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "End Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    }
                    
                    cout << endl;
                    cout << "Ticket Price(RM)  : RM ";
                    cin.ignore();
                    getline(cin, prc);
                    cout << endl;

                    cout << "\t\t\t======================================================" << endl;
                    cout << endl;
                    cout << "\t\t\t    Trip ID            : " << tripId << endl;
                    cout << "\t\t\t    Bus                : " << numplate << endl;
                    cout << "\t\t\t    Driver             : " << drivid << endl;
                    cout << "\t\t\t    Destination        : " << dest << endl;
                    cout << "\t\t\t    Start Time         : " << start << endl;
                    cout << "\t\t\t    End Time           : " << end << endl;
                    cout << "\t\t\t    Duration           : " << dur << endl;
                    cout << "\t\t\t    Date Start         : " << dtstart << endl;
                    cout << "\t\t\t    Date End           : " << dtend << endl;
                    cout << "\t\t\t    Price(RM)          : RM " << prc << endl;
                    cout << "\t\t\t    Seat Available     : " << seat << endl;
                    cout << endl;
                    cout << "\t\t\t=======================================================" << endl;
                    cout << endl;
                    cout << "Are you sure want to Add this Trip? (Y or N)" << endl;
                    cout << endl;

                    do {
                        cout << "Option  : ";
                        cin >> atoption;

                        if (atoption == "Y" || atoption == "y") {
                            string ak;
                            // T.add_trip(tripId, numplate, drivid, dest, start, end, dur, dtstart, prc, seat, dtend); // Assuming add_trip is a member function of class Trip
                            cout << endl;
                            std::string seatStr = std::to_string(seat);

                            // Construct the INSERT query
                            std::string insertQuery = "INSERT INTO trip (trip_ID, number_plate, driver_ID, destination, start_time, end_time, duration, start_date, end_date, ticket_price, seat_available) VALUES ('" + tripId + "', '" + numplate + "', '" + drivid + "', '" + dest + "', '" + start + "', '" + end + "', '" + dur + "', '" + dtstart + "', '" + dtend + "', '" + prc + "', '" + seatStr + "')";

                            // Execute the query
                            stmt->execute(insertQuery);

                            // Print success message
                            cout << "Trip added successfully!" << endl;

                            cout << "Press any key to continue..." << endl;
                            cin >> ak;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            admin_trip(akaun, pass);
                        }
                        else if (atoption == "N" || atoption == "n") {
                            string aa;
                            cout << endl;
                            cout << "***  Trip not Added  ***" << endl;
                            cout << endl;
                            cout << "Press any key to continue..." << endl;
                            cin >> aa;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            add_trip(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl << endl;
                        }
                    } while (atoption != "Y" && atoption != "y" && atoption != "N" && atoption != "n");

                }
                catch (const SQLException& e) {
                    cerr << "SQLException caught: " << e.what() << endl;
                }
                catch (const exception& e) {
                    cerr << "Exception caught: " << e.what() << endl;
                }

            }
            else {
                cout << "Incorrect" << endl << endl;
            }
        } while (bo != "1" && bo != "2");
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

    closeDatabaseConnection(); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_trip(string akaun, string pass)
{
    connectToDatabase();

    string tripId, bm;
    int choice;
    trip_list();
    cout << std::endl;
    cout << "Enter 1 to Back Menu or 2 to Update Trip" << std::endl;
    cout << std::endl;

    do {
        cout << endl;
        std::cout << "Option  : ";
        std::cin >> bm;
        if (bm == "1")
        {
            system("cls");
            admin_trip(akaun, pass);
        }
        else if (bm == "2")
        {
            connectToDatabase();

            sql::Statement* stmt = globalCon->createStatement();

            int count{};
            do {
                std::cout << "\nEnter Trip ID to Update: ";
                std::cin >> tripId;

                sql::ResultSet* res = stmt->executeQuery("SELECT COUNT(*) FROM trip WHERE trip_ID = '" + tripId + "'");

                if (res->next()) {
                    count = res->getInt(1);
                    if (count == 0) {
                        std::cout << "Trip ID does not exist." << std::endl << std::endl;
                        do {
                            std::cout << "Enter 1 to Retry, 2 to Exit" << std::endl;
                            std::cout << "Option  :  ";
                            std::cin >> choice;
                            if (choice == 1)
                            {
                                system("cls");
                                update_trip(akaun, pass);
                            }
                            else if (choice == 2)
                            {
                                system("cls");
                                admin_trip(akaun, pass);
                            }
                            else {
                                std::cout << "Incorrect" << std::endl << std::endl;
                            }
                        } while (choice != 1 && choice != 2);
                    }

                    delete res;
                }
            } while (count == 0);
            cout << endl;

            system("cls");
            connectToDatabase();

            pstmt = globalCon->prepareStatement("SELECT * FROM trip WHERE trip_ID = ?");
            pstmt->setString(1, tripId);

            sql::ResultSet* res = pstmt->executeQuery();

            // Print trip details
            std::cout << "Trip Details:" << std::endl;
            while (res->next()) {
                cout << "Trip ID: " << res->getString("trip_ID") << std::endl;
                cout << "Bus Number Plate: " << res->getString("number_plate") << std::endl;
                cout << "Driver ID: " << res->getString("driver_ID") << std::endl;
                cout << "Destination: " << res->getString("destination") << std::endl;
                cout << "Start Time: " << res->getString("start_time") << std::endl;
                cout << "End Time: " << res->getString("end_time") << std::endl;
                cout << "Duration: " << res->getString("duration") << std::endl;
                cout << "Date Start: " << res->getString("start_date") << std::endl;
                cout << "Date End: " << res->getString("end_date") << std::endl;
                cout << "Price: " << res->getString("ticket_price") << std::endl;
                cout << "---------------------------------------" << std::endl;
            }

            delete res;

            string newValue;
            string columnName;
            bool validChoice = false;

            do {
                // Allow user to choose which column to update
                cout << "Choose the column to update:" << endl;
                cout << "1. Destination" << endl;
                cout << "2. Start Time" << endl;
                cout << "3. End Time" << endl;
                cout << "4. Duration" << endl;
                cout << "5. Start Date" << endl;
                cout << "6. End Date" << endl;
                cout << "7. Price" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                // Handle user choice and update the selected column
                if (choice == 1) {
                    cout << "\nEnter New Destination :";
                    columnName = "destination";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 2) {
                    cout << "\nEnter New Start Time :";
                    columnName = "start_time";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 3) {
                    cout << "\nEnter New end Time :";
                    columnName = "end_time";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 4) {
                    cout << "\nEnter New Duration Time :";
                    columnName = "duration";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 5) {
                    cout << "\nEnter New Start Date :";
                    columnName = "start_date";
                    bool validsDate = false;
                    do {
                        cin >> newValue;
                        if (isValidDate(newValue)) {
                            validsDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "Start Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    } while (!validsDate);
                    validChoice = true;
                }
                else if (choice == 6) {
                    cout << "\nEnter New End Date :";
                    columnName = "end_date";
                    bool validDate = false;
                    do {
                        cin >> newValue;
                        if (isValidDate(newValue)) {
                            validDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "End Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    } while (!validDate);
                    validChoice = true;
                }
                else if (choice == 7) {
                    cout << "\nEnter New Price :";
                    columnName = "ticket_price";
                    cin >> newValue;
                    validChoice = true;
                }
                else {
                    cout << "Invalid choice. Please try again." << endl << endl;
                    cin.clear(); // Clear any error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!validChoice);

            // Update the database with new value
            string updateQuery = "UPDATE trip SET " + columnName + " = '" + newValue + "' WHERE trip_ID = '" + tripId + "'";
            stmt->executeUpdate(updateQuery);
            cout << "Trip updated successfully!" << std::endl;

            string op;
            do {
                cout << "\nEnter 1 to Back \n";
                cout << "\n Option : ";
                cin >> op;
                if (op == "1")
                {
                    system("cls");
                    admin_menu(akaun, pass);
                }
                else
                {
                    cout << "\n Invalid Input \n";
                }
            } while (op != "1");
        }
        else
        {
            cout << "Incorrect" << std::endl << std::endl;
        }
    } while (bm != "1" && bm != "2");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_trip(string akaun, string pass) {
    try {
        connectToDatabase();

        string tripId, dtoption, YorN, choice;

        do {
            system("cls");
            trip_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Trip" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dtoption;

            if (dtoption == "1") {
                admin_trip(akaun, pass);
                return;
            }
            else if (dtoption == "2") {
                int count{};
                do {
                    cout << "\nEnter Trip ID to Delete: ";
                    cin >> tripId;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM trip WHERE trip_ID = '" + tripId + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Trip does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the trip ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_trip(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM trip WHERE trip_ID = '" + tripId + "'");
                while (res->next()) {
                    cout << "\t\t\t                 TRIP DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Trip ID             : " << res->getString("trip_ID") << endl;
                    cout << "\t\t\t   Bus Number Plate    : " << res->getString("number_plate") << endl;
                    cout << "\t\t\t   Driver ID           : " << res->getString("driver_ID") << endl;
                    cout << "\t\t\t   Destination         : " << res->getString("destination") << endl;
                    cout << "\t\t\t   Start Time          : " << res->getString("start_time") << endl;
                    cout << "\t\t\t   End Time            : " << res->getString("end_time") << endl;
                    cout << "\t\t\t   Duration            : " << res->getString("duration") << endl;
                    cout << "\t\t\t   Start Date          : " << res->getString("start_date") << endl;
                    cout << "\t\t\t   End Date            : " << res->getString("end_date") << endl;
                    cout << "\t\t\t   Ticket Price (RM)   : RM " << res->getString("ticket_price") << endl;
                    cout << "\t\t\t   Seat Available      : " << res->getInt("seat_available") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure want to Delete this " << tripId << " Trip ?" << endl;

                    do {
                        cout << "Enter Y to Delete N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete trip directly
                            executeInstruction("DELETE FROM trip WHERE trip_ID = '" + tripId + "'");
                            cout << endl;
                            cout << "Trip deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            admin_trip(akaun, pass);
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Trip not Deleted  ***" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            delete_trip(akaun, pass);
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
                delete res;
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dtoption != "1" && dtoption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_list() {
    cout << endl;
    cout << endl;
    cout << "    STAFF  LIST" << endl;
    cout << "-------------------" << endl;
    cout << endl;
    cout << endl;

    try {
        connectToDatabase(); // Assuming this function sets up the globalCon variable

        if (!globalCon) {
            cerr << "Database connection is not established." << endl;
            return;
        }

        unique_ptr<Statement> stmt(globalCon->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT * FROM staff"));

        vector<vector<string>> table;
        vector<string> columnNames = {
            "| Staff ID", "| Name", "| Email", "| Phone Number", "| Address", "| Position", "| Date Hire"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);

        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("staff_ID"));
            rowData.push_back(res->getString("staff_name"));
            rowData.push_back(res->getString("staff_email"));
            rowData.push_back(res->getString("staff_phonenumber"));
            rowData.push_back(res->getString("staff_address"));
            rowData.push_back(res->getString("staff_position"));
            rowData.push_back(res->getString("staff_date_hire"));

            table.push_back(rowData);
        }
        displayTable(table);
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    closeDatabaseConnection(); // Close the database connection at the end of the function
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_staff(string akaun, string pass)
{
    try {
        connectToDatabase();

        string sid, sn, se, sp, sa, sposition, sdate_hire, spassword, bo, adoption, choice;

        staff_list();
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back Menu or 2 to Add Staff" << endl;
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                admin_staff(akaun, pass);
            }
            else if (bo == "2") {
                cin.ignore();

                // Check if the staff already exists
                int count = 0;
                do {
                    cout << "\nEnter Staff ID to Add: ";
                    getline(cin, sid);

                    ResultSet* res = executeQuery("SELECT COUNT(*) FROM staff WHERE staff_ID = '" + sid + "'");

                    if (res->next()) {
                        count = res->getInt(1);
                        if (count > 0) {
                            cout << "Staff ID already exists." << endl;
                            do {
                                cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                cout << "Option  :  ";
                                cin >> choice;
                                if (choice == "1") {
                                    system("cls");
                                    add_staff(akaun, pass);
                                }
                                else if (choice == "2") {
                                    system("cls");
                                    admin_staff(akaun, pass);
                                }
                                else {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (choice != "1" && choice != "2");
                        }
                        delete res;
                    }
                } while (count > 0);

                cout << "\nStaff Name  : ";
                getline(cin, sn);
                cout << endl;

                bool validEmail = false;
                while (!validEmail) {
                    cout << "Staff Email : ";
                    cin.ignore();
                    getline(cin, se);
                    cout << endl;

                    if (isValidEmail(se)) {
                        validEmail = true;
                    }
                    else {
                        cerr << "This is an Invalid Email , Please Enter a Valid One ." << endl;
                    }
                }
               /* cout << "Staff Email  : ";
                getline(cin, se);*/
                cout << endl;
                cout << "Staff Phone Number  : ";
               
                bool validPhoneNumber = false;
                while (!validPhoneNumber) {
                    getline(cin, sp);

                    if (isValidPhoneNumber(sp)) {
                        validPhoneNumber = true;
                    }
                    else {
                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                    }
                }
                
                // getline(cin, sp);
                cout << endl;
                cout << "Staff Address  : ";
                getline(cin, sa);
                cout << endl;
                cout << "Staff Position  : ";
                getline(cin, sposition);
                cout << endl;
                cout << "Staff Date Hire (YYYY-MM-DD)  : ";
                
                bool validDate = false;

                while (!validDate) {
                    cin >> sdate_hire;

                    if (isValidDate(sdate_hire)) {
                        validDate = true;
                    }
                    else {
                        cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                        cout << "Staff Date Hire (YYYY-MM-DD)  : ";
                        cin.clear(); // Clear any error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                    }
                }
               
                cout << endl;
                cout << "Staff Password  : ";
                cin.ignore();
                getline(cin, spassword);
                cout << endl;

                cout << "=======================================================================================" << endl;
                cout << endl;
                cout << "     Staff ID               : " << sid << endl;
                cout << "     Staff Name             : " << sn << endl;
                cout << "     Staff Email            : " << se << endl;
                cout << "     Staff Phone Number     : " << sp << endl;
                cout << "     Staff Address          : " << sa << endl;
                cout << "     Staff Position         : " << sposition << endl;
                cout << "     Staff Date Hire        : " << sdate_hire << endl;
                cout << "     Staff Password         : " << spassword << endl;
                cout << endl;
                cout << "=======================================================================================" << endl;
                cout << endl;
                cout << "Are you sure you want to Add this Staff? (Y or N)" << endl;
                cout << "Enter Y for Yes, N for No" << endl;
                do {
                    cout << "Option  : ";
                    cin >> adoption;

                    if (adoption == "Y" || adoption == "y") {
                        string ad;
                        // Execute SQL insert statement to add staff directly
                        executeInstruction("INSERT INTO staff(staff_ID, staff_name, staff_email, staff_phonenumber, staff_address, staff_position, staff_date_hire, staff_password) VALUES ('" + sid + "', '" + sn + "', '" + se + "', '" + sp + "', '" + sa + "', '" + sposition + "', '" + sdate_hire + "', '" + spassword + "')");
                        cout << endl;
                        cout << "Staff Added Successfully." << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        admin_staff(akaun, pass);
                    }
                    else if (adoption == "N" || adoption == "n") {
                        string bw;
                        cout << endl;
                        cout << "***  Staff not Added  ***" << endl;
                        cout << endl;
                        cout << "Press any key to continue..." << endl;
                        cin >> bw;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        add_staff(akaun, pass);
                    }
                    else {
                        cout << "Invalid Input, Please Enter Y for Yes, N for No " << endl;
                        cout << endl;
                    }
                } while (adoption != "Y" && adoption != "y" && adoption != "N" && adoption != "n");
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }

        } while (bo != "1" && bo != "2");

        closeDatabaseConnection();
    }
    catch (const exception& e) {
        // Handle the exception here
        cerr << "Exception caught: " << e.what() << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_staff(string akaun, string pass) {
    try {
        connectToDatabase();

        string sm, choice, column, c, b, staffID, newValue;

        do {
            system("cls");
            staff_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Update Staff" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> sm;

            if (sm == "1") {
                system("cls");
                admin_staff(akaun, pass);
                return; // Exit the function
            }
            else if (sm == "2") {
                int count{};
                do {
                    cout << "\nEnter Staff ID to Update: ";
                    cin >> staffID;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM staff WHERE staff_ID = '" + staffID + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << "Staff does not exist." << endl << endl;

                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;

                            if (choice == "1") {
                                count = 0; // Reset count to allow retry
                                break; // Break out of the inner loop to allow re-entering the staff ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_staff(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                system("cls");

                ResultSet* res = executeQuery("SELECT * FROM staff WHERE staff_ID = '" + staffID + "'");

                while (res->next()) {
                    cout << "\t\t\t                 STAFF DETAIL                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Staff ID           : " << res->getString("staff_ID") << endl;
                    cout << endl;
                    cout << "\t\t\t   Name               : " << res->getString("staff_name") << endl;
                    cout << endl;
                    cout << "\t\t\t   Email              : " << res->getString("staff_email") << endl;
                    cout << endl;
                    cout << "\t\t\t   Phone Number       : " << res->getString("staff_phonenumber") << endl;
                    cout << endl;
                    cout << "\t\t\t   Address            : " << res->getString("staff_address") << endl;
                    cout << endl;
                    cout << "\t\t\t   Position           : " << res->getString("staff_position") << endl;
                    cout << endl;
                    cout << "\t\t\t   Date Hire          : " << res->getString("staff_date_hire") << endl;
                    cout << endl;
                    cout << "\t\t\t   Password           : " << res->getString("staff_password") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Which column do you want to update?" << endl;
                    cout << endl;
                    cout << "\t1. Name        2. Email        3. Phone Number        4. Address        5. Position        6. Date Hire        7. Password        8. Back" << endl;
                    cout << endl;

                    do {
                        cout << "Option  :  ";
                        cin >> column;

                        if (column == "1" || column == "2" || column == "3" || column == "4" || column == "5" || column == "6" || column == "7") {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            if (column == "1") {
                                cout << "Enter the new name for this staff:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "2") {
                               
                                bool validEmail = false;
                                while (!validEmail) {
                                    cout << "Enter the new email for this staff:  ";
                                    cin.ignore();
                                    getline(cin, newValue);
                                    
                                    // Check if the account ID already exists in any of the tables
                                    if (isValidEmail(newValue)) {
                                        validEmail = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Email , Please Enter a Valid One ." << endl;
                                    }
                                }
                              
                            }
                            else if (column == "3") {
                                cin.ignore();
                                cout << "Enter the new phone number for this staff:  ";
                                
                                bool validPhoneNumber = false;
                                while (!validPhoneNumber) {
                                    
                                    getline(cin, newValue);

                                    if (isValidPhoneNumber(newValue)) {
                                        validPhoneNumber = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                                    }
                                }
                                
                                
                            }
                            else if (column == "4") {
                                cout << "Enter the new address for this staff:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "5") {
                                cout << "Enter the new position for this staff:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "6") {
                                cout << "Enter the new date hire for this staff (YYYY-MM-DD):  ";
                               
                                bool validDate = false;

                                while (!validDate) {
                                    cin >> newValue;

                                    if (isValidDate(newValue)) {
                                        validDate = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                                        cout << "Staff Date Hire (YYYY-MM-DD)  : ";
                                        cin.clear(); // Clear any error flags
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                                    }
                                }
                                
                                
                                /* cin.ignore();
                                getline(cin, newValue);*/
                            }
                            else if (column == "7") {
                                cout << "Enter the new password for this staff:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                           
                            cout << endl;
                            cout << endl;
                            string oldValue = column == "1" ? res->getString("staff_name") : column == "2" ? res->getString("staff_email") : column == "3" ? res->getString("staff_phonenumber") : column == "4" ? res->getString("staff_address") : column == "5" ? res->getString("staff_position") : column == "6" ? res->getString("staff_date_hire") : res->getString("staff_password");
                            cout << "Are you sure you want to change " << oldValue << " to " << newValue << "?" << endl;
                            cout << endl;
                            cout << "Enter Y for Yes, N for No" << endl;
                            cout << endl;
                            do {
                                cout << "Option  :  ";
                                cin >> c;

                                if (c == "Y" || c == "y") {
                                    string query;
                                    if (column == "1") {
                                        query = "UPDATE staff SET staff_name = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    else if (column == "2") {
                                        query = "UPDATE staff SET staff_email = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    else if (column == "3") {
                                        query = "UPDATE staff SET staff_phonenumber = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    else if (column == "4") {
                                        query = "UPDATE staff SET staff_address = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    else if (column == "5") {
                                        query = "UPDATE staff SET staff_position = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    else if (column == "6") {
                                        query = "UPDATE staff SET staff_date_hire = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    else if (column == "7") {
                                        query = "UPDATE staff SET staff_password = '" + newValue + "' WHERE staff_ID = '" + staffID + "'";
                                    }
                                    executeInstruction(query);
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << "\t\t\t|      Staff Update Successfully     |" << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress any key to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    admin_staff(akaun, pass);
                                }
                                else if (c == "N" || c == "n") {
                                    system("cls");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t***  Staff not Updated  ***" << endl;
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress any key to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    update_staff(akaun, pass);
                                }
                                else {
                                    cout << "Invalid Input, Please Enter Y for Yes, N for No " << endl;
                                    cout << endl;
                                }
                            } while (c != "Y" && c != "y" && c != "N" && c != "n");
                        }
                        else if (column == "8") {
                            system("cls");
                            update_staff(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl;
                            cout << endl;
                        }
                    } while (column != "1" && column != "2" && column != "3" && column != "4" && column != "5" && column != "6" && column != "7" && column != "8");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (sm != "1" && sm != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_staff(string akaun, string pass) {
    try {
        connectToDatabase();

        string staffID, dboption, YorN, choice;

        do {
            system("cls");
            staff_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Staff" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dboption;

            if (dboption == "1") {
                system("cls");
                admin_staff(akaun, pass);
                return; // Exit the function
            }
            else if (dboption == "2") {
                int count{};
                do {
                    cout << "\nEnter Staff ID to Delete: ";
                    cin >> staffID;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM staff WHERE staff_ID = '" + staffID + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Staff does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the staff ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                admin_staff(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM staff WHERE staff_ID = '" + staffID + "'");
                while (res->next()) {
                    cout << "\t\t\t                 STAFF DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Staff ID           : " << res->getString("staff_ID") << endl;
                    cout << endl;
                    cout << "\t\t\t   Name               : " << res->getString("staff_name") << endl;
                    cout << endl;
                    cout << "\t\t\t   Email              : " << res->getString("staff_email") << endl;
                    cout << endl;
                    cout << "\t\t\t   Phone Number       : " << res->getString("staff_phonenumber") << endl;
                    cout << endl;
                    cout << "\t\t\t   Address            : " << res->getString("staff_address") << endl;
                    cout << endl;
                    cout << "\t\t\t   Position           : " << res->getString("staff_position") << endl;
                    cout << endl;
                    cout << "\t\t\t   Date Hire          : " << res->getString("staff_date_hire") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure you want to delete this staff?" << endl;

                    do {
                        cout << "Enter Y to Delete, N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete staff directly
                            executeInstruction("DELETE FROM staff WHERE staff_ID = '" + staffID + "'");
                            cout << endl;
                            cout << "Staff deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            admin_staff(akaun, pass);
                            return; // Exit the function
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Staff not Deleted  ***" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            delete_staff(akaun, pass);
                            return; // Exit the function
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dboption != "1" && dboption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_trip(string ac, string pw) {
    // Connect to the database
    connectToDatabase();

    //// Prepare SQL statement to check admin credentials
    //string query = "SELECT * FROM admin WHERE admin_ID = '" + ac + "' AND admin_password = '" + pw + "'";
    //executeInstruction(query);

    //ResultSet* rs = executeQuery(query);

    string option ,bam ;
    cout << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|          TRIP MANAGEMENT          |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Trip               |" << endl;
    cout << "\t\t\t|         2. Edit Trip              |" << endl;
    cout << "\t\t\t|         3. Delete Trip            |" << endl;
    cout << "\t\t\t|         4. View Trip List         |" << endl;;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;

    do {
        cout << "Option  : ";
        cin >> option;
        if (option == "1") {
            system("cls");
            staff_add_trip(ac, pw);
        }
        else if (option == "2") {
            system("cls");
            staff_update_trip(ac, pw);
        }
        else if (option == "3") {
            system("cls");
            staff_delete_trip(ac, pw);
        }
        else if (option == "4") {
            system("cls");
            staff_trip_list();
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;

                if (bam == "1") {
                    system("cls");
                    staff_trip(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5") {
            system("cls");
            staff_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    // Close the database connection
    closeDatabaseConnection();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_cust(string ac, string pw)
{
    connectToDatabase();

    

    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|        CUSTOMER MANAGEMENT        |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|       1. View Customer List       |" << endl;
    cout << "\t\t\t|       2. Back                     |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;
    do {
        cout << "Option  :  ";
        cin >> option;
        cout << endl;
        if (option == "1")
        {
            system("cls");
            try {
                connectToDatabase();

                // Execute the query
                ResultSet* res = executeQuery("SELECT * FROM customer");

                vector<vector<string>> table;
                vector<string> columnNames =
                {
                    "| Customer ID", "| Name", "| Email", "| Address", "| Phone Number"
                };

                // Add table headers with custom column names
                table.push_back(columnNames);

                while (res->next()) {
                    vector<string> rowData;
                    rowData.push_back(res->getString("customer_ID"));
                    rowData.push_back(res->getString("customer_name"));
                    rowData.push_back(res->getString("customer_email"));
                    rowData.push_back(res->getString("customer_address"));
                    rowData.push_back(res->getString("customer_phonenumber"));

                    table.push_back(rowData);
                }
                displayTable(table);


            }
            catch (sql::SQLException& e) {
                cout << "# ERR: " << e.what();
                cout << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            }
            string gbm;
            cout << endl;
            cout << "Enter 1 to Back " << endl;
            do {
                cout << "Option  :  ";
                cin >> gbm;

                if (gbm == "1")
                {
                    system("cls");
                    staff_menu(ac, pw);
                }
                else
                {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (gbm != "1");
        }
        else if (option == "2")
        {
            system("cls");
            staff_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2");

    closeDatabaseConnection();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_driver(string ac, string pw)
{
    connectToDatabase();

    // Prepare SQL statement to check admin credentials
   /* string query = "SELECT * FROM admin WHERE admin_ID = '" + ac + "' AND admin_password = '" + pw + "'";
    executeInstruction(query);

    ResultSet* rs = executeQuery(query);*/

    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|         DRIVER MANAGEMENT         |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Driver             |" << endl;
    cout << "\t\t\t|         2. Edit Driver            |" << endl;
    cout << "\t\t\t|         3. Delete Driver          |" << endl;
    cout << "\t\t\t|         4. View Driver List       |" << endl;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;
    do {
        cout << "Option  : ";
        cin >> option;
        cout << endl;
        if (option == "1")
        {
            system("cls");
            staff_add_driver(ac, pw);
        }
        else if (option == "2")
        {
            system("cls");
            staff_update_driver(ac, pw);
        }
        else if (option == "3")
        {
            system("cls");
            staff_delete_driver(ac, pw);
        }
        else if (option == "4")
        {
            string bam;
            system("cls");
            staff_driver_list();
            cout << endl;
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;
                cout << endl;
                if (bam == "1")
                {
                    system("cls");
                    staff_driver(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5")
        {
            system("cls");
            staff_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    closeDatabaseConnection();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_bus(string ac, string pw)
{
    connectToDatabase();

    // Prepare SQL statement to check admin credentials
    /*string query = "SELECT * FROM admin WHERE admin_ID = '" + ac + "' AND admin_password = '" + pw + "'";
    executeInstruction(query);

    ResultSet* rs = executeQuery(query);*/

    string option;

    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|          BUS MANAGEMENT           |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t|         1. Add Bus                |" << endl;
    cout << "\t\t\t|         2. Edit Bus               |" << endl;
    cout << "\t\t\t|         3. Delete Bus             |" << endl;
    cout << "\t\t\t|         4. View Bus List          |" << endl;
    cout << "\t\t\t|         5. Back                   |" << endl;
    cout << "\t\t\t|                                   |" << endl;
    cout << "\t\t\t+===================================+" << endl;
    cout << endl;
    do
    {
        cout << "Option  : ";
        cin >> option;
        cout << endl;
        if (option == "1")
        {
            system("cls");
            staff_add_bus(ac, pw);
        }
        else if (option == "2")
        {
            system("cls");
            staff_update_bus(ac, pw);
        }
        else if (option == "3")
        {
            system("cls");
            staff_delete_bus(ac, pw);
        }
        else if (option == "4")
        {
            string bam;
            system("cls");
            staff_bus_list();
            cout << endl;
            cout << "Enter 1 to Back menu" << endl;
            do {
                cout << "Option  :  ";
                cin >> bam;
                cout << endl;
                if (bam == "1")
                {
                    system("cls");
                    staff_bus(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bam != "1");
        }
        else if (option == "5")
        {
            system("cls");
            staff_menu(ac, pw);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5");

    closeDatabaseConnection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_about_me(string ac, string pw) {
    string dp, yon, choice, newValue, column, goback, newPassword, confirmPassword;

    connectToDatabase();

    try {
        // Prepare SQL statement to check staff credentials
        string query = "SELECT * FROM staff WHERE staff_ID = ? AND staff_password = ?";
        PreparedStatement* pstmt = globalCon->prepareStatement(query);
        pstmt->setString(1, ac);
        pstmt->setString(2, pw);

        ResultSet* rs = pstmt->executeQuery();

        while (rs->next()) {
            cout << "\t\t\t                USER PROFILE                " << endl;
            cout << "\t\t\t=============================================" << endl;
            cout << endl;
            cout << "\t\t\t   Username       : " << rs->getString("staff_ID") << endl;
            cout << endl;
            cout << "\t\t\t   Name           : " << rs->getString("staff_name") << endl;
            cout << endl;
            cout << "\t\t\t   Email          : " << rs->getString("staff_email") << endl;
            cout << endl;
            cout << "\t\t\t   Address        : " << rs->getString("staff_address") << endl;
            cout << endl;
            cout << "\t\t\t   Phone Number   : " << rs->getString("staff_phonenumber") << endl;
            cout << endl;
            cout << endl;

            cout << "Do you want to change your details?" << endl;
            do {
                cout << "Enter 1 for Update details, 2 for Back" << endl;
                cout << endl;

                cout << "Option  :  ";
                cin >> yon;

                if (yon == "1") {
                    do {
                        cout << endl;
                        cout << "Which detail do you want to update?" << endl;
                        cout << "1. Email" << endl;
                        cout << "2. Name" << endl;
                        cout << "3. Address" << endl;
                        cout << "4. Phone Number" << endl;
                        cout << "5. Password" << endl;
                        cout << "6. Back" << endl;
                        cout << endl;

                        cout << "Option: ";
                        cin >> choice;
                        cin.ignore();

                        if (choice == "6") {
                            system("cls");
                            this_thread::sleep_for(chrono::seconds(1));
                            staff_menu(ac, pw);
                            break; // Exit the loop and go back to the menu
                        }

                        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5") {
                            cout << "Invalid option. Please enter a number between 1 and 6." << endl;
                            continue; // Restart the loop to ask for a valid choice
                        }

                        if (choice == "5") {
                            do {
                                cout << "Enter the new password: ";
                                getline(cin, newPassword);
                                cout << "Confirm the new password: ";
                                getline(cin, confirmPassword);

                                if (newPassword != confirmPassword) {
                                    cout << "Passwords do not match. Try again." << endl;
                                }
                            } while (newPassword != confirmPassword);

                            column = "staff_password";
                            newValue = newPassword;
                        }
                        else {
                            cout << "Enter the new value: ";
                          

                            if (choice == "1") {
                                column = "staff_email";
                                bool validEmail = false;
                                while (!validEmail) {

                                    cin.ignore();
                                    getline(cin, newValue);

                                    // Check if the account ID already exists in any of the tables
                                    if (isValidEmail(newValue)) {
                                        validEmail = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Email , Please Enter a Valid One ." << endl;
                                    }
                                }
                                
                            }
                            else if (choice == "2") {
                                column = "staff_name";
                                cin.ignore();
                                getline(cin, newValue);
                                cout << endl;
                            }
                            else if (choice == "3") {
                                column = "staff_address";
                                cin.ignore();
                                getline(cin, newValue);
                                cout << endl;
                            }
                            else if (choice == "4") {

                                column = "staff_phonenumber";
                                bool validPhoneNumber = false;
                                while (!validPhoneNumber) {
                                    getline(cin, newValue);

                                    if (isValidPhoneNumber(newValue)) {
                                        validPhoneNumber = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                                    }
                                }
                                
                                
                            }
                        }
                        connectToDatabase();
                        // Prepare and execute SQL statement to update staff details
                        query = "UPDATE staff SET " + column + " = ? WHERE staff_ID = ?";
                        PreparedStatement* stmt = globalCon->prepareStatement(query);
                        stmt->setString(1, newValue);
                        stmt->setString(2, ac);
                        stmt->executeUpdate();

                        cout << endl;
                        cout << "\t\t-------------------------------" << endl;
                        cout << "\t\t|      Update Successfully     |" << endl;
                        cout << "\t\t-------------------------------" << endl;
                        cout << endl;

                        delete stmt;
                        this_thread::sleep_for(chrono::seconds(4));
                        system("cls");
                        staff_menu(ac, pw);
                    } while (true);
                }
                else if (yon == "2") {
                    system("cls");
                    this_thread::sleep_for(chrono::seconds(1));
                    staff_menu(ac, pw);
                }
                else {
                    cout << "Invalid input. Please enter 1 or 2." << endl;
                    cout << endl;
                }
            } while (yon != "1" && yon != "2");
        }

        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_bus_list() {
    try {
        connectToDatabase();

        cout << endl << endl;
        cout << "    BUS  LIST" << endl;
        cout << "----------------" << endl;
        cout << endl << endl;

        // Execute SQL query to retrieve bus list
        ResultSet* res = executeQuery("SELECT * FROM bus");

        vector<vector<string>> table;
        vector<string> columnNames = {
            "|  Number Plate", "|  Capacity", "|  Type", "|  Brand", "|  Condition"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);

        // Fetch and display bus data
        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("number_plate"));
            rowData.push_back(res->getString("capacity"));
            rowData.push_back(res->getString("type"));
            rowData.push_back(res->getString("brand"));
            rowData.push_back(res->getString("condition"));

            table.push_back(rowData);
        }

        // Display the table
        displayTable(table);

        // Clean up
        delete res;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_add_bus(string akaun, string pass) {
    try {
        connectToDatabase();

        string np, t, br, co, bo, aboption, choice;
        int ca;

        staff_bus_list();
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back Menu or 2 to Add Bus" << endl;
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                staff_bus(akaun, pass);
            }
            else if (bo == "2") {
                cin.ignore();

                // Check if the bus already exists
                int count = 0;
                do {
                    cout << "\nEnter Bus Number Plate to Add: ";
                    getline(cin, np);

                    ResultSet* res = executeQuery("SELECT COUNT(*) FROM bus WHERE number_plate = '" + np + "'");

                    if (res->next()) {
                        count = res->getInt(1);
                        if (count > 0) {
                            cout << "Bus already exists." << endl;
                            do {
                                cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                cout << "Option  :  ";
                                cin >> choice;
                                if (choice == "1") {
                                    system("cls");
                                    staff_add_bus(akaun, pass);
                                }
                                else if (choice == "2") {
                                    system("cls");
                                    staff_bus(akaun, pass);
                                }
                                else {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (choice != "1" && choice != "2");
                        }
                        delete res;
                    }
                } while (count > 0);

                cout << "Bus Capacity  : ";
                cin >> ca;
                cin.ignore();
                cout << "Bus Type  : ";
                getline(cin, t);
                cout << "Bus Brand  : ";
                getline(cin, br);
                cout << "Bus Condition : ";
                getline(cin, co);
                cout << "==========================================================" << endl;
                cout << endl;
                cout << "     Bus Number Plate    : " << np << endl;
                cout << "     Bus Capacity        : " << ca << endl;
                cout << "     Bus Type            : " << t << endl;
                cout << "     Bus Brand           : " << br << endl;
                cout << "     Bus Condition       : " << co << endl;
                cout << endl;
                cout << "==========================================================" << endl;
                cout << endl;
                cout << "Are you sure want to Add this Bus? (Y or N)" << endl;
                cout << "Enter Y for Yes, N for No" << endl;
                do {
                    cout << "Option  : ";
                    cin >> aboption;

                    if (aboption == "Y" || aboption == "y") {
                        string ab;
                        // Execute SQL insert statement to add bus directly
                        executeInstruction("INSERT INTO bus (number_plate, capacity, type, brand, `condition`) VALUES ('" + np + "', " + to_string(ca) + ", '" + t + "', '" + br + "', '" + co + "')");
                        cout << endl;
                        cout << "Bus added successfully." << endl;
                        /*  cout << "Press any key to continue..." << endl;
                          cin >> ab;*/
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        staff_bus(akaun, pass);
                    }
                    else if (aboption == "N" || aboption == "n") {
                        string bw;
                        cout << endl;
                        cout << "***  Bus not Added  ***" << endl;
                        cout << endl;
                        cout << "Press any key to continue..." << endl;
                        cin >> bw;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        staff_add_bus(akaun, pass);
                    }
                    else {
                        cout << "Invalid Input , Please Enter Y for Yes, N for No " << endl;
                        cout << endl;
                    }
                } while (aboption != "Y" && aboption != "y" && aboption != "N" && aboption != "n");
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }

        } while (bo != "1" && bo != "2");

        closeDatabaseConnection();
    }
    catch (const std::exception& e) {
        // Handle the exception here
        cerr << "Exception caught: " << e.what() << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_update_bus(string akaun, string pass) {
    try {
        connectToDatabase();

        string bm, choice, column, c, b, numplate, condition;

        do {
            system("cls");
            staff_bus_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Update Bus" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> bm;

            if (bm == "1") {
                system("cls");
                staff_bus(akaun, pass);
            }
            else if (bm == "2") {
                int count{};
                do {
                    cout << "\nEnter Bus Number Plate to Update: ";
                    cin >> numplate;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM bus WHERE number_plate = '" + numplate + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << "Bus does not exist." << endl << endl;

                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;

                            if (choice == "1") {
                                count = 0; // Reset count to allow retry
                                break; // Break out of the inner loop to allow re-entering the bus number plate
                            }
                            else if (choice == "2") {
                                system("cls");
                                staff_bus(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                system("cls");

                ResultSet* res = executeQuery("SELECT * FROM bus WHERE number_plate = '" + numplate + "'");

                while (res->next()) {
                    cout << "\t\t\t                 BUS DETAIL                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Bus Number Plate    : " << res->getString("number_plate") << endl;
                    cout << endl;
                    cout << "\t\t\t   Capacity            : " << res->getString("capacity") << endl;
                    cout << endl;
                    cout << "\t\t\t   Type                : " << res->getString("type") << endl;
                    cout << endl;
                    cout << "\t\t\t   Brand               : " << res->getString("brand") << endl;
                    cout << endl;
                    cout << "\t\t\t   Condition           : " << res->getString("condition") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Which column you want to update?" << endl;
                    cout << endl;
                    cout << "\t1. Condition        2. Back" << endl;
                    cout << endl;

                    do {
                        cout << "Option  :  ";
                        cin >> column;

                        if (column == "1") {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            cout << "Enter the condition for this Bus:  ";
                            cin.ignore();
                            getline(cin, condition);
                            cout << endl;
                            cout << endl;
                            cout << "Are you sure you want to change " << res->getString("condition") << " to " << condition << " ?" << endl;
                            cout << endl;
                            cout << "Enter Y for Yes, N for No" << endl;
                            cout << endl;
                            do {
                                cout << "Option  :  ";
                                cin >> c;

                                if (c == "Y" || c == "y") {
                                    executeInstruction("UPDATE bus SET `condition` = '" + condition + "' WHERE number_plate = '" + numplate + "'");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << "\t\t\t|      Bus Update Successfully     |" << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress anykey to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    staff_bus(akaun, pass);
                                }
                                else if (c == "N" || c == "n") {
                                    system("cls");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t***  Bus not Updated  ***" << endl;
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress anykey to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    staff_update_bus(akaun, pass);
                                }
                                else {
                                    cout << "Invalid Input , Please Enter Y for Yes, N for No " << endl;
                                    cout << endl;
                                }
                            } while (c != "Y" && c != "y" && c != "N" && c != "n");
                        }
                        else if (column == "2") {
                            system("cls");
                            staff_update_bus(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl;
                            cout << endl;
                        }
                    } while (column != "1" && column != "2");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (bm != "1" && bm != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_delete_bus(string akaun, string pass) {
    try {
        connectToDatabase();

        string numplate, dboption, YorN, choice;

        do {
            system("cls");
            staff_bus_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Bus" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dboption;

            if (dboption == "1") {
                //system("cls");
                staff_bus(akaun, pass);
            }
            else if (dboption == "2") {
                int count{};
                do {
                    cout << "\nEnter Bus Number Plate to Delete: ";
                    cin >> numplate;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM bus WHERE number_plate = '" + numplate + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Bus does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the bus number plate
                            }
                            else if (choice == "2") {
                                system("cls");
                                staff_bus(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM bus WHERE number_plate = '" + numplate + "'");
                while (res->next()) {
                    cout << "\t\t\t                 BUS DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Bus Number Plate    : " << res->getString("number_plate") << endl;
                    cout << endl;
                    cout << "\t\t\t   Capacity            : " << res->getInt("capacity") << endl;
                    cout << endl;
                    cout << "\t\t\t   Type                : " << res->getString("type") << endl;
                    cout << endl;
                    cout << "\t\t\t   Brand               : " << res->getString("brand") << endl;
                    cout << endl;
                    cout << "\t\t\t   Condition           : " << res->getString("condition") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure want to Delete this " << numplate << " Bus ?" << endl;


                    do {


                        cout << "Enter Y to Delete N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete bus directly
                            executeInstruction("DELETE FROM bus WHERE number_plate = '" + numplate + "'");
                            cout << endl;
                            cout << "Bus deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            staff_bus(akaun, pass);
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Bus not Deleted  **" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            staff_delete_bus(akaun, pass);
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dboption != "1" && dboption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_driver_list()
{
    connectToDatabase();

    cout << endl;
    cout << endl;
    cout << "    DRIVER  LIST" << endl;
    cout << "-------------------" << endl;
    cout << endl;
    cout << endl;

    try {
        connectToDatabase();


        ResultSet* res = executeQuery("SELECT * FROM driver");

        vector<vector<string>> table;
        vector<string> columnNames =
        {
            "|  Driver ID", "|  Name", "|  Address", "|  Phone Number"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);


        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("driver_ID"));
            rowData.push_back(res->getString("driver_name"));
            rowData.push_back(res->getString("driver_address"));
            rowData.push_back(res->getString("driver_phonenumber"));

            table.push_back(rowData);

        }
        displayTable(table);

        delete res;
        closeDatabaseConnection();


    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_add_driver(string akaun, string pass)
{
    try {
        connectToDatabase();

        string did, dn, da, dp, bo, adoption, choice;


        staff_driver_list();
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back Menu or 2 to Add Driver" << endl;
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                staff_driver(akaun, pass);
            }
            else if (bo == "2") {
                cin.ignore();

                // Check if the bus already exists
                int count = 0;
                do {
                    cout << "\nEnter Driver ID to Add: ";
                    getline(cin, did);

                    ResultSet* res = executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + did + "'");

                    if (res->next()) {
                        count = res->getInt(1);
                        if (count > 0) {
                            cout << "Driver ID already exist." << endl;
                            do {
                                cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                cout << "Option  :  ";
                                cin >> choice;
                                if (choice == "1") {
                                    system("cls");
                                    staff_add_driver(akaun, pass);
                                }
                                else if (choice == "2") {
                                    system("cls");
                                    staff_driver(akaun, pass);
                                }
                                else {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (choice != "1" && choice != "2");
                        }
                        delete res;
                    }
                } while (count > 0);

                cout << "Driver Name  : ";
                getline(cin, dn);
                cout << endl;
                cout << "Driver Address  : ";
                getline(cin, da);
                cout << endl;
                cout << "Driver Phone Number  : ";

                bool validPhoneNumber = false;
                while (!validPhoneNumber) {
                    getline(cin, dp);

                    if (isValidPhoneNumber(dp)) {
                        validPhoneNumber = true;
                    }
                    else {
                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                    }
                }
                
                cout << endl;

                cout << "=======================================================================================" << endl;
                cout << endl;
                cout << "     Driver ID               : " << did << endl;
                cout << "     Driver Name             : " << dn << endl;
                cout << "     Driver Address          : " << da << endl;
                cout << "     Driver Phone Number     : " << dp << endl;
                cout << endl;
                cout << "=======================================================================================" << endl;
                cout << endl;
                cout << "Are you sure want to Add this Bus? (Y or N)" << endl;
                cout << "Enter Y for Yes, N for No" << endl;
                do {
                    cout << "Option  : ";
                    cin >> adoption;

                    if (adoption == "Y" || adoption == "y") {
                        string ad;
                        // Execute SQL insert statement to add bus directly
                        executeInstruction("INSERT INTO driver(driver_ID, driver_name, driver_address, driver_phonenumber) VALUES ('" + did + "', '" + dn + "', '" + da + "', '" + dp + "')");
                        cout << endl;
                        cout << "Driver Added Successfully." << endl;
                        /*  cout << "Press any key to continue..." << endl;
                          cin >> ad;*/
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        staff_driver(akaun, pass);
                    }
                    else if (adoption == "N" || adoption == "n") {
                        string bw;
                        cout << endl;
                        cout << "***  driver not Added  ***" << endl;
                        cout << endl;
                        cout << "Press any key to continue..." << endl;
                        cin >> bw;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        staff_add_driver(akaun, pass);
                    }
                    else {
                        cout << "Invalid Input , Please Enter Y for Yes, N for No " << endl;
                        cout << endl;
                    }
                } while (adoption != "Y" && adoption != "y" && adoption != "N" && adoption != "n");
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }

        } while (bo != "1" && bo != "2");

        closeDatabaseConnection();
    }
    catch (const std::exception& e) {
        // Handle the exception here
        cerr << "Exception caught: " << e.what() << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_update_driver(string akaun, string pass) {
    try {
        connectToDatabase();

        string dm, choice, column, c, b, driverID, newValue;

        do {
            system("cls");
            staff_driver_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Update Driver" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dm;

            if (dm == "1") {
                system("cls");
                staff_driver(akaun, pass);
                return; // Exit the function
            }
            else if (dm == "2") {
                int count{};
                do {
                    cout << "\nEnter Driver ID to Update: ";
                    cin >> driverID;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + driverID + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << "Driver does not exist." << endl << endl;

                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;

                            if (choice == "1") {
                                count = 0; // Reset count to allow retry
                                break; // Break out of the inner loop to allow re-entering the driver ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                staff_driver(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                system("cls");

                ResultSet* res = executeQuery("SELECT * FROM driver WHERE driver_ID = '" + driverID + "'");

                while (res->next()) {
                    cout << "\t\t\t                 DRIVER DETAIL                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Driver ID           : " << res->getString("driver_ID") << endl;
                    cout << endl;
                    cout << "\t\t\t   Name                : " << res->getString("driver_name") << endl;
                    cout << endl;
                    cout << "\t\t\t   Address             : " << res->getString("driver_address") << endl;
                    cout << endl;
                    cout << "\t\t\t   Phone Number        : " << res->getString("driver_phonenumber") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Which column do you want to update?" << endl;
                    cout << endl;
                    cout << "\t1. Name        2. Address        3. Phone Number        4. Back" << endl;
                    cout << endl;

                    do {
                        cout << "Option  :  ";
                        cin >> column;

                        if (column == "1" || column == "2" || column == "3") {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            if (column == "1") {
                                cout << "Enter the new name for this driver:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "2") {
                                cout << "Enter the new address for this driver:  ";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (column == "3") {
                               
                                cin.ignore();
                                cout << "Enter the new phone number for this driver:  ";

                                bool validPhoneNumber = false;
                                while (!validPhoneNumber) {

                                    getline(cin, newValue);

                                    if (isValidPhoneNumber(newValue)) {
                                        validPhoneNumber = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                                    }
                                }
                                
                            }
                            cout << endl;
                            cout << endl;
                            string oldValue = column == "1" ? res->getString("driver_name") : column == "2" ? res->getString("driver_address") : res->getString("driver_phonenumber");
                            cout << "Are you sure you want to change " << oldValue << " to " << newValue << "?" << endl;
                            cout << endl;
                            cout << "Enter Y for Yes, N for No" << endl;
                            cout << endl;
                            do {
                                cout << "Option  :  ";
                                cin >> c;

                                if (c == "Y" || c == "y") {
                                    string query;
                                    if (column == "1") {
                                        query = "UPDATE driver SET driver_name = '" + newValue + "' WHERE driver_ID = '" + driverID + "'";
                                    }
                                    else if (column == "2") {
                                        query = "UPDATE driver SET driver_address = '" + newValue + "' WHERE driver_ID = '" + driverID + "'";
                                    }
                                    else if (column == "3") {
                                        query = "UPDATE driver SET driver_phonenumber = '" + newValue + "' WHERE driver_ID = '" + driverID + "'";
                                    }
                                    executeInstruction(query);
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << "\t\t\t|      Driver Update Successfully     |" << endl;
                                    cout << "\t\t\t------------------------------------\n";
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress any key to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    staff_driver(akaun, pass);
                                }
                                else if (c == "N" || c == "n") {
                                    system("cls");
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t***  Driver not Updated  ***" << endl;
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\tPress any key to continue..." << endl;
                                    cin >> b;
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    staff_update_driver(akaun, pass);
                                }
                                else {
                                    cout << "Invalid Input, Please Enter Y for Yes, N for No " << endl;
                                    cout << endl;
                                }
                            } while (c != "Y" && c != "y" && c != "N" && c != "n");
                        }
                        else if (column == "4") {
                            system("cls");
                            staff_update_driver(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl;
                            cout << endl;
                        }
                    } while (column != "1" && column != "2" && column != "3" && column != "4");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dm != "1" && dm != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_delete_driver(string akaun, string pass) {
    try {
        connectToDatabase();

        string driverID, dboption, YorN, choice;

        do {
            system("cls");
            staff_driver_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Driver" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dboption;

            if (dboption == "1") {
                system("cls");
                staff_driver(akaun, pass);
            }
            else if (dboption == "2") {
                int count{};
                do {
                    cout << "\nEnter Driver ID to Delete: ";
                    cin >> driverID;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + driverID + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Driver does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the driver ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                staff_driver(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM driver WHERE driver_ID = '" + driverID + "'");
                while (res->next()) {
                    cout << "\t\t\t                 DRIVER DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Driver ID           : " << res->getString("driver_ID") << endl;
                    cout << endl;
                    cout << "\t\t\t   Name                : " << res->getString("driver_name") << endl;
                    cout << endl;
                    cout << "\t\t\t   Address             : " << res->getString("driver_address") << endl;
                    cout << endl;
                    cout << "\t\t\t   Phone Number        : " << res->getString("driver_phonenumber") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure you want to delete this driver?" << endl;

                    do {
                        cout << "Enter Y to Delete, N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete driver directly
                            executeInstruction("DELETE FROM driver WHERE driver_ID = '" + driverID + "'");
                            cout << endl;
                            cout << "Driver deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            staff_driver(akaun, pass);
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Driver not Deleted  ***" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            staff_delete_driver(akaun, pass);
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dboption != "1" && dboption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_trip_list()
{
    connectToDatabase();

    cout << endl;
    cout << endl;
    cout << "\t\t\t   TRIP  LIST" << endl;
    cout << "\t\t\t----------------" << endl;
    cout << endl;
    cout << endl;

    try {
        connectToDatabase();

        ResultSet* res = executeQuery("SELECT * FROM trip");

        vector<vector<string>> table;
        vector<string> columnNames =
        {
            "| Trip ID", "| Bus", "| Driver ID", "| Destination", "| Start Time", "| End Time", "| Duration", "| Date Start", "| Date End ", "| Price", "| Seat Available"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);

        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("trip_ID"));
            rowData.push_back(res->getString("number_plate"));
            rowData.push_back(res->getString("driver_ID"));
            rowData.push_back(res->getString("destination"));
            rowData.push_back(res->getString("start_time"));
            rowData.push_back(res->getString("end_time"));
            rowData.push_back(res->getString("duration"));
            rowData.push_back(res->getString("start_date"));
            rowData.push_back(res->getString("end_date"));
            rowData.push_back(res->getString("ticket_price"));
            rowData.push_back(res->getString("seat_available"));

            table.push_back(rowData);
        }
        displayTable(table);

        delete res;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_add_trip(string akaun, string pass) {
    try {
        connectToDatabase(); // Establish the database connection

        string tripId, numplate, drivid, dest, start, end, dur, dtstart, dtend, prc, atoption, bo, choice, choice1, choice2, choice3;
        int count = 0;
        int seat;

        staff_trip_list();
        connectToDatabase();
        cout << endl << endl;
        cout << "Enter 1 to Back Menu or 2 to Add Trip" << endl;
        cout << endl;

        do {
            cout << "Option  : ";
            cin >> bo;
            if (bo == "1") {
                system("cls");
                staff_trip(akaun, pass);
                return; // Exit the function to avoid further execution
            }
            else if (bo == "2") {
                cin.ignore();

                try {
                    if (!globalCon) {
                        cerr << "Database connection is not established." << endl;
                        return; // Handle the error appropriately
                    }

                    unique_ptr<Statement> stmt(globalCon->createStatement()); 

                    int count1 = 0;

                    do {
                        cout << endl << "Enter Trip ID to add: ";
                        getline(cin, tripId);
                        cout << endl;
                        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*) FROM trip WHERE trip_ID = '" + tripId + "'"));

                        if (res->next()) {
                            count1 = res->getInt(1);
                            if (count1 > 0) {
                                cout << "Trip ID already exists." << endl << endl;
                                do {
                                    cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                    cout << "Option  :  ";
                                    cin >> choice;
                                    if (choice == "1") {
                                        system("cls");
                                        staff_add_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else if (choice == "2") {
                                        system("cls");
                                        staff_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else {
                                        cout << "Incorrect" << endl << endl;
                                    }
                                } while (choice != "1" && choice != "2");
                            }
                        }
                    } while (count1 > 0);

                    do {
                        count = 0;

                        system("cls");
                        staff_bus_list();
                        cout << endl;
                        cout << "Bus number plate for this trip: ";
                        getline(cin, numplate);

                        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*), capacity FROM bus WHERE number_plate = '" + numplate + "'"));

                        if (res->next()) {
                            count = res->getInt(1);
                            seat = res->getInt(2);

                            if (count == 0) {
                                cout << "Bus does not exist." << endl << endl;

                                do {
                                    cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                    cout << "Option: ";
                                    cin >> choice1;

                                    if (choice1 == "1") {
                                        cin.ignore();
                                        break;
                                    }
                                    else if (choice1 == "2") {
                                        system("cls");
                                        staff_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else {
                                        cout << "Incorrect" << endl << endl;
                                    }

                                } while (choice1 != "1" && choice1 != "2");
                            }
                        }

                    } while (count == 0);

                    do {
                        system("cls");
                        staff_driver_list();
                        cout << endl;
                        cout << "Driver for this trip (Driver ID)  : ";
                        getline(cin, drivid);

                        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*) FROM driver WHERE driver_ID = '" + drivid + "'"));

                        if (res->next()) {
                            count = res->getInt(1);
                            if (count == 0) {
                                cout << "Driver does not exist." << endl << endl;
                                do {
                                    cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                    cout << "Option  :  ";
                                    cin >> choice2;
                                    if (choice2 == "1") {
                                        cin.ignore();
                                        break;
                                    }
                                    else if (choice2 == "2") {
                                        system("cls");
                                        staff_add_trip(akaun, pass);
                                        return; // Exit to prevent further execution
                                    }
                                    else {
                                        cout << "Incorrect" << endl << endl;
                                    }
                                } while (choice2 != "1" && choice2 != "2");
                            }
                        }
                    } while (count == 0);

                    cout << endl;
                    cout << "Destination of this trip  : ";
                    getline(cin, dest);
                    cout << endl;
                    cout << "Start Time : ";
                    getline(cin, start);
                    cout << endl;
                    cout << "End Time  : ";
                    getline(cin, end);
                    cout << endl;
                    cout << "Duration : ";
                    getline(cin, dur);
                    cout << endl;
                    cout << "Start Date(YYYY-MM-DD)  : ";

                    bool validsDate = false;

                    while (!validsDate) {
                        cin >> dtstart;
                        if (isValidDate(dtstart)) {
                            validsDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "Start Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    }

                    cout << endl;
                    cout << "End Date(YYYY-MM-DD)  : ";
                    bool valideDate = false;

                    while (!valideDate) {
                        cin >> dtend;

                        if (isValidDate(dtend)) {
                            valideDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "End Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    }

                    cout << endl;
                    cout << endl;
                    cout << "Ticket Price(RM)  : RM ";
                    cin.ignore();
                    getline(cin, prc);
                    cout << endl;

                    cout << "\t\t\t======================================================" << endl;
                    cout << endl;
                    cout << "\t\t\t    Trip ID            : " << tripId << endl;
                    cout << "\t\t\t    Bus                : " << numplate << endl;
                    cout << "\t\t\t    Driver             : " << drivid << endl;
                    cout << "\t\t\t    Destination        : " << dest << endl;
                    cout << "\t\t\t    Start Time         : " << start << endl;
                    cout << "\t\t\t    End Time           : " << end << endl;
                    cout << "\t\t\t    Duration           : " << dur << endl;
                    cout << "\t\t\t    Date Start         : " << dtstart << endl;
                    cout << "\t\t\t    Date End           : " << dtend << endl;
                    cout << "\t\t\t    Price(RM)          : RM " << prc << endl;
                    cout << "\t\t\t    Seat Available     : " << seat << endl;
                    cout << endl;
                    cout << "\t\t\t=======================================================" << endl;
                    cout << endl;
                    cout << "Are you sure want to Add this Trip? (Y or N)" << endl;
                    cout << endl;

                    do {
                        cout << "Option  : ";
                        cin >> atoption;

                        if (atoption == "Y" || atoption == "y") {
                            string ak;
                            // T.add_trip(tripId, numplate, drivid, dest, start, end, dur, dtstart, prc, seat, dtend); // Assuming add_trip is a member function of class Trip
                            cout << endl;
                            std::string seatStr = std::to_string(seat);

                            // Construct the INSERT query
                            std::string insertQuery = "INSERT INTO trip (trip_ID, number_plate, driver_ID, destination, start_time, end_time, duration, start_date, end_date, ticket_price, seat_available) VALUES ('" + tripId + "', '" + numplate + "', '" + drivid + "', '" + dest + "', '" + start + "', '" + end + "', '" + dur + "', '" + dtstart + "', '" + dtend + "', '" + prc + "', '" + seatStr + "')";

                            // Execute the query
                            stmt->execute(insertQuery);

                            // Print success message
                            cout << "Trip added successfully!" << endl;

                            cout << "Press any key to continue..." << endl;
                            cin >> ak;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            staff_trip(akaun, pass);
                        }
                        else if (atoption == "N" || atoption == "n") {
                            string aa;
                            cout << endl;
                            cout << "***  Trip not Added  ***" << endl;
                            cout << endl;
                            cout << "Press any key to continue..." << endl;
                            cin >> aa;
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            staff_add_trip(akaun, pass);
                        }
                        else {
                            cout << "Incorrect" << endl << endl;
                        }
                    } while (atoption != "Y" && atoption != "y" && atoption != "N" && atoption != "n");

                }
                catch (const SQLException& e) {
                    cerr << "SQLException caught: " << e.what() << endl;
                }
                catch (const exception& e) {
                    cerr << "Exception caught: " << e.what() << endl;
                }

            }
            else {
                cout << "Incorrect" << endl << endl;
            }
        } while (bo != "1" && bo != "2");
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

    closeDatabaseConnection(); // Close the database connection at the end of the function
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_update_trip(string akaun, string pass)
{
    connectToDatabase();

    string tripId, bm;
    int choice;
    staff_trip_list();
    cout << std::endl;
    cout << "Enter 1 to Back Menu or 2 to Update Trip" << std::endl;
    cout << std::endl;

    do {
        cout << endl;
        std::cout << "Option  : ";
        std::cin >> bm;
        if (bm == "1")
        {
            system("cls");
            staff_trip(akaun, pass);
        }
        else if (bm == "2")
        {
            connectToDatabase();

            sql::Statement* stmt = globalCon->createStatement();

            int count{};
            do {
                std::cout << "\nEnter Trip ID to Update: ";
                std::cin >> tripId;

                sql::ResultSet* res = stmt->executeQuery("SELECT COUNT(*) FROM trip WHERE trip_ID = '" + tripId + "'");

                if (res->next()) {
                    count = res->getInt(1);
                    if (count == 0) {
                        std::cout << "Trip ID does not exist." << std::endl << std::endl;
                        do {
                            std::cout << "Enter 1 to Retry, 2 to Exit" << std::endl;
                            std::cout << "Option  :  ";
                            std::cin >> choice;
                            if (choice == 1)
                            {
                                system("cls");
                                staff_update_trip(akaun, pass);
                            }
                            else if (choice == 2)
                            {
                                system("cls");
                                staff_trip(akaun, pass);
                            }
                            else {
                                std::cout << "Incorrect" << std::endl << std::endl;
                            }
                        } while (choice != 1 && choice != 2);
                    }

                    delete res;
                }
            } while (count == 0);
            cout << endl;

            system("cls");
            connectToDatabase();

            pstmt = globalCon->prepareStatement("SELECT * FROM trip WHERE trip_ID = ?");
            pstmt->setString(1, tripId);

            sql::ResultSet* res = pstmt->executeQuery();

            // Print trip details
            std::cout << "Trip Details:" << std::endl;
            while (res->next()) {
                cout << "Trip ID: " << res->getString("trip_ID") << std::endl;
                cout << "Bus Number Plate: " << res->getString("number_plate") << std::endl;
                cout << "Driver ID: " << res->getString("driver_ID") << std::endl;
                cout << "Destination: " << res->getString("destination") << std::endl;
                cout << "Start Time: " << res->getString("start_time") << std::endl;
                cout << "End Time: " << res->getString("end_time") << std::endl;
                cout << "Duration: " << res->getString("duration") << std::endl;
                cout << "Date Start: " << res->getString("start_date") << std::endl;
                cout << "Date End: " << res->getString("end_date") << std::endl;
                cout << "Price: " << res->getString("ticket_price") << std::endl;
                cout << "---------------------------------------" << std::endl;
            }

            delete res;

            string newValue;
            string columnName;
            bool validChoice = false;

            do {
                // Allow user to choose which column to update
                cout << "Choose the column to update:" << endl;
                cout << "1. Destination" << endl;
                cout << "2. Start Time" << endl;
                cout << "3. End Time" << endl;
                cout << "4. Duration" << endl;
                cout << "5. Start Date" << endl;
                cout << "6. End Date" << endl;
                cout << "7. Price" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                // Handle user choice and update the selected column
                if (choice == 1) {
                    cout << "\nEnter New Destination :";
                    columnName = "destination";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 2) {
                    cout << "\nEnter New Start Time :";
                    columnName = "start_time";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 3) {
                    cout << "\nEnter New end Time :";
                    columnName = "end_time";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 4) {
                    cout << "\nEnter New Duration Time :";
                    columnName = "duration";
                    cin >> newValue;
                    validChoice = true;
                }
                else if (choice == 5) {
                    cout << "\nEnter New Start Date :";
                    columnName = "start_date";
                    bool validsDate = false;
                    do {
                        cin >> newValue;
                        if (isValidDate(newValue)) {
                            validsDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "Start Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    } while (!validsDate);
                    validChoice = true;
                }
                else if (choice == 6) {
                    cout << "\nEnter New End Date :";
                    columnName = "end_date";
                    bool validDate = false;
                    do {
                        cin >> newValue;
                        if (isValidDate(newValue)) {
                            validDate = true;
                        }
                        else {
                            cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                            cout << "End Date (YYYY-MM-DD)  : ";
                            cin.clear(); // Clear any error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                        }
                    } while (!validDate);
                    validChoice = true;
                }
                else if (choice == 7) {
                    cout << "\nEnter New Price :";
                    columnName = "ticket_price";
                    cin >> newValue;
                    validChoice = true;
                }
                else {
                    cout << "Invalid choice. Please try again." << endl << endl;
                    cin.clear(); // Clear any error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!validChoice);

            // Update the database with new value
            string updateQuery = "UPDATE trip SET " + columnName + " = '" + newValue + "' WHERE trip_ID = '" + tripId + "'";
            stmt->executeUpdate(updateQuery);
            cout << "Trip updated successfully!" << std::endl;

            string op;
            do {
                cout << "\nEnter 1 to Back \n";
                cout << "\n Option : ";
                cin >> op;
                if (op == "1")
                {
                    system("cls");
                    staff_menu(akaun, pass);
                }
                else
                {
                    cout << "\n Invalid Input \n";
                }
            } while (op != "1");
        }
        else
        {
            cout << "Incorrect" << std::endl << std::endl;
        }
    } while (bm != "1" && bm != "2");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void staff_delete_trip(string akaun, string pass) {
    try {
        connectToDatabase();

        string tripId, dtoption, YorN, choice;

        do {
            system("cls");
            staff_trip_list();
            cout << endl;
            cout << "Enter 1 to Back Menu or 2 to Delete Trip" << endl;
            cout << endl;
            cout << "Option  : ";
            cin >> dtoption;

            if (dtoption == "1") {
                staff_trip(akaun, pass);
                return;
            }
            else if (dtoption == "2") {
                int count{};
                do {
                    cout << "\nEnter Trip ID to Delete: ";
                    cin >> tripId;

                    ResultSet* countResult = executeQuery("SELECT COUNT(*) FROM trip WHERE trip_ID = '" + tripId + "'");
                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        delete countResult;
                    }

                    if (count == 0) {
                        cout << endl;
                        cout << "Trip does not exist." << endl;
                        cout << endl;
                        do {
                            cout << "Enter 1 to Retry, 2 to Exit" << endl;
                            cout << "Option  :  ";
                            cin >> choice;
                            if (choice == "1") {
                                break; // Break out of the inner loop to allow re-entering the trip ID
                            }
                            else if (choice == "2") {
                                system("cls");
                                staff_trip(akaun, pass);
                                return; // Exit the function
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (choice != "1" && choice != "2");
                    }
                } while (count == 0);

                if (count == 0) {
                    continue; // Continue to the next iteration of the outer loop to display the menu again
                }

                // Confirm deletion
                system("cls");
                ResultSet* res = executeQuery("SELECT * FROM trip WHERE trip_ID = '" + tripId + "'");
                while (res->next()) {
                    cout << "\t\t\t                 TRIP DETAILS                " << endl;
                    cout << "\t\t\t=============================================" << endl;
                    cout << endl;
                    cout << "\t\t\t   Trip ID             : " << res->getString("trip_ID") << endl;
                    cout << "\t\t\t   Bus Number Plate    : " << res->getString("number_plate") << endl;
                    cout << "\t\t\t   Driver ID           : " << res->getString("driver_ID") << endl;
                    cout << "\t\t\t   Destination         : " << res->getString("destination") << endl;
                    cout << "\t\t\t   Start Time          : " << res->getString("start_time") << endl;
                    cout << "\t\t\t   End Time            : " << res->getString("end_time") << endl;
                    cout << "\t\t\t   Duration            : " << res->getString("duration") << endl;
                    cout << "\t\t\t   Start Date          : " << res->getString("start_date") << endl;
                    cout << "\t\t\t   End Date            : " << res->getString("end_date") << endl;
                    cout << "\t\t\t   Ticket Price (RM)   : RM " << res->getString("ticket_price") << endl;
                    cout << "\t\t\t   Seat Available      : " << res->getInt("seat_available") << endl;
                    cout << endl;
                    cout << endl;

                    cout << "Are you sure want to Delete this " << tripId << " Trip ?" << endl;

                    do {
                        cout << "Enter Y to Delete N to Cancel" << endl;
                        cout << "Option  :  ";
                        cin >> YorN;

                        if (YorN == "Y" || YorN == "y") {
                            // Execute SQL delete statement to delete trip directly
                            executeInstruction("DELETE FROM trip WHERE trip_ID = '" + tripId + "'");
                            cout << endl;
                            cout << "Trip deleted successfully." << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            staff_trip(akaun, pass);
                        }
                        else if (YorN == "N" || YorN == "n") {
                            cout << endl;
                            cout << "***  Trip not Deleted  ***" << endl;
                            cout << "Press any key to continue..." << endl;
                            cin.ignore();
                            cin.get(); // Wait for key press
                            system("cls");
                            staff_delete_trip(akaun, pass);
                        }
                        else {
                            cout << "Incorrect input. Please enter Y or N." << endl;
                            cout << endl;
                        }
                    } while (YorN != "Y" && YorN != "y" && YorN != "N" && YorN != "n");
                }
                delete res;
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (dtoption != "1" && dtoption != "2");
    }
    catch (sql::SQLException& e) {
        cerr << "# ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "# ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void about_me(string ac, string pw) {
    string dp, yon, choice, newValue, column, goback, newPassword, confirmPassword;

    connectToDatabase();

    try {
        // Prepare SQL statement to check customer credentials
        string query = "SELECT * FROM customer WHERE customer_ID = ? AND customer_password = ?";
        PreparedStatement* pstmt = globalCon->prepareStatement(query);
        pstmt->setString(1, ac);
        pstmt->setString(2, pw);

        ResultSet* rs = pstmt->executeQuery();

        while (rs->next()) {
            cout << "\t\t\t                USER PROFILE                " << endl;
            cout << "\t\t\t=============================================" << endl;
            cout << endl;
            cout << "\t\t\t   Username       : " << rs->getString("customer_ID") << endl;
            cout << endl;
            cout << "\t\t\t   Name           : " << rs->getString("customer_name") << endl;
            cout << endl;
            cout << "\t\t\t   Email          : " << rs->getString("customer_email") << endl;
            cout << endl;
            cout << "\t\t\t   Address        : " << rs->getString("customer_address") << endl;
            cout << endl;
            cout << "\t\t\t   Phone Number   : " << rs->getString("customer_phonenumber") << endl;
            cout << endl;
            cout << endl;

            cout << "Do you want to change your details?" << endl;
            do {
                cout << "Enter 1 for Update details, 2 for Back" << endl;
                cout << endl;

                cout << "Option  :  ";
                cin >> yon;

                if (yon == "1") {
                    do {
                        cout << endl;
                        cout << "Which detail do you want to update?" << endl;
                        cout << "1. Email" << endl;
                        cout << "2. Name" << endl;
                        cout << "3. Address" << endl;
                        cout << "4. Phone Number" << endl;
                        cout << "5. Password" << endl;
                        cout << "6. Back" << endl;
                        cout << endl;

                        cout << "Option: ";
                        cin >> choice;
                        cin.ignore();

                        if (choice == "6") {
                            system("cls");
                            this_thread::sleep_for(chrono::seconds(1));
                            cust_menu(ac, pw);
                            break; // Exit the loop and go back to the menu
                        }

                        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5") {
                            cout << "Invalid option. Please enter a number between 1 and 6." << endl;
                            continue; // Restart the loop to ask for a valid choice
                        }

                        if (choice == "5") {
                            do {
                                cout << "Enter the new password: ";
                                getline(cin, newPassword);
                                cout << "Confirm the new password: ";
                                getline(cin, confirmPassword);

                                if (newPassword != confirmPassword) {
                                    cout << "Passwords do not match. Try again." << endl;
                                }
                            } while (newPassword != confirmPassword);

                            column = "customer_password";
                            newValue = newPassword;
                        }
                        else {
                            cout << "Enter the new value: ";
                            

                            if (choice == "1") {
                                
                                column = "customer_email";
                                bool validEmail = false;
                                while (!validEmail) {
                                 
                                    cin.ignore();
                                    getline(cin, newValue);

                                   
                                    if (isValidEmail(newValue)) {
                                        validEmail = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Email , Please Enter a Valid One ." << endl;
                                    }
                                }
                                
                            }
                            else if (choice == "2") {
                                column = "customer_name";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (choice == "3") {
                                column = "customer_address";
                                cin.ignore();
                                getline(cin, newValue);
                            }
                            else if (choice == "4") {
                                column = "customer_phonenumber";
                                bool validPhoneNumber = false;
                                while (!validPhoneNumber) {
                                    getline(cin, newValue);

                                    if (isValidPhoneNumber(newValue)) {
                                        validPhoneNumber = true;
                                    }
                                    else {
                                        cerr << "\nThis is an Invalid Phone Number, Please Enter a Valid One." << endl;
                                    }
                                }
                                
                                
                            }
                        }
                        connectToDatabase();
                       
                        query = "UPDATE customer SET " + column + " = ? WHERE customer_ID = ?";
                        PreparedStatement* stmt = globalCon->prepareStatement(query);
                        stmt->setString(1, newValue);
                        stmt->setString(2, ac);
                        stmt->executeUpdate();

                        cout << endl;
                        cout << "\t\t-------------------------------" << endl;
                        cout << "\t\t|      Update Successfully     |" << endl;
                        cout << "\t\t-------------------------------" << endl;
                        cout << endl;

                        delete stmt;
                        this_thread::sleep_for(chrono::seconds(4));
                        system("cls");
                        cust_menu(ac, pw);
                    } while (true);
                }
                else if (yon == "2") {
                    system("cls");
                    this_thread::sleep_for(chrono::seconds(1));
                    cust_menu(ac, pw);
                }
                else {
                    cout << "Invalid input. Please enter 1 or 2." << endl;
                    cout << endl;
                }
            } while (yon != "1" && yon != "2");
        }

        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cust_trip_list()
{
    connectToDatabase();

    cout << endl;
    cout << endl;
    cout << "\t\t\t   TRIP  LIST" << endl;
    cout << "\t\t\t----------------" << endl;
    cout << endl;
    cout << endl;

    try {
        connectToDatabase();

        ResultSet* res = executeQuery("SELECT * FROM trip");

        vector<vector<string>> table;
        vector<string> columnNames =
        {
            "| Trip ID", "| Bus", "| Driver ID", "| Destination", "| Start Time", "| End Time", "| Duration", "| Date Start", "| Date End ", "| Price", "| Seat Available"
        };

        // Add table headers with custom column names
        table.push_back(columnNames);

        while (res->next()) {
            vector<string> rowData;
            rowData.push_back(res->getString("trip_ID"));
            rowData.push_back(res->getString("number_plate"));
            rowData.push_back(res->getString("driver_ID"));
            rowData.push_back(res->getString("destination"));
            rowData.push_back(res->getString("start_time"));
            rowData.push_back(res->getString("end_time"));
            rowData.push_back(res->getString("duration"));
            rowData.push_back(res->getString("start_date"));
            rowData.push_back(res->getString("end_date"));
            rowData.push_back(res->getString("ticket_price"));
            rowData.push_back(res->getString("seat_available"));

            table.push_back(rowData);
        }
        displayTable(table);

        delete res;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void booking(string custid, string pass) {
    string tripid, option, poption, dc, cd, dcopt, cdopt, dop, back, paymentmethod, firstletter, choice, sold;

    connectToDatabase();

    try {
        sql::PreparedStatement* stmt = globalCon->prepareStatement("SELECT * FROM customer WHERE customer_ID = ? AND customer_password = ?");
        stmt->setString(1, custid);
        stmt->setString(2, pass);

        sql::ResultSet* res = stmt->executeQuery();

        cout << "\t\t\t+==================================+" << endl;
        cout << "\t\t\t|          BOOKING  MENU           |" << endl;
        cout << "\t\t\t+==================================+" << endl;
        cout << endl;
        cout << endl;

        cust_trip_list();
        connectToDatabase();
        cout << endl;

        do {
            cout << "Enter 1 to Book, 2 to Back " << endl;
            cout << "Option  :  ";
            cin >> back;

            if (back == "1") {
                string tripId;
                int count = 0;

                do {
                    cout << "\nEnter Trip ID to Book  : ";
                    cin >> tripId;

                    stmt = globalCon->prepareStatement("SELECT COUNT(*) FROM trip WHERE trip_ID = ?");
                    stmt->setString(1, tripId);

                    sql::ResultSet* countResult = stmt->executeQuery();

                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        if (count == 0) {
                            cout << endl;
                            cout << "Trip ID does not exist." << endl;
                            cout << endl;
                        }
                    }

                    delete countResult; // Delete the ResultSet after using it

                } while (count == 0);

                stmt = globalCon->prepareStatement("SELECT seat_available FROM trip WHERE trip_ID = ?");
                stmt->setString(1, tripId);

                res = stmt->executeQuery();
                if (res->next()) {
                    int seatAvailable = res->getInt("seat_available");

                    if (seatAvailable == 0) {
                        cout << endl;
                        cout << "Trip Sold Out" << endl;
                        cout << endl;
                        cout << "Enter 1 to continue with another booking" << endl;
                        cout << endl;
                        do {
                            cout << "Option  :  ";
                            cin >> sold;
                            if (sold == "1") {
                                system("cls");
                                booking(custid, pass);
                            }
                            else {
                                cout << endl;
                                cout << "Incorrect" << endl;
                            }
                        } while (sold != "1");
                    }
                    else {

                        stmt = globalCon->prepareStatement("SELECT * FROM trip WHERE trip_ID = ?");
                        stmt->setString(1, tripId);

                        res = stmt->executeQuery();

                        while (res->next()) {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            cout << "\t\t                      TRIP  DETAILS                      " << endl;
                            cout << "\t\t=========================================================" << endl;
                            cout << "\t\t                                                         " << endl;
                            cout << "\t\t   Trip ID         : " << res->getString("trip_ID") << endl;
                            cout << "\t\t   Destination     : " << res->getString("destination") << endl;
                            cout << "\t\t   Start Time      : " << res->getString("start_time") << endl;
                            cout << "\t\t   End Time        : " << res->getString("end_time") << endl;
                            cout << "\t\t   Duration        : " << res->getString("duration") << endl;
                            cout << "\t\t   Start Date      : " << res->getString("start_date") << endl;
                            cout << "\t\t   End Date        : " << res->getString("end_date") << endl;
                            cout << "\t\t   Price           : RM" << res->getString("ticket_price") << endl;
                            cout << "\t\t                                                         " << endl;
                            cout << endl;
                        }

                        cout << "Are you sure you want to book this Trip? " << endl;
                        cout << "Enter Y for Yes, N for No, B for Exit" << endl;
                        cout << endl;
                        do {
                            cout << "Option  :  ";
                            cin >> option;

                            if (option == "Y" || option == "y") {
                                system("cls");
                                payment_menu(custid, pass, tripId);
                            }
                            else if (option == "N" || option == "n") {
                                cout << endl;
                                cout << "***  Booking Unsuccessful  ***" << endl;
                                cout << endl;
                                this_thread::sleep_for(chrono::seconds(2));
                                system("cls");
                                booking(custid, pass);
                            }
                            else if (option == "B" || option == "b") {
                                this_thread::sleep_for(chrono::seconds(2));
                                system("cls");
                                cust_menu(custid, pass);
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (option != "Y" && option != "y" && option != "N" && option != "n" && option != "B" && option != "b");
                    }
                }

            }
            else if (back == "2") {
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                cust_menu(custid, pass);
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (back != "1" && back != "2");

        delete res;
        delete stmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void payment_menu(string id, string ps, string tr)
{
    string seat, seatbooking, choice, choice1;
    cout << endl;
    cout << "\t\t\t+=============================+" << endl;
    cout << "\t\t\t|       SEAT SELECTION        |" << endl;
    cout << "\t\t\t+=============================+" << endl;

    cout << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  1A  |  1B  |  1C  |  1D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  2A  |  2B  |  2C  |  2D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  3A  |  3B  |  3C  |  3D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  4A  |  4B  |  4C  |  4D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  5A  |  5B  |  5C  |  5D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  6A  |  6B  |  6C  |  6D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  7A  |  7B  |  7C  |  7D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  8A  |  8B  |  8C  |  8D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t|  9A  |  9B  |  9C  |  9D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << "\t\t\t| 10A  | 10B  | 10C  | 10D  |" << endl;
    cout << "\t\t\t+------+------+------+------+" << endl;
    cout << endl;
    cout << endl;

    connectToDatabase();
    sql::PreparedStatement* stmt = globalCon->prepareStatement("SELECT * FROM booking WHERE trip_ID = ?");
    stmt->setString(1, tr);
    sql::ResultSet* res = stmt->executeQuery();

    bool isBooked;
    cout << "Seats Available : " << endl;

    for (int i = 1; i <= 10; i++) {
        for (char j = 'A'; j <= 'D'; j++) {
            seat = to_string(i) + j;
            isBooked = false;

            res->beforeFirst();

            while (res->next()) {
                if (res->getString("seat_number") == seat) {
                    isBooked = true;
                    break;
                }
            }

            if (!isBooked) {
                cout << seat << " ";
            }
        }
        cout << endl;
    }

    delete res;
    delete stmt;

    bool bookingfound = false;
    int count = 0;
    cout << endl;
    do {
        cout << "Please select your seat" << endl;
        cout << endl;
        cout << "Enter your seat number : ";
        cin >> seatbooking;
        cout << endl;

        if (seatbooking != "1A" && seatbooking != "1B" && seatbooking != "1C" && seatbooking != "1D" &&
            seatbooking != "2A" && seatbooking != "2B" && seatbooking != "2C" && seatbooking != "2D" &&
            seatbooking != "3A" && seatbooking != "3B" && seatbooking != "3C" && seatbooking != "3D" &&
            seatbooking != "4A" && seatbooking != "4B" && seatbooking != "4C" && seatbooking != "4D" &&
            seatbooking != "5A" && seatbooking != "5B" && seatbooking != "5C" && seatbooking != "5D" &&
            seatbooking != "6A" && seatbooking != "6B" && seatbooking != "6C" && seatbooking != "6D" &&
            seatbooking != "7A" && seatbooking != "7B" && seatbooking != "7C" && seatbooking != "7D" &&
            seatbooking != "8A" && seatbooking != "8B" && seatbooking != "8C" && seatbooking != "8D" &&
            seatbooking != "9A" && seatbooking != "9B" && seatbooking != "9C" && seatbooking != "9D" &&
            seatbooking != "10A" && seatbooking != "10B" && seatbooking != "10C" && seatbooking != "10D")
        {
            cout << endl;
            cout << "***  Invalid Seat number  ***" << endl;
            cout << endl;
            cout << "Enter 1 to Retry, 2 to Exit" << endl;
            do {
                cout << "Option  :  ";
                cin >> choice1;
                if (choice1 == "1")
                {
                    this_thread::sleep_for(chrono::seconds(2));
                    system("cls");
                    payment_menu(id, ps, tr);
                }
                else if (choice1 == "2")
                {
                    this_thread::sleep_for(chrono::seconds(2));
                    system("cls");
                    booking(id, ps);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (choice1 != "1" && choice1 != "2");
        }
        else
        {
            stmt = globalCon->prepareStatement("SELECT COUNT(*) FROM booking WHERE trip_ID = ? AND seat_number = ?");
            stmt->setString(1, tr);
            stmt->setString(2, seatbooking);
            res = stmt->executeQuery();

            if (res->next()) {
                count = res->getInt(1);
                if (count > 0) {
                    cout << endl;
                    cout << "***  Seat already booked  ***" << endl;
                    cout << endl;
                    bookingfound = true;
                    do {
                        cout << "Enter 1 to Retry, 2 to Exit" << endl;
                        cout << "Option : ";
                        cin >> choice;
                        if (choice == "1")
                        {
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            payment_menu(id, ps, tr);
                        }
                        else if (choice == "2")
                        {
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            booking(id, ps);
                        }
                        else {
                            cout << "Incorrect" << endl;
                            cout << endl;
                        }
                    } while (choice != "1" && choice != "2");
                }
                else {
                    delete res;
                    delete stmt;
                    break;
                }
            }
            else {
                cerr << "Error checking seat availability in database." << endl;
                delete res;
                delete stmt;
            }
        }
    } while (true);

    if (!bookingfound) {
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");

        string poption, paymentmethod, firstletter;

        stmt = globalCon->prepareStatement("SELECT * FROM customer WHERE customer_ID = ? AND customer_password = ?");
        stmt->setString(1, id);
        stmt->setString(2, ps);
        res = stmt->executeQuery();

        cout << endl;
        cout << "\t\t\t+===============================+" << endl;
        cout << "\t\t\t|        PAYMENT METHOD         |" << endl;
        cout << "\t\t\t+===============================+" << endl;
        cout << "\t\t\t|                               |" << endl;
        cout << "\t\t\t|      1.  Debit Card           |" << endl;
        cout << "\t\t\t|      2.  Credit Card          |" << endl;
        cout << "\t\t\t|      3.  Online Banking       |" << endl;
        cout << "\t\t\t|      4.  Back                 |" << endl;
        cout << "\t\t\t|                               |" << endl;
        cout << "\t\t\t+===============================+" << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "Please choose a payment method" << endl;
        cout << endl;
        do {
            cout << "Option  :  ";
            cin >> poption;

            if (poption == "1")
            {
                paymentmethod = "Debit Card";
                firstletter = "db";
                payment(id, ps, paymentmethod, firstletter, tr, seatbooking);
            }
            else if (poption == "2")
            {
                paymentmethod = "Credit Card";
                firstletter = "cr";
                payment(id, ps, paymentmethod, firstletter, tr, seatbooking);
            }
            else if (poption == "3")
            {
                paymentmethod = "Online Banking";
                firstletter = "on";
                online_payment(id, ps, paymentmethod, firstletter, tr, seatbooking);
            }
            else if (poption == "4")
            {
                system("cls");
                booking(id, ps);
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (poption != "1" && poption != "2" && poption != "3" && poption != "4");
    }

    closeDatabaseConnection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string generatereceipt(const std::string& trip, const std::string& bd, const std::string& d, const std::string& st, const std::string& et, const std::string& du, const std::string& ds, const std::string de, const std::string& p, const std::string& seatnumber, const std::string& bid, const std::string& bdate, const std::string& pdate, const std::string& pid, const std::string& pmethod, const std::string& cid)
{
   
    std::ostringstream receipt;

    receipt << std::endl;
    receipt << "\t\t\t                     BOOKING                       " << endl;
    receipt << "\t\t\t==================================================" << endl;
    receipt << "\t\t\t                                                  " << endl;
    receipt << "\t\t\t   Trip ID         : " << trip << endl;
    receipt << "\t\t\t   Bus Details     : " << bd << endl;
    receipt << "\t\t\t   Destination     : " << d << endl;
    receipt << "\t\t\t   Start Time      : " << st << endl;
    receipt << "\t\t\t   End Time        : " << et << endl;
    receipt << "\t\t\t   Duration        : " << du << endl;
    receipt << "\t\t\t   Date Start      : " << ds << endl;
    receipt << "\t\t\t   Date End        : " << de << endl;
    receipt << "\t\t\t   Price           : RM " << p << endl;
    receipt << "\t\t\t   Seat Number     : " << seatnumber << endl;
    receipt << "\t\t\t   Booking ID      : " << bid << endl;
    receipt << "\t\t\t   Booking Date    : " << bdate << endl;
    receipt << "\t\t\t   Payment Date    : " << pdate << endl;
    receipt << "\t\t\t   Payment ID      : " << pid << endl;
    receipt << "\t\t\t   Payment Method  : " << pmethod << endl;
    receipt << "\t\t\t   Customer        : " << cid << endl;
    receipt << "\t\t\t                                                  " << endl;
    receipt << endl;


   return receipt.str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void payment(string customerid, string password, string paymethod, string fl, string trip, string seat)
{
    string dcopt, dc, dop;
    double final_price;

    connectToDatabase();

    sql::PreparedStatement* stmt = globalCon->prepareStatement("SELECT * FROM customer WHERE customer_ID = ? AND customer_password = ?");
    stmt->setString(1, customerid);
    stmt->setString(2, password);
    sql::ResultSet* res = stmt->executeQuery();

    cout << "Are you confirm want to do this Payment" << endl;
    cout << "Enter Y for Yes, N for No" << endl;
    cout << endl;

    do {
        cout << endl;
        cout << "Option  :  ";
        cin >> dcopt;
        cout << endl;

        if (dcopt == "Y" || dcopt == "y")
        {
            system("cls");
            auto now = chrono::system_clock::now();
            time_t currentTime = chrono::system_clock::to_time_t(now);

            tm localTime;
            localtime_s(&localTime, &currentTime);

            int year = localTime.tm_year + 1900;
            int month = localTime.tm_mon + 1;
            int day = localTime.tm_mday;

            string paymentdate, paymentid, bookingid, bookingdate;
            int previousnumber = 0;

            int min = 100000;
            int max = 999999;

            for (int i = 5; i <= 7; ++i)
            {
                int num = rand() % (max - min + 1) + min;

                bookingid = fl + randomnumbercr(previousnumber);

                ostringstream oss;
                oss << year << '-' << setfill('0') << setw(2) << month << '-' << setfill('0') << setw(2) << day;
                paymentdate = oss.str();

                paymentid = bookingid + "y" + to_string(year) + to_string(month) + to_string(day);
                bookingdate = paymentdate;

                cout << endl;
                cout << endl;
                cout << "\t\t\t                 BOOKING DETAILS                   " << endl;
                cout << "\t\t\t==================================================" << endl;
                cout << endl;
                cout << "\t\t\t   Booking ID       :  " << bookingid << endl;
                cout << "\t\t\t   Booking Date     :  " << bookingdate << endl;
                cout << "\t\t\t   Payment Date     :  " << paymentdate << endl;
                cout << "\t\t\t   Payment ID       :  " << paymentid << endl;
                cout << "\t\t\t   Payment method   :  " << paymethod << endl;
                cout << "\t\t\t   Customer         :  " << customerid << endl;
                cout << "\t\t\t   Seat Number      :  " << seat << endl;
                cout << endl;
                cout << endl;

                double discounted_price = discount(customerid, password, trip);
                final_price = discounted_price > 0 ? discounted_price : stod(res->getString("ticket_price"));
                ostringstream inner_oss;
                inner_oss << fixed << setprecision(2) << final_price;
                string price_str = inner_oss.str();

                string oo;
                cout << endl;
                cout << "Are you sure continue with Payment" << endl;
                cout << "Enter Y for Yes, N for Cancel the Booking" << endl;
                cout << endl;

                do {
                    cout << "Option  :  ";
                    cin >> oo;

                    if (oo == "Y" || oo == "y")
                    {
                        try
                        {
                            sql::PreparedStatement* stmt;

                            connectToDatabase();

                            stmt = globalCon->prepareStatement("INSERT INTO booking(booking_ID, customer_ID, trip_ID, booking_date, seat_number, final_price) VALUES (?,?,?,?,?,?)");
                            stmt->setString(1, bookingid);
                            stmt->setString(2, customerid);
                            stmt->setString(3, trip);
                            stmt->setString(4, bookingdate);
                            stmt->setString(5, seat);
                            stmt->setDouble(6, final_price);
                            stmt->executeUpdate();

                            stmt = globalCon->prepareStatement("INSERT INTO payment(payment_ID, booking_ID, payment_method, payment_date) VALUES (?,?,?,?)");
                            stmt->setString(1, paymentid);
                            stmt->setString(2, bookingid);
                            stmt->setString(3, paymethod);
                            stmt->setString(4, paymentdate);
                            stmt->executeUpdate();

                            stmt = globalCon->prepareStatement("UPDATE trip SET seat_available = seat_available - 1 WHERE trip_ID = ?");
                            stmt->setString(1, trip);
                            stmt->executeUpdate();

                            system("cls");
                            cout << endl;
                            cout << endl;
                            cout << endl;
                            cout << endl;
                            cout << endl;
                            cout << endl;
                            cout << "\t\t\tYour Booking in Process" << endl;
                            cout << "\t\t\tPlease wait..." << endl;
                            cout << endl;
                            cout << endl;
                            //loading();
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            cout << endl;
                            cout << endl;
                            cout << "\t\t***  Booking Successful  ***" << endl;
                            cout << endl;

                            stmt = globalCon->prepareStatement("SELECT * FROM trip WHERE trip_ID = ?");
                            stmt->setString(1, trip);
                            res = stmt->executeQuery();

                            while (res->next())
                            {
                                cout << "\t//  RM " << final_price << " deducted from " << paymethod << endl;

                                string trip, busdetail, dest, start, end, dur, datestart, dateend;

                                trip = res->getString("trip_ID");
                                busdetail = res->getString("number_plate");
                                dest = res->getString("destination");
                                start = res->getString("start_time");
                                end = res->getString("end_time");
                                dur = res->getString("duration");
                                datestart = res->getString("start_date");
                                dateend = res->getString("end_date");

                                string receipt = generatereceipt(trip, busdetail, dest, start, end, dur, datestart, dateend, price_str, seat, bookingid, bookingdate, paymentdate, paymentid, paymethod, customerid);
                                saveReceiptToFile(receipt, "receipt.txt");
                                cout << endl;
                                cout << "\tThank You for Booking" << endl;
                                cout << endl;
                                cout << receipt;
                                cout << endl;
                                cout << endl;
                            }

                            cout << "Enter 1 to Continue with Another Booking, 2 to Exit" << endl;
                            do {
                                cout << endl;
                                cout << "Option  :  ";
                                cin >> dop;
                                cout << endl;
                                if (dop == "1")
                                {
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    booking(customerid, password);
                                }
                                else if (dop == "2")
                                {
                                    this_thread::sleep_for(chrono::seconds(2));
                                    system("cls");
                                    cust_menu(customerid, password);
                                }
                                else
                                {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (dop != "1" && dop != "2");

                            delete res;
                            delete stmt;

                        }
                        catch (const exception& e)
                        {
                            cerr << e.what() << '\n';
                        }
                    }
                    else if (oo == "N" || oo == "n")
                    {
                        string hb;
                        cout << endl;
                        cout << "***  Payment Unsuccessful  ***" << endl;
                        cout << "Press any key to continue..." << endl;
                        cin >> hb;
                        this_thread::sleep_for(chrono::seconds(2));
                        system("cls");
                        payment_menu(customerid, password, trip);
                    }
                    else {
                        cout << "Incorrect" << endl;
                        cout << endl;
                    }
                } while (oo != "Y" && oo != "y" && oo != "N" && oo != "n");
            }

        }
        else if (dcopt == "N" || dcopt == "n")
        {
            string pak;
            cout << endl;
            cout << "***  Payment Unsuccessful  ***" << endl;
            cout << endl;
            cout << "Press any key to continue..." << endl;
            cin >> pak;
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            payment_menu(customerid, password, trip);
        }
        else
        {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (dcopt != "Y" && dcopt != "y" && dcopt != "N" && dcopt != "n");

    closeDatabaseConnection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double discount(string a, string p, string trip)
{
    double discountRate = 0.8;
    double newPrice = 0.0;

    try
    {
        connectToDatabase();

        sql::PreparedStatement* stmt = globalCon->prepareStatement("SELECT * FROM customer WHERE customer_ID = ? AND customer_password = ?");
        stmt->setString(1, a);
        stmt->setString(2, p);

        sql::ResultSet* res = stmt->executeQuery();

        if (!res->next()) {
            cout << "Customer not found or password incorrect." << endl;
            return newPrice;
        }

        int count = 0;

        sql::PreparedStatement* pstmt = globalCon->prepareStatement("SELECT COUNT(*) FROM booking WHERE customer_ID = ?");
        pstmt->setString(1, a);
        sql::ResultSet* countResult = pstmt->executeQuery();

        if (countResult->next()) {
            count = countResult->getInt(1);
        }

        delete countResult;
        delete pstmt;

        stmt = globalCon->prepareStatement("SELECT * FROM trip WHERE trip_ID = ?");
        stmt->setString(1, trip);
        res = stmt->executeQuery();

        while (res->next())
        {
            string priceStr = res->getString("ticket_price");
            double price = stod(priceStr);

            if (count == 0) {
                cout << endl;
                cout << "First booking can get a discount of 20%" << endl;
                cout << endl;
                newPrice = price * discountRate;
                cout << "You get a 20% discount from RM " << price << ". You only need to Pay RM " << newPrice << endl;
                cout << endl;
            }
            else {
                cout << endl;
                cout << "Discount is not applied " << endl;
                newPrice = price;
            }
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e)
    {
        cout << "SQL Exception: " << e.what() << endl;
    }

    closeDatabaseConnection();

    return newPrice;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string randomnumbercr(int previousNumber)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int newNumber;
    do {
        newNumber = rand() % 900000 + 100000;
    } while (newNumber == previousNumber);

    return std::to_string(newNumber);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string randomnumberon(int previousNumber)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int newNumber;
    do {
        newNumber = rand() % 900000 + 100000;
    } while (newNumber == previousNumber);

    return "on" + std::to_string(newNumber);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void online_payment(string ac, string pw, string paymethod, string fl, string trip, string seat) {
    string bank, namebank, dc, dcopt, dop;
    double final_price;

    try {
        connectToDatabase();

        string query = "SELECT * FROM customer WHERE customer_ID = '" + ac + "' AND customer_password = '" + pw + "'";
        ResultSet* res = executeQuery(query);

        if (res && res->next()) {
            cout << "\t\t\t+================================+" << endl;
            cout << "\t\t\t|          BANK  NAME            |" << endl;
            cout << "\t\t\t+================================+" << endl;
            cout << "\t\t\t|                                |" << endl;
            cout << "\t\t\t|       1.  Maybank              |" << endl;
            cout << "\t\t\t|       2.  BSN                  |" << endl;
            cout << "\t\t\t|       3.  CIMB                 |" << endl;
            cout << "\t\t\t|       4.  Hong Leong           |" << endl;
            cout << "\t\t\t|       5.  Public Bank          |" << endl;
            cout << "\t\t\t|       6.  Ambank               |" << endl;
            cout << "\t\t\t|       7.  RHB                  |" << endl;
            cout << "\t\t\t|       8.  Bank Islam           |" << endl;
            cout << "\t\t\t|       9.  Back                 |" << endl;
            cout << "\t\t\t|                                |" << endl;
            cout << "\t\t\t+================================+" << endl;

            cout << endl;
            cout << "Please choose a bank for payment " << endl;
            cout << endl;
            do {
                cout << "Option  :  ";
                cin >> bank;

                if (bank == "1") {
                    namebank = "Maybank";
                    break;
                }
                else if (bank == "2") {
                    namebank = "BSN";
                    break;
                }
                else if (bank == "3") {
                    namebank = "CIMB";
                    break;
                }
                else if (bank == "4") {
                    namebank = "Hong Leong Bank";
                    break;
                }
                else if (bank == "5") {
                    namebank = "Public Bank";
                    break;
                }
                else if (bank == "6") {
                    namebank = "Ambank";
                    break;
                }
                else if (bank == "7") {
                    namebank = "RHB";
                    break;
                }
                else if (bank == "8") {
                    namebank = "Bank Islam";
                    break;
                }
                else if (bank == "9") {
                    system("cls");
                    payment_menu(ac, pw, trip);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (bank != "1" && bank != "2" && bank != "3" && bank != "4" && bank != "5" && bank != "6" && bank != "7" && bank != "8" && bank != "9");

            cout << "Are you confirm want to do this Payment" << endl;
            cout << "Enter Y for Yes, N for No" << endl;
            cout << endl;
            do {
                cout << endl;
                cout << "Option  :  ";
                cin >> dcopt;
                cout << endl;
                if (dcopt == "Y" || dcopt == "y") {
                    system("cls");
                    auto now = chrono::system_clock::now();
                    time_t currentTime = chrono::system_clock::to_time_t(now);

                    tm localTime;
                    localtime_s(&localTime, &currentTime);

                    int year = localTime.tm_year + 1900;
                    int month = localTime.tm_mon + 1;
                    int day = localTime.tm_mday;

                    string paymentdate, paymentid, bookingid, bookingdate;
                    int previousNumber = 0;

                    int min = 100000;
                    int max = 999999;

                    for (int i = 5; i <= 7; ++i) {
                        int num = rand() % (max - min + 1) + min;

                        bookingid = randomnumberon(previousNumber);

                        ostringstream oss;
                        oss << year << '-' << setfill('0') << setw(2) << month << '-' << setfill('0') << setw(2) << day;

                        paymentdate = oss.str();
                        paymentid = bookingid + "y" + to_string(year) + to_string(month) + to_string(day);
                        bookingdate = paymentdate;

                        cout << endl;
                        cout << endl;
                        cout << "\t\t\t                BOOKING DETAILS                    " << endl;
                        cout << "\t\t\t==================================================" << endl;
                        cout << "\t\t\t                                                  " << endl;
                        cout << "\t\t\t   Booking ID       :  " << bookingid << endl;
                        cout << "\t\t\t   Booking Date     :  " << bookingdate << endl;
                        cout << "\t\t\t   Payment Date     :  " << paymentdate << endl;
                        cout << "\t\t\t   Payment ID       :  " << paymentid << endl;
                        cout << "\t\t\t   Payment method   :  " << paymethod << endl;
                        cout << "\t\t\t   Customer         :  " << ac << endl;
                        cout << "\t\t\t   Seat Number      :  " << seat << endl;
                        cout << "\t\t\t                                                  " << endl;
                        cout << endl;

                        double discounted_price = discount(ac, pw, trip);
                        double final_price = discounted_price > 0 ? discounted_price : stod(res->getString("ticket_price"));
                        ostringstream inner_oss;
                        inner_oss << fixed << setprecision(2) << final_price;
                        string price_str = inner_oss.str();

                        string oo;
                        cout << endl;
                        cout << "Are you sure want to continue with Payment" << endl;
                        cout << "Enter Y for Yes, N for Cancel the Booking" << endl;
                        cout << endl;
                        do {
                            cout << "Option  :  ";
                            cin >> oo;

                            if (oo == "Y" || oo == "y") {
                                try {
                                    connectToDatabase();

                                    string insertBookingQuery = "INSERT INTO booking(booking_ID, customer_ID, trip_ID, booking_date, seat_number, final_price) VALUES ('" + bookingid + "','" + ac + "','" + trip + "','" + bookingdate + "','" + seat + "'," + to_string(final_price) + ")";
                                    executeInstruction(insertBookingQuery);

                                    string insertPaymentQuery = "INSERT INTO payment(payment_ID, booking_ID, payment_date, payment_method, bank_name, payment_amount) VALUES ('" + paymentid + "','" + bookingid + "','" + paymentdate + "','" + paymethod + "','" + namebank + "'," + to_string(final_price) + ")";
                                    executeInstruction(insertPaymentQuery);

                                    cout << "\t\t\t//  RM " << final_price << " deducted from " << namebank << endl;
                                    cout << endl;
                                    cout << endl;
                                    cout << "\t\t\t//  RM " << final_price << " deducted from " << namebank << endl;
                                    cout << endl;

                                    query = "SELECT * FROM trip WHERE trip_ID = '" + trip + "'";
                                    ResultSet* tripRes = executeQuery(query);
                                    while (tripRes && tripRes->next()) {
                                        string trip, busdetail, dest, start, end, dur, datestart, dateend, price;

                                        trip = tripRes->getString("trip_ID");
                                        busdetail = tripRes->getString("number_plate");
                                        dest = tripRes->getString("destination");
                                        start = tripRes->getString("start_time");
                                        end = tripRes->getString("end_time");
                                        dur = tripRes->getString("duration");
                                        datestart = tripRes->getString("start_date");
                                        dateend = tripRes->getString("end_date");
                                        price = tripRes->getString("ticket_price");

                                        string receipt = generatereceipt(trip, busdetail, dest, start, end, dur, datestart, dateend, price_str, seat, bookingid, bookingdate, paymentdate, paymentid, paymethod, ac);
                                        saveReceiptToFile(receipt, "receipt.txt");
                                        cout << endl;
                                        cout << "\tThank You for Booking" << endl;
                                        cout << endl;
                                       cout << receipt;
                                        cout << endl;
                                        cout << endl;
                                    }

                                    delete tripRes;

                                    cout << "Enter 1 to Continue with Another Booking, 2 to Exit" << endl;
                                    do {
                                        cout << endl;
                                        cout << "Option  :  ";
                                        cin >> dop;
                                        cout << endl;
                                        if (dop == "1") {
                                            this_thread::sleep_for(chrono::seconds(2));
                                            system("cls");
                                            booking(ac, pw);
                                        }
                                        else if (dop == "2") {
                                            this_thread::sleep_for(chrono::seconds(2));
                                            system("cls");
                                            cust_menu(ac, pw);
                                        }
                                        else {
                                            cout << "Incorrect" << endl;
                                            cout << endl;
                                        }
                                    } while (dop != "1" && dop != "2");

                                }
                                catch (const exception& e) {
                                    cerr << e.what() << '\n';
                                }
                            }
                            else if (oo == "N" || oo == "n") {
                                string hh;
                                cout << endl;
                                cout << "***  Payment Unsuccessfull  ***" << endl;
                                cout << "Press any key to continue..." << endl;
                                cin >> hh;
                                this_thread::sleep_for(chrono::seconds(2));
                                system("cls");
                                payment_menu(ac, pw, trip);
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (oo != "Y" && oo != "y" && oo != "N" && oo != "n");
                    }
                }
                else if (dcopt == "N" || dcopt == "n") {
                    string pak;
                    cout << endl;
                    cout << "***  Payment Unsuccessfull  ***" << endl;
                    cout << endl;
                    cout << "Press any key to continue..." << endl;
                    cin >> pak;
                    this_thread::sleep_for(chrono::seconds(2));
                    system("cls");
                    payment_menu(ac, pw, trip);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (dcopt != "Y" && dcopt != "y" && dcopt != "N" && dcopt != "n");
        }

        delete res;

    }
    catch (const exception& e) {
        cerr << e.what() << '\n';
    }
    
        closeDatabaseConnection();
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mybooking(string account, string password)
{
    string back, tripId, bsd, dt, st, en, dr, ds, de, p, bookingid, bookingdate, seats, paymentdate, paymentid, paymentmethod, choice, choice1, option, cc;
    string receipt;

    try {
        connectToDatabase(); // Establish connection using the custom function

        string query = "SELECT * FROM customer WHERE customer_ID = '" + account + "' AND customer_password = '" + password + "'";
        ResultSet* res = executeQuery(query);

        if (res->next()) { // If the customer exists

            string queryBooking = "SELECT * FROM booking WHERE customer_ID = '" + account + "'";
            ResultSet* resTrip = executeQuery(queryBooking);

            cout << endl;
            cout << endl;
            cout << "\t\tYour Booking" << endl;
            cout << endl;

            cout << "\t\t\t+--------------+-----------------+-----------------+" << endl;
            cout << "\t\t\t|   Booking ID |     Trip ID     |   Booking Date  |" << endl;
            cout << "\t\t\t+--------------+-----------------+-----------------+" << endl;

            bool bookingFound = false;
            while (resTrip->next()) {
                bookingFound = true;
                string booking = resTrip->getString("booking_ID");
                string trip = resTrip->getString("trip_ID");
                string bookingdate = resTrip->getString("booking_date");

                cout << "\t\t\t| " << setw(12) << booking << " | " << setw(14) << trip << "  | " << setw(13) << fixed << setprecision(2) << bookingdate << "   |" << endl;
            }

            if (!bookingFound) {
                system("cls");
                cout << endl;
                cout << endl;
                cout << endl;

                cout << "\t\t\t+---------------------------+" << endl;
                cout << "\t\t\t|      No booking found     |" << endl;
                cout << "\t\t\t+---------------------------+" << endl;
                cout << endl;
                cout << endl;

                do {
                    cout << "Enter 1 to Booking, 2 to Back" << endl;
                    cout << "Option  :  ";
                    cin >> back;

                    if (back == "1") {
                        system("cls");
                        booking(account, password);
                    }
                    else if (back == "2") {
                        system("cls");
                        cust_menu(account, password);
                    }
                    else {
                        cout << "Incorrect" << endl;
                        cout << endl;
                    }
                } while (back != "1" && back != "2");
            }

            cout << "\t\t\t+--------------+-----------------+-----------------+" << endl;
            cout << endl;
            cout << endl;

            int count = 0;
            do {
                cout << "Enter 1 to Cancel Booking, 2 to see Booking details, 3 to Back" << endl;
                cout << endl;
                cout << "Option  :  ";
                cin >> option;

                if (option == "1") {
                    do {
                        cout << "\nEnter Trip ID to cancel: ";
                        cin >> tripId;

                        try {
                            string queryCheckTrip = "SELECT COUNT(*) FROM booking WHERE trip_ID = '" + tripId + "' AND customer_ID = '" + account + "'";
                            ResultSet* resCheckTrip = executeQuery(queryCheckTrip);

                            if (resCheckTrip->next()) {
                                count = resCheckTrip->getInt(1);
                                if (count == 0) {
                                    cout << "Trip ID does not exist for the customer." << endl;
                                    cout << endl;

                                    do {
                                        cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                        cout << "Option  :  ";
                                        cin >> choice;
                                        if (choice == "1") {
                                            system("cls");
                                            mybooking(account, password);
                                        }
                                        else if (choice == "2") {
                                            system("cls");
                                            cust_menu(account, password);
                                        }
                                        else {
                                            cout << "Incorrect" << endl;
                                            cout << endl;
                                        }
                                    } while (choice != "1" && choice != "2");
                                }
                            }

                            delete resCheckTrip;
                        }
                        catch (exception& e) {
                            cerr << e.what() << endl;
                        }
                    } while (count == 0);

                    try {
                        string deletePaymentQuery = "DELETE FROM payment WHERE booking_ID = (SELECT booking_ID FROM booking WHERE trip_ID = '" + tripId + "' AND customer_ID = '" + account + "')";
                        executeInstruction(deletePaymentQuery);

                        string deleteBookingQuery = "DELETE FROM booking WHERE trip_ID = '" + tripId + "' AND customer_ID = '" + account + "'";
                        executeInstruction(deleteBookingQuery);

                        string updateTripQuery = "UPDATE trip SET seat_available = seat_available + 1 WHERE trip_ID = '" + tripId + "'";
                        executeInstruction(updateTripQuery);

                        cout << "\n";
                        cout << "\t\t---------------------------------------\n";
                        cout << "\t\t|     Booking Deleted Successfully     |" << endl;
                        cout << "\t\t---------------------------------------\n";
                        cout << "\n";
                        cout << endl;
                        cout << "Enter 1 to Back" << endl;
                        cout << endl;
                        do {
                            cout << "Option  :  ";
                            cin >> cc;

                            if (cc == "1") {
                                system("cls");
                                mybooking(account, password);
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (cc != "1");
                    }
                    catch (exception& e) {
                        cerr << "SQL Error: " << e.what() << endl;
                        cout << "\n";
                        cout << "Sorry Have trouble in Delete this Booking. Please try again.";
                        cout << "\n";
                    }
                }
                else if (option == "2") {
                    do {
                        cout << "\nEnter Trip ID to see details: ";
                        cin >> tripId;

                        try {
                            string queryCheckTrip = "SELECT COUNT(*) FROM booking WHERE trip_ID = '" + tripId + "' AND customer_ID = '" + account + "'";
                            ResultSet* resCheckTrip = executeQuery(queryCheckTrip);

                            if (resCheckTrip->next()) {
                                count = resCheckTrip->getInt(1);
                                if (count == 0) {
                                    cout << "Trip ID does not exist for the customer." << endl;
                                    cout << endl;

                                    do {
                                        cout << "Enter 1 to Retry, 2 to Exit" << endl;
                                        cout << "Option  :  ";
                                        cin >> choice;
                                        if (choice == "1") {
                                            system("cls");
                                            mybooking(account, password);
                                        }
                                        else if (choice == "2") {
                                            system("cls");
                                            cust_menu(account, password);
                                        }
                                        else {
                                            cout << "Incorrect" << endl;
                                            cout << endl;
                                        }
                                    } while (choice != "1" && choice != "2");
                                }
                            }

                            delete resCheckTrip;
                        }
                        catch (exception& e) {
                            cerr << e.what() << endl;
                        }
                    } while (count == 0);

                    cout << endl;

                    try {
                        string queryTripDetails = "SELECT booking_ID, trip_ID, booking_date FROM booking WHERE customer_ID = '" + account + "'";
                        ResultSet* resTrip = executeQuery(queryTripDetails);

                        if (resTrip->next()) {
                            tripId = resTrip->getString("trip_ID");

                            string queryBusDetails = "SELECT * FROM trip WHERE trip_ID = '" + tripId + "'";
                            ResultSet* resBus = executeQuery(queryBusDetails);

                            if (resBus->next()) {
                                bsd = resBus->getString("number_plate");
                                dt = resBus->getString("destination");
                                st = resBus->getString("start_time");
                                en = resBus->getString("end_time");
                                dr = resBus->getString("duration");
                                ds = resBus->getString("start_date");
                                de = resBus->getString("end_date");
                                p = resBus->getString("ticket_price");
                            }

                            delete resBus;

                            string queryBookingDetails = "SELECT * FROM booking WHERE customer_ID = '" + account + "'";
                            ResultSet* resBook = executeQuery(queryBookingDetails);

                            if (resBook->next()) {
                                bookingid = resBook->getString("booking_ID");
                                bookingdate = resBook->getString("booking_date");
                                seats = resBook->getString("seat_number");
                            }

                            delete resBook;

                            string queryPaymentDetails = "SELECT * FROM payment WHERE booking_ID = '" + bookingid + "'";
                            ResultSet* resPay = executeQuery(queryPaymentDetails);

                            if (resPay->next()) {
                                paymentid = resPay->getString("payment_ID");
                                paymentdate = resPay->getString("payment_date");
                                paymentmethod = resPay->getString("payment_method");
                            }

                            delete resPay;

                            system("cls");
                            cout << endl;
                           /* receipt =*/ generatereceipt(tripId, bsd, dt, st, en, dr, ds, de, p, seats, bookingid, bookingdate, paymentdate, paymentid, paymentmethod, account);
                            /*cout << receipt;*/
                            cout << endl;
                            cout << endl;

                            do {
                                cout << "Enter 1 to go Back" << endl;
                                cout << endl;
                                cout << "Option  :  ";
                                cin >> choice1;

                                if (choice1 == "1") {
                                    system("cls");
                                    mybooking(account, password);
                                }
                                else {
                                    cout << "Incorrect" << endl;
                                    cout << endl;
                                }
                            } while (choice1 != "1");
                        }

                    }
                    catch (exception& e) {
                        cerr << e.what() << endl;
                    }
                }
                else if (option == "3") {
                    system("cls");
                    cust_menu(account, password);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (option != "1" && option != "2" && option != "3");
        }
        else {
            cout << "Invalid customer_ID or cust_password" << endl;
        }

        closeDatabaseConnection(); // Close connection using the custom function
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void monthly_report(string akaun, string pass)
{
    string option, option1, month, year, back;
    string monthname;

    try {
        // Establish the connection to the database
        connectToDatabase();

        sql::PreparedStatement* pstmt = globalCon->prepareStatement("SELECT * FROM admin WHERE admin_ID = ? AND admin_password = ?");
        pstmt->setString(1, akaun);
        pstmt->setString(2, pass);
        sql::ResultSet* rs = pstmt->executeQuery();

        // Proceed only if the admin credentials are correct
        if (rs->next()) {
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "Enter 1 to Back, 2 to choose a year" << endl;
            cout << endl;
            do {
                cout << "Option  :  ";
                cin >> back;
                if (back == "1") {
                    system("cls");
                    report(akaun, pass);
                }
                else if (back == "2") {
                    cout << endl;
                    cout << "Enter a year   :  ";
                    cin >> year;
                    system("cls");
                    selected_monthly_report(akaun, pass, month, year, monthname);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (back != "1" && back != "2");
        }
        else {
            cout << "Invalid admin_ID or admin_password" << endl;
        }

        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << endl;
        closeDatabaseConnection();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void selected_monthly_report(string ac, string pw, string month, string year, string monthname) {
    string option;
    double avgSales = 0;
    double minSales = 0;
    double maxSales = 0;

    try {
        // Establish the connection to the database
        connectToDatabase();

        sql::PreparedStatement* pstmt = globalCon->prepareStatement("SELECT * FROM admin WHERE admin_ID = ? AND admin_password = ?");
        pstmt->setString(1, ac);
        pstmt->setString(2, pw);
        sql::ResultSet* rs = pstmt->executeQuery();

        cout << endl;
        cout << endl;
        cout << "\t\t\t+===========================+" << endl;
        cout << "\t\t\t|          MONTHS           |" << endl;
        cout << "\t\t\t+===========================+" << endl;
        cout << "\t\t\t|                           |" << endl;
        cout << "\t\t\t|      1.  January          |" << endl;
        cout << "\t\t\t|      2.  February         |" << endl;
        cout << "\t\t\t|      3.  March            |" << endl;
        cout << "\t\t\t|      4.  April            |" << endl;
        cout << "\t\t\t|      5.  May              |" << endl;
        cout << "\t\t\t|      6.  June             |" << endl;
        cout << "\t\t\t|      7.  July             |" << endl;
        cout << "\t\t\t|      8.  August           |" << endl;
        cout << "\t\t\t|      9.  September        |" << endl;
        cout << "\t\t\t|     10.  October          |" << endl;
        cout << "\t\t\t|     11.  November         |" << endl;
        cout << "\t\t\t|     12.  December         |" << endl;
        cout << "\t\t\t|     13.  Back             |" << endl;
        cout << "\t\t\t|                           |" << endl;
        cout << "\t\t\t+===========================+" << endl;
        cout << endl;
        cout << endl;
        cout << "Choose a month" << endl;
        cout << endl;

        do {
            cout << "Option  :  ";
            cin >> month;

            if (month == "1") {
                monthname = "January";
            }
            else if (month == "2") {
                monthname = "February";
            }
            else if (month == "3") {
                monthname = "March";
            }
            else if (month == "4") {
                monthname = "April";
            }
            else if (month == "5") {
                monthname = "May";
            }
            else if (month == "6") {
                monthname = "June";
            }
            else if (month == "7") {
                monthname = "July";
            }
            else if (month == "8") {
                monthname = "August";
            }
            else if (month == "9") {
                monthname = "September";
            }
            else if (month == "10") {
                monthname = "October";
            }
            else if (month == "11") {
                monthname = "November";
            }
            else if (month == "12") {
                monthname = "December";
            }
            else if (month == "13") {
                system("cls");
                monthly_report(ac, pw);
                return;
            }
            else {
                cout << "Invalid month" << endl;
                cout << endl;
                continue;
            }

            // Only valid months reach this point
            sql::PreparedStatement* stmt = globalCon->prepareStatement(
                "SELECT b.trip_ID, COUNT(*) AS Num_Bookings, SUM(b.final_price) AS Total_Sales "
                "FROM booking b "
                "JOIN trip t ON b.trip_ID = t.trip_ID "
                "WHERE YEAR(b.booking_date) = ? AND MONTH(b.booking_date) = ? "
                "GROUP BY b.trip_ID "
                "ORDER BY Num_Bookings DESC");
            stmt->setString(1, year);
            stmt->setString(2, month);
            sql::ResultSet* res = stmt->executeQuery();

            // Query for overall aggregates
            sql::PreparedStatement* aggStmt = globalCon->prepareStatement(
                "SELECT AVG(b.final_price) AS Avg_Sales, MIN(b.final_price) AS Min_Sales, MAX(b.final_price) AS Max_Sales, SUM(b.final_price) AS Total_Sales "
                "FROM booking b "
                "JOIN trip t ON b.trip_ID = t.trip_ID "
                "WHERE YEAR(b.booking_date) = ? AND MONTH(b.booking_date) = ?");
            aggStmt->setString(1, year);
            aggStmt->setString(2, month);
            sql::ResultSet* aggRes = aggStmt->executeQuery();

            if (aggRes->next()) {
                avgSales = aggRes->getDouble("Avg_Sales");
                minSales = aggRes->getDouble("Min_Sales");
                maxSales = aggRes->getDouble("Max_Sales");
            }

            if (res->rowsCount() == 0) {
                system("cls");
                cout << endl;
                cout << endl;
                cout << "\t\t\t Report for " << monthname << " " << year << endl;
                cout << endl;
                cout << "\t\t\t----------------------------------------" << endl;
                cout << "\t\t\t|      No bookings for this Month       |" << endl;
                cout << "\t\t\t----------------------------------------" << endl;
                cout << endl;
                cout << endl;
                cout << endl;
                cout << "Enter 1 to Back" << endl;
                do {
                    cout << "Option  :  ";
                    cin >> option;

                    if (option == "1") {
                        system("cls");
                        selected_monthly_report(ac, pw, month, year, monthname);
                    }
                    else {
                        cout << "Incorrect" << endl;
                        cout << endl;
                    }
                } while (option != "1");
            }
            else {
                system("cls");
                cout << endl;
                cout << "\t\t\t Report for " << monthname << " " << year << endl;
                cout << endl;
                cout << "\t\t\t+-----------+---------------+-----------------+" << endl;
                cout << "\t\t\t|  Trip ID  | Num Bookings  | Total Sales(RM) |" << endl;
                cout << "\t\t\t+-----------+---------------+-----------------+" << endl;
                double totalAmount = 0; // Reset totalAmount for the current month's calculation
                while (res->next()) {
                    string tripID = res->getString("trip_ID");
                    int numBookings = res->getInt("Num_Bookings");
                    double totalSales = res->getDouble("Total_Sales");
                    totalAmount += totalSales; // Accumulate total sales for this month
                    cout << "\t\t\t| " << setw(9) << tripID << " | " << setw(13) << numBookings << " | " << setw(14) << fixed << setprecision(2) << totalSales << "  |" << endl;
                }
                cout << "\t\t\t+-----------+---------------+-----------------+" << endl;
                cout << "\n\t\t\tThe Total Amount = " << totalAmount << " RM" << endl;
                cout << "\t\t\tAverage Sales = " << fixed << setprecision(2) << avgSales << " RM" << endl;
                cout << "\t\t\tMinimum Sale = " << fixed << setprecision(2) << minSales << " RM" << endl;
                cout << "\t\t\tMaximum Sale = " << fixed << setprecision(2) << maxSales << " RM" << endl << endl;

                do {
                    cout << "Enter 1 to Back" << endl;
                    cout << endl;
                    cout << "Option  :  ";
                    cin >> option;

                    if (option == "1") {
                        system("cls");
                        selected_monthly_report(ac, pw, month, year, monthname);
                    }
                    else {
                        cout << "Incorrect" << endl;
                        cout << endl;
                    }
                } while (option != "1");
            }

            delete res;
            delete stmt;
            delete aggRes;
            delete aggStmt;

        } while (true);
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << endl;
        closeDatabaseConnection();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void annual_report(string akaun, string pass) {
    string option, year, option1, back;

    // Connect to the database
    connectToDatabase();

    try {
        vector<string> params = { akaun, pass };
        string query = "SELECT * FROM admin WHERE admin_ID = '" + akaun + "' AND admin_password = '" + pass + "'";
        sql::ResultSet* rs = executeQuery(query);

        cout << endl << endl << endl << endl;
        cout << "Enter 1 to Back, 2 to choose a year" << endl;
        cout << endl;

        do {
            cout << "Option  :  ";
            cin >> back;
            if (back == "1") {
                system("cls");
                closeDatabaseConnection();
                report(akaun, pass);
                return; // Exit the function
            }
            else if (back == "2") {
                cout << endl;
                cout << "Enter a year   :  ";
                cin >> year;
                system("cls");
                closeDatabaseConnection();
                selected_annual_report(akaun, pass, year);
                return; // Exit the function
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (true); // Continue the loop until a valid option is selected

    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << endl;
    }

    closeDatabaseConnection(); // Ensure the connection is closed
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void selected_annual_report(string ac, string pw, string year) {
    string option;
    double totalAmount = 0;
    double avgSales = 0;
    double minSales = 0;
    double maxSales = 0;
    connectToDatabase(); // Ensure the connection is established

    // Validate admin credentials (optional step based on your original code)
    string query = "SELECT * FROM admin WHERE admin_ID = '" + ac + "' AND admin_password = '" + pw + "'";
    sql::ResultSet* rs = executeQuery(query);
    if (!rs || !rs->next()) {
        cout << "Invalid admin credentials." << endl;
        closeDatabaseConnection();
        return;
    }
    delete rs; // Clean up the ResultSet

    // Query for annual report
    string reportQuery = "SELECT b.trip_ID, COUNT(*) AS Num_Bookings, SUM(b.final_price) AS Total_Sales "
        "FROM booking b JOIN trip t ON b.trip_ID = t.trip_ID "
        "WHERE YEAR(b.booking_date) = '" + year + "' "
        "GROUP BY b.trip_ID ORDER BY Num_Bookings DESC";
    rs = executeQuery(reportQuery);

    // Query for overall aggregates
    string aggregateQuery = "SELECT AVG(b.final_price) AS Avg_Sales, MIN(b.final_price) AS Min_Sales, MAX(b.final_price) AS Max_Sales, SUM(b.final_price) AS Total_Sales "
        "FROM booking b JOIN trip t ON b.trip_ID = t.trip_ID "
        "WHERE YEAR(b.booking_date) = '" + year + "'";
    sql::ResultSet* aggregateRs = executeQuery(aggregateQuery);

    if (!aggregateRs || !aggregateRs->next()) {
        cout << endl << endl;
        cout << "\t\t\t----------------------------------------" << endl;
        cout << "\t\t\t|      No bookings for this Year       |" << endl;
        cout << "\t\t\t----------------------------------------" << endl;
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back" << endl;
            cout << "Option  :  ";
            cin >> option;

            if (option == "1") {
                system("cls");
                annual_report(ac, pw);
                break; // Exit the loop
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (true);
    }
    else {
        avgSales = aggregateRs->getDouble("Avg_Sales");
        minSales = aggregateRs->getDouble("Min_Sales");
        maxSales = aggregateRs->getDouble("Max_Sales");
        totalAmount = aggregateRs->getDouble("Total_Sales");
    }

    delete aggregateRs; // Clean up the ResultSet for aggregates

    if (!rs || rs->rowsCount() == 0) {
        cout << endl << endl;
        cout << "\t\t\t----------------------------------------" << endl;
        cout << "\t\t\t|      No bookings for this Year       |" << endl;
        cout << "\t\t\t----------------------------------------" << endl;
        cout << endl << endl;

        do {
            cout << "Enter 1 to Back" << endl;
            cout << "Option  :  ";
            cin >> option;

            if (option == "1") {
                system("cls");
                annual_report(ac, pw);
                break; // Exit the loop
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (true);
    }
    else {
        cout << endl;
        trip_list();
        cout << endl << endl;
        cout << "\t\t\t Report for year " << year << endl;
        cout << endl;
        cout << "\t\t\t+-----------+---------------+-----------------+" << endl;
        cout << "\t\t\t|  Trip ID  | Num Bookings  | Total Sales(RM) |" << endl;
        cout << "\t\t\t+-----------+---------------+-----------------+" << endl;

        while (rs->next()) {
            string tripID = rs->getString("trip_ID");
            int numBookings = rs->getInt("Num_Bookings");
            double totalSales = rs->getDouble("Total_Sales");
            cout << "\t\t\t| " << setw(9) << tripID << " | " << setw(13) << numBookings << " | " << setw(14) << fixed << setprecision(2) << totalSales << "  |" << endl;
        }
        cout << "\t\t\t+-----------+---------------+-----------------+" << endl;
        cout << "\n\t\t\tThe Total Amount = " << totalAmount << " RM" << endl;
        cout << "\t\t\tAverage Sales = " << fixed << setprecision(2) << avgSales << " RM" << endl;
        cout << "\t\t\tMinimum Sale = " << fixed << setprecision(2) << minSales << " RM" << endl;
        cout << "\t\t\tMaximum Sale = " << fixed << setprecision(2) << maxSales << " RM" << endl << endl;

        do {
            cout << "Enter 1 to Back" << endl;
            cout << "Option  :  ";
            cin >> option;

            if (option == "1") {
                system("cls");
                annual_report(ac, pw);
                break; // Exit the loop
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (true);
    }

    delete rs; // Clean up the ResultSet for main report
    closeDatabaseConnection(); // Ensure the connection is closed
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void date_report(string akaun, string pass) {
    string start_date, end_date, option;

    connectToDatabase(); 

    string query = "SELECT * FROM admin WHERE admin_ID = '" + akaun + "' AND admin_password = '" + pass + "'";
    sql::ResultSet* rs = executeQuery(query);
    if (!rs || !rs->next()) {
        cout << "Invalid admin credentials." << endl;
        closeDatabaseConnection();
        return;
    }
    delete rs; // Clean up the ResultSet

    cout << endl << endl << endl;

    cout << "Enter 1 to continue with Customize date, 2 to Back" << endl;
    cout << endl;
    do {
        cout << "Option  :  ";
        cin >> option;
        if (option == "1") {
            cout << endl << endl;

            cout << "Start Date(YYYY-MM-DD)  : ";

            bool validsDate = false;

            while (!validsDate) {
                cin >> start_date;
                if (isValidDate(start_date)) {
                    validsDate = true;
                }
                else {
                    cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                    cout << "Start Date (YYYY-MM-DD)  : ";
                    cin.clear(); // Clear any error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                }
            }

            cout << endl;
            cout << "End Date(YYYY-MM-DD)  : ";
            bool valideDate = false;

            while (!valideDate) {
                cin >> end_date;

                if (isValidDate(end_date)) {
                    valideDate = true;
                }
                else {
                    cerr << "\nThis is an Invalid Date, Please Enter a Valid One (YYYY-MM-DD)." << endl;
                    cout << "End Date (YYYY-MM-DD)  : ";
                    cin.clear(); // Clear any error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                }
            }


            selected_date_report(akaun, pass, start_date, end_date);
        }
        else if (option == "2") {
            system("cls");
            report(akaun, pass);
        }
        else {
            cout << "Incorrect" << endl;
            cout << endl;
        }
    } while (option != "1" && option != "2");

    closeDatabaseConnection(); // Ensure the connection is closed
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void selected_date_report(string ac, string pw, string start_date, string end_date) {
    string option;
    double totalAmount = 0;
    double avgSales = 0;
    double minSales = 0;
    double maxSales = 0;
    connectToDatabase();

    string query = "SELECT * FROM admin WHERE admin_ID = '" + ac + "' AND admin_password = '" + pw + "'";
    sql::ResultSet* rs = executeQuery(query);
    if (!rs || !rs->next()) {
        cout << "Invalid admin credentials." << endl;
        closeDatabaseConnection();
        return;
    }
    delete rs; // Clean up the ResultSet

    try {
        sql::PreparedStatement* stmt;
        sql::ResultSet* res;

        // Query for report details
        stmt = globalCon->prepareStatement(
            "SELECT b.trip_ID, COUNT(*) AS Num_Bookings, SUM(b.final_price) AS Total_Sales "
            "FROM booking b JOIN trip t ON b.trip_ID = t.trip_ID "
            "WHERE b.booking_date BETWEEN ? AND ? "
            "GROUP BY b.trip_ID ORDER BY Num_Bookings DESC");
        stmt->setString(1, start_date);
        stmt->setString(2, end_date);
        res = stmt->executeQuery();

        // Query for overall aggregates
        sql::PreparedStatement* aggStmt = globalCon->prepareStatement(
            "SELECT AVG(b.final_price) AS Avg_Sales, MIN(b.final_price) AS Min_Sales, MAX(b.final_price) AS Max_Sales, SUM(b.final_price) AS Total_Sales "
            "FROM booking b JOIN trip t ON b.trip_ID = t.trip_ID "
            "WHERE b.booking_date BETWEEN ? AND ?");
        aggStmt->setString(1, start_date);
        aggStmt->setString(2, end_date);
        sql::ResultSet* aggRes = aggStmt->executeQuery();

        if (aggRes->next()) {
            avgSales = aggRes->getDouble("Avg_Sales");
            minSales = aggRes->getDouble("Min_Sales");
            maxSales = aggRes->getDouble("Max_Sales");
            totalAmount = aggRes->getDouble("Total_Sales");
        }
        delete aggRes;
        delete aggStmt;

        if (res->rowsCount() == 0) {
            system("cls");
            cout << endl;
            cout << "\t\tReport for " << start_date << " to " << end_date << endl;
            cout << endl;
            cout << "\t\t---------------------------------------------------" << endl;
            cout << "\t\t|     No bookings for the specified date range     |" << endl;
            cout << "\t\t---------------------------------------------------" << endl;
            cout << endl;
            cout << "Enter 1 to Back" << endl;
            cout << endl;
            do {
                cout << "Option  :  ";
                cin >> option;
                if (option == "1") {
                    system("cls");
                    date_report(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (option != "1");

        }
        else {
            system("cls");
            cout << endl;
            trip_list();
            cout << endl;
            cout << endl;
            cout << "\t\tReport for " << start_date << " to " << end_date << endl;
            cout << endl;
            cout << "\t\t+-----------+---------------+-----------------+" << endl;
            cout << "\t\t|  Trip ID  | Num Bookings  | Total Sales(RM) |" << endl;
            cout << "\t\t+-----------+---------------+-----------------+" << endl;

            while (res->next()) {
                string tripID = res->getString("trip_ID");
                int numBookings = res->getInt("Num_Bookings");
                double totalSales = res->getDouble("Total_Sales");
                cout << "\t\t| " << setw(9) << tripID << " | " << setw(13) << numBookings << " | " << setw(14) << fixed << setprecision(2) << totalSales << "  |" << endl;
            }

            cout << "\t\t+-----------+---------------+-----------------+" << endl;
            cout << "\n\t\t\tThe Total Amount = " << totalAmount << " RM" << endl;
            cout << "\t\t\tAverage Sales = " << fixed << setprecision(2) << avgSales << " RM" << endl;
            cout << "\t\t\tMinimum Sale = " << fixed << setprecision(2) << minSales << " RM" << endl;
            cout << "\t\t\tMaximum Sale = " << fixed << setprecision(2) << maxSales << " RM" << endl << endl;

            cout << "Enter 1 to Back" << endl;
            cout << endl;
            do {
                cout << "Option  :  ";
                cin >> option;
                if (option == "1") {
                    system("cls");
                    date_report(ac, pw);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (option != "1");
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << endl;
    }

    closeDatabaseConnection();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SearchForTrip(string custid, string pass) {
    string tripid, option, poption, dc, cd, dcopt, cdopt, dop, back, paymentmethod, firstletter, choice, sold;
    char conf;

    connectToDatabase();

    try {
        sql::PreparedStatement* stmt = globalCon->prepareStatement("SELECT * FROM customer WHERE customer_ID = ? AND customer_password = ?");
        stmt->setString(1, custid);
        stmt->setString(2, pass);

        sql::ResultSet* res = stmt->executeQuery();

        cout << "\t\t\t+==================================+" << endl;
        cout << "\t\t\t|          BOOKING  MENU           |" << endl;
        cout << "\t\t\t+==================================+" << endl;
        cout << endl;
        cout << endl;

        connectToDatabase();

        string destination;
        cout << "Enter desired destination: ";
        cin.ignore();
        getline(cin, destination);
        cout << endl;
        transform(destination.begin(), destination.end(), destination.begin(), ::toupper);

       

        string query = "SELECT * FROM trip WHERE destination = '" + destination + "'";
        sql::ResultSet* tripsRes = executeQuery(query);

        vector<string> tripIDs;
        
                cout << "\nAvailable trips to " << destination << ":\n\n";
                cout << "Trip ID  | Number Plate  |  Start Time  |  End Time  |  Duration  |  Date Start  |  Date End  |  Price\n";
                cout << "------------------------------------------------------------------------------------------------------\n";
           
        bool tripsAvailable = false;

        while (tripsRes->next()) {
            tripsAvailable = true;
            string tripID = tripsRes->getString("trip_ID");
            tripIDs.push_back(tripID);

            string bd = tripsRes->getString("number_plate");
            string st = tripsRes->getString("start_time");
            string et = tripsRes->getString("end_time");
            string du = tripsRes->getString("duration");
            string ds = tripsRes->getString("start_date");
            string de = tripsRes->getString("end_date");
            string p = tripsRes->getString("ticket_price");

            cout << tripID << "  |  " << bd << "      |  " << st << "       |  " << et << "     |  " << du << "        |  " << ds << "  | " << de << " |  RM" << p << "\n";
        }

        if (!tripsAvailable) {
            cout << "\nNo available trips for the destination " << destination << "." << endl;
            cout << "\nEnter 2 to go back to the previous menu." << endl;
        }

        do {
            cout << "\nEnter 1 to Book, 2 to Back " << endl;
            cout << "Option  :  ";
            cin >> back;

            if (back == "1") {
                if (!tripsAvailable) {
                    cout << "\nNo trips available to book for the specified destination." << endl;
                    // continue;
                    do {
                        cout << "\n Do You Want to Try Again (Y/N) ? \n";
                        //char conf;
                        cin >> conf;
                        if (conf == 'Y' || conf == 'y')
                        {
                            system("cls");
                            SearchForTrip(custid, pass);
                        }
                        else if (conf == 'N' || conf == 'n')
                        {
                            system("cls");
                            cust_menu(custid, pass);
                        }
                        else
                        {
                            cout << "\n Invalid Input Please Enter(Y/N) \n";
                        }
                    } while (conf != 'Y' && conf != 'y' && conf != 'N' && conf != 'n');

                }
                string tripId;
                int count = 0;

                do {
                    cout << "\nEnter Trip ID to Book  : ";
                    cin >> tripId;

                    stmt = globalCon->prepareStatement("SELECT COUNT(*) FROM trip WHERE trip_ID = ?");
                    stmt->setString(1, tripId);

                    sql::ResultSet* countResult = stmt->executeQuery();

                    if (countResult->next()) {
                        count = countResult->getInt(1);
                        if (count == 0) {
                            cout << endl;
                            cout << "Trip ID does not exist." << endl;
                            cout << endl;
                        }
                    }

                    delete countResult; // Delete the ResultSet after using it

                } while (count == 0);

                stmt = globalCon->prepareStatement("SELECT seat_available FROM trip WHERE trip_ID = ?");
                stmt->setString(1, tripId);

                res = stmt->executeQuery();
                if (res->next()) {
                    int seatAvailable = res->getInt("seat_available");

                    if (seatAvailable == 0) {
                        cout << endl;
                        cout << "Trip Sold Out" << endl;
                        cout << endl;
                        cout << "Enter 1 to continue with another booking" << endl;
                        cout << endl;
                        do {
                            cout << "Option  :  ";
                            cin >> sold;
                            if (sold == "1") {
                                system("cls");
                                booking(custid, pass);
                            }
                            else {
                                cout << endl;
                                cout << "Incorrect" << endl;
                            }
                        } while (sold != "1");
                    }
                    else {

                        stmt = globalCon->prepareStatement("SELECT * FROM trip WHERE trip_ID = ?");
                        stmt->setString(1, tripId);

                        res = stmt->executeQuery();

                        while (res->next()) {
                            system("cls");
                            cout << endl;
                            cout << endl;
                            cout << "\t\t                      TRIP  DETAILS                      " << endl;
                            cout << "\t\t=========================================================" << endl;
                            cout << "\t\t                                                         " << endl;
                            cout << "\t\t   Trip ID         : " << res->getString("trip_ID") << endl;
                            cout << "\t\t   Destination     : " << res->getString("destination") << endl;
                            cout << "\t\t   Start Time      : " << res->getString("start_time") << endl;
                            cout << "\t\t   End Time        : " << res->getString("end_time") << endl;
                            cout << "\t\t   Duration        : " << res->getString("duration") << endl;
                            cout << "\t\t   Date Start      : " << res->getString("start_date") << endl;
                            cout << "\t\t   Date Start      : " << res->getString("end_date") << endl;
                            cout << "\t\t   Price           : RM" << res->getString("ticket_price") << endl;
                            cout << "\t\t                                                         " << endl;
                            cout << endl;
                        }

                        cout << "Are you sure you want to book this Trip? " << endl;
                        cout << "Enter Y for Yes, N for No, B for Exit" << endl;
                        cout << endl;
                        do {
                            cout << "Option  :  ";
                            cin >> option;

                            if (option == "Y" || option == "y") {
                                system("cls");
                                payment_menu(custid, pass, tripId);
                            }
                            else if (option == "N" || option == "n") {
                                cout << endl;
                                cout << "***  Booking Unsuccessful  ***" << endl;
                                cout << endl;
                                this_thread::sleep_for(chrono::seconds(2));
                                system("cls");
                                cust_menu(custid, pass);
                            }
                            else if (option == "B" || option == "b") {
                                this_thread::sleep_for(chrono::seconds(2));
                                system("cls");
                                cust_menu(custid, pass);
                            }
                            else {
                                cout << "Incorrect" << endl;
                                cout << endl;
                            }
                        } while (option != "Y" && option != "y" && option != "N" && option != "n" && option != "B" && option != "b");
                    }
                }

            }
            else if (back == "2") {
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                cust_menu(custid, pass);
            }
            else {
                cout << "Incorrect" << endl;
                cout << endl;
            }
        } while (back != "1" && back != "2");

        delete res;
        delete stmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawMonthlyBookingsChart(const std::string& ac, const std::string& pw, const std::string& year) {
    try {
        // Establish the connection to the database
        connectToDatabase();

        sql::PreparedStatement* pstmt = globalCon->prepareStatement("SELECT * FROM admin WHERE admin_ID = ? AND admin_password = ?");
        pstmt->setString(1, ac);
        pstmt->setString(2, pw);
        sql::ResultSet* rs = pstmt->executeQuery();

        if (!rs->next()) {
            std::cerr << "Invalid admin credentials." << std::endl;
            return;
        }

        std::vector<std::string> months = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };

        std::vector<int> bookings(12, 0);

        for (int month = 1; month <= 12; ++month) {
            sql::PreparedStatement* stmt = globalCon->prepareStatement(
                "SELECT COUNT(*) AS Num_Bookings "
                "FROM booking "
                "WHERE YEAR(booking_date) = ? AND MONTH(booking_date) = ?"
            );
            stmt->setString(1, year);
            stmt->setInt(2, month);

            sql::ResultSet* res = stmt->executeQuery();

            if (res->next()) {
                bookings[month - 1] = res->getInt("Num_Bookings");
            }

            delete res;
            delete stmt;
        }

        std::cout << "\nMonthly Bookings for " << year << "\n\n";

        for (size_t i = 0; i < months.size(); ++i) {
            std::cout << std::setw(10) << months[i] << " | ";

            for (int j = 0; j < bookings[i]; ++j) {
                std::cout << "*";
            }

            std::cout << " (" << bookings[i] << " bookings)\n";
        }

        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what()
            << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        closeDatabaseConnection();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void chart_report(string akaun, string pass)
{
    string option, option1, month, year, back;
    string monthname;

    try {
        connectToDatabase();

        sql::PreparedStatement* pstmt = globalCon->prepareStatement("SELECT * FROM admin WHERE admin_ID = ? AND admin_password = ?");
        pstmt->setString(1, akaun);
        pstmt->setString(2, pass);
        sql::ResultSet* rs = pstmt->executeQuery();

        // Proceed only if the admin credentials are correct
        if (rs->next()) {
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "Enter 1 to Back, 2 to choose a year" << endl;
            cout << endl;
            do {
                cout << "Option  :  ";
                cin >> back;
                if (back == "1") {
                    system("cls");
                    report(akaun, pass);
                }
                else if (back == "2") {
                    cout << endl;
                    cout << "Enter a year   :  ";
                    cin >> year;
                    system("cls");
                    drawMonthlyBookingsChart(akaun, pass,  year);
                    cout << "\n------------------------------------------------------\n";
                    drawDestinationBookingsChart(akaun, pass, year);
                }
                else {
                    cout << "Incorrect" << endl;
                    cout << endl;
                }
            } while (back != "1" && back != "2");
        }
        else {
            cout << "Invalid admin_ID or admin_password" << endl;
        }

        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Exception: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << endl;
        closeDatabaseConnection();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawDestinationBookingsChart(const string& ac, const string& pw, const string& year) {
    try {
       
        connectToDatabase();

        sql::PreparedStatement* pstmt = globalCon->prepareStatement("SELECT * FROM admin WHERE admin_ID = ? AND admin_password = ?");
        pstmt->setString(1, ac);
        pstmt->setString(2, pw);
        sql::ResultSet* rs = pstmt->executeQuery();

        if (!rs->next()) {
            std::cerr << "Invalid admin credentials." << std::endl;
            delete rs;
            delete pstmt;
            closeDatabaseConnection();
            return;
        }

        // Prepare the query to get bookings per destination
        sql::PreparedStatement* stmt = globalCon->prepareStatement(
            "SELECT t.destination, COUNT(*) AS Num_Bookings "
            "FROM booking b "
            "JOIN trip t ON b.trip_ID = t.trip_ID "
            "WHERE YEAR(b.booking_date) = ? "
            "GROUP BY t.destination"
        );
        stmt->setString(1, year);
        sql::ResultSet* res = stmt->executeQuery();

        std::map<std::string, int> destinationBookings;
        while (res->next()) {
            std::string destination = res->getString("destination");
            int numBookings = res->getInt("Num_Bookings");
            destinationBookings[destination] = numBookings;
        }

        cout << "\nBookings by Destination for " << year << "\n\n";

        for (const auto& entry : destinationBookings) {
            cout << std::setw(20) << entry.first << " | ";

            for (int j = 0; j < entry.second; ++j) {
                cout << "*";
            }

            std::cout << " (" << entry.second << " bookings)\n";
        }
        string op; 
        do {
            cout << "\nEnter 1 to Back \n";
            cout << "\n Option : ";
            cin >> op; 
            if (op == "1")
            {
                system("cls");
                report(ac, pw);
            }
            else
            {
                cout << "\n Invalid Input \n";
            }
        } while (op != "1");
        delete res;
        delete stmt;
        delete rs;
        delete pstmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what()
            << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        closeDatabaseConnection();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void saveReceiptToFile(const string& receipt, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << receipt;
        outFile.close();
        cout << "Receipt saved to " << filename << endl;
    }
    else {
        cerr << "Error opening file: " << filename << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////