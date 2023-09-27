# beams
This program is build to graph the shear and moment diagrams for simply supported beams

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

R;1;10
P;5,5
D;1:3,5 
M;4,5;5,4

key: 
    R = reaction
    P = point force
    D = destributed load
    M = moment
Notation:
    ; = new force
    a,b = force at a with magnitude b
    a:b,c = force destributed from a to b with magnitude c

    summary:
        1st number is location
        :# is a destributed load
        last number is magnitude
