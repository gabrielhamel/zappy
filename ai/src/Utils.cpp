/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Utils
*/

#include "Utils.hpp"

std::vector<std::string> Utils::split(std::string str, const std::string &delimiter)
{
    std::size_t pos = 0;
    std::string token;
    std::vector<std::string> vector;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        if (token != "")
            vector.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    if (str != "")
        vector.push_back(str);
    return (vector);
}

std::vector<std::vector<std::string>> Utils::extract(const std::string &str)
{
    auto first = split(str, "\n");
    std::vector<std::vector<std::string>> second;

    for (auto i : first)
        second.push_back(split(i, " "));
    return (second);
}