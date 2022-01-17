/*
 * Author: Suki Sahota
 */
#include "Player.h"

using namespace std;

void initializeGame(Player *user, vector<int> &property_prices) {
    user->setGrowth(2); // 2% initial growth rate
    user->initializeProperty(property_prices);

    srand(time(0)); // Seed random variable
}

void printHorizontalLine() {
    cout << "_____________________________"
         << "_____________________________";
}

void printInstructions(Player *user) {
    cout << endl;
    printHorizontalLine();
    cout << endl;
    printHorizontalLine();
    cout << endl;
    printHorizontalLine();
    cout << endl;

    cout << "\nOk " << user->getName() << ", the year is " << Player::THIS_YEAR
         << ". Each round of this game represents\none year, and the game ends "
         << "when you retire at the end of " << Player::END_YEAR << ".\nThe "
         << "rules are simple. Each round you will be afforded the\nopportunity"
         << " to buy and sell Real Estate Properties. At the end\nof the game, "
         << "we liquidate your assets and calculate your net worth.\nThe higher"
         << " your 'score' at the end, the better judgements you made,\nhence, "
         << "the better you did in this game." << endl;
}

void findHealthOfEconomy(Player *user) {
    int growth = user->getGrowth();
    int economy = 1 + rand() % 100; // [1, 100]
    cout << endl;
    
    // Check the pulse of the economy
    if (economy > 30) { user->healthyEcon(growth); }   // 31-100 is healthy econ
    else if (economy < 20) { user->poorEcon(growth); } // 01-19 is poor economy
    else { user->stagEcon(growth); }                   // 20-30 is stag economy
}

void printHorizontalDoubleLine() {
    cout << "============================="
         << "=============================" << endl;
}

void initializeRound(Player *user,
                     vector<bool> &isOwnerOf,
                     vector<int> &property_prices,
                     int &cur_year)
{
    cout << endl;
    printHorizontalDoubleLine();
    printHorizontalDoubleLine();

    if (cur_year == Player::END_YEAR - 1) {
        cout << "\nIt is now " << cur_year 
             << "! You will retire at the end of this year!!\n" << endl;
    } else if (cur_year == Player::END_YEAR - 2) {
        cout << "\nIt is now " << cur_year
             << ". You have this year and next year still left to play!\n"
             << endl;
    } else {
        cout << "\nIt is " << cur_year << " and there are "
             << Player::END_YEAR - cur_year
             << " years left until retirement.\n" << endl;
    }
    cout << endl;

    user->valueProperty(property_prices); // Revalue property accordingly
    user->displayProperty(property_prices, isOwnerOf);
}

void validateUserInput(string &temp) {
    while (1) {
        cin >> temp;

        transform(
            temp.begin(),
            temp.end(),
            temp.begin(),
            ::tolower
        );

        if (temp.compare("yes") == 0 || temp.compare("y") == 0
            || temp.compare("no") == 0 || temp.compare("n") == 0)
        {
            return;
        }

        cout << "Sorry but that is not a valid command. ";
        cout << "Please type yes or no." << endl;
    }
}

void promptForSales(Player *user,
                    vector<bool> &isOwnerOf,
                    vector<int> &property_prices)
{
    string temp;
    int index;
    bool first = true;

    for (vector<bool>::iterator it = isOwnerOf.begin();
        it != isOwnerOf.end();
        ++it)
    {
        if (*it) {
            if (first) {
                cout << "\n\nTime to sell property! "
                     << "What would you like to sell today?" << endl;
                first = false;
            }

            index = distance(isOwnerOf.begin(), it);
            cout << "\nYou have $" << user->getMoney() 
                 << " in your account." << endl;

            cout << user->getName() << ", would you like to SELL property "
                 << index + 1 << "? \nType 'yes' if you want to sell now! Type "
                 << "no if you want to pass. ";

            validateUserInput(temp);

            user->setDecision(temp);
            if (user->getDecision()) {
                index = distance(isOwnerOf.begin(), it);
                user->sellProperty(property_prices, isOwnerOf, index);
                cout << "Selling property " << index + 1 << " . . . " << endl;
            }
        }
    }
}

