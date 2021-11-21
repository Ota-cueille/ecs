## VARIABLES ##
CC = gcc
EXEC = program

# Configuration
RELEASE_DIR = release
RELEASE_EXEC = $(RELEASE_DIR)/$(EXEC)
DEBUG_DIR = debug
DEBUG_EXEC = $(DEBUG_DIR)/$(addsuffix -debug, $(EXEC))

# DIRECTORIES
ifndef SRC
	SRC = src/main.c
endif

# DEPENDENCIES
INCLUDE_DIR = -I include
RELEASE_OBJS_DIR = $(RELEASE_DIR)/OBJ
DEBUG_OBJS_DIR = $(DEBUG_DIR)/OBJ

DEBUG_FLAGS = -g
CC_FLAGS = -static -static-libgcc

LIBS=

## MAKEFILE TARGETS ##

all: debug release
re: clean debug release
rer: cleanr release
red: cleand  debug

exe:
	@./$(RELEASE_EXEC)

# Release
release: $(RELEASE_EXEC)

$(RELEASE_EXEC):
	@for file in $(SRC) ; do \
        make --no-print-directory compile_release SRC=$$file ; \
    done
	$(CC) -o $@ $(RELEASE_OBJS_DIR)/*.o $(CC_FLAGS) $(LIBS)

COMPILE_RELEASE = $(SRC:$(SRC)=$(RELEASE_OBJS_DIR)/$(patsubst %.cpp,%.o,$(lastword $(subst /, ,$(SRC)))))

compile_release: $(COMPILE_RELEASE)

$(RELEASE_OBJS_DIR)/%.o:$(SRC)
	$(CC) -o $@ -c $< $(INCLUDE_DIR) $(CC_FLAGS) $(LIBS)

# Debug
debug: $(DEBUG_EXEC)

$(DEBUG_EXEC):
	@for file in $(SRC) ; do \
        make --no-print-directory compile_debug SRC=$$file ; \
    done
	$(CC) -o $@ $(DEBUG_OBJS_DIR)/*.o $(CC_FLAGS) $(LIBS)

COMPILE_DEBUG = $(SRC:$(SRC)=$(DEBUG_OBJS_DIR)/$(patsubst %.cpp,%.o,$(lastword $(subst /, ,$(SRC)))))

compile_debug: $(COMPILE_DEBUG)

$(DEBUG_OBJS_DIR)/%.o:$(SRC)
	$(CC) $(DEBUG_FLAGS) -o $@ -c $< $(INCLUDE_DIR) $(CC_FLAGS) $(LIBS)

# Delete directories
delete: deleter deleted

deleter:
	rm -r $(RELEASE_DIR)

deleted:
	rm -r $(DEBUG_DIR)

# Clean files
clean: cleanr cleand

cleanr:
	rm -rf $(RELEASE_DIR)/*.exe
	rm -rf $(RELEASE_OBJS_DIR)/*.o

cleand:
	rm -rf $(DEBUG_DIR)/*.exe
	rm -rf $(DEBUG_OBJS_DIR)/*.o

# Todo only once to make folders
prep:
	mkdir include | mkdir src | touch src/main.c
	mkdir $(DEBUG_DIR) | mkdir $(RELEASE_DIR)
	mkdir $(DEBUG_DIR)/OBJ | mkdir $(RELEASE_DIR)/OBJ

.PHONY: exe clean