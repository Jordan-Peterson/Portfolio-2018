package cs455.scaling.server;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class WorkerThread implements Runnable {

	// Create local variables
	private boolean available = true;
	private Task task = null;
	private boolean done = false;
	private ThreadManager threadManager;

	// Constructor
	public WorkerThread(ThreadManager t) {
		this.threadManager = t;
	}

	@Override
	public void run() {
		while (true) {

			// While this thread has a task to do, work on it
			if (this.hasTask()) {

				// Make itself unavailable
				this.setAvailable(false);

				// Get the byte[] from the task and create a hash of it
				this.task.setResult(this.doWork(this.task.getTask()));

				// Finished hashing and notify that it is done
				this.setDone(true);

				// Wait until it has been acknowledged
				while (this.isDone()) {

				}

				// Reset task, make itself available, return itself to the thread pool
				this.setTask(null);
				this.setAvailable(true);
				this.threadManager.retThread(this);

			}
		}

	}

	// Check if this worker is available
	public synchronized boolean available() {
		return this.available;
	}

	// Change the availablility of this worker
	public synchronized void setAvailable(boolean b) {
		this.available = b;
	}

	// Give this worker a task
	public synchronized void setTask(Task t) {
		this.task = t;
	}

	// Check if this worker has a task to do
	private synchronized boolean hasTask() {
		if (this.task == null) {
			return false;
		} else {
			return true;
		}
	}

	// Set this worker to done working
	public synchronized void setDone(boolean b) {
		this.done = b;
	}

	// Check if this worker is done working
	public synchronized boolean isDone() {
		return this.done;
	}

	// Create hash of task
	private String doWork(byte[] b) {
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

}