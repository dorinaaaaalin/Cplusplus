#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width, float _height) 
              : Shape (_name, _colour, _xcen, _ycen) {
   
    width = _width;
    height  = _height;
    
}


Rectangle::~Rectangle () {
   // No dynamic memory to delete
}


void Rectangle::print () const {
   Shape::print();
   cout << "rectangle width: " << width << " height: " << height << endl; 
}


void Rectangle::scale (float scaleFac) {  
      width *= scaleFac;
      height *= scaleFac;
}
   

float Rectangle::computeArea () const {
   // width * height
   float area;  
   area = width * height;
   return area;
}


float Rectangle::computePerimeter () const {
   float perimeter = 0;
   perimeter += (width * 2 + height * 2);
   
   return perimeter;
}


void Rectangle::draw (easygl* window) const {
    float x1,y1,x2,y2;
    x1 = getXcen() - width/2;
    y1 = getYcen() + height/2;
    x2 = getXcen() + width/2;
    y2 = getYcen() - height/2;
    
    window->gl_setcolor(getColour());
    window->gl_fillrect(x1,y1,x2,y2);
}

//determine if location (x,y) falls within this shape
bool Rectangle::pointInside (float x, float y) const {
    float x1,y1,x2,y2;
    x1 = getXcen() - width/2;
    y1 = getYcen() + height/2;
    x2 = getXcen() + width/2;
    y2 = getYcen() - height/2;
    
   if(x >= x1 && x <= x2 && y >= y2 && y <= y1)
       return true;
   else
       return false;
}


