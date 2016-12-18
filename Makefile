SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
BIN=$(BIN_DIR)/$(if $(DEBUG),automountdbg.exe,automount.exe)

SRC=$(wildcard $(SRC_DIR)/*.cc)
OBJ=$(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC:.cc=.o)) 

INCS=-I./include
CFLAGS=-O2 ${INCS} $(if $(DEBUG),-DDEBUG=1)
CXXFLAGS=$(CFLAGS)
LDFLAGS=

ARCH=arm-mingw32ce
CC=${ARCH}-gcc ${CFLAGS}
CXX=${ARCH}-g++
MAKE=make
WINDRES=${ARCH}-windres

all: clean build

build: dir $(OBJ) $(BIN)

dir:
	mkdir -p $(BIN_DIR) $(OBJ_DIR) 

$(BIN): $(OBJ)
	${CXX} ${LDFLAGS} $? -o $@ 

$(OBJ): 
	${CXX} ${CXXFLAGS} -c $(SRC_DIR)/$(notdir $(@:.o=.cc)) -o $@ 

clean:
	rm -rf $(BIN) $(OBJ_DIR)/*.o

test: 
	${MAKE} DEBUG=1
	