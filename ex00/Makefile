# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/16 16:52:28 by ulyssezyber       #+#    #+#              #
#    Updated: 2026/07/16 16:52:29 by ulyssezyber      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= convert

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRC			= main.cpp ScalarConverter.cpp
OBJ			= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
