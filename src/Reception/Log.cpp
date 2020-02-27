//
// EPITECH PROJECT, 2019
// Log.cpp
// File description:
// Log.cpp
//

#include <fstream>
#include "Reception.hpp"
#include "Cook.hpp"
#include "Log.hpp"

void write_in_file(std::vector<std::string> command_array, std::ofstream *fd)
{
    std::vector<std::string> pizzas_array;
    std::vector<int> count_array;

    for (std::vector<int>::size_type i = 0; i < command_array.size(); i = i + 2) {
    	if (count_array.empty())
    		count_array.push_back(0);
    	if (pizzas_array.empty())
    		pizzas_array.push_back(command_array[i] + " " + command_array[i + 1]);
    	for (std::vector<int>::size_type j = 0; j < pizzas_array.size(); j++) {
    		if (command_array[i] + " " + command_array[i + 1] != pizzas_array[j] &&
    		std::find(pizzas_array.begin(), pizzas_array.end(), command_array[i] + " " + command_array[i + 1]) == pizzas_array.end()) {
    			pizzas_array.push_back(command_array[i] + " " + command_array[i + 1]);
    			count_array.push_back(0);
    		} else if (command_array[i] + " " + command_array[i + 1] == pizzas_array[j]) {
    			count_array[j] = count_array[j] + 1;
    		}
    	}
    }
    for (std::vector<int>::size_type j = 0; j < pizzas_array.size(); j++)
        (*fd) << pizzas_array[j] << " x" << count_array[j] << " " << "\n";
    (*fd) << "----------------\n";
}

void print_file(const char *file)
{
    std::ifstream f(file);

    if (f.is_open()) {
        std::cout << f.rdbuf();
        remove(file);
    }
}