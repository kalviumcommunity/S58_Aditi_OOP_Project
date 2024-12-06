#include <iostream>
#include <string>
using namespace std;

class Pet
{
protected:
    string name;
    int hunger;
    int happiness;
    int health;

public:
    Pet()
    {
        setName("Unnamed Pet");
        setHunger(50);
        setHappiness(50);
        setHealth(100);
        cout << "A pet with no name was created!" << endl;
    }

    Pet(string petName)
    {
        setName(petName);
        setHunger(50);
        setHappiness(50);
        setHealth(100);
    }

    string getName()
    {
        return name;
    }

    void setName(string petName)
    {
        name = petName;
    }

    int getHunger()
    {
        return hunger;
    }

    void setHunger(int newHunger)
    {
        hunger = max(0, min(100, newHunger));
    }

    int getHappiness()
    {
        return happiness;
    }

    void setHappiness(int newHappiness)
    {
        happiness = max(0, min(100, newHappiness));
    }

    int getHealth()
    {
        return health;
    }

    void setHealth(int newHealth)
    {
        health = max(0, min(100, newHealth));
    }

    virtual void feed()
    {
        setHunger(getHunger() - 10);
        setHealth(getHealth() + 5);
        cout << getName() << " has been fed. Hunger: " << getHunger() << ", Health: " << getHealth() << endl;
    }

    virtual void play()
    {
        setHappiness(getHappiness() + 10);
        setHunger(getHunger() + 5);
        setHealth(getHealth() - 5);
        cout << getName() << " played. Happiness: " << getHappiness() << ", Hunger: " << getHunger() << ", Health: " << getHealth() << endl;
    }

    virtual void rest()
    {
        setHealth(getHealth() + 10);
        setHunger(getHunger() + 5);
        cout << getName() << " is resting. Health: " << getHealth() << ", Hunger: " << getHunger() << endl;
    }

    bool isAlive()
    {
        return getHealth() > 0;
    }

    virtual void displayStatus()
    {
        cout << getName() << "'s Status - Hunger: " << getHunger() << ", Happiness: " << getHappiness() << ", Health: " << getHealth() << endl;
    }
};

class Dog : public Pet
{
public:
    Dog(string petName) : Pet(petName) {}

    void play() override
    {
        setHappiness(getHappiness() + 15);
        setHunger(getHunger() + 5);
        setHealth(getHealth() - 7);
        cout << getName() << " (the Dog) played enthusiastically. Happiness: " << getHappiness() << ", Hunger: " << getHunger() << ", Health: " << getHealth() << endl;
    }

    void displayStatus() override
    {
        cout << getName() << " (the Dog) - Hunger: " << getHunger() << ", Happiness: " << getHappiness() << ", Health: " << getHealth() << endl;
    }
};

class Cat : public Pet
{
public:
    Cat(string petName) : Pet(petName) {}

    void rest() override
    {
        setHealth(getHealth() + 15);
        setHunger(getHunger() + 3);
        cout << getName() << " (the Cat) is napping. Health: " << getHealth() << ", Hunger: " << getHunger() << endl;
    }

    void displayStatus() override
    {
        cout << getName() << " (the Cat) - Hunger: " << getHunger() << ", Happiness: " << getHappiness() << ", Health: " << getHealth() << endl;
    }
};

class Game
{
private:
    Pet *pet;

public:
    Game(Pet *p)
    {
        setPet(p);
    }

    Pet *getPet()
    {
        return pet;
    }

    void setPet(Pet *p)
    {
        pet = p;
    }

    void startGame()
    {
        cout << "Welcome to the gamee! Let's take care of " << getPet()->getName() << "!" << endl;
    }

    void takeTurn()
    {
        int choice;
        cout << "\nWhat would you like to do?\n";
        cout << "1. Feed\n2. Play\n3. Rest\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            getPet()->feed();
            break;
        case 2:
            getPet()->play();
            break;
        case 3:
            getPet()->rest();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    void playGame()
    {
        startGame();
        while (getPet()->isAlive())
        {
            getPet()->displayStatus();
            takeTurn();
        }
        cout << getPet()->getName() << " has passed away. Game over." << endl;
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

    Pet *pet;
    if (petType == 1)
        pet = new Dog(petName);
    else if (petType == 2)
        pet = new Cat(petName);
    else
    {
        cout << "Invalid pet type. Creating a default pet." << endl;
        pet = new Pet(petName);
    }

    Game game(pet);
    game.playGame();

    delete pet;
    return 0;
}
