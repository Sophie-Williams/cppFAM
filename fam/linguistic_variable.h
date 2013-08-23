//
//  linguistic_variable.h
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
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
