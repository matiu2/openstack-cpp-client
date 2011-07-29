#!/bin/sh
g++ -DDEBUG -ggdb -o test -O0 -lboost_system -lssl test.cpp
