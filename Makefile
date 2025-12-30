CYPHARE := cyphare.elf
CC := pcc
CFLAGS := -std=c99 -O3 -g -Wc,-Werror=implicit-function-declaration,-Werror=missing-prototypes,-Werror=pointer-sign,-Werror=sign-compare,-Werror=strict-prototypes,-Werror=shadow
#CFLAGS_PIC := -shared -fPIC 

SRC_DIR := source
INC_DIR := include
BIN_DIR := binary
LIB_DIR := library
LIBRUFSHARE_HDR := include/librufshare

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
HDR_FILES := $(wildcard $(INC_DIR)/*.h, $(INC_DIR)/utils/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

LIB_FLAGS := -Wl,--library-path=$(LIB_DIR),-rpath=$(LIB_DIR)

INCLUDE_FLAGS := -I$(INC_DIR) -I$(LIBRUFSHARE_HDR)

LIBRUFSHARE := $(LIB_DIR)/librufshare.so

POINTER_SYM := "\e[91m->\e[0m"

$(CYPHARE) : $(OBJ_FILES) $(LIBRUFSHARE) $(HDR_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[96mlinking modules into" $@ "\e[0m"
	$(CC) $(CFLAGS) -o $@ $(LIBRUFSHARE) $(OBJ_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[93mstrip" $@ "\e[0m"
	#@strip $@

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h $(HDR_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[93mcompiling module" $< "\e[0m"
	$(CC) -c $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $<

clean :
	rm $(wildcard $(BIN_DIR)/*.o) $(CYPHARE)

clear : clean
