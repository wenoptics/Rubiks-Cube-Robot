# Rubiks-Cube-Robot

A Rubik's Cube _(actually [Rubik's Revenge](https://en.wikipedia.org/wiki/Rubik%27s_Revenge))_ robot,
does nothing but solves a `4x4x4 Rubik's Cube`. 

:hammer: Crafted with [LEGO Mindstorms](https://www.lego.com/en-us/mindstorms/products/mindstorms-ev3-31313).


## What

The project was completed using parts from LEGO Mindstorms NXT. It's limited to used only 3 motors (actuators)
and complete the task of solving a 4x4x4 Rubik's Cube (aka Rubik's Revenge) from any valid state.

## Design

Goal: Design combination of mechanisms to accomplish any valid operation in a Rubik's Revenge.

### The nature of a Rubik's Revenge

Any valid operation is composed of rotations of certain layer of the cube. I will call these rotation operations 
atomic operations, which essentially means these are the minimal operations dividable. 

![cube layer operation]()


All methods of rotation of the Rubik's Cube, including a Rubik's Cube solution in an out-of-order state, are collections 
of atomic operations.

The cube fourth-order cube can create a coordinate system of three orthogonal axes in space, then the atomic operation 
can also be expressed as a rotation operation on a layer on one of the three axes.
For this project, I will use the Cartesian right-handed coordinate system.

### Movement Design

Since only three actuators is the limitation of the project, the whole design will be in such premise.
"`layer selection`" action, the "`layer turn`" action, and the Rubik's cube `X-axis flip` action is the 3 actions required. 
The combined use of the three actions will enable the machine to perform any valid operation on the Cube.

Below shows the idea of my design process:

#### 

1) Design a single axial layer operating mechanism (named `A`) so that the cube layer in one axial direction can perform 
a rotating operation.

In practice, I make this axis the `y` axis. The figure shows the layer rotation on Y-axis.

![the layer rotation on Y-axis]()


2) Design the "`layer selection`" mechanism (B) so that the Cube and the layer rotation mechanism (A) can move relative to 
each other, and is able to rotate the n layers of the shaft (Y axis) up to the top face.

![The cube moves upward relative to the layer-turning mechanism, and the top layers can be rotated together]()


Specifically, I denote rotating +90° as `lRt(n)`; the rotation -90° is denoted as \bar{lRt}(n).

So far, all layer atom operations in the direction of one axis (i.e. the Y axis) have developed.


3) Design the Cube X-axis turning mechanism (`C`) so that the Cube can be flipped around its X axis. Denoted the symbol 
of flipping the cube around the X axis by +90° as `cRt(x)`.

![the flip operation on X axis]()


In particular, layer rotation of the layer `n=4` is equivalent to rotation of the cube around the Y axis, i.e.

lRt\left(4\right)=cRt(y)

Therefore, the combination of the layer transition and the layer selection mechanism (`A` and `B`) can achieve the 
rotation of the cube around the Y axis.

In addition,

cRt\left(z\right)=cRt\left(y\right)+\bar{cRt}\left(x\right)+\bar{cRt}(y)

That is, the combination of the motion of the Cube around the X axis and the rotation around the Y axis 
can cause the cube to rotate about the Z axis.

At this point, all the axes of the Rubik's cube have been flipped.

With the flip operation on X axis, I can flip any layer on the axial axis to the Y-axis and cooperate with the Y-axis 
layer-turning mechanism (ie, the combination of `A` and `B`) to achieve the rotation of all layers of the cube.

### Overall Robot Design

Since there is no color recognition module existed in LEGO Mindstorms NXT, the solution ends with image capture using a 
USB camera and run color recognition with OpenCV. To make it simple, I decide to collect the image with a camera and 
processed on a PC, and the color recognition result will be transmitted to the NXT controller via Bluetooth, 
the electromechanical driver and solver algorithms will be run on the NXT controller. 

The block diagram of the system is shown below.

$\beta$ $\infty$
