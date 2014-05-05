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

namespace fuzzy {
    class TrapezoidHasher;

    class Trapezoid {
        const double _left;
        const double _top_left;
        const double _top_right;
        const double _right;
        const double _height;

        void print( std::ostream &strm) const {
            strm << "Trapezoid {" << this << ", " << this->_left << "/" << this->_top_left << "/" << this->_top_right << "/" << this->_right << " (" << this->_height << ")}";
        }

    public:
        Trapezoid();

        /**
         Construct a trapzeoid. The X-coordinates of the 4 corners are required, and the height
         optional and defaults to 1.0. Height should be in the range of 0..1.0.
         A trapezoid can masquerade as a triangle if you use the same X-coord for tl & tr.
         */
        Trapezoid(const double l, const double tl, const double tr, const double r, const double h=1.0);

        double left() const { return _left; }
        double topLeft() const { return _top_left; }
        double topRight() const { return _top_right; }
        double right() const { return _right; }
        double height() const { return _height; }

        /**
         Given a value, determine that value's degree-of-fit in this trapezoid.
         Basically, the height of the trapezoid at the given value.
         @param value the value you wish to check for degree-of-fit
         @return the degree-of-fit as 0..1.0
         */
        double calculateMu(const double value) const;

        /**
         Calculate the centroid of this trapezoid relative to the X-axis.
         @return the x-coordinate of the shape
         */
        double calculateXCentroid() const;

        /**
         Scaling.
         @param ratio the scaling factor to use, e.g. 0.8
         @return a new trapezoid
         */
        Trapezoid larsen(const double ratio) const;

        /**
         Clipping.
         @param clip_height the height at which to clip the trapezoid, e.g. 0.5
         @return a new trapezoid
         */
        Trapezoid mamdami(const double clip_height) const;

        /**
         Overload the equality operator. Permits usage of Trapezoid as the
         key in an unordered_map.
         @param other the other trapezoid to compare to
         @return true if they are equal in every way, false otherwise
         */
        bool operator==(const Trapezoid &other) const;
        
        friend std::ostream& operator<<( std::ostream& out, const Trapezoid& b ) {
            b.print( out );
            return out;
        }

        friend TrapezoidHasher;
    };

    /**
     A specialized hasher for Trapezoid. Permits the trapezoid to be
     used as the key in an unordered_map. Also requires operator==,
     which is declared in Trapezoid.
     */
    struct TrapezoidHasher {
        std::size_t operator()(const Trapezoid& k) const {
            return std::hash<double>()(k._left) +
            std::hash<double>()(k._top_left) +
            std::hash<double>()(k._top_right) +
            std::hash<double>()(k._right) +
            std::hash<double>()(k._height);
        }
    };
}

#endif /* defined(__fam__trapezoid__) */
