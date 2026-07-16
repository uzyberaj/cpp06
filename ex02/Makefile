# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/16 16:54:09 by ulyssezyber       #+#    #+#              #
#    Updated: 2026/07/16 16:54:10 by ulyssezyber      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= identify

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRC			= main.cpp Base.cpp identify.cpp
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
