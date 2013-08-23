//
//  triangle.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#ifndef __fam__triangle__
#define __fam__triangle__

#include <iostream>
#include <cmath>
#include "fuzzy_set.h"
#include "trapezoid.h"

using namespace std;

class Triangle : public FuzzySet {

private:
    double _left;
    double _center;
    double _right;

public:
    Triangle(double l, double c, double r, double h=1.0);
    Triangle();

    double calculateMu(double value);
    double calculateXCentroid();

    Triangle *larsen(double ratio);
    Trapezoid *mamdami(double clip_height);

    void setHeight(double height);

    inline friend ostream& operator<<(ostream &strm, const Triangle &tri) {
        // print something from v to str, e.g: Str << v.getX();
        strm << "Triangle " << &tri << ", " << tri._left << "/" << tri._center << "/" << tri._right << " (" << tri._height << ")";
        return strm;
    }
};

#endif /* defined(__fam__triangle__) */
