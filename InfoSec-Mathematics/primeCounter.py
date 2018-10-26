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
		primeCount += is_Prime(i)
		i += 2
	return primeCount

## Check the primality of a number by seeing if there is a witness that satisfies:
## a^q == 1 mod p
## and a^(2^i * q) == -1 mod p
## for a random 'a'
def is_Prime(p):
	## Take care of trivial cases
	if (p == 2 or p == 3):
		return 1
	elif(p < 2 or p % 2 ==0):
		return 0

	## all that's left under 9 is 5 or 7
	elif(p < 9):
		return 1
	elif(p % 3 == 0):
		return 0

	r = int(math.sqrt(p))
	f = 5

	while(f <= r):
		if (p % f ==0 or p %(f+2) == 0):
			return 0
		else:
			f+=6
	return 1


if __name__ == '__main__':
	main(sys.argv[-1:])
