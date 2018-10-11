# Purpose

This project is a personal package for performing information security mathematical formulas. The current modules include:

* modularInverse.py : This module supports finding the GCD of two values and the modular inverse through the Extended Euclidian algorithm. Use of this module is as follows:

	* GCD(a,b) : -g <a,b> Used to find the gcd between to numbers using the euclidian algorithm
                    @Returns: single integer value of greatest common divisor of a,b

	* Extended Euclidian Algorithm(a,p) : -e <a,p> Used to find the inverse of 'a' with respect to prime number 'p'.

* shankAlg.py : This module computes implementes Shank's (Babystep-Giantstep) Algorithm to solve the discrete logorithm problem in O( sqrt(ORD(g)) * log(ORD(g)) ) time and O( sqrt(ORD(g)) ) space. Use of this module is as follows:
  	* Shank's Algorithm: -g <a value within a group> -h <a value == g^(some x) mod p> -p <a prime integer>
		* Note: g must have an order greater than or equal to 2 for this algorithm to work. This algorithm solves for x in the above equation.

### Language:

* Python
