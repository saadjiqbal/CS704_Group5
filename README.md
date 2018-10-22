# CS704 Project 2
---

### Authors:
Saad Iqbal
Abdul Baseer Syed
Sharsha Thota
---

### Directory Layout:
After cloning the repository, the directory structure will look like the following:

```
CS704_Group5/
|----README.md
|----csvParser/
|--------main.py
|--------Project_2_beacon_locations.csv
|----pythonGUI/
|--------csvParser.py
|--------pythonGUI.py
|--------Project_2_beacon_locations.csv
|----matrixCalculations/
|--------main.c
|----SimplicityCode/
|--------BASE.zip/
|--------MOBILE.zip/
```
---

### HOW TO RUN:
##### Finding the COM port:
1. Open the start menu and search for device manager
2. Scroll down until you see the dropdown for `Ports(COM & LPT)`
3. In this menu you should see an entry labelled as: `JLink CDC UART Port (COM#)`. The COM number will be different on each device, in our case the COM number was 3, hence why we have used 3 in our code and our terminal.

---
##### Simplicity Code:
Insie the `SimplicityCode` folder, you'll find a `BASE.zip` and a `MOBILE.zip`. These compressed folders contain all the project files, however, we couldn't figure out how to import or export projects in Simplicity. So our suggestion would be to create a new project and copy over the contents of the main.c file.

For the Mobile Station, the project has additional settings through "#define" found at the top of the "main.c" file. There are two methods of calculating distance of mobile station from beacons using RSSI. However, this is prone to causing a crash in the program. To turn this off, change the value of the "DIST_METHOD" define to 0. Turns off distance prints. To use method one, change the value of the "DIST_METHOD" define to 1. Prints distance. To use method two, change the value of the "DIST_METHOD" define to 2. Prints distance. To initialise the external accelerometer and magnetometer sensors, change the value of the "PRINT_I2C" define to 1. Prints success/fail information.
			
For the Base Station, this project does not have any special settings. It prints out the value sent from the mobile station over bluetooth to the base station.
	
The projects need to be built, and for this we would suggest following the instructions in the Simplicity lab document, however, the one difference would be to copy over the contents of the main.c file from the project that you would like to build. After building both projects, connect the mobile station (The board with external accelerometer and magnetometer sensors) to the computer, then start debugging. By the instructions stated above, determine the COM port of the board and make note of it. Once the board has been programmed, terminate the debugger, and disconnect the mobile station.
	
Next, connect the base station (The board without an external accelerometer and magnetometer sensor) to the computer, then start debugging. Once again, using the instructions above, determine the COM port of the board and make note of it. Once the board has been programmed, terminate the debugger, and disconnect the base station.
	
Open a terminal program such as Putty and configure it with the following settings:
* Baudrate `115200`.
* `8` data bits.
* `1` stop bit.
* No parity bit.
* No flow control.
* Implicit CR in every LF.
* Port value set as one of the COM ports of the board you wish to read.
	
Connect the mobile station to the computer first, then the base station. These two have been flashed with their logic, so the debugger isn't necessary. The terminal program should now print out data as selected by the user.

---

##### Matrix Calculation:
Insie the `matrixCalculation` folder, you'll find a `main.c` file. This file can be run on any IDE with a C compiler or online. We used [Reply](http://repl.it) as it was easier for us.

The calculations in the `main.c` script have been based off the `Basic Positioning Techniques` reading provided to us on Canvas. The test cases and values are also based off the reading. When the script is run, it'll keep printint the current location estimate until our correction vector is less than `0.01` in both x and y directions. 

For all test cases, the algorithm seems to work fine.

---

##### Python GUI:
Inside the `pythonGUI` folder, you'll find `csvParser.py`, `pythonGUI.py` and `Project_2_beacon_locations.csv`.

To run the GUI, you first have to connect your mobile station to some power source and your base station to your computer. The `csvParser.py` script takes in a csv file and converts into a txt file where the first 20 lines are x coordinates, the second 20 lines are y coordinates and the third 20 lines are z coordinates. Because the GUI is 2D, we ignore the last 20 lines. These coordinates will be stored into a `coordinates.txt` that gets generated automatically when the script is run. For simplicity purposes, we've provided the beacon locations given to us.

Once you've run that script, open up command prompt and run the following command:

```
pip install --user pyserial
```

The `pythonGUI` script reads the serial data being sent by the base station. The module `pyserial` allows us to do this. The `--user` allows you to install the module for your own user only. Once the module has been downloaded, make sure your `COM` port is set correctly in the code looking at the instructions provided above. When you are sure that everything is correct, run the script and you'll see a window open with a simple room map.

The dark grey rectangles on the map, two of them to be precise, represent inaccessible areas in the room. The small green squares represent the beacons. The red circle represents the person.

The map has been scaled down by 5 and is inverted in comparison to the map that was given to us i.e. (0, 0) on the gui represents (0, 1900) on the given map and (1057, 1900) on the gui represents (1057, 0) on the given map.

Because we haven't done localistaion, the mobile station currently only sends the index value of the beacon that it received an update from.

---

##### CSV Parser:
Inside the `csvParser` folder, you'll find `main.py` and `Project_2_beacon_locations.csv`. This csv parser is different to the one used in the Python GUI script. In this csvParser, we print out c code that we can copy paste into our `main.c` to store beacon locations rather than hardcoding the values. For simplicity purposes, we've provided the beacon locations given to us.

### Testing:
Unfortunately, due to some errors and bugs, we could not get our localisation working. We have included all the source code, including our matrix multiplication which is a major part of our localisation calculations.

Even with fixed size matrices, the program would not run and crash, and we couldn't figure out where this was. The matrix multiplication can be run and tested to see that our logic is in fact correct, but there is some error in our implementation.





HOW TO RUN:

	
	Finally, run the <>.py script to view the GUI.