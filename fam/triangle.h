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

using std::unique_ptr;

namespace fuzzy {
    class Triangle : public FuzzySet {
    private:
        double _left;
        double _center;
        double _right;

    public:
        Triangle();
        Triangle(const double l, const double c, const double r, const double h=1.0);

        void setHeight(const double height) {
            _height = height;
        }

        double calculateMu(const double value) const;

        double calculateXCentroid() const {
            return (_left + _right + _center) / 3.0;
        }

        unique_ptr<FuzzySet> larsen(const double ratio) const;

        unique_ptr<FuzzySet> mamdami(const double clip_height) const;

        void print( std::ostream &strm) const {
            strm << "Triangle " << this << ", " << this->_left << "/" << this->_center << "/" << this->_right << " (" << this->_height << ")";
        }

    };
}

#endif /* defined(__fam__triangle__) */
