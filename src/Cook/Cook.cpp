//
// EPITECH PROJECT, 2019
// Cook.cpp
// File description:
// Cook.cpp
//

#include <chrono>
#include <thread>
#include <iostream>
#include <Cook.hpp>

#include "Mutex.hpp"
#include "Cook.hpp"

Cook::Cook(char **av)
{
	this->_doe = 5;
	this->_tomato = 5;
	this->_gruyere = 5;
	this->_ham = 5;
	this->_mushrooms = 5;
	this->_steak = 5;
	this->_eggplant = 5;
	this->_goatcheese = 5;
	this->_nbCook = std::stol(av[2], nullptr, 0);
}

Cook::~Cook()
{
}

int Cook::getDoe() const
{
	return (this->_doe);
}

int Cook::getTomato() const
{
	return (this->_tomato);
}

int Cook::getGruyere() const
{
	return (this->_gruyere);
}

int Cook::getHam() const
{
	return (this->_ham);
}

int Cook::getMushrooms() const
{
	return (this->_mushrooms);
}

int Cook::getSteak() const
{
	return (this->_steak);
}

int Cook::getEggplant() const
{
	return (this->_eggplant);
}

int Cook::getGoatcheese() const
{
	return (this->_goatcheese);
}

std::string Cook::getIngredients() const
{
	std::string ingredients;

	ingredients += "Doe: " + std::to_string(getDoe()) + "\n" + "Tomato: " + std::to_string(getTomato()) + "\n" + "Gruyere: " + std::to_string(getGruyere()) + "\n"
	+ "Ham: " + std::to_string(getHam()) + "\n" + "Mushrooms: " + std::to_string(getMushrooms()) + "\n" + "Steak: " + std::to_string(getSteak()) + "\n"
	+ "Eggplant: " + std::to_string(getEggplant()) + "\n" + "Goat cheese: " + std::to_string(getGoatcheese()) + "\n";

	return (ingredients);
}

void Cook::incrementTime(char **av)
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    std::chrono::milliseconds interval(std::stol(av[3], nullptr, 0));
    std::this_thread::sleep_for(interval);
    this->_doe += 1;
    this->_tomato += 1;
    this->_gruyere += 1;
    this->_ham += 1;
    this->_mushrooms += 1;
    this->_steak += 1;
    this->_eggplant += 1;
    this->_goatcheese += 1;
    mutex->unlock();
}

void Cook::makeRegina(char **av, int size, int *nb_cooker)
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    (*nb_cooker)++;
    this->_doe -= size;
    this->_tomato -= size;
    this->_gruyere -= size;
    this->_ham -= size;
    this->_mushrooms -= size;
    std::chrono::seconds interval(2*std::stol(av[1], nullptr, 0));
    std::this_thread::sleep_for(interval);
    this->_command.erase(this->_command.begin());
    (*nb_cooker)--;
    mutex->unlock();
}

void Cook::makeMargarita(char **av, int size, int *nb_cooker)
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    (*nb_cooker)++;
	this->_doe -= size;
	this->_tomato -= size;
	this->_gruyere -= size;
    std::chrono::seconds interval(1*std::stol(av[1], nullptr, 0));
    std::this_thread::sleep_for(interval);
    this->_command.erase(this->_command.begin());
    (*nb_cooker)--;
	mutex->unlock();

}

void Cook::makeAmericana(char **av, int size, int *nb_cooker)
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    (*nb_cooker)++;
	this->_doe -= size;
	this->_tomato -= size;
	this->_gruyere -= size;
	this->_steak -= size;
	std::chrono::seconds interval(2*std::stol(av[1], nullptr, 0));
	std::this_thread::sleep_for(interval);
    this->_command.erase(this->_command.begin());
    (*nb_cooker)--;
    mutex->unlock();
}

void Cook::makeFantasia(char **av, int size, int *nb_cooker)
{
    Mutex *mutex = new Mutex();

    mutex->lock();
    (*nb_cooker)++;
	this->_doe -= size;
	this->_tomato -= size;
	this->_eggplant -= size;
	this->_goatcheese -= size;
    std::chrono::seconds interval(4*std::stol(av[1], nullptr, 0));
    std::this_thread::sleep_for(interval);
    this->_command.erase(this->_command.begin());
    (*nb_cooker)--;
	mutex->unlock();
}

void Cook::addCommand(std::string command)
{
    this->_command.push_back(command);
}

int Cook::getNbCommand() const
{
    return (this->_command.size());
}

void Cook::displayCommand(int i)
{
    std::string to_display;

    to_display += "####KITCHEN " + std::to_string(i / 6) + "####\n";
    to_display += "Loading orders:\n\n";
    for (std::vector<int>::size_type j = 0; j < this->_command.size(); j++)
        to_display += this->_command[j] + "\n";
    to_display += "-----------------\n";
    to_display += "Ingredients:\n\n";
    to_display += getIngredients();
    to_display += "#################\n\n";
    std::cout << to_display;
}

const char *Cook::getPlace(char **av)
{
    return ((std::to_string(std::stol(av[2], nullptr, 0) * 2 - this->_command.size())).c_str());
}

int Cook::getNbCooker() const
{
	return (this->_nbCook);
}