void promptForPurchases(Player *user,
                        vector<bool> &isOwnerOf,
                        vector<int> &property_prices)
{
    string temp;
    int index;
    bool first = true;

    for (vector<bool>::iterator it = isOwnerOf.begin();
        it != isOwnerOf.end();
        ++it)
    {
        index = distance(isOwnerOf.begin(), it);

        if (!(*it) && user->getMoney() >= property_prices[index]) {
            if (first) {
                cout << "\n\nTime to buy property! "
                     << "What would you like to sell today?" << endl;
                first = false;
            }

            cout << "\nYou have $" << user->getMoney()
                 << " in your account." << endl;
            cout << user->getName() << ", would you like to PURCHASE property "
                 << index + 1 << "? \nType 'yes' if you want to buy now! Type no "
                 << "if you want to pass. ";

            validateUserInput(temp);

            user->setDecision(temp);
            if (user->getDecision()) {
                user->purchaseProperty(property_prices, isOwnerOf, index);
                cout << "Buying property " << index + 1 << " . . . " << endl;
            }
        }
    }
}

void playRound(Player *user,
               vector<bool> &isOwnerOf,
               vector<int> &property_prices)
{
    promptForSales(user, isOwnerOf, property_prices);
    promptForPurchases(user, isOwnerOf, property_prices);
}

void printResults(Player *user) {
    cout << "\nYour net worth is now $" << user->getMoney() << "!" << endl;

    // Results of the game depending on user performance
    if (user->getMoney() > 3000000) {
        cout << "Wow! You must be a mathematician. "
             << "You cracked the algorithm..." << endl;
    } else if (user->getMoney() > 2750000) {
        cout << "Excellent. You must work on wall street, "
             << "you know how the game is played. Well done..." << endl;
    } else if (user->getMoney() > 2500000) {
        cout << "Very good. You are either lucky or really smart..." << endl;
    } else {
        cout << "Good try. Don't be afraid to get back in the game..." << endl;
    }
}

void liquidation(Player *user,
                 vector<bool> &isOwnerOf,
                 vector<int> &property_prices)
{
    cout << "\nGet ready for retirement. It's time to liquidate your assets "
         << "\n"
         << "and check your net worth." << endl;

    for (int i = 0; i < isOwnerOf.size(); ++i) {
        if (isOwnerOf[i]) {
            cout << "Selling property " << i + 1 << " . . . " << endl;
            user->sellProperty(property_prices, isOwnerOf, i);
        }
    }

    printResults(user);
}

// ------ Main Process ------
int main() {
    string name;
    vector<bool> isOwnerOf(5, false);
    vector<int> property_prices(5);

    cout << "\nWelcome to Suki's Real Estate game!!\n" << endl;
    cout << "May I have your name please? ";
    cin >> name;

    // Instantiate 'user' and allocate $1.5 MM to begin the game
    Player user_var(name, 1'500'000);
    Player *user = &user_var;

    initializeGame(user, property_prices);
    printInstructions(user);

    // For loop to play 5 rounds of game (years 1-5)
    for (int cur_year = Player::THIS_YEAR;
        cur_year <= Player::END_YEAR;
        ++(cur_year))
    {
        findHealthOfEconomy(user);
        initializeRound(user, isOwnerOf, property_prices, cur_year);

        if (cur_year != Player::END_YEAR) {
            playRound(user, isOwnerOf, property_prices);
        } else {
            // On beginning of 6th year, time to sell property and calc score
            liquidation(user, isOwnerOf, property_prices);
        }
    }

    cout << "\nI hope you enoyed yourself. Good bye.\n" << endl;

    return 0;
}
