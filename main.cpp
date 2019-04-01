/*
 * Author: Suki Sahota
 * Description: Real Estate Game
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Player class to play game
class Player {
    private:
        // Instance variables
        string name;
        int money;
        int growth;
        bool decision;
    
    public:
        // Global variables
        static int THIS_YEAR;
        static const int END_YEAR = 2024;

        // Two-argument constructor
        Player(string &newName, int newMoney) {
            name = newName;
            money = newMoney;
        }

        // Destructor
        ~Player() {}

        // Getter methods
        string getName() {
            return name;
        }

        int getMoney() {
            return money;
        }

        int getGrowth() {
            return growth;
        }

        bool getDecision() {
            return decision;
        }

        // Setter methods
        void setName(string &newName) {
            name = newName;
        }

        void setMoney(int &newMoney) {
            money = newMoney;
        }

        void setGrowth(int &newGrowth) {
            growth = newGrowth;
        }

        void setDecision(string &newDecision) {
            // Transform newDecision argument to lowercase string
            transform(newDecision.begin(), newDecision.end(), newDecision.begin(), ::tolower);
            if (newDecision == "yes") decision = true;
            else decision = false;
        }

        // Method to initialize real estate property values in the beginning of the game
        void initializeProperty(vector<int> &property) {
            for(vector<int>::iterator it = property.begin(); it != property.end(); ++it) {
                // Assign each property an initial value from $300,000-500,000
                *it = 300000 + rand() % (200000 + 1);
            }
        }

        // Method to appreciate/depreciate real estate property after we access the health of the economy
        void valueProperty(vector<int> &property) {
            for (vector<int>::iterator it = property.begin(); it != property.end(); ++it) {
                // Use iterator to read and write data from property vector
                *it *= (1 + (this->getGrowth() * 0.01));
            }
        }

        // Method to display property values to the user
        void displayProperty(const vector<int> &property, const vector<bool> &isOwner) {

            // Table to show data
            cout << "                          ------------------------------" << endl;
            cout << "                          ||  SUMMARY OF REAL ESTATE  ||" << endl;
            cout << "---------------------------------------------------------------------------------------" << endl;

            string homeOwner;
            vector<bool>::const_iterator iter = isOwner.cbegin();

            for (vector<int>::const_iterator it = property.cbegin(); it != property.cend(); ++it, ++iter) {
                if (*iter) homeOwner = "Yes ";
                else homeOwner = "Nope";
                cout << "|  Property " << it - property.cbegin() + 1 << " ~ Price: $" << *it << " || " << "Property Owner: " << homeOwner << " || " << "Lot Number: " << &*it << "  |" << endl;
            }

            cout << "---------------------------------------------------------------------------------------" << endl;
        }

        // Method to sell property
        void sellProperty(vector<int> &property, vector<bool> &isOwner, int &index) {
            // Mark isOwner false where this property is located in isOwner vector
            isOwner[index] = false;

            int tempMoney = this->getMoney() + property[index];

            // Debit user account with market value of this real estate property
            this->setMoney(tempMoney);
        }

        // Method to purchase property
        void purchaseProperty(vector<int> &property, vector<bool> &isOwner, int &index) {
            // Mark isOwner true to keep track of the property being purchased
            isOwner[index] = true;

            int tempMoney = this->getMoney() - property[index];

            // Credit user account with market value of this real estate property
            this->setMoney(tempMoney);
        }

        // Method for healthy economy
        void healthyEcon(int &rate) {
            cout << "The economy looks strong as an ox!" << endl;

            if (rate > 6) rate += 5;
            else if (rate >= 0) rate += 2;
            else rate = 0;

            cout << "The growth rate just became " << rate << "%!" << endl;
            this->setGrowth(rate);

            // user receives bonus because the economy is doing well
            cout << "Because the economy is doing so well, you got a $50,000 bonus at work!" << endl;

            int tempMoney = this->getMoney() + 50000;

            this->setMoney(tempMoney);
        }

        // Method for poor economy
        void poorEcon(int &rate) {
            cout << "The economy isn't doing so good." << endl;

            if (rate > 10) rate = 2;
            else if (rate > 4) rate = 0;
            else if (rate > -10) rate = -10;
            else rate = -15;

            cout << "The growth rate just became " << rate << "%!" << endl;
            this->setGrowth(rate);
        }

        // Method for relatively unchanged economy
        void stagEcon(int &rate) {
            cout << "The economy hasn't changed much since last quarter.." << endl;

            rate = 0;

            cout << "The growth rate just became " << rate << "%!" << endl;
            this->setGrowth(rate);
        }
};


int Player::THIS_YEAR = 2019;
const int Player::END_YEAR;


int main() {

    // Welcome message
    cout << "\nWelcome to the Real Estate game!!\n" << endl;

    // Prompt user for name
    cout << "May I have your name please? ";

    // Create name variable to store user's name from the console
    string name;
    cin >> name;

    // Instantiate 'user' and allocate $1.5 MM to begin the game
    Player user(name, 1500000);

    // This vector is used to hold the price of each real estate property
    vector<int> property(5);

    // This vector is used to keep track of which properties the user owns
    vector<bool> isOwner(5);

    // Declare and initialize growth to (2%) and then set user growth rate
    int growth = 2;
    user.setGrowth(growth);

    // Declare temp variable that will be used to store user input from the console
    string temp;

    // Declare index variable which describes specific property
    int index;

    // Declare economy variable
    int economy;

    // Seed random function using computer's internal clock
    srand(time(0));

    // Initialize real estate property values using smart pointer to our vector
    user.initializeProperty(property);

    // Game instructions
    cout << endl;
    cout << "__________________________________________________________" << endl;
    cout << "__________________________________________________________" << endl;
    cout << "__________________________________________________________" << endl;
    cout << "\nOk " << user.getName() << ", the year is " << Player::THIS_YEAR << ". Each round of this game represents one year, and the game ends when you retire at the end of " << Player::END_YEAR << ". The rules are simple. Each round you will be afforded the opportunity to buy and sell Real Estate Properties. At the end of the game, we liquidate your assets and calculate your net worth. The higher your 'score' at the end, the better judgements you made, hence, the better you did in this game." << endl;


    // For loop to play 5 rounds of game (5 years)
    for (Player::THIS_YEAR; Player::THIS_YEAR <= Player::END_YEAR; ++Player::THIS_YEAR) {
        growth = user.getGrowth();

        cout << endl;
        cout << "==========================================================" << endl;
        cout << "==========================================================" << endl;
        if (Player::THIS_YEAR == Player::END_YEAR) {
            cout << "\nIt is now " << Player::THIS_YEAR << "! You will retire at the end of this year!!\n" << endl;
        } else if (Player::THIS_YEAR == Player::END_YEAR - 1) {
            cout << "\nIt is now " << Player::THIS_YEAR << ". You have this year and next year still left to play!\n" << endl;
        } else {
            cout << "\nIt is now " << Player::THIS_YEAR << " and there are " << Player::END_YEAR - Player::THIS_YEAR + 1 << " years left until retirement.\n" << endl;
        }

        // Generate random number between 1 and 100
        economy = 1 + rand() % 100;
        
        // Check the pulse of the economy
        if (economy < 70) user.healthyEcon(growth);
        else if (economy > 80) user.poorEcon(growth);
        else user.stagEcon(growth);

        cout << endl;

        // Appreciate/depreciate real estate property values based off of the health of the economy
        user.valueProperty(property);

        // Display real estate properties for user to see
        user.displayProperty(property, isOwner);

        // Don't execute this if it is the last year of the game
        if (!(Player::THIS_YEAR == Player::END_YEAR)) {
            // Loop through isOwner and ask user if they would like to sell for all true values, if so, run user.sellProperty(someIndex);
            for (vector<bool>::iterator it = isOwner.begin(); it != isOwner.end(); ++it) {
                if (*it) {
                    index = it - isOwner.begin();
                    cout << "\nYou have $" << user.getMoney() << " in your account." << endl;
                    cout << user.getName() << ", would you like to SELL property " << index + 1 << "? Type 'yes' if you want to sell now! Type no if you want to pass. ";
                    cin >> temp;
                    user.setDecision(temp);
                    if (user.getDecision()) {
                        index = it - isOwner.begin();
                        user.sellProperty(property, isOwner, index);
                        cout << "Selling property " << index + 1 << " . . . " << endl;
                    }
                }
            }

            // Loop through isOwner and ask user if they would like to purchase real estate that they do not already own
            for (vector<bool>::iterator it = isOwner.begin(); it != isOwner.end(); ++it) {
                index = it - isOwner.begin();
                if (!(*it) && user.getMoney() >= property[index]) {
                    cout << "\nYou have $" << user.getMoney() << " in your account." << endl;
                    cout << user.getName() << ", would you like to PURCHASE property " << index + 1 << "? Type 'yes' if you want to buy now! Type no if you want to pass. ";
                    cin >> temp;
                    user.setDecision(temp);
                    if (user.getDecision()) {
                        user.purchaseProperty(property, isOwner, index);
                        cout << "Buying property " << index + 1 << " . . . " << endl;
                    }
                }
            }

        // Liquidation for last part of the game
        } else {
            cout << "\nGet ready for retirement. It's time to liquidate your assets and check your net worth." << endl;
            for (int i = 0; i < isOwner.size(); ++i) {
                if (isOwner[i]) {
                    user.sellProperty(property, isOwner, i);
                    cout << "Selling property " << i + 1 << " . . . " << endl;
                }
            }

            // Display net worth to user
            cout << "\nYour net worth is now $" << user.getMoney() << "!" << endl;

            // Results of the game depending on user performance
            if (user.getMoney() > 3000000) {
                cout << "Wow! You must be Berkeley Mathematics alumni. You cracked the algorithm..." << endl;
            } else if (user.getMoney() > 2750000) {
                cout << "Dang. You must have studied at Haas, you know how the game is played. Well done..." << endl;
            } else if (user.getMoney() > 2500000) {
                cout << "Very good. You are either lucky or really smart..." << endl;
            } else {
                cout << "Good try. Don't be afraid to get back in the game..." << endl;
            }
        }
    }

    // Exit message
    cout << "\nI hope you enjoyed yourself. Good bye.\n" << endl;
    return 0;
}