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

namespace fuzzy {
    class Trapezoid : public FuzzySet {
        double _left;
        double _top_left;
        double _top_right;
        double _right;

    public:
        Trapezoid();
        Trapezoid(const double l, const double tl, const double tr, const double r, const double h=1.0);

        void setHeight(const double height) {
            _height = height;
        }

        double calculateMu(const double value) const;

        double calculateXCentroid() const;

        std::unique_ptr<FuzzySet> larsen(const double ratio) const;

        std::unique_ptr<FuzzySet> mamdami(const double clip_height) const;

        void print( std::ostream &strm) const {
            strm << "Trapezoid " << this << ", " << this->_left << "/" << this->_top_left << "/" << this->_top_right << "/" << this->_right << " (" << this->_height << ")";
        }
    };
}

#endif /* defined(__fam__trapezoid__) */
