# Ben Rohman, benrohman3@gmail.com

# compiler and flags
CXX := g++
DEBUG := -g -O0
CXXFLAGS := $(DEBUG) -Wall -Werror -std=c++17 -Ibackend/include -Ifrontend/include

# directories
B_SRC := backend/src
B_INC := backend/include
BACK := $(B_SRC) $(B_INC)
F_SRC := frontend/src
F_INC := frontend/include
FRONT := $(F_SRC) $(F_INC)
SRC_DIRS := $(B_SRC) $(F_SRC)
ALL_CODE := $(FRONT) $(BACK) main.cpp
OBJ := obj
B_OBJ := $(OBJ)/backend
F_OBJ := $(OBJ)/frontend

# executeable -- output name
BIN := game

# find all .cpp files and build object file paths
B_FILES := $(wildcard $(B_SRC)/*.cpp)
F_FILES := $(wildcard $(F_SRC)/*.cpp)
SRCS := $(B_FILES) $(F_FILES) main.cpp

# map source files to object files
BOBJ := $(patsubst $(B_SRC)/%.cpp, $(B_OBJ)/%.o, $(B_FILES))
FOBJ := $(patsubst $(F_SRC)/%.cpp, $(F_OBJ)/%.o, $(F_FILES))
M_OBJ := $(OBJ)/main.o
OBJ_FILES := $(BOBJ) $(FOBJ) $(M_OBJ)

# default rule
all: $(BIN)

# link final executable
$(BIN): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# compile rules
$(B_OBJ)/%.o: $(B_SRC)/%.cpp | $(B_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(F_OBJ)/%.o : $(F_SRC)/%.cpp | $(F_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)/main.o: main.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# make object directories so cleaning up is easier
$(B_OBJ):
	mkdir -p $(B_OBJ)

$(F_OBJ):
	mkdir -p $(F_OBJ)

$(OBJ):
	mkdir -p $(OBJ)

#clean up
clean: 
	rm -rf $(OBJ) $(BIN)

#revision control
#	RCS = "Revision Control System": same as github but UNIX based
ci:
	if [ ! -d RCS ] ; then mkdir RCS; fi
	ci -t-none -m "$$(basename $$PWD) - $$(date '+%Y-%m-%d %H:%M:%S')" -l $(ALL_CODE)

git:
	if [ ! -d .git ] ; then git init; fi
	git add $(ALL_CODE) ?akefile
	git commit -m "$$(basename $$PWD) - $$(date '+%Y-%m-%d %H:%M:%S')"
.PHONY: all clean
