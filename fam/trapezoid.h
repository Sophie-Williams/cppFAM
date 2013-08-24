//
//  trapezoid.h
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

#ifndef __fam__trapezoid__
#define __fam__trapezoid__

#include <iostream>
#include <cmath>
#include "fuzzy_set.h"

using namespace std;

namespace fuzzy {
    class Trapezoid : public FuzzySet {
        double _left;
        double _top_left;
        double _top_right;
        double _right;

    public:
        Trapezoid(const double l, const double tl, const double tr, const double r, const double h=1.0);
        Trapezoid();

        double calculateMu(double value) const;
        double calculateXCentroid() const;

        std::shared_ptr<FuzzySet> larsen(double ratio) const;
        std::shared_ptr<FuzzySet> mamdami(double clip_height) const;

        void setHeight(double height);

        void print( std::ostream &strm) const {
            strm << "Trapezoid " << this << ", " << this->_left << "/" << this->_top_left << "/" << this->_top_right << "/" << this->_right << " (" << this->_height << ")";
        }

    //    inline friend ostream& operator<<(ostream &strm, const Trapezoid &tri) {
    //        // print something from v to str, e.g: Str << v.getX();
    //        strm << "Trapezoid " << &tri << ", " << tri._left << "/" << tri._top_left << "/" << tri._top_right << "/" << tri._right << " (" << tri._height << ")";
    //
    //        return strm;
    //    }
    };
}

#endif /* defined(__fam__trapezoid__) */
