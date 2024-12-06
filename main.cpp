#include <iostream>
#include <string>
using namespace std;

class AbstractPet
{
protected:
    string name;
    int hunger = 50;
    int happiness = 50;
    int health = 100;

public:
    AbstractPet(string petName) : name(petName) {}
    virtual ~AbstractPet() {}

    virtual void speak() const = 0;
    virtual void play() = 0;

    void feed()
    {
        hunger = max(0, hunger - 10);
        health = min(100, health + 5);
        cout << name << " has been fed. Hunger: " << hunger << ", Health: " << health << endl;
    }

    void rest()
    {
        health = min(100, health + 10);
        hunger = min(100, hunger + 5);
        cout << name << " is resting. Health: " << health << ", Hunger: " << hunger << endl;
    }

    void displayStatus() const
    {
        cout << name << " - Hunger: " << hunger << ", Happiness: " << happiness << ", Health: " << health << endl;
    }

    bool isAlive() const { return health > 0; }
};

class Dog : public AbstractPet
{
public:
    Dog(string petName) : AbstractPet(petName) {}

    void speak() const override { cout << name << " says: Woof Woof!" << endl; }

    void play() override
    {
        happiness = min(100, happiness + 15);
        hunger = min(100, hunger + 5);
        health = max(0, health - 7);
        cout << name << " (Dog) played enthusiastically. Happiness: " << happiness << ", Hunger: " << hunger << ", Health: " << health << endl;
    }
};

class Cat : public AbstractPet
{
public:
    Cat(string petName) : AbstractPet(petName) {}

    void speak() const override { cout << name << " says: Meow!" << endl; }

    void play() override
    {
        happiness = min(100, happiness + 10);
        hunger = min(100, hunger + 5);
        health = max(0, health - 5);
        cout << name << " (Cat) played calmly. Happiness: " << happiness << ", Hunger: " << hunger << ", Health: " << health << endl;
    }
};

class Game
{
private:
    AbstractPet *pet;

public:
    Game(AbstractPet *p) : pet(p) {}

    ~Game()
    {
        delete pet;
    }

    void startGame()
    {
        cout << "Welcome! Let's take care of " << pet->displayStatus() << "!" << endl;
    }

    void takeTurn()
    {
        int choice;
        cout << "\nWhat would you like to do?\n";
        cout << "1. Feed\n2. Play\n3. Rest\n4. Speak\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            pet->feed();
            break;
        case 2:
            pet->play();
            break;
        case 3:
            pet->rest();
            break;
        case 4:
            pet->speak();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    void playGame()
    {
        startGame();
        while (pet->isAlive())
        {
            pet->displayStatus();
            takeTurn();
        }
        cout << "Game over. Your pet has passed away." << endl;
    }
};

int main()
{
    string petName;
    int petType;

    cout << "Choose your pet type:\n1. Dog\n2. Cat\nEnter choice: ";
    cin >> petType;

    cout << "Enter the name of your pet: ";
    cin >> petName;

    AbstractPet *pet = nullptr;

    if (petType == 1)
    {
        pet = new Dog(petName);
    }
    else if (petType == 2)
    {
        pet = new Cat(petName);
    }
    else
    {
        cout << "Invalid choice. Defaulting to a Dog." << endl;
        pet = new Dog(petName);
    }

    Game game(pet);
    game.playGame();

    return 0;
}
