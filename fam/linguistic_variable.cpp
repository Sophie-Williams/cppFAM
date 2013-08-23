//
//  linguistic_variable.cpp
//  fam
//
//  Created by Chris Powell on 8/19/13.
//  Copyright (c) 2013 Prylis Inc. All rights reserved.
//

#include "linguistic_variable.h"

LinguisticVariable::LinguisticVariable() :
_name {""}
{
}

LinguisticVariable::LinguisticVariable(std::string name) :
_name {name}
{
}

std::string LinguisticVariable::name() {
    return _name;
}

void LinguisticVariable::addSet(FuzzySet * const set) {
    _sets.push_back(set);
}

