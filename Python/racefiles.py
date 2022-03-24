import sys
import os
import dotmap
import json
import csv

# The structure of the data file 
# { groups: [ {
#    "group": "groupname1",
#    "racers" : [ {
#                   "name":"Jim Bob",
#                   "car_name":"The Flash",
#                   "car_number":1,
#                   "times": [1,2,3,4,5,6,7,8]
#           },
#      ]
#   } 
#  ]
# }
#
#

class Racer:
    name = ''
    car_name = ''
    car_number = -1
    times = []

    def __init__(self, name, car_name, car_number, times) -> None:
        self.name = name
        self.car_name = car_name
        self.car_number = car_number
        self.times = times

    def set_times(self, times):
        self.times = times

    def dict(self):
        result = {}
        result['name'] = self.name
        result['car_name'] = self.car_name
        result['car_number'] = self.car_number
        result['times'] = self.times
        
        return result

class Group:
    name = ''
    racers = []

    def __init__(self, name) -> None:
        self.name = name
        self.racers = []

    def add_racer(self, racer):
        self.racers.append(racer)

    def remove_racer(self,racer_name):
        pass

    def dict(self):
        result = []
        for racer in self.racers:
            result.append(racer.dict())
        
        return {"name":self.name, "racers":result}

class RaceData:
    filename = None
    groups = []

    def __init__(self, filename = None) -> None:

        if filename is not None:
            self.filename = filename
            with open(self.filename) as json_file:
                data_json = json.load(json_file)
                data = dotmap.DotMap(data_json)

                for group in data.groups:                
                    g = Group(group.name)
                    for racer in group.racers:
                        r = Racer(racer.name, racer.car_name, racer.car_number, racer.times)
                        g.add_racer(r)
                    self.groups.append(g)

                #self.groups = data.groups
                print(self.groups)

    def import_from_csv(self,csv_filename):
        with open(csv_filename, newline='\n') as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            group_name = ''
            group = None
            for row in reader:
                if row[0] != group_name:
                    if group != None:
                        self.groups.append(group)
                    group_name = row[0]
                    group = Group(group_name)

                racer = Racer(row[1],row[2],row[3],[])
                group.add_racer(racer)
            if group != None:
                self.groups.append(group)

    def dict(self):
        result = []
        for group in self.groups:
            result.append(group.dict())
        
        return {"groups":result}





    

