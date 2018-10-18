import sys
import getopt
import random
import math

def main(argv):
	## Take in all the arguments from command line and define flags
	try:
		opts, args = getopt.getopt(sys.argv[1:],"p:m:",["p=","m="])
	except getopt.GetoptError:
		errorMessage()
		sys.exit(1)

	## Asign flag values to the correct global variables
	for opt, arg in opts:
		if opt in ("-p", "--p"):
			p = int(arg)
			primes = CountPrime(p)
			print("# of primes between 2 and " + str(p) + " is " + str(primes) + ". With ratio " + str(primes/(p/math.log(p))))
		elif opt in ("-m", "--m"):
			print(Miller_Rabin(int(arg)))

		## print error message if unknown flag is used
		else:
			errorMessage()
			sys.exit(1)

def errorMessage():
	print("Unfamiliar flags, try python3 modularInverse.py -h")

## run the miller-rabin primality test for each number from 2 to a given input
## output the number of prime integers between 2 and X
def CountPrime(p):
	primeCount = 1
	i = 3
	while( i <= p):
		if(Miller_Rabin(i)):
			primeCount += 1
		i += 2
	return primeCount

## Check the primality of a number by seeing if there is a witness that satisfies:
## a^q == 1 mod p
## and a^(2^i * q) == -1 mod p
## for a random 'a'
def Miller_Rabin(p):
	flag = True
	a = 2
	## for T number of tests
	if (p > 10):
		testRange = math.floor(2*(math.log(p)**2))
	else:
		testRange = 10

	for i in range(0,testRange):
		## represent p-1 as 2^k * q, where q is odd
		k = -1
		q = 0
		while (q % 2 is 0):
			k += 1
			q = ((p-1)//(2**k))
		## pick a random number "a"
		if(p <= 3):
			a = random.randint(2,p-1)

		## if a^q != 1 mod p
		## AND a^(2^i * q) != -1 mod p for all 0 <= i <= k-1
		## Then then p is composite because a is a witness
		## if not, then we do not know, move on to next test
		if((a**q)%p != 1):
			for i in range(k):
				if((a**((2**i)*q)) % p == p-1):
					flag = False
			if(flag):
				return False
		a += 1
	return True


if __name__ == '__main__':
	main(sys.argv[-1:])
