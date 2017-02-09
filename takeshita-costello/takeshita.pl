#!/usr/bin/perl
# Copyright (C) 1997, 1998, 1999, 2017 Oscar Y. Takeshita.
# This program generates a sequence of distinct numbers
# such that the length of the sequence can be any power of 2.
# A particular characteristic of the generated sequence is that
# it is symmetric in the sense that an entry j in row i (0<i,j<2^n-1)
# implies that the entry in row j is i.
# More information can be found in O. Y. Takeshita and D. J. Costello, Jr,:
# New classes of algebraic interleavers for turbo-codes," Proc. 1998 IEEE
# International Symposium on Information Theory, Boston, p. 419,
# Aug 16-21, 1998.
#----------------------------------------------------------------------
sub CheckCmdLine {
    chop($ExecName=`basename $0`);
     if ($ARGV[0] eq "") {
        printf "\n\nUsage:  $ExecName Interleaver_Length=2^n \n";
        exit(0);
    }
}
#----------------------------------------------------------------------
sub PrintResult {
    my $Count=0;
    while ($Count <  $Length) {
        print $Perm[$Count] . "\n";
        $Count+=1;
    };
}
#----------------------------------------------------------------------
sub GenerateDT {
    my $Count=0;
    my $Point=$DShift+$CShift;
    my $Quest=$Step+$DShift;
    while ($Count < $Length-1) {
        $Quest%=$Length;
        $Point%=$Length;
        $Perm[$Point]=$Quest;
        $Point=$Quest+$CShift;
        $Count+=1;
        $Quest+=($Count+1)*$Step;
    };
    $Point%=$Length;
    $Perm[$Point]=$DShift; # Close last element.
}
#======================================================================
# MAIN
$Length=$ARGV[0];
CheckCmdLine;
$Step=1;   # default coefficient of permuter (k in the paper);
$DShift=0; # default diagonal shift of the permuter
$CShift=$Length/2; # default cyclic shift of the permuter
                   # generates a type C2 interleaver
GenerateDT;
PrintResult;
#======================================================================

