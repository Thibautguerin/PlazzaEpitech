/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main for plazza
*/

#include "Reception.hpp"
#include "Log.hpp"
#include <vector>
#include <math.h>
#include <chrono>
#include <thread>
#include <fstream>
#include "Write.hpp"
#include "Read.hpp"

std::vector<std::string> parse_command(std::string command)
{
    std::vector<std::string> new_commands;
    std::vector<std::string> buff;
    std::string word;

    for (std::string::size_type i = 0; i < command.length(); i++) {
        if (command[i] == ' ' || command[i] == ';') {
            if (word.length() != 0)
                buff.push_back(word);
            word = "";
        } else if (command[i] == 'x' && command[i + 1] > '0' && command[i + 1] <= '9')
            continue;
        else
            word = word + command[i];
    }
    if (word.length() != 0)
        buff.push_back(word);
    for (std::vector<int>::size_type i = 2; i < buff.size(); i = i + 3) {
        for (int nb_pizza = std::stoi(buff[i]); nb_pizza != 0; nb_pizza--) {
            new_commands.push_back(buff[i - 2]);
            new_commands.push_back(buff[i - 1]);
        }
    }

    return (new_commands);
}

void waiting_line(std::string command, std::vector<std::string> *command_array)
{
    std::vector<std::string> new_commands = parse_command(command);

    for (std::vector<int>::size_type i = 0; i < new_commands.size(); i++) {
        command_array->push_back(new_commands[i]);
    }
}

void action(char **av, std::vector<std::string> *command_array, std::vector<int> *cook_array)
{
    char buff[100];
    std::vector<int>::size_type i = 0;
    int size;
    int free_places = 0;
    Read *read = new Read();
    Write *write = new Write();

    for (std::vector<int>::size_type j = 0; j < (*cook_array).size(); j = j + 6) {
        write->my_write((*cook_array)[j + 1], "get_place\0", 10);
        size = read->my_read((*cook_array)[j + 2], buff, 100);
        buff[size] = '\0';
        free_places += std::stol(buff, nullptr, 0);
    }
    float needed_cook = ((float)((*command_array).size() - 2 * (float)(free_places)) / 4.0) / (float)(std::stol(av[2], nullptr, 0));

    while (needed_cook > 0) {
        add_new_cook(av, cook_array);
        needed_cook--;
    }

    while (i < (*command_array).size()) {
        for (std::vector<int>::size_type j = 0; j < (*cook_array).size(); j = j + 6) {
            write->my_write((*cook_array)[j + 1], ((*command_array)[i]+" "+(*command_array)[i + 1]+"\0").c_str(), std::strlen(((*command_array)[i]+" "+(*command_array)[i + 1]+"\0").c_str()));
            size = read->my_read((*cook_array)[j + 2], buff, 100);
            buff[size] = '\0';
            if (std::strcmp(buff, "yes\0") == 0) {
                (*command_array).erase((*command_array).begin());
                (*command_array).erase((*command_array).begin());
            }
            if ((*command_array).size() == 0)
                break;
        }
    }
}

void verif_kitchen_func(std::vector<int> *cook_array, std::string *running)
{
    char buff[100];
    int size;
    Read *read = new Read();

    while ((*running) != "stop") {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        for (std::vector<int>::size_type j = 0; j < (*cook_array).size(); j = j + 6) {
            size = read->my_read((*cook_array)[j + 4], buff, 100);
            buff[size] = '\0';
            if (std::strcmp(buff, "stop") == 0) {
                (*cook_array).erase((*cook_array).begin() + j);
                (*cook_array).erase((*cook_array).begin() + j);
                (*cook_array).erase((*cook_array).begin() + j);
                (*cook_array).erase((*cook_array).begin() + j);
                (*cook_array).erase((*cook_array).begin() + j);
                (*cook_array).erase((*cook_array).begin() + j);
                break;
            }
        }
    }
}

void command(char **av, std::vector<int> *cook_array, std::string *running)
{
    std::regex pattern { R"((((regina|margarita|americana|fantasia) (s|m|l|xl|xxl) (x[1-9][0-9]*); )*((regina|margarita|americana|fantasia) (s|m|l|xl|xxl) (x[1-9][0-9]*)))|(stop)|(status))" };
    std::string command;
    std::ofstream fd;
    std::vector<std::string> command_array;
    Write *write = new Write();

    fd.open("log");
    fd << "####ADDITION####\n";

    std::thread verif_kitchen = std::thread(verif_kitchen_func, cook_array, running);

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "What can we do for you? -> ";
        std::getline(std::cin, command);
        std::cout << "\n";
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (std::cin.eof() == 1) {
            break;
        }
        if (std::regex_match(command, pattern) != 1) {
            std::cout << "Wrong command!\n" << std::endl;
            continue;
        }
        else if (command == "status") {
            for (std::vector<int>::size_type j = 0; j < (*cook_array).size(); j = j + 6) {
                write->my_write((*cook_array)[j + 1], "status\0", 7);
            }
        } else if (command == "stop")
            break;
        else {
            waiting_line(command, &command_array);
            write_in_file(command_array, &fd);
            action(av, &command_array, cook_array);
        }
    }
    for (std::vector<int>::size_type j = 0; j < (*cook_array).size(); j = j + 6) {
        write->my_write((*cook_array)[j + 1], "end\0", 4);
    }
    (*running) = "stop";
    verif_kitchen.join();
    fd.close();
    print_file("log");
}

int error_management(int ac, char **av)
{
    std::regex pattern { R"((( ./plazza )(([1-9][0-9]*(\.[0-9]+)?)|([0-9]+\.[0-9]+)) [1-9][0-9]* [1-9][0-9]*)|( ./plazza -h))" };
    std::string string;

    for (int i = 0; av[i] != NULL; i++)
        string = string + " " + av[i];
    if (std::regex_match(string, pattern) != 1)
        return (84);
    if (strcmp(av[1], "-h") == 0 && ac == 2)
        return (1);
    if (ac < 4 || ac > 4)
        return (84);
    return (0);
}

void print_helper()
{
    std::cout << "USAGE\n";
    std::cout << "\t./plazza [multiplier] [nb_cooks] [increment_time]\n\n";
    std::cout << "DESCRIPTION\n";
    std::cout << "\tmultiplier\tmultiplier for cooking time\n";
    std::cout << "\tnb_cooks\tnumber of cooks per kitchen\n";
    std::cout << "\tincrement_time\ttime inverval for ingredients incrementation\n\n";
    std::cout << "COMMANDS\n";
    std::cout << "\torder\texample: regina XXL x2; fantasia M x3; margarita S x1\n";
    std::cout << "\tstatus\tprinting orders in each kitchen and ingredients remaining\n";
    std::cout << "\tstop\tquitting the program\n";
}

int main(int ac, char **av)
{
    int error = error_management(ac, av);
    std::vector<int> cook_array;
    std::string running = "going";

    if (error == 84)
        return (84);
    if (error == 1) {
        print_helper();
        return (0);
    }
    command(av, &cook_array, &running);
    return (0);
}