# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 17:04:35 by uisroilo          #+#    #+#              #
#    Updated: 2023/03/29 09:20:03 by uisroilo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv
CXX		=	c++
CPPFLAGS	=	-std=c++98 -Wall -Wextra -Werror

SRCS	=	main.cpp srcs/InitialParse.cpp srcs/Server.cpp srcs/CommandParse.cpp\
 			srcs/Users.cpp srcs/Printing.cpp srcs/ServerUtils.cpp

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