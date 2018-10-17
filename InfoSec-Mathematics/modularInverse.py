import sys
import getopt

def main(argv):

	## Take in all the arguments from command line and define flags
	try:
		opts, args = getopt.getopt(sys.argv[1:],"g:e:",["gcd=","extend=="])
	except getopt.GetoptError:
		errorMessage()
		sys.exit(1)

	## Asign flag values to the correct global variables
	for opt, arg in opts:
		if opt in ("-g","--gcd"):
			values = arg.split(',')
			print(Gcd(int(values[0]),int(values[1])))
		elif opt in ("-e", "--extend"):
			values = arg.split(',')
			ExtendedEuclid(int(values[0]),int(values[1])).toString()

		## print error message if unknown flag is used
		else:
			errorMessage()
			sys.exit(1)

def errorMessage():
	print("Unfamiliar flags, try python3 modularInverse.py -h")

class Remainder():

	def __init__(self, name, value1, value2):
		self.name = name
		self.value1 = value1
		self.value2 = value2
		self.q1 = 1
		self.q2 = -1

	def getQ1(self):
		return self.q1

	def getQ2(self):
		return self.q2

	def toString(self):
		print(str(self.name) + " = " + str(self.value1) + " (" + str(self.q1) + ") + " + str(self.value2) + " (" + str(self.q2) + ")")

def Gcd(a,b):
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

def ExtendedEuclid(a, b):
	rList = []
	qList = []
	objList = []

	if(a == b):
		return a

	if(b > a):
		a, b = b, a
	x = a
	y = b

	qList.append(a//b)
	r = a % b
	rList.append(r)
	while r != 0:
		a = b
		b = r
		qList.append(a//b)
		r = a % b
		rList.append(r)

	i = 0
	for r in rList[:-1]:

		objList.append(Remainder(r,x,y))

		if(r == rList[0]):
			objList[-1].q2 = (qList[i] * (-1))
			i += 1

		elif(r == rList[1]):
			print(qList[i])
			objList[-1].q1 = -qList[i]
			objList[-1].q2 = -(qList[i-1] * objList[-1].q2) + 1
			i += 1

		else:
			objList[-1].q1 = objList[-3].q1 -(qList[i] * objList[-2].q1)
			objList[-1].q2 = objList[-3].q2 -(qList[i] * objList[-2].q2)
			i += 1

	return objList.pop()

if __name__== '__main__':
	main(sys.argv[1:])
