//
//  fuzzy_set.h
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

#ifndef __fam__fuzzy_set__
#define __fam__fuzzy_set__

#include <ostream>

namespace fuzzy {
    class FuzzySet {
    private:
        virtual void print( std::ostream& ) const = 0; // See operator<< below

    protected:
        double _height;

    public:
        // Empty virtual destructor for proper cleanup.
        // This allows you to pass pointer ownership to another party without exposing
        // the concrete derived class.
        virtual ~FuzzySet() {};

        virtual double calculateMu(double value) const = 0;

        virtual double calculateXCentroid() const = 0;

        virtual std::unique_ptr<FuzzySet> larsen(const double ratio) const = 0;
        virtual std::unique_ptr<FuzzySet> mamdami(const double clip_height) const = 0;

        double getHeight() const {
            return _height;
        }

        // When "cout" is passed a FuzzySet pointer, the actual derived object will
        // be asked to print itself.
        friend std::ostream& operator<<( std::ostream& out, const FuzzySet& b ) {
            b.print( out );
            return out;
        }

    };
}
#endif /* defined(__fam__fuzzy_set__) */
