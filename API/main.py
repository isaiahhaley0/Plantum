# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import time

from flask import Flask, request, jsonify,Response,make_response
import Services.DBHandler as mh
import Services.Stats as st
import Services.CameraControl as CC
from PIL import Image
import io
import os
app = Flask(__name__)


mhd = mh.DBHandler()

@app.route("/")
def hello():
    return "Hello, World!"


@app.route("/light", methods=['GET', 'PUT'])
def record_light_reading():
    rq = request
    data = request.json
    print(data["light"])
    mhd.Insert_Reading(data)
    return "heey"

@app.route("/camera",methods=['GET'])
def check_should_flash():
    flash = CC.should_flash()
    data = {
        "flash":flash,
    }
    print(flash)
    return jsonify(data)

@app.route("/camera_info",methods=['GET'])
def get_camera_information():
    return mhd.get_camera_data()


@app.route("/upload",methods=['POST'])
def upload_photo():
    print("uploading")
    image_raw_bytes = request.get_data()  # get the whole body
    tme = time.time().__str__()
    save_location = "E:/plant/TimeLapse/"+time.time().__str__()+".jpg"  # save to the same folder as the flask app live in
    info = {}
    info['time'] = tme
    info['save_path'] = save_location
    name = request.args.get('name')
    if name is None:
        name = 'cam1'

    info['name'] = name
    print(name)
    f = open(save_location, 'wb')  # wb for write byte data in the file instead of string
    f.write(image_raw_bytes)  # write the bytes from the request body to the file
    f.close()
    mhd.insert_photo_record(info)
    print("Image saved")

    #return "image saved"
    data = {'message': 'Done', 'code': 'SUCCESS'}
    return make_response(jsonify(data),200)


@app.route("/stats")
def get_stats():
    read = mhd.get_readings()

    avg = 0

    for r in read:
        avg = avg + r["light"]


    return st.get_hla()

if __name__ == "__main__":
    app.run(host='0.0.0.0')