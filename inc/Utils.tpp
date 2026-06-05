#ifndef UTILS_TPP
# define UTILS_TPP

#include "Server.hpp"

template <typename T>
std::string Server::ft_itoa(T num) const {
    double n = static_cast<double>(num);
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

template <typename Container>
Container Server::ft_split(const std::string& str, char delimiter) const {
    Container result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
            result.push_back(token);
    }

    return result;
}

#endif