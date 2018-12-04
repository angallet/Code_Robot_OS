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
SOURCE_DIR = ./source
IP_ADDRESS = 192.168.137.3

#here all the file we have to use to compile the program
OBJS = \
	$(BUILD_DIR)/main.o \
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

docker:
	docker run --rm -it -h ev3 -v ~/OS_Rover_APA/:/src -w /src ev3cc /bin/bash

install-shared:
	cd ev3dev-c/source/ev3/&&make&&sudo make install&&make shared&&sudo make shared-install

send:
	scp main robot@$(IP_ADDRESS):

clean:
	rm -rf *.o
	rm ./main
