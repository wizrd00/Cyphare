CYPHARE := cyphare.elf
CC ?= pcc

SRC_DIR := source
INC_DIR := include
BIN_DIR := binary
LIB_DIR := library

ifeq ($(CC), pcc)
	CFLAGS := -std=c99 -O3 -Wc,-Werror=implicit-function-declaration,-Werror=missing-prototypes,-Werror=pointer-sign,-Werror=sign-compare,-Werror=strict-prototypes,-Werror=shadow -pthread
	LIBRUFSHARE_OBJ := $(LIB_DIR)/librufshare.so
	LIB_FLAGS := -Wl,--library-path=$(LIB_DIR),-rpath=$(LIB_DIR)
else ifeq ($(CC), gcc)
	CFLAGS := -std=c99 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wcast-align -Wconversion -Wsign-conversion -Wshadow -Wswitch-enum -pthread	
	LIBRUFSHARE_OBJ :=
	LIB_FLAGS := -L$(LIB_DIR) -lrufshare -Wl,-rpath=$(LIB_DIR) 
else
	$(error unsupported compiler : $(CC))
endif
LIBRUFSHARE_HDR := include/librufshare

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
HDR_FILES := $(wildcard $(INC_DIR)/*.h) $(wildcard $(INC_DIR)/utils/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))


INCLUDE_FLAGS := -I$(INC_DIR) -I$(LIBRUFSHARE_HDR)

LIBRUFSHARE := $(LIB_DIR)/librufshare.so

POINTER_SYM := "\e[91m->\e[0m"

$(CYPHARE) : $(BIN_DIR) $(OBJ_FILES) $(LIBRUFSHARE) $(HDR_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[96mlinking modules into" $@ "\e[0m"
	$(CC) $(CFLAGS) -o $@ $(LIBRUFSHARE_OBJ) $(OBJ_FILES) $(LIB_FLAGS)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[93mstrip" $@ "\e[0m"
	@strip $@

$(BIN_DIR) :
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h $(HDR_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[93mcompiling module" $< "\e[0m"
	$(CC) -c $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $<

clean :
	rm $(wildcard $(BIN_DIR)/*.o) $(CYPHARE)

clear : clean
