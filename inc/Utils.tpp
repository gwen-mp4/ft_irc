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

#endif