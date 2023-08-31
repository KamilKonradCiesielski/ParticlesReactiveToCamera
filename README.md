Description

This project combines computer vision techniques and particle simulation to create an interactive visual effect. A webcam captures real-world images and then analyzes them to locate foreground objects. Based on these objects, repelling forces are generated, which interact with particles on the screen.

Prerequisites

Before starting to use the project, make sure you have the following elements installed:

    OpenFrameworks: Installation instructions
    Webcam available on your system

Running

    Ensure that your webcam is connected and accessible to the project.
    Run the project in the OpenFrameworks environment.
    The project should start and display the webcam image in the window.

Documentation

The project consists of four files:

    particle.h
    particle.cpp
    ofApp.cpp
    ofApp.h

-----------------------------------------------particle.h----------------------------------------------------------------------------------

The particle class represents an individual particle in the project. It has several functions that implement different aspects of particle behavior:

    Constructor particle::particle(): Creates a new instance of the particle class.
    Function void particle::setup(): Initializes the initial parameters of the particle, such as position, velocity, force, size, etc.
    Function void particle::update(float speed, float noise): Updates the position and velocity of the particle based on given overall speed and noise level.
    Function void particle::draw(float sizeDot): Draws the particle on the screen with a specified size.
    Function void particle::repel(vector<ofVec2f> repelPt): Repels the particle from a set of repel points.

The particle class contains various parameters and vectors, such as position (pos), velocity (vel), force (frc), repelling force (repelFrc), drag coefficient (drag), unique values for generating noise (uniqueVal), and size (size). This class is essential for the project as it represents elements that create the visual effect through interaction between them.

------------------------------------------------particle.cpp------------------------------------------------------------------------------------
The code presents the implementation of the particle class, which describes the behavior of an individual particle in the project. Here's a description of each function:

    Constructor particle::particle(): This is the constructor of the particle class, which is empty in this case. The constructor initializes a new instance of the particle class.

    Function void particle::setup(): This function initializes the particle's parameters at the beginning of its existence. It sets:
        pos: a random position on the screen.
        vel: a random velocity for the particle in both axes.
        frc: a force vector, initially set to (0, 0).
        uniqueVal: unique values used for generating noise for the ofSignedNoise function.
        size: a random size for the particle.
        drag: a random drag coefficient for velocity damping.

    Function void particle::update(float speed, float noise): This function updates the position and velocity of the particle based on the given speed and noise values. The main steps include:
        Generating noise for frc.x and frc.y using the ofSignedNoise function.
        Modifying frc by the noise.
        Applying velocity damping.
        Flattening by subtracting repelFrc, which acts as a repelling force.
        Adding frc to vel to update velocity.

    Function void particle::draw(float sizeDot): This function draws the particle on the screen. It uses the ofDrawCircle function to draw a circle with pos.x and pos.y as the center and size * sizeDot as the radius. This function also randomly changes the color of the particle.

    Function void particle::repel(vector<ofVec2f> repelPt): This function is responsible for repelling the particle from a set of repel points. The main steps are:
        Resetting repelFrc at the beginning of each loop iteration.
        Calculating the distance between the particle and the repel point.
        If the distance is less than 150, adding a repelling force (repelFrc) from the particle to the repel point.

These functions together define the behavior of an individual particle in the project, including its movement, interaction with contours, and drawing on the screen.

--------------------------------------------------ofApp.cpp---------------------------------------------------------------------------------------

This code snippet represents the implementation of the ofApp class, which is the main entry point and controller in the project. Below, I describe the individual parts of the code:

    Function void ofApp::setup(): This function initializes various parameters and components when the application starts. The steps include:
        Initializing the webcam (webCam) with a size of 320x240 pixels.
        Allocating memory for various images (colorImg, grayImg, grayBg, grayDiff) with a size of 320x240 pixels.
        Initializing the graphical user interface (GUI) and adding sliders and buttons to control parameters like speed, noise level, and difference threshold.
        Creating an array (p) containing 1000 objects of the particle type and calling their setup() functions.

    Function void ofApp::update(): This function is responsible for updating the application's state in each frame. In the main part:
        The data from the webcam (webCam) is refreshed, and it's checked whether
