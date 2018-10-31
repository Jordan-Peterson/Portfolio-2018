import sys
import getopt
import random
import math

def main(argv):
	## Take in all the arguments from command line and define flags
	try:
		opts, args = getopt.getopt(sys.argv[1:],"p:s:",["p=","s="])
	except getopt.GetoptError:
		errorMessage()
		sys.exit(1)

	## Asign flag values to the correct global variables
	for opt, arg in opts:

		if opt in ("-p","--p"):
			factor1, factor2 = pollard_P1(int(arg))
			print("Factor1 : " + str(factor1) + " Factor2: " + str(factor2))
		elif opt in ("-s", "--s"):
			f1,f2 = difSquare(int(arg))
			print("Factor1 : " + str(f1) + " Factor2 : " + str(f2))


def pollard_P1(N):

	a = 2

	for i in range(2,N):
		a = (a**i) % N
		d = math.gcd(a-1,N)

		if(d > 1 and d < N):
			return d, N//d

def difSquare(N):

	b = 1
	x = N + b
	while(math.sqrt(x)-int(math.sqrt(x)) != 0):
		 b += 1
		 x = N + math.pow(b,2);

	return (int(math.sqrt(x))+b),(int(math.sqrt(x))-b)

if __name__ == '__main__':
	main(sys.argv[-1:])
