//
//  triangle.cpp
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

#include "triangle.h"

fuzzy::Triangle::Triangle(const double l, const double c, const double r, const double h) :
_left {l},
_center {c},
_right {r}
{
    _height=h;
}

fuzzy::Triangle::Triangle() :
_left {0},
_center {0},
_right {0}
{
    _height=0;
}

double fuzzy::Triangle::calculateMu(double value) const {
    if (value < _left || value > _right) {
        return 0.0;
    } else {
        return (1.0 - (std::abs(_center-value) / ((_right-_left) / 2.0 )));
    }
}

double fuzzy::Triangle::calculateXCentroid() const {
    return (_left + _right + _center) / 3.0;
}

void fuzzy::Triangle::setHeight(double height) {
    _height = height;
}

fuzzy::Triangle *fuzzy::Triangle::larsen(double ratio) const {
    Triangle *dup = new Triangle(*this);
    dup->setHeight(_height * ratio);
    return dup;
}

fuzzy::Trapezoid *fuzzy::Triangle::mamdami(double clip_height) const {
    double l  = _left;
    double tl = _left + (clip_height * (_center - _left));
    double tr = _right - (clip_height * (_right - _center));
    double r  = _right;

    return new Trapezoid(l, tl, tr, r, clip_height);
}
