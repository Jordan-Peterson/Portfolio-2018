package cs455.scaling.server;

import java.nio.channels.SelectionKey;

public class Task {

	// Create local variables
	private byte[] task = null;
	private SelectionKey key = null;
	private String result = "";

	// Constructor
	public Task(byte[] b, SelectionKey k) {
		this.task = b;
		this.key = k;
	}

	// Get the result in byte[]
	public byte[] getBytes() {
		byte[] tmp = this.result.getBytes();
		return tmp;
	}

	// Get the task
	public byte[] getTask() {
		return task;
	}

	// Set the task
	public void setBytes(byte[] b) {
		this.task = b;
	}

	// Set the result
	public void setResult(String s) {
		this.result = s;
	}

	// Get the key for the destination
	public SelectionKey getKey() {
		return this.key;
	}

	// Set the key for the destination
	public void setKey(SelectionKey k) {
		this.key = k;
	}
}
