#include <iostream>
#include "Misc_functions.h"
#pragma once


template <typename T>//can be any class/datatype
bool Misc_functions::is_in(T& find_this, T in_this[], int in_this_len) {//checks if an element is in an array
    for (int i=0; i<in_this_len;i++){
        if (find_this==in_this[i]) {
            return true;
        }
    }
    return false;
}

int Misc_functions::max(int a, int b) {
    if (a>b) {
        return a;
    }else {
        return b;
    }

}int Misc_functions::min(int a, int b) {
    if (a<b) {
        return a;
    }else {
        return b;
    }
}

template <typename T>
bool Misc_functions::arrs_are_same(T& A, T& B, int len) {//checks if contents of two arrays are the same
    for (int i=0; i<len; i++) {
        if (A[i]!=B[i]) {
            return false;
        }
    }
    return true;
}

std::string Misc_functions::st2nd3rd(int n) {
    std::string out;
    switch (n) {
        case 1:
            out="1st";
        break;
        case 2:
            out="2nd";
        break;
        case 3:
            out="3rd";
        break;
    }//will do the rest later :)
    return out;
}