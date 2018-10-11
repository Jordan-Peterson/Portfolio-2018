import math
import sys
import getopt
import modularInverse

def main(argv):
	##Given values:
	g = 0 # Must be from a group, with order >= 2
	h = 0
	p = 0 # Must be prime

	## Take in all the arguments from command line and define flags
	try:
		opts, args = getopt.getopt(sys.argv[1:],"g:h:p:",["g=","h=","p="])
	except getopt.GetoptError:
		errorMessage()
		sys.exit(1)

	## Asign flag values to the correct global variables
	for opt, arg in opts:
		if opt in ("-g","--g"):
			g = int(arg)
		elif opt in ("-h","--h"):
			h = int(arg)
		elif opt in ("-p","--p"):
			p = int(arg)

		## print error message if unknown flag is used
		else:
			errorMessage()
			sys.exit(1)

	##STEP 1: compute 1 + floor(sqrt(ORD(g)))
	n = 1 + math.floor(math.sqrt(findOrder(g,p)))

	##STEP 2: create two list: [1] e,g,g^2,g^3,...g^n [2] h,h*g^-n, h*g^-2n,...,h*g^-n^2
	listOne = genList(0,g,h,n,p)
	listTwo = genList(1,g,h,n,p)

	##STEP 3: find a match within the two lists
	sorted_listOne, sorted_listTwo, match = findMatch(listOne,listTwo)

	# check if there was a match
	if not match:
		print("failed to find a match")
		sys.exit(1)

	##STEP 4: x = i + jn
	x = listOne.index(match) + listTwo.index(match)*n

	##Return answer
	print("The solution for : " + str(g) + "^x = " + str(h) + " is : x = " + str(x))

## Given g and p, find the order of g through exponentiation
## : yes this is brute forcing, but the time spent shouldn't matter
def findOrder(g, p):
	order = 1
	while (g**order % p) is not 1:
		order += 1

	return order

## Given input v of either 0 or 1 generate a list of elements e,g,...,g^n
## or generate a list of elements h, h*g^-n, h*g^-2n,...,h*g^-n^2
def genList(v,g,h,n,p):

	if not v:								#[1]
		list = [1]
		for i in range(1,n):
			list.append((g**i) % p)
		return list

	else:									#[2]
		list = [h]
		g = modularInverse.ExtendedEuclid(g**n,p).q1
		for i in range(1,n):
			list.append((h * (g**i))%p)
		return list


## Find a match between two given lists.
## [1] First sort both lists
## [2] Then iterate through the list until you find a find a match
## : again a brute force, but the comparisons shouldn't take too long
def findMatch(listOne, listTwo):

											#[1]
	sorted_listOne = sorted(listOne)
	sorted_listTwo = sorted(listTwo)

											#[2]
	for e1 in sorted_listOne:
		for e2 in sorted_listTwo:
			if e1 == e2:
				return sorted_listOne, sorted_listTwo, e1

	return sorted_listOne, sorted_listTwo, 0

def errorMessage():
	print("Unfamiliar flags, try python3 shankAlg.py -[g <number for g>, h <number for h>, p <number for p>")

if __name__ =='__main__':
	main(sys.argv[1:])
