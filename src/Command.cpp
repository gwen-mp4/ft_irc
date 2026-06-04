/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:15:59 by gwen              #+#    #+#             */
/*   Updated: 2026/06/01 16:13:39 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Command.hpp"

Command::Command() : _prefix(""), _command("") {}

Command::Command(const Command &other) {
	*this = other;
}

Command &Command::operator=(const Command &other) {
	if (this != &other) {
		this->_prefix = other._prefix;
		this->_command = other._command;
		this->_params = other._params;
	}
	return *this;
}

Command::~Command() {}

void	Command::sanitizeLine(std::string line) {
	if (!line.empty() && line.size() - 1 == '\n')
		line.erase(line.size() - 1);
	if (!line.empty() && line.size() - 1 == '\r')
		line.erase(line.size() - 1);
}

void Command::parseCmd(std::string line) {
	size_t	pos = 0;

	sanitizeLine(line);
	if (line.empty() || line.find_first_not_of(" \r\n") == std::string::npos)
		return ;
	
	// For prefix (optional) that starts with ':'
	if (!line.empty() && line.at(0) == ':') {
		size_t	space = line.find(' ');
		if (space != std::string::npos) {
			_prefix = line.substr(pos + 1, space - 1);
			pos = space + 1;
		}
	}
	
	while (pos < line.size() && line.at(pos) == ' ') pos++;

	// Command (e.g. NICK, PASS, USER etc)
	size_t	space = line.find(' ', pos);
	if (space == std::string::npos) {
		_command = line.substr(pos);
		pos = line.size();
	}
	else {
		_command = line.substr(pos, space - pos);
		pos = space + 1;
	}

	// Parameters
	while (pos < line.size()) {
		while (pos < line.size() && line.at(pos) == ' ') pos++;
		if (pos >= line.size()) break ;
		if (line.at(pos) == ':') {
			_params.push_back(line.substr(pos + 1));
			break ;
		}
		size_t	next_space = line.find(' ', pos);
		if (next_space == std::string::npos) {
			_params.push_back(line.substr(pos));
			break ;
		}
		else {
			_params.push_back(line.substr(pos, next_space - pos));
			pos = next_space + 1;
		}
	}

	// // DEBUG
	// std::cout << "PREFIX : [" << _prefix << "]\n";
	// std::cout << "CMD : [" << _command << "]\n";
	// std::cout << "NB ARGS: " << _params.size() << "\n";
	// for (size_t i = 0; i < _params.size(); ++i) {
	// 	std::cout << "Arg " << i << ": [" << _params.at(i) << "]\n";
	// }
}

std::string Command::getPrefix() const {
	return _prefix;
}

// For error
std::string	Command::getCommand() const {
	return _command;
}

std::string Command::	getCommandUpcase() const {
    std::string uppercaseCommand = _command;
    std::transform(uppercaseCommand.begin(), uppercaseCommand.end(), uppercaseCommand.begin(), ::toupper);
	return uppercaseCommand;
}

std::vector<std::string> Command::getParams() const {
	return _params;
}

// int	main(int ac, char **av) {
// 	if (ac != 1)
// 		return 1;
// 	(void) av;
// 	std::string	line;
// 	while (std::getline(std::cin, line)) {
// 			if (line.empty()) {
// 				std::cout << "> ";
// 				continue ;
// 		}
// 	}
// 	return 0;
// }
