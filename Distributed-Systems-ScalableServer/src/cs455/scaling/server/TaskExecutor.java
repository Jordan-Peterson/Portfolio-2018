package cs455.scaling.server;

import java.util.HashMap;
import java.util.Map;

public class TaskExecutor implements Runnable {

	// Create local variables
	private Map<WorkerThread, Task> tasks;
	private Server server;

	// Constructor
	public TaskExecutor(Server s) {
		this.server = s;
		this.tasks = new HashMap<WorkerThread, Task>();
	}

	@Override
	public void run() {
		while (true) {

			// While there are workers working on tasks, check to see if any has finished
			while (!isEmpty()) {

				// Call finishing method
				this.finishWorker();
			}
		}
	}

	// Check if there are any workers with tasks
	public synchronized boolean isEmpty() {
		return this.tasks.isEmpty();
	}

	// Add a worker and task to the list and start the task
	public synchronized void taskSet(WorkerThread w, Task t) {
		this.tasks.put(w, t);
		w.setTask(t);

	}

	// For each worker that is finished, give the result to the server
	private synchronized void finishWorker() {
		for (WorkerThread w : tasks.keySet()) {
			if (w.isDone()) {
				this.server.doneAdd(this.tasks.get(w));
				this.finished(w);
				break;
			}
		}
	}

	// Return the worker to the thread
	public synchronized void finished(WorkerThread w) {
		this.tasks.remove(w);
		w.setDone(false);
	}

}