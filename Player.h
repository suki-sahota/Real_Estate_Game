/*
 * Author: Suki Sahota
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <cmath>

class Player {
private:
    // Instance variables
    std::string name;
    int money;
    int growth;
    bool decision;

public:
    // Global variables
    static const int THIS_YEAR = 2022;
    static const int END_YEAR = 2027;

    Player(std::string &newName, int newMoney);
    ~Player();

    // Getter methods
    std::string getName();
    int getMoney();
    int getGrowth();
    bool getDecision();

    // Setter methods
    void setName(std::string &newName);
    void setMoney(int &newMoney);
    void setGrowth(int newGrowth);
    void setDecision(std::string &newDecision);

    // Method to initialize real estate property values
    // in the beginning of the game
    void initializeProperty(std::vector<int> &property);

    // Method to appreciate/depreciate real estate property
    // after we access the health of the economy
    void valueProperty(std::vector<int> &property);

    // Method to display property values to the user
    void displayProperty(const std::vector<int> &property,
                         const std::vector<bool> &isOwner);

    // Method to sell property
    void sellProperty(std::vector<int> &property, 
                      std::vector<bool> &isOwner,
                      int &index);

    // Method to purchase property
    void purchaseProperty(std::vector<int> &property,
                          std::vector<bool> &isOwner,
                          int &index);

    // Method for healthy economy
    void healthyEcon(int &rate);
    // Method for poor economy
    void poorEcon(int &rate);
    // Method for relatively unchanged economy
    void stagEcon(int &rate);
};

#endif
