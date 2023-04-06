/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 06:34:09 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/06 08:01:47 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

#define SERVER_NAME "localhost"

#define ERR_NEEDMOREPARAMS(servername, client, command) \
(":" + servername + " 461 * " + client + " " + command + " :Not enough parameters\n")

#define ERR_NOSUCHSERVER(servername, client) \
(": ERROR  :No such server " + servername + "\n")

#define ERR_NOSUCHNICK(servername, nick, client) \
(":" + servername + " 401 * " + nick + " " + client + " :No such nick\n")

#define ERR_ALREADYREGISTERED(servername, nickname) \
(":" + servername + " 461 * " + nickname + " " + " :You may not reregister\n")

#define ERR_NICKNAMEINUSE(servername, nickname) \
(":" + servername + " 433 " + nickname + " " + " :Nickname is already in use\r\n")

#define ERR_ERRONEUSNICKNAME(servername, nickname) \
(":" + servername + " 432 " + nickname + " " + " :Erroneus nickname\r\n")

#define ERR_NOOPERHOST(servername, nickname) \
(":" + servername + " 491 " + nickname + " :Invalid oper credentials\r\n")

#define RPL_YOUREOPER(servername, nickname) \
(":" + servername + " 381 " + nickname + " :You are now an IRC operator\r\n")

#define ERR_NOPRIVILEGES(servername, nickname) \
(":" + servername + " 481 " + nickname + " :Permission Denied- You're not an IRC operator\r\n")

# define ERR_PASSWDMISMATCH ":Password incorrect\r\n"
# define CMD_PASS_ERR "Typing PASS invalid or check your password\r\n"
// # define ERR_NICKNAMEINUSE " :Nickname is already in use\r\n"
# define RAND_ERR "As second input it must 'NICK nickname\r\n'"
# define ERR_ERRONEUSUSERNAME "Erroneus nickname\r\n"

#define ERR_NONICKNAMEGIVEN(servername, nickname) \
(":" + servername + " 431 " + nickname + " :No nickname given\n")

// #define RPL_KILL(operator, murderer, message) \
// (":" + operator + " Killed " + murderer + " " + message + "\n")

#define RPL_KILL(servername, nickname, comment) \
(":" + servername + " 1 " + " KILL " + nickname + " :KILL from operator " + "(" + comment +")\n")

#define RPL_SQUIT(servername, nickname, comment) \
("ERROR :Closing link: " + servername + " (SERVER QUIT (" + comment + "))" "\n")

#define ERROR(servername, nickname, comment) \
("ERROR :Closing link: (~" + nickname + "@" + servername + ") " + "[Quit " + comment +"]\r\n")

#define ERR_BADCHANMASK(servername, nickname, wrongChannel) \
(":" + servername + " 476 " + nickname + " " + wrongChannel + ":Invalid channel name\r\n")

#define REP_CHAN_SUCCESS(servername, nickname, channel) \
(":" + nickname + "!~" + nickname + "@" + servername + " JOIN :" + channel + "\r\n")


#define RPL_PRIVMSG(sender, recipient, message) \
(":" + sender + " PRIVMSG " + recipient + " " + message + "\n")

#endif