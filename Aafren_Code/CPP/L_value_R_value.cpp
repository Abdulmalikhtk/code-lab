/*
An lvalue is a variable with a permanent memory address. An rvalue is a temporary value that is about to disappear.
 We use rvalue references (&&) to move data instead of copying it, which makes our apps run much faster.
*/

#include <iostream>
#include <string>
#include <utility> // Required for std::move

int main() {
    // =============================================================
    // 1. INITIAL SETUP (Lvalues holding our values)
    // =============================================================
    std::string name1 = "kiccha";
    std::string name2 = "hema";
    int age1 = 31;
    int age2 = 45;

    // =============================================================
    // 2. REFERENCES SETUP
    // =============================================================
    // Lvalue References (&) -> Direct aliases/nicknames to existing variables
    std::string& nameRef = name1;
    int& ageRef = age1;

    // Rvalue References (&&) -> Extend the life of raw, temporary literals
    std::string&& tempName = "hema"; // Binds directly to temporary text literal
    int&& tempAge = 45;              // Binds directly to temporary number literal


    // =============================================================
    // PRINTING: BEFORE ANY CHANGES OR MOVES
    // =============================================================
    std::cout << "================= BEFORE CHANGES =================" << "\n";
    std::cout << "name1 original variable : " << name1 << "\n";
    std::cout << "nameRef (lvalue reference): " << nameRef << "\n";
    std::cout << "tempName (rvalue reference): " << tempName << "\n";
    std::cout << "--------------------------------------------------" << "\n";
    std::cout << "age1 original variable  : " << age1 << "\n";
    std::cout << "ageRef (lvalue reference) : " << ageRef << "\n";
    std::cout << "tempAge (rvalue reference) : " << tempAge << "\n\n";


    // =============================================================
    // 3. THE EXPERIMENTS (Modifying reference & Moving)
    // =============================================================
    
    // Experiment A: Modifying through an lvalue reference
    nameRef = "kiccha kicchu"; // This updates name1 because nameRef is its alias.
    ageRef = 32;               // This updates age1 because ageRef is its alias.

    // Experiment B: Resource stealing via std::move
    // We convert 'name2' into an rvalue and pass it to a new string variable.
    std::string stolenName = std::move(name2);


    // =============================================================
    // PRINTING: AFTER CHANGES AND MOVES
    // =============================================================
    std::cout << "================= AFTER CHANGES =================" << "\n";
    std::cout << "[Exp A] Modified nameRef. name1 is now       : " << name1 << "\n";
    std::cout << "[Exp A] Modified ageRef. age1 is now         : " << age1 << "\n";
    std::cout << "--------------------------------------------------" << "\n";
    
    // Look closely at what happened to name2!
    std::cout << "[Exp B] original name2 box after std::move   : " << name2 << " (Stripped Empty!)\n";
    std::cout << "[Exp B] new stolenName box after std::move   : " << stolenName << "\n";
    
    return 0;
}




/*

================= BEFORE CHANGES =================
name1 original variable : kiccha
nameRef (lvalue reference): kiccha
tempName (rvalue reference): hema
--------------------------------------------------
age1 original variable  : 31
ageRef (lvalue reference) : 31
tempAge (rvalue reference) : 45

================= AFTER CHANGES =================
[Exp A] Modified nameRef. name1 is now       : kiccha
[Exp A] Modified ageRef. age1 is now         : 32
--------------------------------------------------
[Exp B] original name2 box after std::move   :  (Stripped Empty!)
[Exp B] new stolenName box after std::move   : hema


*/



/*
1. The Simple Meanings
• lvalue: The Lunch Box itself. It has a physical place on your table. You can touch it, open it, and change what's inside.
	• Example: A variable named box = "kiccha".
• rvalue: The Food inside the box, or a loose piece of food not in any box yet.
	• Example: The raw text "hema" or the raw number 31.
2. The Simple References (Why and Where)
lvalue Reference (&) = Sharing the Box
• What it is: You give your friend a straw to drink from your lunch box.
• Why we need it: If your friend drinks, the juice inside your box goes down. You are sharing the exact same box.
• Where we use it: When two parts of your program need to work on the same variable without making a copy.
rvalue Reference (&&) = Stealing the Food
• What it is: Someone is about to throw a perfectly good hamburger into the trash can (a temporary value that is about to disappear). Instead of letting it go to waste, you steal the hamburger and put it in your own box.
• Why we need it: It saves money and time. In programming, copying data takes a lot of computer power. Moving (stealing) data takes zero effort.
• Where we use it: When loading heavy data (like a profile picture or a long list of user names like "kiccha", "hema", 31). Instead of duplicating the data, the computer just slides it over.

*/