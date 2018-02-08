/*
 * Create these files and implement the Rectangle class. This
 * class must inherit from the Shape class. You will have to add appropriate data members (which must
 * be of private type), and implement Rectangle versions of all the virtual functions defined in Shape.
 */

/* 
 * File:   Rectangle.h
 * Author: linxinzh
 *
 * Created on December 1, 2017, 11:27 PM
 */



#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "easygl.h"

class Rectangle : public Shape {
private:
   float width;
   float height;
   
public:
   Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float width, float height);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Rectangle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif /* RECTANGLE_H */

