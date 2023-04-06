# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 17:04:35 by uisroilo          #+#    #+#              #
#    Updated: 2023/04/04 17:59:34 by uisroilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv
CXX		=	c++
CPPFLAGS	=	-std=c++98 -Wall -Wextra -Werror

SRCS	=	main.cpp srcs/InitialParse.cpp srcs/Server.cpp srcs/CommandParse.cpp\
 			srcs/Users.cpp srcs/Printing.cpp srcs/ServerUtils.cpp srcs/CommandParseUtils.cpp\
			srcs/cmd_NICK.cpp srcs/cmd_OPER.cpp srcs/cmd_PASS.cpp srcs/cmd_USER.cpp\
			srcs/cmd_KILL.cpp srcs/cmd_QUIT.cpp srcs/cmd_SQUIT.cpp srcs/cmd_JOIN.cpp\
			srcs/Channels.cpp

OBJ = $(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean	:
		@ rm -rf $(OBJ)

fclean 	:	clean
		@ rm -f $(NAME)

re 		: 	fclean all

.PHONY	:	all clean fclean re