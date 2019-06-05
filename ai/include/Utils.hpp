/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Utils
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace Utils {

    std::vector<std::string> split(std::string str, const std::string &delimiter);
    std::vector<std::vector<std::string>>extract(const std::string &str);

}