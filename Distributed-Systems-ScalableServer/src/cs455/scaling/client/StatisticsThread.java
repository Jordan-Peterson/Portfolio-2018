package cs455.scaling.client;

public class StatisticsThread implements Runnable {

	// Create local variables
	private volatile long packets_sent = 0;
	private volatile long packets_received = 0;

	@Override
	public void run() {
		while (true) {
			try {
				// Every 20 seconds print the statistics
				Thread.sleep(20000);
				this.printStats();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}

	// Print statistics
	private synchronized void printStats() {

		System.out.println("[" + System.currentTimeMillis() + "] Total Sent Count: " + this.getSent()
				+ ", Total Received Count: " + this.getRec());
		this.packets_received = 0;
		this.packets_sent = 0;

	}

	// Log a packet being sent
	public synchronized void addPS() {
		this.packets_sent++;
	}

	// Log a packet being received
	public synchronized void addPR() {
		this.packets_received++;
	}

	// Get number of packets sent
	private synchronized long getSent() {
		return this.packets_sent;
	}

	// Get number of packets received
	private synchronized long getRec() {
		return this.packets_received;
	}

}
