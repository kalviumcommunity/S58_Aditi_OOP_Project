#include <iostream>
#include <string>
using namespace std;

class Pet{
    private:
    string name;
    int hunger;
    int happiness;
    int health;

    public:
    Pet(string petName) : name(petName), hunger(50), happiness(50), health(100){}

    void feed(){
        hunger = max(0, hunger -20);
        cout << name << " has been fed!" << endl;
    }

    void play(){
        happiness = min(100, happiness + 20);
        hunger = min(100, hunger + 10);
        cout << name << " enjoyes playing!" << endl;
    }

    string getName() const {
        return name;
    }
};

class Game{
    private:
    Pet pet;

    public:
    Game(string petName) : pet(petName){}

    void startGame(){
        cout << "Welcome to HappyPaws! Let's take care of " << pet.getName() << "!" << endl;
    }

    void takeTurn(){
        int choice;
        cout<< "What would you like to do?\n1. Feed\n2. Play\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: pet.feed();
            break;
        case 2: pet.play();
            break;
        default: cout<< "Invalid choice!" << endl;
            break;
        }
    }
};

int main(){
    Game game("Fluffy");
    game.startGame();

    game.takeTurn();
    game.takeTurn();

    return 0;
}

