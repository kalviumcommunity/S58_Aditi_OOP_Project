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
    Pet(string name){
        this->name = name;
        this->hunger = 50;
        this->happiness = 50;
        this->health = 100;
    }

    Pet& feed(int hunger = 20){
        this->hunger = max(0, this->hunger - hunger);
        this->health = min(100, this->health + 5);
        cout << this->name << " has been fed!" << endl;
        return *this;
    }

    Pet& play(int happiness = 20){
        this->happiness = min(100, this->happiness + happiness);
        this->hunger = min(100, this->hunger + 10);
        this->health = max(0, this->health - 5 );
        cout << this->name << " enjoyed playing!" << endl;
        return *this;
    }

    Pet& rest(){
        this->health = min(100, this->health + 10);
        this->hunger = min(100, this->hunger + 5);
        cout << this->name << " is resting!" << endl;
        return *this;
    }

    void passTime(){
        this->hunger = min(100, this->hunger + 5);
        this->happiness = max(0, this->happiness - 5);
        if(this->hunger > 80 || this->happiness < 20){
            this->health = max (0, this->health - 10);
        }
    }

    void displayStatus() const{
        cout << "Current Status of " << this->name << ":\n"
             << "Hunger: " << this->hunger << "\n"
             << "Happiness: " << this->happiness << "\n"
             << "Health: " << this->health << endl;
    }

    bool isAlive() const {return this->health > 0;}

    string getName() const {return this->name;}

};

class Game{
private:
    Pet pet;

public:
    Game(string petName) : pet(petName){}

    void startGame(){
        cout<< "Welcome to HappyPaws! Let's take care of " << this->pet.getName() << "!" << endl;
    }

    void takeTurn(){
        int choice;
        cout << "\nWhat would you like to do?\n1. Feed\n2. Play\n3. Rest\nEnter your choice: ";
        cin >> choice;

        switch(choice){
            case 1: this->pet.feed();
            break;
            case 2: this->pet.play();
            break;
            case 3: this->pet.rest();
            break;
            default: cout << "Invalid choice!" << endl;
            break;
        }

        this->pet.passTime();
    }

    void playGame(){
        this->startGame();
        while(this->pet.isAlive()){
            this->pet.displayStatus();
            this->takeTurn();
        }
        cout << this->pet.getName() << " has passed away. Game over." << endl;
    }
};

int main(){
    const int numPets = 3;
    Pet pets[numPets] = {Pet(""), Pet(""), Pet("")};

    for(int i = 0; i < numPets; i++){
        string petName;
        cout << "Enter the name of pet #" << (i + 1) << ": ";
        cin >> petName;
        pets[i] = Pet(petName);
    }

    for(int i = 0; i < numPets; i++){
        cout << "Interacting with " << pets[i].getName() << "!" << endl;
        Game game(pets[i].getName());
        game.playGame();
    }

    return 0;
}
