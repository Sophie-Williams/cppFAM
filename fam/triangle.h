//
//  triangle.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//
//  This file is part of The C++ Fuzzy Associative Memory
//  http://github.com/cpowell/fuzzy-associative-memory-cplusplus
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the library.
//

#ifndef __fam__triangle__
#define __fam__triangle__

#include <iostream>
#include <cmath>
#include "fuzzy_set.h"
#include "trapezoid.h"

using namespace std;

namespace fuzzy {
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

        void print( std::ostream &strm) const {
            strm << "Triangle " << this << ", " << this->_left << "/" << this->_center << "/" << this->_right << " (" << this->_height << ")";
        }

    //    inline friend ostream& operator<<(ostream &strm, const Triangle &tri) {
    //        // print something from v to str, e.g: Str << v.getX();
    //        strm << "Triangle " << &tri << ", " << tri._left << "/" << tri._center << "/" << tri._right << " (" << tri._height << ")";
    //        return strm;
    //    }
    };
}

#endif /* defined(__fam__triangle__) */
