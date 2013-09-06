//
//  linguistic_variable.cpp
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

#include "linguistic_variable.h"

fuzzy::LinguisticVariable::LinguisticVariable() :
_name {""}
{
}

fuzzy::LinguisticVariable::LinguisticVariable(std::string name) :
_name {name}
{
}

std::string fuzzy::LinguisticVariable::name() {
    return _name;
}

void fuzzy::LinguisticVariable::addSet(std::shared_ptr<FuzzySet> const set) {
    _sets.push_back(set);
}

