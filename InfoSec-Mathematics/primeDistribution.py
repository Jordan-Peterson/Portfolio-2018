import sys
import getopt
import random

def main(argv):
	## Take in all the arguments from command line and define flags
	try:
		opts, args = getopt.getopt(sys.argv[1:],"p:",["p="])
	except getopt.GetoptError:
		sys.exit(1)

	## Asign flag values to the correct global variables
	for opt, arg in opts:
		if opt in ("-p","--p"):
			print(PollardRho(int(arg)))

		## print error message if unknown flag is used
		else:
			sys.exit(1)

			
## This algorithm is used to find the prime factorization of a number n
## credit to this algorithm is to geeksforgeeks
## url: https://www.geeksforgeeks.org/pollards-rho-algorithm-prime-factorization/
## This is my python conversion of the C/C++ code they wrote
def PollardRho(n):

	## no factorization of 1
	if (n == 1):
		return n
	## number is even
	if (n % 2 == 0):
		return 2

	x = random.randint(2,n-1)
	y = x

	c = random.randint(1,n-1)

	d = 1

	while (d==1):

		## Tortoise Move: x(i+1) = f(x(i))
		x = (pow(x,2,n) + c + n)%n

		## Hare Move: y(i+1) = f(f(y(i)))
		y = (pow(y, 2, n) + c + n)%n
		y = (pow(y, 2, n) + c + n)%n

		d = GCD(abs(x-y),n)

		if (d==n):
			PollardRho(n)
	return d

def GCD(a,b):
	if(a == b):
		return a

	if(b > a):
		a, b = b, a

	if(a > b):
		r = a % b
		while r != 0:
			a = b
			b = r
			r = a % b
		return b

if __name__ == '__main__':
	main(sys.argv[1:])
