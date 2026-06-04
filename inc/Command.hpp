/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:16:12 by gwen              #+#    #+#             */
/*   Updated: 2026/06/01 16:13:02 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Include.hpp"

class Command {
	private:
		std::string	_prefix;
		std::string	_command;
		std::vector<std::string>	_params;

	public:
		Command();
		Command(const Command& other);
		Command& operator=(const Command& other);
		~Command();

		void	sanitizeLine(std::string & line);
		void	parseCmd(std::string line);

		std::string	getPrefix() const;
		std::string	getCommand() const;
		std::string	getCommandUpcase() const;
		std::vector<std::string>	getParams() const;
};

#endif
