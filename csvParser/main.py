import csv

with open('Project_2_beacon_locations.csv') as csv_file:
  csv_reader = csv.DictReader(csv_file, delimiter=',')
  index = 0
  for row in csv_reader:
    toPrint = ""
    toPrint += 'beaconLocation['+str(index)+'].x = '+row['X']+'; '
    toPrint += 'beaconLocation['+str(index)+'].y = '+row['Y']+'; '
    toPrint += 'beaconLocation['+str(index)+'].z = '+row['Z']+'; '
    print(toPrint)
    index = index + 1
