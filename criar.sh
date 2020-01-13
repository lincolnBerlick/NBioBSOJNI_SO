#!/bin/bash


g++ -fPIC -I/usr/lib/jvm/java-11-openjdk-amd64/include/ -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux/ -shared -o libNBioBSPJNI.so NBioBSPJNI.cpp -ldl -lNBioBSP
cp libNBioBSPJNI.so /usr/lib


