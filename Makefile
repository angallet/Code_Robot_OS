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
CFLAGS     =-O2 -g -std=gnu99 -W -Wall -Wno-comment
INCLUDES   =-I./ev3dev-c/source/ev3 -I./include/
LDFLAGS    =-L.libraries -lrt -lm -lev3dev-c -lpthread -lbluetooth
BUILD_DIR  = ./build
SOURCE_DIR = ./source

#here all the file we have to use to compile the program
OBJS = \
	$(BUILD_DIR)/main.o \

all: main

main: ${OBJS}
	$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(LDFLAGS) -o main

$(OBJS): $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)


# create all the .o file from the .c file
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c $(SOURCE_DIR)/$*.c $(INCLUDES) -o $(BUILD_DIR)/$*.o

clean:
	rm -rf *.o
	rm ./main
