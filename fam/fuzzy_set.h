//
//  fuzzy_set.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#ifndef __fam__fuzzy_set__
#define __fam__fuzzy_set__

#include <iostream>

class FuzzySet {
protected:
    double _height;

public:
    // Empty virtual destructor for proper cleanup.
    // This allows you to pass pointer ownership to another party without exposing
    // the concrete derived class.
    virtual ~FuzzySet() {};

    virtual double calculateMu(double value) = 0;

    virtual double calculateXCentroid() = 0;

    virtual FuzzySet *larsen(double ratio) = 0;
    virtual FuzzySet *mamdami(double clip_height) = 0;

    double getHeight() {
        return _height;
    }

};

#endif /* defined(__fam__fuzzy_set__) */
