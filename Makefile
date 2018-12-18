# The structure of the project is :
# 	root/
#		Makefile (this file)
#		ev3dev-c/
#		libraries/
#			libbluetooth.a
#			libev2dev-c.a
#		include/
#			*.h
#		source/
#			*.c

CC         =arm-linux-gnueabi-gcc
CFLAGS     =-O2 -std=gnu99 -W -Wall -Wno-comment -g
INCLUDES   =-I./ev3dev-c/source/ev3 -I./include/
LDFLAGS    =-lm -lev3dev-c -L./libraries -lrt -lpthread #-lbluetooth
BUILD_DIR  = ./build
BUILD_DIR_THROW =./build_throw
SOURCE_DIR = ./source
IP        ?= 192.168.137.3 # the IP can be override by the user with the use of argument make send IP=X.X.X.X

#here all the file we have to use to compile the program
OBJS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/motors.o \

OBJS_THROW = \
	$(BUILD_DIR)/main_throw.o \
	$(BUILD_DIR)/motors.o \

all: main

main: ${OBJS}
	$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(LDFLAGS) -o main

$(OBJS): $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)


# create all the .o file from the .c file
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c $(SOURCE_DIR)/$*.c $(INCLUDES) -o $(BUILD_DIR)/$*.o

throw: main_throw

main_throw: ${OBJS_THROW}
	$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(LDFLAGS) -o main_throw

$(OBJS_THROW): $(BUILD_DIR_THROW)

$(BUILD_DIR_THROW):
	mkdir $(BUILD_DIR_THROW)

$(BUILD_DIR_THROW)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c $(SOURCE_DIR)/$*.c $(INCLUDES) -o $(BUILD_DIR_THROW)/$*.o

docker:
	docker run --rm -it -h ev3 -v ~/OS_Rover_APA/:/src -w /src ev3cc /bin/bash

install-shared:
	cd ev3dev-c/source/ev3/&&make&&sudo make install&&make shared&&sudo make shared-install

send:
	scp main robot@$(IP):

clean:
	rm -rf *.o
	rm ./main
