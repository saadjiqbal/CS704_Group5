import csv, os

# Since we append to the coordinates file, check to see if it exists,
# if it does then delete it
if os.path.isfile('coordinates.txt'):
    os.remove('coordinates.txt')
    
coordinate_file = open('coordinates.txt', 'a+')

# append all the values in the x column
with open('Project_2_beacon_locations.csv') as csv_file:
  csv_reader = csv.DictReader(csv_file, delimiter=',')

  for row in csv_reader:
    coordinate_file.write(row['X'] + '\n')

# append all the values in the y column
with open('Project_2_beacon_locations.csv') as csv_file:
  csv_reader = csv.DictReader(csv_file, delimiter=',')

  for row in csv_reader:
    coordinate_file.write(row['Y'] + '\n')

# append all the values in the z column
with open('Project_2_beacon_locations.csv') as csv_file:
  csv_reader = csv.DictReader(csv_file, delimiter=',')

  for row in csv_reader:
    coordinate_file.write(row['Z'] + '\n')

coordinate_file.close()