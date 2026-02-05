#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Laptop.h"
#include "File_Handling.h"
#include<iostream>
#include<limits> // we had to include this for issue which forced user sometimes to press "Enter" twice before going to next menu

#define MAX_LAPTOPS 100  // Maximum number of laptops allowed in inventory 

using namespace std;


//========================//
//  Defining Admin Class  //
//========================//

class Admin : public User 
{

private:
    Laptop* inventory;
    int& inventorySize;


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
        clearScreen();
        cout << "\n\n   ========= Laptop Inventory =========\n\n";

        if (inventorySize == 0) 
        {
            cout << "   No laptops available.\n";
        }

        else 
        {
            for (int i = 0; i < inventorySize; ++i)
                inventory[i].display(i);
        }
        pauseScreen();
    }


    //============================//
    // Function to add new laptop //
    //============================//
    void addLaptop() 
    {
        clearScreen();

        if (inventorySize >= MAX_LAPTOPS) 
        {
            cout << "\n   Inventory full. Cannot add more laptops."; // if inventory is full
            pauseScreen();
            return;
        }

        string name, brand;
        double price;

        cout << "\n\n   ========= Add New Laptop =========\n\n";
        cin.ignore();
        cout << "   Enter laptop name: ";
        getline(cin, name);
        cout << "   Enter brand: ";
        getline(cin, brand);
        cout << "   Enter price: $";
        cin >> price;

        inventory[inventorySize++] = Laptop(name, brand, price);
        cout << "\n   Laptop added successfully!";
        pauseScreen();
    }


    //=================================================//
    // Function to update existing laptop in inventory //
    //=================================================//
    void updateLaptop() 
    {
        clearScreen();

        viewAllLaptops();

        if (inventorySize == 0) return;

        int index;
        cout << "\n   Enter laptop number to update: ";
        cin >> index;

        if (index < 1 || index > inventorySize)  // if invalid number is entered
        {
            cout << "   Invalid laptop number.\n";
            pauseScreen();
            return;
        }

        cin.ignore();
        string name, brand;
        double price;

        cout << "\n   Updating Laptop " << index << ":\n";
        cout << "   New name: ";
        getline(cin, name);
        cout << "   New brand: ";
        getline(cin, brand);
        cout << "   New price: $";
        cin >> price;

        inventory[index - 1] = Laptop(name, brand, price); // addinng updated laptop to inventory
        cout << "\n   Laptop updated successfully!";
        pauseScreen();
    }


    //==========================================//
    // Function to delete laptop from inventory //
    //==========================================//
    void deleteLaptop() 
    {
        clearScreen();

        viewAllLaptops();

        if (inventorySize == 0) 
            return;

        int index;
        cout << "\n   Enter laptop number to delete (0 to return): ";
        cin >> index;

        if (index == 0)
            return;

        if (index < 1 || index > inventorySize) // if invalid number is entered
        {
            cout << "   Invalid laptop number.\n";
            pauseScreen();
            return;
        }

        for (int i = index - 1; i < inventorySize - 1; ++i) 
        {
            inventory[i] = inventory[i + 1];
        }

        --inventorySize;
        cout << "\n   Laptop deleted successfully!";

        pauseScreen();
    }


    //====================================//
    // Function to save data to .txt file //
    //====================================//
    void saveToFile() 
    {
        clearScreen();

        string filename = "laptops.txt";

        //===============================//
        // Saving data to specified file //
        //===============================//
        try 
        {
            saveLaptopsToFile(inventory, inventorySize, filename);
            cout << "\n   Inventory saved to " << filename << "\n";
        }


        //=========================================================//
        // If any kind of errors occure while saving data to file  //
        //=========================================================//
        catch (...) 
        {
            cout << "\n   Failed to save inventory.";
        }

        pauseScreen();
    }

    //======================================//
    // Function to load data from .txt file //
    //======================================//
    void loadFromFile() 
    {
        clearScreen();

        string filename = "laptops.txt";

        //==================================//
        // Loading data from specified file //
        //==================================//
        try 
        {
            inventorySize = loadLaptopsFromFile(inventory, filename);
            cout << "\n   Inventory loaded from " << filename << "\n";
        }

        //============================================================//
        // If any kind of errors occure while loading data from file  //
        //============================================================//
        catch (...) 
        {
            cout << "\n   Failed to load inventory.";
        }
        pauseScreen();
    }


public:

    //=======================================================//
    // Defining parametrized constructor which receives data //
    //=======================================================//

    Admin(const string& name, Laptop* sharedInventory, int& sharedSize)
        : User(name), inventory(sharedInventory), inventorySize(sharedSize) {}


    //================================================//
    // DEfining function for Main Menu of Admin panel //
    //================================================//
    void showMenu() override 
    {
        int choice;

        do 
        {
            clearScreen();

            cout << "\n\n   ========== Admin Panel ==========\n\n";
            cout << "      1. View All Laptops\n";
            cout << "      2. Add New Laptop\n";
            cout << "      3. Update Existing Laptop\n";
            cout << "      4. Delete Laptop\n";
            cout << "      5. Save Inventory to File\n";
            cout << "      6. Load Inventory from File\n";
            cout << "      7. Logout\n";
            cout << "\n   =================================\n";
            cout << "   Enter your choice: ";
            cin >> choice;

            switch (choice) 
            {
            case 1: viewAllLaptops(); 
                break;
            case 2: addLaptop(); 
                break;
            case 3: updateLaptop(); 
                break;
            case 4: deleteLaptop(); 
                break;
            case 5: saveToFile(); 
                break;
            case 6: loadFromFile(); 
                break;
            case 7: cout << "\n   Logging out...\n"; 
                break;
            default: cout << "\n   Invalid choice!"; 
                
                pauseScreen();
            }

        } while (choice != 7);
    }
};

#endif // ADMIN_H
