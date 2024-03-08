import time

import Services.DBHandler as DB
from PIL import Image, ImageSequence
import sys,os

mh = DB.DBHandler()


def get_photos(camera_name):
    photo_list = mh.get_photos(cam_name=camera_name)
    status = photo_list[0]["name"] +" selected"
    return photo_list

def resize_image(image):
    to_resize = Image.open(image)
    x,y = to_resize.size
    x = x * .5
    y = y * .5
    quality_val = 90
    image.save("filename", 'JPEG', quality=quality_val)


def make_gif(image_list, minutes_between_frames = 30):
    frames = [Image.open(image['save_path']) for image in image_list]
    frame_one = frames[0]
    save_location = "Z:/Plant/gifs/"+image_list[0]['name']+time.time().__str__()+".gif"
    frame_one.save(save_location, append_images=frames[1::minutes_between_frames],
               save_all=True, duration=10, loop=1)
    return save_location

