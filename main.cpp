#include <iostream>
#include <string>
using namespace std;

class Pet {
private:
  string name;
  int hunger;
  int happiness;
  int health;

public:
  Pet(string petName) : name(petName), hunger(50), happiness(50), health(100) {}

  void feed() {
    hunger = max(0, hunger - 20);
    health = min(100, health + 5);
    cout << name << " has been fed!" << endl;
  }

  void play() {
    happiness = min(100, happiness + 20);
    hunger = min(100, hunger + 10);
    health = max(0, health - 5);
    cout << name << " enjoyed playing!" << endl;
  }

  void rest() {
    health = min(100, health + 10);
    hunger = min(100, hunger + 5);
    cout << name << " is resting!" << endl;
  }

  void passTime() {
    hunger = min(100, hunger + 5);
    happiness = max(0, happiness - 5);
    if (hunger > 80 || happiness < 20) {
      health = max(0, health - 10);
    }
  }

  void displayStatus() const {
    cout << "Current Status of " << name << ":\n"
         << "Hunger: " << hunger << "\n"
         << "Happiness: " << happiness << "\n"
         << "Health: " << health << endl;
  }

  bool isAlive() const { return health > 0; }

  string getName() const { return name; }
};

class Game {
private:
  Pet pet;

public:
  Game(string petName) : pet(petName) {}

  void startGame() {
    cout << "Welcome to HappyPaws! Let's take care of " << pet.getName() << "!"
         << endl;
  }

  void takeTurn() {
    int choice;
    cout << "\nWhat would you like to do?\n1. Feed\n2. Play\n3. Rest\nEnter "
            "your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      pet.feed();
      break;
    case 2:
      pet.play();
      break;
    case 3:
      pet.rest();
      break;
    default:
      cout << "Invalid choice!" << endl;
      break;
    }

    pet.passTime(); 
  }

  void playGame() {
    startGame();
    while (pet.isAlive()) {
      pet.displayStatus();
      takeTurn();
    }
    cout << pet.getName() << " has passed away. Game over." << endl;
  }
};

int main() {
  string petName;
  cout << "Enter the name of your pet: ";
  cin >> petName;

  Game game(petName);
  game.playGame();

  return 0;
}
