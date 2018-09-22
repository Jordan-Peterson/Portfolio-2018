import random

## Node class that represents a single vertex in the graph
class Node:

	## Constructor
	def __init__(self, nodeID, nodeValue, edges):
		self.nodeID = nodeID
		self.nodeValue = nodeValue
		self.edges = edges

	## Give one value to each node connected to self.
	## Subtract the number of connected edges from self value.
	def pushOnEdge(self):
		self.nodeValue -= len(edges)
		for e in edges:
			e.nodeValue += 1

	## Get one value from each connected node.
	## add the number of connected edges to self value.
	def pullOnEdge(self):
		self.nodeValue += len(edges)
		for e in edges:
			e.nodeValue -= 1

## Generate a random solvable graph.
## "Solvable" satisfies the equation V - E + 1 = G where sum(all nodes) >= G
def generateGraph(gSize):
	randVal =[]
	nodes = []
	graph = {}

	## Create a list of random numbers that make up a solvable graph
	## Random numbers range from -100 to 100 for a basic use case
	while(randVal and summation(randVal) is not 0):
		for i in range(0,gSize):
			randVal.append(random.randint(-100,100))

	##Generate nodes and populate them with the random numbers already made.
	for e in range(0,gSize):
		node =(Node(e, randVal.pop(), []) 
		nodes.append(node)
		graph.update(e, [])

	## Connect edges randomly from node to node
	## Finished when a solvable graph is created.
	while(not isSolvable(graph)):
		tmpNode1 = nodes[random.randint(0,gSize)]
		tmpNode2 = nodes[random.randint(0,gSize)]

		if(not tmpNode1.edges.contains(tmpNode2)):
			tmpNode1.edges.append(tmpNode2)
			tmpNode2.edges.append(tmpNode1)
			graph.update(tmpNode1.nodeID, tmpNode1.edges)
			graph.update(tmpNode2.nodeID, tmpNode2.edges)


## Add up all the values in a list and return if the sum is 0 or not
## Return True if sum is 0, else return False
def summation(list):
	total = 0
	for i in list:
		total += i
	if total == 0:
		return True
	return False


## Look at a graph and calculate G = V - E + 1
## Return True if sum of nodes >= G, else return False
def isSolvable(graph):


if __name__ == __main__:
main()
