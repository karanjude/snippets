/*
Problem Statement
    
Consider 26 different substances, labeled 'A' through 'Z' (quotes for clarity only). Some of these substances can be created from the others by an alchemical reaction. Each alchemical reaction takes at least two different substances. Exactly 1 gram of each input substance is combined, causing an explosion. After the dust settles, we are left with just 1 gram of the resulting substance.
Alchemists don't like extra work, thus, for any given substance, there's at most one known reaction that results in that substance.
You are given a String initial describing the substances that you have initially. Each occurrence of a letter indicates 1 gram, so if a letter appears k times in initial, it means you have k grams of that substance. You are also given a String[] reactions describing all the possible alchemical reactions. Each element of reactions describes a single reaction and is formatted as "ingredients->result" (quotes for clarity only), where ingredients is the list of substances consumed and result is the substance produced. Return the minimal number of reactions required to obtain at least 1 gram of the substance 'X', or -1 if it is impossible.
Definition
    
Class:
QuantumAlchemy
Method:
minSteps
Parameters:
string, vector <string>
Returns:
int
Method signature:
int minSteps(string initial, vector <string> reactions)
(be sure your method is public)
    

Constraints
-
initial will contain between 1 and 50 characters, inclusive.
-
initial will contain only uppercase letters ('A'-'Z').
-
reactions will contain between 1 and 26 elements, inclusive.
-
Each element of reactions will contain between 5 and 28 characters, inclusive.
-
Each element of reactions will be formatted as "ingredients->result" (quotes for clarity only).
-
Each ingredients will be a string of distinct uppercase letters ('A'-'Z').
-
Each result will be an uppercase letter ('A'-'Z').
-
Each result will be distinct.
-
Each ingredients will not contain the corresponding result.
Examples
0)

    
"ABCDE"
{"ABC->F", "FE->X"}
Returns: 2
Some substances may be left unused.
1)

    
"AABBB"
{"BZ->Y", "ZY->X", "AB->Z"}
Returns: 4
First, we make two grams of 'Z' by applying the last reaction twice. Second, we make 'Y' via the first reaction, and we still have 1 gram of 'Z' left, so that we can finally make 'X'.
2)

    
"AAABB"
{"BZ->Y", "ZY->X", "AB->Z"}
Returns: -1
Not enough.
3)

    
"AAXB"
{"BZ->Y", "ZY->X", "AB->Z"}
Returns: 0
No need to bother if we're already there.
4)

    
"ABCDEFGHIJKLMNOPQRSTUVWYZABCDEFGHIJKLMNOPQRSTUVWYZ"
{"ABCE->Z", "RTYUIO->P", "QWER->T", "MN->B"}
Returns: -1
We have a lot of stuff and some reactions, but none of them results in 'X'.
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/