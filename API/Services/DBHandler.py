import time
import pymongo


class DBHandler:
    def __init__(self):
        self.__started = False;
        self.__client = pymongo.MongoClient("localhost",27017)
        self.__db = self.__client.plantum

    def Insert_Reading(self, reading):
        self.__db = self.__client.plantum
        reading["time"] = time.time()
        coll = self.__db.environment_readings
        coll.insert_one(reading)

    def get_readings(self, trailing_minutes = 1):
        coll = self.__db.environment_readings
        ms = trailing_minutes *600

        query = {"time": {"$gt": time.time()-ms}}
        mine = list(coll.find(query))

        print(len(mine))
        return mine

    def get_last(self):
        coll = self.__db.environment_readings
        return coll.find_one({},sort=[('_id',pymongo.DESCENDING)])

    def insert_photo_record(self, photo_record):
        coll = self.__db.photo_records
        coll.insert_one(photo_record)

    def get_camera_data(self):
        coll = self.__db.photo_records
        cameras = []
        records = coll.find({}).distinct('name')
        clist = {}
        clist['cameras'] = records
        return clist