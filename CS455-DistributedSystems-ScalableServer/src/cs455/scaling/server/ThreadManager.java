package cs455.scaling.server;

import java.nio.channels.SelectionKey;
import java.util.ArrayList;
import java.util.LinkedList;

public class ThreadManager implements Runnable {

	// Create local variables
	private int poolSize = 0;
	private ArrayList<WorkerThread> threadPool;
	private LinkedList<Task> taskList;
	private TaskExecutor taskExecute;
	private Server server;

	// Constructor
	protected ThreadManager(int size, TaskExecutor exec, Server s) {
		this.poolSize = size;
		this.taskExecute = exec;
		threadPool = new ArrayList<WorkerThread>(size);
		this.server = s;
		this.initialize();
	}

	// Initialize the thread pool and task list
	public void initialize() {

		// Initialize taskList
		this.taskList = new LinkedList<Task>();

		// create a new thread for total size of pool
		for (int i = 0; i < this.poolSize; ++i) {
			threadPool.add(new WorkerThread(this));
		}

		// Start each thread in thread pool
		for (WorkerThread t : threadPool) {
			new Thread(t).start();
		}

	}

	@Override
	public void run() {

		while (true) {
			// While there are tasks to be processed, find a worker and give the pair to the
			// task executor
			if (!this.taskIsEmpty()) {
				WorkerThread w = this.getThread();
				if (w != null) {
					taskExecute.taskSet(w, this.taskGet());
				}
			}
		}

	}

	// Check if the task list is empty
	private synchronized boolean taskIsEmpty() {
		return taskList.isEmpty();
	}

	// Create a new task and add the task to the task list
	public synchronized boolean taskAdd(byte[] b, SelectionKey k) {
		return this.taskList.add(new Task(b, k));
	}

	// Get a task from the task list
	private synchronized Task taskGet() {
		return this.taskList.remove();
	}

	// Get a free worker thread from the thread pool
	private synchronized WorkerThread getThread() {
		for (int i = 0; i < this.threadPool.size(); ++i) {
			if (this.threadPool.get(i).available()) {
				this.threadPool.get(i).setAvailable(false);
				return this.threadPool.get(i);
			}
		}
		return null;
	}

	// Handle a worker thread returning itself
	public synchronized void retThread(WorkerThread w) {
		for (int i = 0; i < this.threadPool.size(); ++i) {
			if (this.threadPool.get(i) == w) {
				this.threadPool.get(i).setAvailable(true);
				break;
			}
		}
	}

}