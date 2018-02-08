/*
 * Also inherits from Shape, just like Circle. You have to handle only
 * polygons without “holes” them (formally: simple, non-self-intersecting polygons). This simplifies
 * computing the polygon area and determining if a point is inside a polygon or not.
 */

/* 
 * File:   Polygon.h
 * Author: linxinzh
 *
 * Created on December 2, 2017, 12:44 AM
 */

#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
    int nPoint;
   t_point relVertex[100];
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Polygon (string _name, string _colour, float _xcen, float _ycen, t_point vertices[100],int _nPoint);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Polygon();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};


#endif /* POLYGON_H */

