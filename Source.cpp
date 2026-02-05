//===============================//
//       OOP Project             //
//  E-commerce Shopping Cart     //
//    by: CyberBober Team        //
//===============================//

#include "Main_Header.h"

// Global shared inventory
Laptop inventory[MAX_LAPTOPS];
int inventorySize = 0;


//===============//
// Main Function //
//===============//

int main() 
{
    showOpeningScreen(); // Opening Screen

    showRoleSelector();  // Role Selection Screen

    return 0;
}
