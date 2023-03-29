
NAME			=	PmergeMe

CC				=	c++

CFLAGS			=	-Wall -Wextra -Werror -std=c++98

SRC				=	main.cpp PmergeMe.cpp 

HEADERS			=	PmergeMe.hpp

OBJDIR			=	obj

OBJS			=	$(addprefix $(OBJDIR)/,$(SRC:%.cpp=%.o))

RED				=	\033[41m
GREEN			=	\033[42m
NC				=	\033[0m

all				:	$(NAME)

$(OBJDIR)/%.o	:	%.cpp $(HEADERS) | $(OBJDIR)
					@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)		:	
					@mkdir $(OBJDIR)

$(NAME)			:	$(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
					@echo "${GREEN}Making ............[OK]${NC}"


clean			:
					@rm -rf $(OBJDIR)
					@echo "${RED}Removing Objects...[OK]${NC}" 

fclean			:	clean
					@rm -rf $(NAME)
					@echo "${RED}Removing All.......[OK]${NC}" 

re				:	fclean all
