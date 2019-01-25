# Projet 2018 LeBot James

Source code of Lebot James
Team members :
Arthur Dion, Antoine Gallet and Paul Monniot


## How to 
if you want to compile directly on your robot just :
''' bash
make
'''
If your are on your computer and want to use cross compilation execute the folloving step
''' bash
make docker
'''
Inside the docker run :
''' bash
make install-blue
make install-shared
make
exit
'''
and nnow send your program with 
''' bash
make send 
'''
By default the IP address defined in the Makefile is 192.168.137.3 you have to change it accordingly on the Makefile in order to be able to run the previous command


Note: that you have to install ev3dev-c in order to make the code runnable by executing the following command :
'''git clone https://github.com/in4lio/ev3dev-c '''
## Makefile
The option in our Makefile are:
- 'main' - make just the main executable
- 'throw' - make just the main_throw executable
- 'docker' - init the docker the docker have to get the right tag (see section on docker)
- 'install-shared' - install the shared librairies on the docker
- 'install-blue' - install the bluetooth librairies on the docker
- 'send' - send the main exectuble on the robot the IP address of the cible (can be passed as an argument) 
- 'connect' - connect to the robot on on the IP address of the cible (can be passed as an argument)
- 'clean' - remove all object files and the executable
## Project structure

Our project has the following structure:

- **libraries** _Required libraries (ev3dev-c excluded)_
- **include** _Headers_
- **source** _Source code_
	- **bluetooth.c**
	- **motors** _all the function of movement_
	- main.c _Main source file_
- Makefile

