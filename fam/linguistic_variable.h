//
//  linguistic_variable.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//
//  This file is part of The C++ Fuzzy Associative Memory
//  http://github.com/cpowell/fuzzy-associative-memory-c++
//  You can redistribute and/or modify this software only in accordance with
//  the terms found in the "LICENSE" file included with the library.
//

#ifndef __fam__linguistic_variable__
#define __fam__linguistic_variable__

#include <iostream>
#include <string>
#include <vector>
#include "fuzzy_set.h"

class LinguisticVariable {
private:
    std::string _name;
    std::vector<FuzzySet *> _sets;

public:
    LinguisticVariable();
    LinguisticVariable(std::string name);

    std::string name();
    void addSet(FuzzySet * const set);
};

#endif /* defined(__fam__linguistic_variable__) */
