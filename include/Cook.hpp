/*
** EPITECH PROJECT, 2019
** Cook.hpp
** File description:
** ${FILEDESCRIPTION}
*/

#ifndef CCP_PLAZZA_2018_COOK_HPP
#define CCP_PLAZZA_2018_COOK_HPP

#include <iostream>
#include <string>
#include <ostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <mutex>

class Cook {
public:
	Cook(char **av);
	~Cook();

	int getDoe() const;
	int getTomato() const;
	int getGruyere() const;
	int getHam() const;
	int getMushrooms() const;
	int getSteak() const;
	int getEggplant() const;
	int getGoatcheese() const;
	int getNbCooker() const;
	std::string getIngredients() const;
	void incrementTime(char **av);
	void makeRegina(char **av, int size, int *nb_cooker);
	void makeMargarita(char **av, int size, int *nb_cooker);
	void makeAmericana(char **av, int size, int *nb_cooker);
	void makeFantasia(char **av, int size, int *nb_cooker);
    void addCommand(std::string command);
    int getNbCommand() const;
    void displayCommand(int i);
    const char *getPlace(char **av);
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    std::vector<std::string> _command;
	int _doe;
	int _tomato;
	int _gruyere;
	int _ham;
	int _mushrooms;
	int _steak;
	int _eggplant;
	int _goatcheese;
	int _nbCook;
};

#endif //CCP_PLAZZA_2018_COOK_HPP
