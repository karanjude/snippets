/*
Problem Statement
    
An encryption algorithm is applied on a piece of original text containing only lowercase letters ('a'-'z') and spaces. The original text contains no leading or trailing spaces, and no consecutive spaces. A word is defined as a maximal consecutive sequence of letters. Each word in the original text is between 2 and 8 characters long, inclusive, and contains at least one vowel ('a', 'e', 'i', 'o' or 'u').
The encryption algorithm works as follows. Spaces and lowercase letters all have corresponding numeric values. The number 0 corresponds to a space, and the numbers 1 through 26 correspond to the letters 'a' through 'z', respectively.
First, a password is chosen. The password is a non-empty sequence of lowercase letters ('a'-'z'). Take the first character of the original text and the first character of the password, and add their numeric values together. This sum, modulo 27, corresponds to the first character of the encrypted text. For example, if the first character of the text is 'x', and the first character of the password is 'd', then the first character of the encrypted text will be 'a' ('x' + 'd' = 24 + 4 = 28, 28 mod 27 = 1 = 'a').
Perform the same transformation using the second character of the original text and the second character of the password, and so on. When you run out of letters in the password, cycle back to the first letter of the password.
For example, let's encrypt the text "hello world" with the password "pun": hello world punpunpunpu ----------- xzzainlieay
The encrypted text is "xzzainlieay".
Given the encrypted text as a String cipherText, you must determine the original text without knowing the password. Thanks to frequency analysis, you know that the password contains exactly 3 letters. Return the original text that satisfies the requirements given above. It is guaranteed that a single unique solution exists. All quotes in the problem statement are for clarity only.
Definition
    
Class:
SimpleRotationDecoder
Method:
decode
Parameters:
string
Returns:
string
Method signature:
string decode(string cipherText)
(be sure your method is public)
    

Notes
-
The password does not contain spaces.
-
The password is not required to contain vowels.
Constraints
-
cipherText will contain between 3 and 50 characters, inclusive.
-
cipherText will contain only spaces (' ') and lowercase letters ('a'-'z').
-
There will be exactly one correct solution.
Examples
0)

    
"mmbtvrbhhtgohaktklqegnrmlelojotyeyeiudvtil ey ffg"
Returns: "the quick brown fox jumps over the lazy dog again"
This text was encrypted with the password "tex".
1)

    
"ntgntgntgntofwlfwlfwlnookookook"
Returns: "he he he heh he he heh he he he"

2)

    
"f sgnzslhzquq ydyuinmqiwfyrtdvn"
Returns: "abkbprnn usmlbqz mdpelkoa jofni"

3)

    
"shxnaaeqjlofhhsuurbhpdgt z"
Returns: "naeiui jrghnca pnzxaxz avs"

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/