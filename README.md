# beams
This program is build to graph the shear and moment diagrams for simply supported beams. Future support for non-linear destributed loads and cantilever beams is being worked on.

To use, clone the repo into your machine. Must have clang compiler and python 3.10 or greater installed.
To run, input data into the "inputs.txt" file. Instructions for the that are bellow.

If it is your first time running run:

    $ make

to run the make file to compile the program.

From then on, you can simply change your input data and run:

    $ sh run.sh 

The program will run and display important data on the command line. It will also open a png file of the shear and moment diagrams for the beam.

Key: 
    R = reaction
    P = point force
    D = destributed load
    M = moment
Notation:
    ; = new force
    a,b = force at a with magnitude b
    a:b,c:d = force destributed from a to b with magnitude c at a and d at b
Summary:
    1st number is location
    :# is a destributed load
    last number is magnitude
Example:
    R;1;10
    P;5,5
    D;1:3,5 
    M;4,5;5,4



future plans:
    have input value be put into an excel sheet
    make it compatible with cantelever beams / 1 support with a moment
    make it able to solve multiple beams at once

future notes:
for slanted destributed loads, pass in as 
    D;start:stop,pressurexfactor
    on pasrse, split the pressure and factor via x
    assign dload struct a factor attribute
    use factor attribute when solveing for reactions and shear/moments
        ex moment = pressure * exp(x, factor)

If there are any questions feel free to ask.
