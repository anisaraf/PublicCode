package codeherb.topcoder;

public class PairingPawns {
    public String[] getSortedList(String[] kings){
       
    }
}


/* Problem Statement
        
    Every good encyclopedia has an index. The entries in the index are usually sorted in alphabetic order. However, there are some notable exceptions. In this task we will consider one such exception: the names of kings.
    In many countries it was common that kings of the same name received ordinal numbers. This ordinal number was written as a Roman numeral and appended to the actual name of the king. For example, "Louis XIII" (read: Louis the thirteenth) was the thirteenth king of France having the actual name Louis.
    In the index of an encyclopedia, kings who share the same name have to be sorted according to their ordinal numbers. For example, Louis the 9th should be listed after Louis the 8th.
    You are given a String[] kings. Each element of kings is the name of one king. The name of each king consists of his actual name, a single space, and a Roman numeral. Return a String[] containing the names rearranged into their proper order: that is, the kings have to be in ascending lexicographic order according to their actual name, and kings with the same name have to be in the correct numerical order.
    Definition
        
    Class:
    KingSort
    Method:
    getSortedList
    Parameters:
    String[]
    Returns:
    String[]
    Method signature:
    String[] getSortedList(String[] kings)
    (be sure your method is public)
        

    Notes
    -
    The Roman numerals for 1 through 10 are I, II, III, IV, V, VI, VII, VIII, IX, and X.
    -
    The Roman numerals for 20, 30, 40, and 50 are XX, XXX, XL, and L.
    -
    The Roman numeral for any other two-digit number less than 50 can be constructed by concatenating the numeral for its tens and the numeral for its ones. For example, 47 is 40 + 7 = "XL" + "VII" = "XLVII".
    -
    Standard string comparison routines give the correct ordering for the actual names of kings.
    -
    Formally, given two different strings A and B we say that A is lexicographically smaller than B if either (A is a prefix of B) or (there is at least one index where A and B differ, and for the smallest such index the character in A has a lower ASCII value than the character in B).
    Constraints
    -
    Each actual name of a king will be a string containing between 1 and 20 characters, inclusive.
    -
    Each actual name will start by an uppercase letter ('A'-'Z').
    -
    Each other character in each actual name will be a lowercase letter ('a'-'z').
    -
    kings will contain between 1 and 50 elements, inclusive.
    -
    Each element of kings will have the form "ACTUALNAME ORDINAL", where ACTUALNAME is an actual name as defined above, and ORDINAL is a valid Roman numeral representing a number between 1 and 50, inclusive.
    -
    The elements of kings will be pairwise distinct.
    Examples
    0)

	    
	    {"Louis IX", "Louis VIII"}
Returns: {"Louis VIII", "Louis IX" }
Louis the 9th should be listed after Louis the 8th.
    1)

	    
	    {"Louis IX", "Philippe II"}
Returns: {"Louis IX", "Philippe II" }
Actual names take precedence over ordinal numbers.
    2)

	    
	    {"Richard III", "Richard I", "Richard II"}
Returns: {"Richard I", "Richard II", "Richard III" }

3)

        
	{"John X", "John I", "John L", "John V"}
Returns: {"John I", "John V", "John X", "John L" }

4)

        
	{"Philippe VI", "Jean II", "Charles V", "Charles VI", "Charles VII", "Louis XI"}
Returns:
{"Charles V",
		"Charles VI",
		"Charles VII",
		"Jean II",
		"Louis XI",
		"Philippe VI" }
These are the French monarchs who ruled between 1328 and 1483.
    5)

	    
	    {"Philippe II", "Philip II"}
Returns: {"Philip II", "Philippe II" }
"Philippe" and "Philip" are distinct names, and "Philip" is lexicographically smaller than "Philippe".
		This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved. */