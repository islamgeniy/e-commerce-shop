#ifndef USER_H
#define USER_H

#include "Laptop.h"
#include "Cart.h"
#include<iostream>
#include<string>
#include<limits> // we had to include this for issue which forced user sometimes to press "Enter" twice before going to next menu

#define MAX_LAPTOPS 100

using namespace std;

//=======================//
//  Defining User Class  //
//=======================//
class User 
{

protected:
    string username;

public:

    //===================================//
    // Defining Parametrized constructor //
    //===================================//
    User(const string& name) : username(name) {}
    virtual void showMenu() = 0;
    virtual ~User() {}
};

// ====================================================//
// Defining Customer Class, inherited from User Class  //
//=====================================================//
class Customer : public User 
{

private:
    Cart cart;
    Laptop* inventory;
    int inventorySize;

    //================================//
    // Function for clearing console  //
    //================================//
    void clearScreen() 
    {
        system("cls");
    }

    //======================================================//
    // Function for pausing screen before cleaning console  //
    //======================================================//
    void pauseScreen() 
    {
        cout << "\n\n   Press Enter to continue...";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // fix of issue where user should press "Enter" twice before moving to next menu
        cin.get();
    }

    //==============================================//
    // Function to view a list of available laptops //
    //==============================================//
    void viewAllLaptops() 
    {
        while (true) 
        {
            clearScreen();

            if (inventorySize == 0) // if admin didn't add items to list
            {
                cout << "\n   No laptops available.\n";
                pauseScreen();
                return;
            }

            cout << "\n   ========= Available Laptops =========\n\n";

            for (int i = 0; i < inventorySize; ++i) 
            {
                cout << "   " << (i + 1) << ". ";
                inventory[i].display();
            }

            cout << "\n   Enter the number of the laptop to add to cart (0 to return): ";
            int choice;
            cin >> choice;

            if (choice == 0) 
                return;

            if (choice >= 1 && choice <= inventorySize) 
            {
                cart.addLaptop(inventory[choice - 1]);
                cout << "\n   Laptop added to cart.";

                pauseScreen();
            }
            else 
            {
                cout << "\n   Invalid selection.";

                pauseScreen();
            }
        }
    }

    //========================================//
    // Function to search Laptops from a list //
    //========================================//
    void searchLaptop() 
    {
        while (true) 
        {
            clearScreen();

            cout << "\n   ========= Search Laptops =========\n\n";
            cout << "   Enter laptop name or brand to search (or 0 to cancel): ";
            string keyword;
            cin >> keyword;

            if (keyword == "0") // for cancelling
                return;

            Laptop results[MAX_LAPTOPS];
            int resultCount = 0;

            for (int i = 0; i < inventorySize; ++i) 
            {
                if (inventory[i].name.find(keyword) != string::npos || inventory[i].brand.find(keyword) != string::npos) 
                {
                    results[resultCount++] = inventory[i];
                }
            }

            if (resultCount == 0) 
            {
                cout << "\n   No laptops found for \"" << keyword << "\".";

                pauseScreen();

                continue;
            }

            while (true) 
            {
                clearScreen();

                cout << "\n   Search results for \"" << keyword << "\":\n\n";
                for (int i = 0; i < resultCount; ++i) 
                {
                    cout << "   " << (i + 1) << ". ";
                    results[i].display();
                }

                cout << "\n   Enter the number of the laptop to add to cart (0 to return): ";
                int choice;
                cin >> choice;

                if (choice == 0) // for cancelling
                    return;

                if (choice >= 1 && choice <= resultCount) 
                {
                    cart.addLaptop(results[choice - 1]);
                    cout << "\n   Laptop added to cart.";
                }

                else 
                {
                    cout << "\n   Invalid selection.";
                }

                pauseScreen();

                return;
            }
        }
    }

public:
    Customer(const string& name) : User(name), inventory(nullptr), inventorySize(0) {}

    void showMenu() override 
    {
        int choice;
        do 
        {
            clearScreen();
            cout << "\n   ========== Welcome, " << username << " ==========\n\n";
            cout << "      1. Show All Laptops\n";
            cout << "      2. Search Laptop by Name\n";
            cout << "      3. Cart\n";
            cout << "      4. Checkout\n";
            cout << "      5. Logout\n";
            cout << "\n   ===================================\n";
            cout << "   Enter your choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) 
            {
            case 1: viewAllLaptops(); break;
            case 2: searchLaptop(); break;
            case 3: cart.showCartMenu(); break;
            case 4: cart.checkout(); break;
            case 5: cout << "\n   Logging out..."; break;
            default: cout << "\n   Invalid choice!"; pauseScreen();
            }

        } while (choice != 5);
    }

    void setInventory(Laptop* sharedInventory, int sharedSize) 
    {
        inventory = sharedInventory;
        inventorySize = sharedSize;
    }
};

#endif // USER_H




