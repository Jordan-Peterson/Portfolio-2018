import sys
import getopt
import random
import math

def main(argv):
	## Take in all the arguments from command line and define flags
	try:
		opts, args = getopt.getopt(sys.argv[1:],"p:",["p="])
	except getopt.GetoptError:
		errorMessage()
		sys.exit(1)

	## Asign flag values to the correct global variables
	for opt, arg in opts:

		if opt in ("-p","--p"):
			factor1, factor2 = pollard_P1(int(arg))
			print("Factor1 : " + str(factor1) + " Factor2: " + str(factor2))

def pollard_P1(N):

	a = 2

	for i in range(2,N):
		a = (a**i) % N
		d = math.gcd(a-1,N)

		if(d > 1 and d < N):
			return d, N//d

if __name__ == '__main__':
	main(sys.argv[-1:])
