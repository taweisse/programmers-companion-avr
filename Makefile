SRC_DIR := $(CURDIR)/src
TEST_DIR := $(CURDIR)/test
BUILD_DIR := $(CURDIR)/build

SOURCES := $(shell find $(SRC_DIR) -name '*.c')
BIN_NAME := program

pre-build:
	mkdir -p $(BUILD_DIR)

main-build: pre-build
	gcc $(SOURCES) -o $(BUILD_DIR)/$(BIN_NAME)

post-build: main-build

.PHONY:
all: post-build

.PHONY:
clean:
	rm -rf $(BUILD_DIR)
