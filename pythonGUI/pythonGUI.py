# import tkinter 
# import random, serial
from tkinter import *
import random, serial, os

# Dimensions of tkinter canvas
C_HEIGHT = 800
C_WIDTH = 1000

# Dimensions of the room
ROOM_HEIGHT = 1900
ROOM_WIDTH = 1057

# Dimensions of one of the inaccessible areas
AREA_A_HEIGHT = 280
AREA_A_WIDTH = 328

# Dimensions of the second inaccessible area
AREA_B_HEIGHT = 1596
AREA_B_WIDTH = 750

# Scale factor is how much we're scaling down the real space by
# Pixel offset is how many pixels are we offset from the origin 
# Beacon size is how big the beacons are in size 
SCALE_FACTOR = 3
PIXEL_OFFSET = 20
BEACON_SIZE = 10

# If file exists then delete it since we want to append
if os.path.isfile('locationHistory.txt'):
    os.remove('locationHistory.txt')

# Get the list of beacon locations
coordinate_file = open('coordinates.txt', 'r')
coordinate_file_lines = coordinate_file.read().splitlines()
coordinate_file.close()
coordinate_file_lines = list(map(int, coordinate_file_lines))

location_file = open('locationHistory.txt', 'a+')

# Creating the tkinter object
root = Tk()
root.title('Location Tracker')
root.geometry('1000x800')

# Creating the canvas
canvas = Canvas(root, bg='white', height = C_HEIGHT, width = C_WIDTH)
canvas.pack()

# Draw room 
canvas.create_rectangle(PIXEL_OFFSET, PIXEL_OFFSET, (ROOM_WIDTH/SCALE_FACTOR) + PIXEL_OFFSET, (ROOM_HEIGHT/SCALE_FACTOR) + PIXEL_OFFSET)

# Two inaccessible areas
canvas.create_rectangle((AREA_A_WIDTH/SCALE_FACTOR)+PIXEL_OFFSET, (0/SCALE_FACTOR) + PIXEL_OFFSET, (ROOM_WIDTH/SCALE_FACTOR) + PIXEL_OFFSET, (AREA_A_HEIGHT/SCALE_FACTOR) + PIXEL_OFFSET, fill='#c8cbd1')
canvas.create_rectangle((AREA_B_WIDTH/SCALE_FACTOR) + PIXEL_OFFSET, (AREA_B_HEIGHT/SCALE_FACTOR) + PIXEL_OFFSET, (ROOM_WIDTH/SCALE_FACTOR) + PIXEL_OFFSET, (ROOM_HEIGHT/SCALE_FACTOR) + PIXEL_OFFSET, fill='#c8cbd1')

# Spawn beacons
for i in range(20):
    beacon = canvas.create_rectangle(PIXEL_OFFSET, PIXEL_OFFSET, PIXEL_OFFSET+BEACON_SIZE, PIXEL_OFFSET+BEACON_SIZE, fill='green')    
    canvas.coords(beacon, (coordinate_file_lines[i]/SCALE_FACTOR) + PIXEL_OFFSET, (coordinate_file_lines[i+20]/SCALE_FACTOR) + PIXEL_OFFSET, ((coordinate_file_lines[i]+BEACON_SIZE)/SCALE_FACTOR) + PIXEL_OFFSET, ((coordinate_file_lines[i+20] + BEACON_SIZE)/SCALE_FACTOR) + PIXEL_OFFSET)

# Draw person object
person_object = canvas.create_oval(5 + PIXEL_OFFSET, 5 + PIXEL_OFFSET, 10 + PIXEL_OFFSET, 10 + PIXEL_OFFSET, fill='red')

def update():
    # Open a serial connection at COM3 with baudrate of 115200
    # Wait until we receive the ascii code of 77, as that means the first letter is M
    #
    # When the first letter is M, it is printing out: MOBILE STATION P00000X00000Y
    # We need to extract the x and y coordinates, however, when we use indexing, it returns ascii code.
    # Therefore, we have to convert from ascii to character.
    #
    # The count variable is there so it doesn't stop counting indefinitely, we only want the latest reading
    # when this is called.
    #
    # The COM number will have to probably change when this is run on a different computer. Please read the README for
    # more instructions
    with serial.Serial('COM3', 115200) as ser:
        count = 0
        for line in ser:
            if count == 1:
                break
            if line[0] == 77: # Ascii code for 'M'
                x_coordinate_str = chr(line[17]) + chr(line[18]) + chr(line[19]) + chr(line[20]) + chr(line[21])
                y_coordinate_str = chr(line[23]) + chr(line[24]) + chr(line[25]) + chr(line[26]) + chr(line[27])
            
                x_coordinate_int = int(x_coordinate_str)*50
                y_coordinate_int = int(y_coordinate_str)*50

                count = count + 1

    # Set the new_x and new_y positions to the coordinates received from the serial data
    new_x = x_coordinate_int
    new_y = y_coordinate_int

    # Move the person object to the new coordinates
    canvas.coords(person_object, (new_x + PIXEL_OFFSET), (new_y + PIXEL_OFFSET), (new_x + 5 + PIXEL_OFFSET), (new_y + 5 + PIXEL_OFFSET))

    # Delete previously written text and create new one with updated coordinates
    canvas.delete('deleteMeX')
    canvas.create_text(500, 100, font='50', text='X: ' + str(new_x), tag='deleteMeX')
    canvas.create_text(500, 120, font='50', text='Y: ' + str(new_y), tag='deleteMeX')

    # Write the current x and y coordinates to the locationHistory.txt file
    location_file.write('X: ' + str(new_x) + ' Y: ' + str(new_y) + '\n')

    # Call this function every second
    root.after(1000, update)

# Start the mainloop for tkinter
root.after(0, update)
root.mainloop()

# Once we close the tkinter window, this will close the locationHistory.txt file
location_file.close()