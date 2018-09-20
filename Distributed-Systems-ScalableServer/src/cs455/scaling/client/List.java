package cs455.scaling.client;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.LinkedList;

public class List {

	// Create local variables
	private LinkedList<String> list = new LinkedList<String>();
	private StatisticsThread stats;

	// Constructor
	public List(StatisticsThread t) {
		this.stats = t;
	}

	// Add a new hash to the linked list
	public synchronized void listAdd(byte[] b) {
		list.add(this.hash(b));
	}

	// Check if a string is in the linked list
	public synchronized void listCheck(byte[] b) {
		String s = new String(b);
		if (!isEmpty()) {
			for (int i = 0; i < list.size(); ++i) {
				if (list.get(i).equals(s)) {
					this.stats.addPR();
					list.remove(i);
				}
			}
		}
	}

	// Hash a message of random bytes
	private String hash(byte[] b) {
		MessageDigest digest;
		try {
			digest = MessageDigest.getInstance("SHA1");
			byte[] hash = digest.digest(b);
			BigInteger hashInt = new BigInteger(1, hash);
			return hashInt.toString(16);
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
			return "";
		}
	}

	// Check if linked list is empty
	public synchronized boolean isEmpty() {
		return list.isEmpty();
	}

}
