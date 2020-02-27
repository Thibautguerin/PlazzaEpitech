/*
** EPITECH PROJECT, 2019
** Reception.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include "Write.hpp"
#include "Read.hpp"
#include <vector>
#include "Pipe.hpp"
#include "Reception.hpp"
#include "Cook.hpp"
#include <thread>
#include <chrono>

void make_regina(char **av, int size, Cook *cook, int *nb_cooker)
{
    cook->makeRegina(av, size, nb_cooker);
}

void make_margarita(char **av, int size, Cook *cook, int *nb_cooker)
{
    cook->makeMargarita(av, size, nb_cooker);
}

void make_americana(char **av, int size, Cook *cook, int *nb_cooker)
{
    cook->makeAmericana(av, size, nb_cooker);
}

void make_fantasia(char **av, int size, Cook *cook, int *nb_cooker)
{
    cook->makeFantasia(av, size, nb_cooker);
}

std::vector<int> match_name(std::string command)
{
    std::vector<std::string> res;
    std::stringstream ss(command);
    std::string tok;
    std::vector<int> tmp;
    int num;

    while(getline(ss, tok, ' ')) {
        res.push_back(tok);
    }
    for (std::vector<int>::size_type i = 0; i < res.size(); i++) {
        if (std::strcmp(res[i].c_str(), "regina") == 0)
            res[i] = "1";
        else if (std::strcmp(res[i].c_str(), "margarita") == 0)
            res[i] = "2";
        else if (std::strcmp(res[i].c_str(), "americana") == 0)
            res[i] = "4";
        else if (std::strcmp(res[i].c_str(), "fantasia") == 0)
            res[i] = "8";
        else if (std::strcmp(res[i].c_str(), "s") == 0)
            res[i] = "1";
        else if (std::strcmp(res[i].c_str(), "m") == 0)
            res[i] = "2";
        else if (std::strcmp(res[i].c_str(), "l") == 0)
            res[i] = "4";
        else if (std::strcmp(res[i].c_str(), "xl") == 0)
            res[i] = "8";
        else if (std::strcmp(res[i].c_str(), "xxl") == 0)
            res[i] = "16";
    }
    for (std::vector<int>::size_type i = 0; i < res.size(); i++) {
        num = std::stoi(res[i]);
        tmp.push_back(num);
    }
    return (tmp);
}

void verif_command(std::time_t *time, std::string *command, Cook *cook)
{
    while ((*command) != "end") {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if ((*cook).getNbCommand() != 0)
            (*time) = std::time(nullptr) + 5;
    }
}

void timer(std::time_t *time, std::string *running, std::vector<int> *cook_array, int i)
{
    Write *write = new Write();
    while (std::time(nullptr) < (*time)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        write->my_write((*cook_array)[i + 5], "going", 5);
    }
    (*running) = "ko";
    write->my_write((*cook_array)[i + 1], "end\0", 4);
    write->my_write((*cook_array)[i + 5], "stop", 4);
}

void increment_ingrdt(Cook *cook, std::string *running, char **av)
{
    while ((*running) != "ko") {
        cook->incrementTime(av);
    }
}

void cooker_management(Cook *cook, std::string *running, char **av)
{
    std::vector<int> param;
    std::vector<std::thread> tab;
    int nb_cooker = 0;

    while ((*running) != "ko") {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (cook->getNbCommand() != 0) {
            param = match_name(cook->_command[0]);
            if (param[0] == 1 && nb_cooker < cook->getNbCooker() && cook->getDoe() >= param[1] && cook->getTomato() >= param[1] && cook->getGruyere() >= param[1] && cook->getHam() >= param[1] && cook->getMushrooms() >= param[1]) {
                tab.push_back(std::thread(make_regina, av, param[1], cook, &nb_cooker));
            } else if (param[0] == 2 && nb_cooker < cook->getNbCooker() && cook->getDoe() >= param[1] && cook->getTomato() >= param[1] && cook->getGruyere() >= param[1]) {
                tab.push_back(std::thread(make_margarita, av, param[1], cook, &nb_cooker));
            } else if (param[0] == 4 && nb_cooker < cook->getNbCooker() && cook->getDoe() >= param[1] && cook->getTomato() >= param[1] && cook->getGruyere() >= param[1] && cook->getSteak() >= param[1]) {
                tab.push_back(std::thread(make_americana, av, param[1], cook, &nb_cooker));
            } else if (param[0] == 8 && nb_cooker < cook->getNbCooker() && cook->getDoe() >= param[1] && cook->getTomato() >= param[1] && cook->getEggplant() >= param[1] && cook->getGoatcheese() >= param[1]) {
                tab.push_back(std::thread(make_fantasia, av, param[1], cook, &nb_cooker));
            } else {
                cook->addCommand(cook->_command[0]);
                cook->_command.erase(cook->_command.begin());
            }
        }
    }
    for (std::vector<int>::size_type i = 0; i < tab.size(); i++)
        tab[i].join();
}

void child(char **av, std::vector<int> *cook_array, int i, std::string *command)
{
    Cook *cook = new Cook(av);
    char buffer[100];
    std::string buff;
    std::stringstream temp;
    const char *get_place;
    Write *write = new Write();
    Read *read = new Read();

    int size;

    std::time_t time = std::time(nullptr) + 5;
    std::string running = "ok";

    std::thread running_t = std::thread(timer ,&time, &running, cook_array, i);
    std::thread running_verif = std::thread(verif_command ,&time, command, cook);

    std::thread increment_ingredient = std::thread(increment_ingrdt, cook, &running, av);

    std::thread cooker = std::thread(cooker_management, cook, &running, av);

    while (1) {
        size = read->my_read((*cook_array)[i], buffer, 100);
        buffer[size] = '\0';
        if (std::strcmp(buffer, "end\0") == 0 || running == "ko") {
            break;
        }
        if (std::strcmp(buffer, "status\0") == 0) {
            cook->displayCommand(i);
            continue;
        }
        if (std::strcmp(buffer, "get_place\0") == 0) {
            get_place = cook->getPlace(av);
            write->my_write((*cook_array)[i + 3], get_place, std::strlen(get_place));
            continue;
        }
        if (cook->getNbCommand() < std::stol(av[2], nullptr, 0) * 2) {
            (*command) = "ok";
            buff = buffer;
            cook->addCommand(buff);
            write->my_write((*cook_array)[i + 3], "yes\0", 4);
        } else
            write->my_write((*cook_array)[i + 3], "no\0", 3);
    }
    (*command) = "end";
    increment_ingredient.join();
    running_t.join();
    cooker.join();
    running_verif.join();
    exit(0);
}

int add_new_cook(char **av, std::vector<int> *cook_array)
{
    pid_t pid;
    Pipe *pipe = new Pipe();
    std::string command = "ok";

    pipe->my_pipe(cook_array);
    pid = fork();
    if (pid == -1)
        return (84);
    else if (pid == 0)
        child(av, cook_array, (*cook_array).size() - 6, &command);
    return (0);
}
