import sys
import os
import dotmap
import json

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




    

