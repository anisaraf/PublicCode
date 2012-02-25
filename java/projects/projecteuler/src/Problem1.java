package projecteuler;

import java.util.List;

public class Problem1 {
    public double getSumofMultiples(int start, int end, List<Integer> multiplesOf){
	double sum = 0;
	for(int i = start; i<=end;i++){
	    for(int m: multiplesOf) {
		if(i % m == 0) {
		    sum+=i;
		    break;
		}
	    }
	}
	return sum;
    }
}




// If we list all the natural numbers below 10 that are multiples of 3 or
// 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.

// LINKS:
// http://stackoverflow.com/questions/1005073/initialization-of-an-arraylist-in-one-line

// Overview:
// target=999
//     Function SumDivisibleBy(n)
//       p=target div n
//     return n*(p*(p+1)) div 2
//     EndFunction
//     Output SumDivisibleBy(3)+SumDivisibleBy(5)-SumDivisibleBy(15)

// better for larger numbers since we can just sum and subtract the common elements. 5(1+2+..) etc.
