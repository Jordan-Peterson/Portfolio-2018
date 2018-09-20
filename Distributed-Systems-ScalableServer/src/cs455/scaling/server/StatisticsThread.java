package cs455.scaling.server;

import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Map;

public class StatisticsThread implements Runnable {

	// Create local variables
	private volatile long packets_sent = 0;
	private volatile long packets_received = 0;
	private volatile int connections = 0;
	private volatile double Mean = 0;
	private volatile double std_dev = 0;
	private volatile double perClientMean = 0;
	private volatile double throughput = 0;

	private Map<SocketChannel, Integer> clientMap = new HashMap<SocketChannel, Integer>();

	@Override
	public void run() {
		while (true) {
			try {
				// Every 20 seconds print stats
				Thread.sleep(20000);
				this.printStats();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	// Calculate and print stats
	private synchronized void printStats() {
		this.perClientMean = this.getMean();
		this.calcThru();
		this.std_dev = this.calcDev();
		System.out.println("[" + System.currentTimeMillis() + "] Server Throughput: " + this.calcThru()
				+ " messages/s, Active Client Connections: " + this.getCon() + ", Mean Per-client Throughput: "
				+ this.perClientMean + " messages/s, Std. Dev. Of Per-client Throughput: " + this.std_dev
				+ " messages/s");
		this.packets_received = 0;
		this.packets_sent = 0;
		this.Mean = 0;
		for (SocketChannel k : this.clientMap.keySet()) {
			this.clientMap.replace(k, 0);
		}

	}

	// log packets sent
	public synchronized void addPS() {
		this.packets_sent++;
	}

	// log packets revceived
	public synchronized void addPR() {
		this.packets_received++;
	}

	// Get number of sent packets
	public synchronized long getSent() {
		return this.packets_sent;
	}

	// Get number of received packets
	public synchronized long getRec() {
		return this.packets_received;
	}

	// log number of connections
	public synchronized void addCon() {
		this.connections++;
	}

	// Get number of connections
	public synchronized int getCon() {
		return this.connections;
	}

	// Calculate throughput
	private synchronized double calcThru() {
		this.throughput = (double) (this.packets_sent / 20);
		return this.throughput;
	}

	// Calculate standard deviation
	private synchronized double calcDev() {
		double ss = 0;
		for (SocketChannel k : this.clientMap.keySet()) {
			ss += Math.pow((this.clientMap.get(k).intValue() / 20) - this.Mean, 2);
		}
		ss /= this.getCon();
		return Math.sqrt(ss);
	}

	// Get mean per-client throughput
	private synchronized double getMean() {
		double sum = 0;
		for (SocketChannel k : this.clientMap.keySet()) {
			sum += this.clientMap.get(k).intValue();
		}
		this.Mean = (sum / this.getCon()) / 20;
		return this.Mean;
	}

	// Log per-client packets processed
	public synchronized void incClient(SocketChannel k) {
		if (this.clientMap.containsKey(k)) {
			int temp = this.clientMap.get(k).intValue();
			this.clientMap.replace(k, temp, temp + 1);
		}
	}

	// Log a new client to keep track of packets processed
	public synchronized void addClient(SocketChannel k) {
		this.clientMap.put(k, 0);
	}

}
