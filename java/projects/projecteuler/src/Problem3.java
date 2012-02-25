package projecteuler;

import java.util.List;

public class Problem3 {
    double largestPrimeFactor(double num){
	double maxPrime = 2;
	for (double i = 2; i <= Math.sqrt(num); i++) {
	    if(num % i == 0){
		maxPrime = i;
		num /=i;
		i--;
		
	    }
	    
	}
	return maxPrime;

    }

}



// The prime factors of 13195 are 5, 7, 13 and 29.

// What is the largest prime factor of the number 600851475143 ?

