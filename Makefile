SRC_DIR=./src
OBJ_DIR=./obj
RC_DIR=./rc
BIN_DIR=./bin
BIN=$(BIN_DIR)/$(if $(DEBUG),automountdbg.exe,automount.exe)

SRC=$(wildcard $(SRC_DIR)/*.cc)
OBJ=$(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC:.cc=.o)) 
RC=$(wildcard $(RC_DIR)/*.rc)
RES=$(subst $(RC_DIR)/,$(OBJ_DIR)/,$(RC:.rc=.res)) 

INCS=-I./include
CFLAGS=-O2 ${INCS} $(if $(DEBUG),-DDEBUG=1)
CXXFLAGS=$(CFLAGS)
LDFLAGS=-static -s

ARCH=arm-mingw32ce
CC=${ARCH}-gcc ${CFLAGS}
CXX=${ARCH}-g++
MAKE=make
WINDRES=${ARCH}-windres

all: clean build

build: dir $(OBJ) $(BIN)

dir:
	mkdir -p $(BIN_DIR) $(OBJ_DIR) 

$(BIN): $(OBJ) $(RES)
	${CXX} ${LDFLAGS} $? -o $@ 

$(OBJ): 
	${CXX} ${CXXFLAGS} -c $(SRC_DIR)/$(notdir $(@:.o=.cc)) -o $@ 
	
$(RES): $(RC)
	${WINDRES} $(RC_DIR)/$(notdir $(@:.res=.rc)) -O coff -o $@

clean:
	rm -rf $(BIN) $(OBJ_DIR)/*.o

test: 
	${MAKE} DEBUG=1
	