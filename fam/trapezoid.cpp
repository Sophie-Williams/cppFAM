//
//  trapezoid.cpp
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

#include "trapezoid.h"

fuzzy::Trapezoid::Trapezoid(double l, double tl, double tr, double r, double h) :
_left {l},
_top_left {tl},
_top_right {tr},
_right {r}
{
    _height=h;
}

fuzzy::Trapezoid::Trapezoid() :
_left {0},
_top_left {0},
_top_right {0},
_right {0}
{
    _height=0;
}

double fuzzy::Trapezoid::calculateMu(double value) {
    if (value < _left || value > _right) {
        return 0.0;
    } else if (value >= _left && value < _top_left) {
        return (value - _left) / (_top_left - _left);
    } else if (value >= _top_left && value <= _top_right) {
        return 1.0;
    } else {
        return (_right - value) / (_right - _top_right);
    }
}

double fuzzy::Trapezoid::calculateXCentroid() {
    double a = _top_right - _top_left;
    double b = _right - _left;
    double c = _top_left - _left;

    double cx = (2.0*a*c + pow(a,2.0) + c*b + a*b + pow(b,2.0)) / (3.0 * (a+b));
    return cx+_left;
}

void fuzzy::Trapezoid::setHeight(double height) {
    _height = height;
}

fuzzy::FuzzySet *fuzzy::Trapezoid::larsen(double ratio) {
    Trapezoid *dup = new Trapezoid(*this);
    dup->setHeight(_height * ratio);
    return dup;
}

fuzzy::FuzzySet *fuzzy::Trapezoid::mamdami(double clip_height) {
    double l = _left;
    double tl = _left + (clip_height * (_top_left - _left));
    double tr = _right + (clip_height * (_right - _top_right));
    double r = _right;

    return new Trapezoid(l, tl, tr, r, clip_height);
}
