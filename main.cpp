#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Activity
{
public:
    virtual void execute(int &happiness, int &hunger, int &health) = 0;
    virtual ~Activity() = default;
};

class PlayDog : public Activity
{
public:
    void execute(int &happiness, int &hunger, int &health) override
    {
        happiness = min(100, happiness + 15);
        hunger = min(100, hunger + 5);
        health = max(0, health - 7);
        cout << "(Dog) played enthusiastically. Happiness: " << happiness
             << ", Hunger: " << hunger << ", Health: " << health << endl;
    }
};

class PlayCat : public Activity
{
public:
    void execute(int &happiness, int &hunger, int &health) override
    {
        happiness = min(100, happiness + 10);
        hunger = min(100, hunger + 5);
        health = max(0, health - 5);
        cout << "(Cat) played calmly. Happiness: " << happiness
             << ", Hunger: " << hunger << ", Health: " << health << endl;
    }
};

class AbstractPet
{
protected:
    string name;
    int hunger = 50;
    int happiness = 50;
    int health = 100;
    unique_ptr<Activity> playActivity;

public:
    AbstractPet(string petName, unique_ptr<Activity> activity)
        : name(petName), playActivity(move(activity)) {}
    virtual ~AbstractPet() = default;

    virtual void speak() const = 0;

    void play()
    {
        playActivity->execute(happiness, hunger, health);
    }

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
        cout << name << " - Hunger: " << hunger << ", Happiness: " << happiness
             << ", Health: " << health << endl;
    }

    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
};

class Dog : public AbstractPet
{
public:
    Dog(string petName) : AbstractPet(petName, make_unique<PlayDog>()) {}

    void speak() const override
    {
        cout << name << " says: Woof Woof!" << endl;
    }
};

class Cat : public AbstractPet
{
public:
    Cat(string petName) : AbstractPet(petName, make_unique<PlayCat>()) {}

    void speak() const override
    {
        cout << name << " says: Meow!" << endl;
    }
};

class PetFactory
{
public:
    static unique_ptr<AbstractPet> createPet(int type, const string &name)
    {
        switch (type)
        {
        case 1:
            return make_unique<Dog>(name);
        case 2:
            return make_unique<Cat>(name);
        default:
            cout << "Invalid choice. Defaulting to a Dog." << endl;
            return make_unique<Dog>(name);
        }
    }
};

class Game
{
private:
    unique_ptr<AbstractPet> pet;

public:
    Game(unique_ptr<AbstractPet> p) : pet(move(p)) {}

    void startGame()
    {
        cout << "Welcome! Let's take care of your pet!" << endl;
        pet->displayStatus();
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

    Game game(PetFactory::createPet(petType, petName));
    game.playGame();

    return 0;
}