#ifndef CART_H
#define CART_H

#include "Laptop.h"
#include<iostream>
#include<limits> // we had to include this for issue which forced user sometimes to press "Enter" twice before going to next menu

#define MAX_CART_ITEMS 100

using namespace std;

//=======================//
//  Defining Cart Class  //
//=======================//
class Cart 
{

private:
    Laptop cartItems[MAX_CART_ITEMS];
    int cartSize = 0;

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
        cin.get();
    }


    //=================================//
    // Function to view items in Cart  //
    //=================================//
    void viewCart() 
    {
        clearScreen();
        cout << "\n\n   ========== Your Cart ==========\n\n";

        if (cartSize == 0) // in case if Cart is empty
        {
            cout << "   Your cart is empty.\n";
        }

        else 
        {
            double total = 0;

            for (int i = 0; i < cartSize; ++i) {
                cout << "   " << (i + 1) << ". ";
                cartItems[i].display();
                total += cartItems[i].price;
            }
            cout << "\n   Total Price: $" << total << "\n"; // displaying overall price of items in Cart
        }

        pauseScreen();
    }


public:

    //===============================//
    // Function to add item to Cart  //
    //===============================//
    void addLaptop(const Laptop& laptop) 
    {
        if (cartSize >= MAX_CART_ITEMS)  // if Cart is full
        {
            cout << "\n   Cart is full. Cannot add more items."; 
            pauseScreen();
            return;
        }
        cartItems[cartSize++] = laptop;
    }

    //==================================//
    // Function to remove item to Cart  //
    //==================================//
    void removeLaptop() 
    {
        clearScreen();

        if (cartSize == 0) // if Cart is emptry
        {
            cout << "\n   Your cart is empty, no items to remove.";
            pauseScreen();
            return;
        }

        cout << "\n   ========== Remove Item from Cart ==========\n\n";

        for (int i = 0; i < cartSize; ++i) 
        {
            cout << "   " << (i + 1) << ". ";
            cartItems[i].display();
        }

        cout << "\n   Enter the number of the laptop to remove (0 to cancel): ";
        int index;
        cin >> index;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // fix of issue where user should press "Enter" twice before moving to next menu

        if (index == 0) // for cancelling
        {
            cout << "\n   Cancelled.";
        }

        else if (index >= 1 && index <= cartSize) 
        {
            for (int i = index - 1; i < cartSize - 1; ++i) 
            {
                cartItems[i] = cartItems[i + 1];
            }
            --cartSize;
            cout << "\n   Laptop removed from the cart!";
        }

        else 
        {
            cout << "\n   Invalid selection!";
        }

        pauseScreen();
    }

    //========================//
    // Function for Checkout  //
    //========================//
    void checkout() 
    {
        clearScreen();

        if (cartSize == 0) // if Cart is empty
        {
            cout << "\n   Your cart is empty. Cannot checkout.\n";
            pauseScreen();
            return;
        }

        double total = 0;

        for (int i = 0; i < cartSize; ++i) 
        {
            total += cartItems[i].price;
        }

        cout << "\n   ========== Checkout ==========\n\n";
        cout << "   Your total amount is: $" << total << "\n\n";
        cout << "   Thank you for your purchase!\n";

        cartSize = 0; // Clear the cart
        pauseScreen();
    }


    //=========================================//
    // DEfining function for Main Menu of Cart //
    //=========================================//
    void showCartMenu() 
    {
        int choice;
        do 
        {
            clearScreen();
            cout << "\n   ========== Cart Menu ==========\n\n";
            cout << "      1. View Cart\n";
            cout << "      2. Remove Laptop from Cart\n";
            cout << "      3. Checkout\n";
            cout << "      4. Return to Customer Menu\n";
            cout << "\n   ===================================\n";
            cout << "   Enter your choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // fix of issue where user should press "Enter" twice before moving to next menu

            switch (choice) 
            {
            case 1: viewCart(); 
                break;
            case 2: removeLaptop(); 
                break;
            case 3: checkout(); 
                break;
            case 4: cout << "\n   Returning to customer menu..."; 
                pauseScreen(); 
                break;
            default: cout << "\n   Invalid choice!"; 
                pauseScreen();
            }

        } 
        while (choice != 4);
    }
};

#endif // CART_H

