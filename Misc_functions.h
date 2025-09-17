//
// Created by User on 14/04/2025.
//

#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H
#pragma once

class Misc_functions {
public:
    template <typename T>
    static bool is_in(T& find_this, T in_this[], int in_this_len);
    static int max(int a, int b);
    static int min(int a, int b);
    template <typename T>
    static bool arrs_are_same(T& A, T& B, int len);
    static std::string st2nd3rd(int n);
};



#endif //MISC_FUNCTIONS_H
