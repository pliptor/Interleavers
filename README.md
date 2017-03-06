# Interleavers

![Interleavers](https://travis-ci.org/pliptor/Interleavers.svg?branch=master) 

## A collection of tools for permutation and interleaver generation

An interleaver is used to reorder a sequence of typically distinct items.
For example: 1, 2, 3, 4, 5 -> 3, 2, 1, 5, 4. In other words, it permutes the items. Often,
a pseudo-random permutation is sufficient. In C++ you may use std::shuffle() for a pseudo-random
permutation. However, sometimes permutations with properties other than random are desirable.

### takeshita-costello folder
Contains perl and python scripts for the generation of takeshita-costello interleavers.
These interleavers are can be found in the communications toolbox of Matlab(R).

### s-random folder
C++ program for the generation of s-random interleavers.
[S. Dolinar and D. Divsalar, "Weight Distributions for Turbo Codes Using Random and Nonrandom Permutations,"
NASA Code 315-91-20-20-53](http://ipnpr.jpl.nasa.gov/progress_report/42-122/122B.pdf)
