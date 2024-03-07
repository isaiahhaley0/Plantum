# README

This is repo is a project I put together that uses esp32 cam, a flask app, and a MAUI app to make timelapses, and to make some determinations about the plants where possible.

# to do

1. set up flask app

    a. esp32 cam takes photos and delivers them to the server via a RESTful API

    b. on request the app should make a gif based on the cam name passed to it

2. set up maui app

    a. allow user to select camera

    b. return timelapse from server(see 1.a)

    