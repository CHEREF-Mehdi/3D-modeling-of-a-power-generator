# 3D-modeling-of-a-power-generator

3D modeling of a power generator -Renewable energy- using GLUT (OpenGL utility toolkit)

# About
![alt text](https://github.com/CHEREF-Mehdi/3D-modeling-of-a-power-generator/blob/master/ImageReadMe/1.png)

We modeled the 3d power-generator using several objects and multiple combinations of geometric transformations.

1- Gear : we create and used the function gear().

	prototype:
  
	static void gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width, GLint teeth, GLfloat tooth_depth)
  
2- Cylindre : we used the predefined function gluCylinder()

3- Sphere : we used the predefined function glutSolidSphere()

# user Interaction

The user can interact in two different ways :
 
1- By using the arrow keys : we rotate the whole model to setup the viewing angle by calling the function rotate().

2- By using the left mouse button : the waterfall animation starts and all the mecanisme begins to move in order to create energy to turn on the lamp 

![alt text](https://github.com/CHEREF-Mehdi/3D-modeling-of-a-power-generator/blob/master/ImageReadMe/2.png)
