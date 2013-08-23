//
//  trapezoid.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#ifndef __fam__trapezoid__
#define __fam__trapezoid__

#include <iostream>
#include <cmath>
#include "fuzzy_set.h"

using namespace std;

class Trapezoid : public FuzzySet {
    double _left;
    double _top_left;
    double _top_right;
    double _right;

public:
    Trapezoid(double l, double tl, double tr, double r, double h=1.0);
    Trapezoid();

    double calculateMu(double value);
    double calculateXCentroid();

    FuzzySet *larsen(double ratio);
    FuzzySet *mamdami(double clip_height);

    void setHeight(double height);

    inline friend ostream& operator<<(ostream &strm, const Trapezoid &tri) {
        // print something from v to str, e.g: Str << v.getX();
        strm << "Trapezoid " << &tri << ", " << tri._left << "/" << tri._top_left << "/" << tri._top_right << "/" << tri._right << " (" << tri._height << ")";

        return strm;
    }
};
#endif /* defined(__fam__trapezoid__) */
