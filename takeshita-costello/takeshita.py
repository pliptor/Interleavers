#!/usr/bin/python3
# Copyright (C) 2017 Oscar Y. Takeshita.
# This program generates a sequence of distinct numbers
# such that the length of the sequence can be any power of 2.
# A particular characteristic of the generated sequence is that
# it is symmetric in the sense that an entry j in row i (0<i,j<2^n-1)
# implies that the entry in row j is i.
# More information can be found in O. Y. Takeshita and D. J. Costello, Jr,:
# New classes of algebraic interleavers for turbo-codes," Proc. 1998 IEEE
# International Symposium on Information Theory, Boston, p. 419,
# Aug 16-21, 1998.
# Note: this is a translation from the original perl script to python3.

import sys

#----------------------------------------------------------------------
def CheckCmdLine():
    if len(sys.argv) != 2:
        print("\n\nUsage: {} Interleaver_Length=2^n \n".format(sys.argv[0]))
        return -1 
    else:
        length = int(sys.argv[1])
        if bin(length).count("1") == 1:
            return length 
        else:
            print("{} is not a power of 2".format(length))
            return -1
#----------------------------------------------------------------------
def PrintResult(a):
    for i in a:
        print(i)
#----------------------------------------------------------------------
def GenerateDT(Length, Step, DShift, CShift): 
    Perm = [0]*Length
    Count = 0
    Point = DShift + CShift
    Quest = Step + DShift
    while Count < Length-1:
        Quest %= Length
        Point %= Length
        Perm[Point] = Quest
        Point = Quest + CShift
        Count += 1
        Quest += (Count+1) * Step
    Point %= Length
    Perm[Point] = DShift # Close last element.
    return Perm
#======================================================================
# MAIN
if __name__ == "__main__":
    Length = CheckCmdLine()
    if Length != -1:
        Step   = 1              # default coefficient of permuter (k in the paper);
        DShift = 0              # default diagonal shift of the permuter
        CShift = int(Length/2); # default cyclic shift of the permuter
                   # generates a type C2 interleaver
        c2dt = GenerateDT(Length, Step, DShift, CShift)
        PrintResult(c2dt)
#======================================================================

