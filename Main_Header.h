#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include<iostream>
#include<string>
#include<limits> // we had to include this for issue which forced user sometimes to press "Enter" twice before going to next menu
#include "User.h"
#include "Admin.h"
#include "Laptop.h"
#include "Cart.h"
#include "File_Handling.h"

#define MAX_LAPTOPS 100

using namespace std;


//================================//
// Function for clearing console  //
//================================//
inline void clearScreen() 
{
    system("cls");
}

//======================================================//
// Function for pausing screen before cleaning console  //
//======================================================//
inline void pauseScreen() 
{
    cout << "\n\n   Press Enter to continue...";
    cin.get();
}

// Global shared inventory
extern Laptop inventory[MAX_LAPTOPS];
extern int inventorySize;

//==================================================================================//
// Login process, both Login and Password are "admin" by default, can't be changed  //
//==================================================================================//
inline bool adminLogin() 
{
    clearScreen();
    string login, password;
    cout << "\n\n   ========== Admin Login ==========\n\n";
    cout << "   Enter login (by default: admin): ";
    getline(cin, login);
    cout << "   Enter password (by default: admin): ";
    getline(cin, password);
    return (login == "admin" && password == "admin");
}

//=============//
// Admin Panel //
//=============//
inline void showAdminMenu() 
{
    Admin admin("admin", inventory, inventorySize);
    admin.showMenu();
}

//==============//
// Customer Menu//
//==============//
inline void showCustomerMenu() 
{
    string name;

    clearScreen();

    cout << "\n\n   ========== Customer Login ==========\n\n"; //Settingg Customer Name
    cout << "   Enter your name: ";
    getline(cin, name);

    Customer customer(name);
    customer.setInventory(inventory, inventorySize);
    customer.showMenu();
}

//=================//
// Opening Screen  //
//=================//
inline void showOpeningScreen() 
{
    clearScreen();
    cout << "\n\n\n";
    cout << "   ================================================\n\n\n";
    cout << "         Welcome to the Premium Laptop Store!       \n\n";
    cout << "        Your Trusted Hub for Quality Laptops       \n\n\n";
    cout << "   ================================================\n";
    pauseScreen();
    clearScreen();
}

//======================================================//
// Function to choose the specific Role: Admin/Customer //
//======================================================//
inline void showRoleSelector() 
{
    int roleChoice;

    do 
    {
        clearScreen();
        cout << "\n\n   ============= Select User Role =============\n\n";
        cout << "      1. Admin\n";
        cout << "      2. Customer\n";
        cout << "      3. Exit\n";
        cout << "\n   ============================================\n";
        cout << "   Enter your choice: ";
        cin >> roleChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // fix of issue where user should press "Enter" twice before moving to next menu

        switch (roleChoice) 
        {
        case 1:
            if (adminLogin()) 
            {
                showAdminMenu();
            }

            else 
            {
                cout << "\n   Login failed. Returning to role selection...\n";
                pauseScreen();
            }
            break;

        case 2:
            showCustomerMenu();
            break;

        case 3:
            clearScreen();
            cout << "   =====================================================\n\n\n";
            cout << "       Thank you for visiting Laptop Store. Goodbye!\n\n\n";
            cout << "   =====================================================\n";
            break;
        default:
            cout << "\n   Invalid choice."; 
            
            pauseScreen();
        }

    } 

    while (roleChoice != 3);
}

#endif // MAIN_HEADER_H


