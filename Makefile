NAME := minishell
COMPILE_FLAGS ?= -Wall -Wextra -Werror
SRC_DIR ?= src
HDR_DIR ?= include
OBJ_DIR ?= obj
LIBS = 
INCLUDE_DIRS := \
	-I "/Users/${USER}/.brew/opt/readline/include/"

LINKING_FLAGS ?= \
	-L "/Users/${USER}/.brew/opt/readline/lib" -lreadline

# All source and header files are in the .mk files
SOURCES :=
include make/sources.mk
HEADERS :=
include make/headers.mk

OBJECTS := $(patsubst %,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

# (0 = no debug)
NOCOLORS ?= 1
DEBUG ?= 0

ifeq ($(DEBUG),1)
	COMPILE_FLAGS += -g -fsanitize=address -D DEBUG=$(DEBUG)
	LINKING_FLAGS += -g -fsanitize=address
endif

ifeq ($(NOCOLORS),1)
	COMPILE_FLAGS += -D NOCOLORS=$(NOCOLORS)
endif

all: $(NAME)

files:
	./make/make_sources.sh

$(NAME): $(LIBS) $(HEADERS) $(OBJECTS)
	@echo "\nLinking files..."
	@$(CC) $(OBJECTS) -o $(NAME) $(LINKING_FLAGS)
	@echo "Done!"

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@echo "Compiling: $@"
	@mkdir -p $(@D)
	@$(CC) $(COMPILE_FLAGS) \
		$(INCLUDE_DIRS) \
		$(patsubst %,-I%,$(dir $(HEADERS))) \
		-c -o $@ $<

clean:
	@echo "Cleaning:"
	@rm -Rf $(OBJ_DIR)/
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Binary cleaned."

re: fclean all

print:
	@echo "---HEADERS: $(HEADERS)" | xargs -n1
	@echo "---SOURCES: $(SOURCES)" | xargs -n1
	@echo "---OBJECTS: $(OBJECTS)" | xargs -n1

run: all
	./$(NAME)

.PHONY: all files clean fclean re print run
