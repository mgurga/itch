#include "ScratchVariable.hpp"

ScratchVariable::ScratchVariable(json sv): 
    name(to_string(sv[0])),
    value(to_string(sv[1])),
    isCloud(sv.size() == 3)
{}