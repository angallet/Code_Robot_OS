# Projet 2018 LeBot James

Source code of Lebot James

Team members :
Arthur Dion, Antoine Gallet and Paul Monniot


## How to 
First clone our git :
```git clone https://gitlab.eurecom.fr/monniot/OS_Rover_APA.git ```

if you want to compile directly on your robot just execute there :

``` bash
make
```

If your are on your computer and want to use cross compilation execute the folloving step : 

1. Install docker on your system https://docs.docker.com/install/
2. Install the docker to do the cross compilation :
	```bash
	docker pull ev3dev/debian-jessie-cross:latest
	docker tag ev3dev/debian-jessie-cross ev3cc
	```
3. Use it (note that the project have to be running on `~/` to run correctly)
	``` bash
	make docker
	```
4. Configure the docker and compile :
	``` bash
	make install-blue
	make install-shared
	make
	exit
	```
5. Send your program on the robot with : 
	``` bash
	make send 
	```
By default the IP address defined in the Makefile is 192.168.137.3 you have to change it accordingly on the Makefile in order to be able to run the previous command


Note: that you have to install ev3dev-c in order to make the code runnable by executing the following command :
```git clone https://github.com/in4lio/ev3dev-c ```
## Makefile
The option in our Makefile are:
- `main` - make just the main executable
- `throw` - make just the main_throw executable
- `docker` - init the docker the docker have to get the right tag (see section on docker)
- `install-shared` - install the shared librairies on the docker
- `install-blue` - install the bluetooth librairies on the docker
- `send` - send the main exectuble on the robot the IP address of the cible (can be passed as an argument) 
- `connect` - connect to the robot on on the IP address of the cible (can be passed as an argument)
- `clean` - remove all object files and the executable
## Project structure

Our project has the following structure:

- **libraries** _Required libraries (ev3dev-c excluded)_
- **include** _Headers_
- **source** _Source code_
	- **bluetooth.c**
	- **motors** _all the function of movement_
	- main.c _Main source file_
- Makefile

