/*
 * Author: Suki Sahota
 */
#include "Player.h"

using namespace std;

// Forward declarations
void displayHeader();
void displayBody(const vector<int> &, const vector<bool> &);
void displayTail();

// Two-argument constructor
Player::Player(string &newName, int newMoney) {
    this->name = newName;
    this->money = newMoney;
}

// Destructor
Player::~Player() {}

// Getter methods
string Player::getName() {
    return this->name;
}

int Player::getMoney() {
    return this->money;
}

int Player::getGrowth() {
    return this->growth;
}

bool Player::getDecision() {
    return this->decision;
}

// Setter methods
void Player::setName(string &newName) {
    this->name = newName;
}

void Player::setMoney(int &newMoney) {
    this->money = newMoney;
}

void Player::setGrowth(int newGrowth) {
    this->growth = newGrowth;
}

void Player::setDecision(string &newDecision) {
    if (newDecision.compare("yes") == 0 || newDecision.compare("y") == 0) {
        this->decision = true;
    } else {
        this->decision = false;
    }
}

// Method to initialize real estate property values in the beginning of the game
void Player::initializeProperty(vector<int> &property) {
    for (vector<int>::iterator it = property.begin();
        it != property.end();
        ++it)
    {
        // Assign each property an initial value from $300,000-500,000
        int price = 300000 + rand() % (200000 + 1);
        *it = price;
    }
}

// Method to appreciate/depreciate real estate property
// after we access the health of the economy
void Player::valueProperty(vector<int> &property) {
    for (vector<int>::iterator it = property.begin();
        it != property.end();
        ++it)
    {
        // Use iterator to read and write data from property vector
        *it *= (1 + (this->getGrowth() * 0.01));
    }
}

// Method to display property values to the user
void Player::displayProperty(const vector<int> &property,
                             const vector<bool> &isOwner)
{
    displayHeader();
    displayBody(property, isOwner);
    displayTail();

}

// Method to sell property
void Player::sellProperty(vector<int> &property,
                          vector<bool> &isOwner,
                          int &index)
{
    // Mark isOwner false where this property is located in isOwner vector
    isOwner[index] = false;

    int tempMoney = this->getMoney() + property[index];

    // Debit user account with market value of this real estate property
    this->setMoney(tempMoney);
}

// Method to purchase property
void Player::purchaseProperty(vector<int> &property,
                              vector<bool> &isOwner,
                              int &index)
{
    // Mark isOwner true to keep track of the property being purchased
    isOwner[index] = true;

    int tempMoney = this->getMoney() - property[index];

    // Credit user account with market value of this real estate property
    this->setMoney(tempMoney);
}

// Method for healthy economy
void Player::healthyEcon(int &rate) {
    cout << "The economy looks strong as an ox!" << endl;

    if (rate > 6) rate += 5;
    else if (rate >= 0) rate += 2;
    else rate = 0;

    cout << "The growth rate just became " << rate << "%!" << endl;
    this->setGrowth(rate);

    // user receives bonus because the economy is doing well
    cout << "Because the economy is doing so well, "
         << "you got a $50,000 bonus at work!" << endl;

    int tempMoney = this->getMoney() + 50000;

    this->setMoney(tempMoney);
}

// Method for poor economy
void Player::poorEcon(int &rate) {
    cout << "The economy isn't doing so good." << endl;

    if (rate > 10) rate = 2;
    else if (rate > 4) rate = 0;
    else if (rate > -10) rate = -10;
    else rate = -15;

    cout << "The growth rate just became " << rate << "%!" << endl;
    this->setGrowth(rate);
}

// Method for relatively unchanged economy
void Player::stagEcon(int &rate) {
    cout << "The economy hasn't changed much since last quarter.." << endl;

    rate = 0;

    cout << "The growth rate just became " << rate << "%!" << endl;
    this->setGrowth(rate);
}

void printLongLine() {
    cout << "--------------------------------------------";
    cout << "-------------------------------------------" << endl;
}

void displayHeader() {
    cout << "                          ------------------------------" << endl;
    cout << "                          ||  SUMMARY OF REAL ESTATE  ||" << endl;
    printLongLine();
}

void displayBody(const vector<int> &property, const vector<bool> &isOwner) {
    string propertyOwner;
    vector<bool>::const_iterator iter = isOwner.cbegin();

    for (vector<int>::const_iterator it = property.cbegin();
        it != property.cend();
        ++it, ++iter)
    {
        if (*iter) { propertyOwner = "Yes "; }
        else { propertyOwner = "Nope"; }

        cout << "|  Property " << it - property.cbegin() + 1 << " ~ Price: $"
             << *it << " || " << "Property Owner: " << propertyOwner << " || "
             << "Lot Number: " << &*it << "  |" << endl;
    }
}

void displayTail() {
    printLongLine();
}
