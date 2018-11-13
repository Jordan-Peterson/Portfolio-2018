import random
import pickle
import networkx as nx

## Node class that represents a single vertex in the graph
class Node:

	## Constructor
	def __init__(self, nodeID, nodeValue=0, edges=[]):
		self.nodeID = nodeID
		self.nodeValue = nodeValue
		self.edges = edges

	## Set and Get
	def setVal(self,i):
		self.nodeValue = i

	def getVal(self):
		return self.nodeValue

	def setNodeID(self,i):
		self.nodeID = i

	def getNodeID(self):
		return self.nodeID

	def addEdge(self,e):
		self.edges.append(e)

	def getEdges(self):
		return self.edges

	def contains(self, n):
		for i in self.edges:
			if(n.getNodeID() == i.getNodeID()):
				return True
		return False

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
## Requirements - a valid graph must have an path between every node
def generateGraph(gSize):

	nodes = {}

	##Generate nodes and populate them with the random numbers already made.
	for e in range(0,gSize):
		nodes.update({e:Node(e,0,[])})
	edges = 0
	## Connect edges randomly from node to node
	## Finished when a solvable graph is created.
	while(not isConnected(nodes)):
		tmpNode1 = nodes.get(random.randint(0,len(nodes)-1))
		tmpNode2 = nodes.get(random.randint(0,len(nodes)-1))
		if(tmpNode1.contains(tmpNode2) or tmpNode2.contains(tmpNode1) or tmpNode1.getNodeID() == tmpNode2.getNodeID()):
			continue
		else:
			tmpNode1.addEdge(tmpNode2)
			tmpNode2.addEdge(tmpNode1)
	return nodes


## Take a generated connected graph and populate each node with random values between 100,-100
def populateGraph(graph,gs):

	## Random numbers range from -10 to 10 for a basic use case
	while(summation(graph) <= 0 or summation(graph) == gs):
		for i in range(0,len(graph)-1):
			graph.get(i).setVal(random.randint(-5,5))
	return graph

## Add up all the values in a graph and return the sum
def summation(graph):
	total = 0
	zeroCount = 0
	for n in graph.values():
		total += n.getVal()
	return total

## Use a simple bfs algorithm to check if a graph is connected or not
## connected: there exists some path from each node to each other node
def isConnected(graph):
	## [1] start at an arbitrary node
	## [2] push its children onto a queue
	## [3] pop the front of the queue
	## [4] add the popped child's children onto the queue
	## [5] if the child has been seen, do nothing
	## [6] End when the queue is empty

	nodesSeen = []
	queue = []

	startNode = random.choice(graph)				#[1]
	nodesSeen.append(startNode.getNodeID())
	for n in startNode.getEdges():					#[2]
		queue.append(n)

	while queue:
		currNode = queue.pop(0)							#[3]
		nodesSeen.append(currNode.getNodeID())
		for n in currNode.getEdges():					#[4]
			if n.getNodeID() not in (nodesSeen) and n not in (queue):			#[5]
				queue.append(n)

	if(len(graph) == len(nodesSeen)):					#[6]
		return True
	else:
		return False

## Look at a graph and calculate G = E - V + 1
## Return True if sum of nodes >= G, else return False
def isSolvable(graph,thresh):

	zeroCount = 0
	pairs = []
	## Find the set of pairs of nodes
	for n in graph.values():
		if(n.getVal() == 0):
			zeroCount += 1
		for c in n.getEdges():
			pair1 = (c.getNodeID(),n.getNodeID())
			pair2 = (n.getNodeID(),c.getNodeID())
			if(pair1 in pairs or pair2 in pairs):
				continue
			else:
				pairs.append(pair1)
				pairs.append(pair2)

	if(len(graph) == zeroCount):
		return False

	## Account for each pairing being counted twice
	edges = len(pairs)//2

	## Calculate the genus of the graph
	genus = edges - len(graph) + 1
	sum = summation(graph)

	## Check if graph is solvable
	if(sum <= genus+thresh and sum >= genus):
		print("solvable graph found with: ",sum," summation and: ",genus," genus")
		return True
	else:
		return False

if __name__ == "__main__":

	## Generate 1 solvable graph
	i = 5
	j = 0
	graphs = []
	while i < 1000000:
		if(j // 100 == 0):
			i += 1
			print(i)
		g = generateGraph(i)
		while not isConnected(g):
			g = generateGraph(i)

		g = populateGraph(g,0)
		while(not isSolvable(g,random.randint(0,10))):
			g = populateGraph(g,summation(g))

		with open("graphs.pickle",'rb') as f:
			try:
				graphs = pickle.load(f)
			except EOFError:
				graphs = []
			graphs.append(g)
		with open("graphs.pickle",'wb') as wf:
			pickle.dump(graphs,wf)
		j +=1
