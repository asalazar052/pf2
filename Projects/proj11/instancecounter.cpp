
#include "instancecounter.h"

extern int g_instantiations;
extern int g_deletions;

InstanceCounter::InstanceCounter(){
    g_instantiations++;
}

InstanceCounter::~InstanceCounter(){
    g_deletions++;
}