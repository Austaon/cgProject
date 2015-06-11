#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "raytracing.h"

#define dot(u,v)   ((u).p[0] * (v).p[0] + (u).p[1] * (v).p[1] + (u).p[2] * (v).p[2])


//temporary variables
//these are only used to illustrate 
//a simple debug drawing. A ray 
Vec3Df testRayOrigin;
Vec3Df testRayDestination;


//use this function for any preprocessing of the mesh.
void init()
{
	//load the mesh file
	//please realize that not all OBJ files will successfully load.
	//Nonetheless, if they come from Blender, they should, if they 
	//are exported as WavefrontOBJ.
	//PLEASE ADAPT THE LINE BELOW TO THE FULL PATH OF THE dodgeColorTest.obj
	//model, e.g., "C:/temp/myData/GraphicsIsFun/dodgeColorTest.obj", 
	//otherwise the application will not load properly
    MyMesh.loadMesh("/Users/Aurel/Documents/cgProject/source/cube.obj", true);
	MyMesh.computeVertexNormals();

	//one first move: initialize the first light source
	//at least ONE light source has to be in the scene!!!
	//here, we set it to the current location of the camera
	MyLightPositions.push_back(MyCameraPosition);
}

//return the color of your pixel.
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest)
{
	std::vector< ::Triangle>::iterator i = MyMesh.triangles.begin();

	Vec3Df color = Vec3Df(0,0,0);


	for(i; i<MyMesh.triangles.end(); i++)
	{
		//Vertex v0 = MyMesh.vertices[i->v[0]].p;
		//Vertex v1 = MyMesh.vertices[i->v[1]].p;
		//Vertex v2 = MyMesh.vertices[i->v[2]].p;

		Vec3Df u = MyMesh.vertices[i->v[1]].p - MyMesh.vertices[i->v[0]].p;
		Vec3Df v = MyMesh.vertices[i->v[2]].p - MyMesh.vertices[i->v[0]].p;
		Vec3Df w = dest - MyMesh.vertices[i->v[0]].p;

		float D = dot(u,v)*dot(u,v) - dot(u,u)*dot(v,v);

		float s = (dot(u,v)*dot(w,v) - dot(v,v)*dot(w,u)) / D;
		float t = (dot(u,v)*dot(w,u) - dot(u,u)*dot(w,v)) / D;

		if(s>=0 && t>=0 && s+t<=1)
		{
			//double r0 = ((double) rand() / (RAND_MAX));
			//double r1 = ((double) rand() / (RAND_MAX));
			//double r2 = ((double) rand() / (RAND_MAX));

			//std::cout << "[" << r0 << ", " << r1 << ", " << r2 << "]" << std::endl;
			color = Vec3Df(1,1,1);
			//std::cout << "[" << s << ", " << t << ", " << s+t << "]" << std::endl;
		}

	}

	return color;
}



void yourDebugDraw()
{
	//draw open gl debug stuff
	//this function is called every frame

	//let's draw the mesh
	MyMesh.draw();
	
	//let's draw the lights in the scene as points
	glPushAttrib(GL_ALL_ATTRIB_BITS); //store all GL attributes
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);
	glPointSize(10);
	glBegin(GL_POINTS);
	for (unsigned int i=0;i<MyLightPositions.size();++i){
		if(i == selectedLight){
			glColor3f(1,0,0);
		}
		glVertex3fv(MyLightPositions[i].pointer());
		if(i == selectedLight){
			glColor3f(1,1,1);
		}
	}
	glEnd();
	glPopAttrib();//restore all GL attributes
	//The Attrib commands maintain the state. 
	//e.g., even though inside the two calls, we set
	//the color to white, it will be reset to the previous 
	//state after the pop.


	//as an example: we draw the test ray, which is set by the keyboard function
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(0,1,1);
	glVertex3f(testRayOrigin[0], testRayOrigin[1], testRayOrigin[2]);
	glColor3f(0,0,1);
	glVertex3f(testRayDestination[0], testRayDestination[1], testRayDestination[2]);
	glEnd();
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3fv(MyLightPositions[0].pointer());
	glEnd();
	glPopAttrib();
	
	//draw whatever else you want...
	////glutSolidSphere(1,10,10);
	////allows you to draw a sphere at the origin.
	////using a glTranslate, it can be shifted to whereever you want
	////if you produce a sphere renderer, this 
	////triangulated sphere is nice for the preview
}


//yourKeyboardFunc is used to deal with keyboard input.
//t is the character that was pressed
//x,y is the mouse position in pixels
//rayOrigin, rayDestination is the ray that is going in the view direction UNDERNEATH your mouse position.
//
//A few keys are already reserved: 
//'L' adds a light positioned at the camera location to the MyLightPositions vector
//'l' modifies the last added light to the current 
//    camera position (by default, there is only one light, so move it with l)
//    ATTENTION These lights do NOT affect the real-time rendering. 
//    You should use them for the raytracing.
//'r' calls the function performRaytracing on EVERY pixel, using the correct associated ray. 
//    It then stores the result in an image "result.ppm".
//    Initially, this function is fast (performRaytracing simply returns 
//    the target of the ray - see the code above), but once you replaced 
//    this function and raytracing is in place, it might take a 
//    while to complete...
void yourKeyboardFunc(char t, int x, int y, const Vec3Df & rayOrigin, const Vec3Df & rayDestination)
{

	//here, as an example, I use the ray to fill in the values for my upper global ray variable
	//I use these variables in the debugDraw function to draw the corresponding ray.
	//try it: Press a key, move the camera, see the ray that was launched as a line.
	testRayOrigin=rayOrigin;	
	testRayDestination=rayDestination;
	
	// do here, whatever you want with the keyboard input t.
	
	//...
	
	
	std::cout<<t<<" pressed! The mouse was in location "<<x<<","<<y<<"!"<<std::endl;	
}
