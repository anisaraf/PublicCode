package projecteuler;

import java.util.List;

public class Problem2 {

    double addEvenFib(double max){
	double sum = 2;
	double a = 1; double b = 2; double c=3;

	while(c<max){
	    if(c % 2 == 0){
		sum +=c;
	    }
	    a =b;
	    b =c;
	    c = a + b;
	}
	return sum;
    }
}


// Each new term in the Fibonacci sequence is generated by adding the
// previous two terms. By starting with 1 and 2, the first 10 terms
// will be:
 
//     1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

//     By considering the terms in the Fibonacci sequence whose values
//     do not exceed four million, find the sum of the even-valued
//     terms.

//Overview : http://projecteuler.net/project/resources/002_e3b16b7a862527d1e8f03f8ba204d6d0/002_overview.pdf
// Get rid of check for even - every third number is even!
// Another formula! F(n) = 4 * f(n-3) + F(n-6)