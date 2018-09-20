package cs455.scaling.server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Server {

	// Create local variables
	private int port;
	private int tpSize = 0;
	private ThreadManager threadManage;
	private TaskExecutor taskExecutor;
	private Thread taskExec;
	private Thread threadManager;
	private StatisticsThread stats;
	private Thread statsThread;
	private Selector selector;
	private Map<SelectionKey, ArrayList<Task>> doneList;
	private int buffSize = 8192;

	// Constructor
	public Server(int port, int tpsize) {
		// Instantiate local variables
		this.port = port;
		this.tpSize = tpsize;

		// Create a TaskExecutor object
		this.taskExecutor = new TaskExecutor(this);
		this.taskExec = new Thread(this.taskExecutor);

		// Create a ThreadManager object
		this.threadManage = new ThreadManager(this.tpSize, taskExecutor, this);
		this.threadManager = new Thread(threadManage);

		// Create a StatisticsThread object
		this.stats = new StatisticsThread();
		this.statsThread = new Thread(stats);

	}

	// Initialize the server
	protected void initialize() {
		// start all threads and open selector
		this.taskExec.start();
		this.threadManager.start();
		this.statsThread.start();
		this.doneList = new HashMap<SelectionKey, ArrayList<Task>>();
		try {
			this.selector = Selector.open();
		} catch (IOException e) {
		}
	}

	// Start server to connect to clients
	private void startServer() throws IOException {
		// Create a Selector
		ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
		serverSocketChannel.configureBlocking(false);
		serverSocketChannel.socket().bind(new InetSocketAddress(this.port));
		serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
		while (true) {
			// wait for events
			this.selector.select();
			// wake up to work on selected keys
			Iterator<SelectionKey> keys = this.selector.selectedKeys().iterator();
			while (keys.hasNext()) {
				// Get what type of key it is
				SelectionKey key = keys.next();
				if (key.isAcceptable()) {
					this.accept(key);
				}
				if (key.isReadable()) {
					this.read(key);
				}
				if (key.isWritable()) {
					if (this.doneList.containsKey(key)) {
						this.write(key);
					}
				}

				keys.remove();
			}
		}
	}

	// Accept an incoming communication
	private void accept(SelectionKey key) throws IOException {
		ServerSocketChannel servSocket = (ServerSocketChannel) key.channel();
		SocketChannel channel = servSocket.accept();
		channel.configureBlocking(false);

		// Add a connection and store the channel for statistics
		this.stats.addCon();
		this.stats.addClient(channel);
		channel.register(selector, SelectionKey.OP_READ);
	}

	// Read in a message from a client
	private void read(SelectionKey key) throws IOException {
		SocketChannel channel = (SocketChannel) key.channel();
		ByteBuffer buffer = ByteBuffer.allocate(buffSize);

		// Read the whole message
		int read = 0;
		try {
			while (buffer.hasRemaining() && read != -1) {
				read = channel.read(buffer);
			}

			// Log stat and give message to the ThreadManager
			this.stats.addPR();
			this.threadManage.taskAdd(buffer.array(), key);
		} catch (IOException e) {
			/* Abnormal termination */
			// Cancel the key and close the socket channel
			key.cancel();
			channel.close();
		}
		buffer.flip();
		if (read == -1) {
			/* Connection was terminated by the client. */
			// Cancel the key and close the socket channel
			key.cancel();
			channel.close();
			return;
		}
		// Give task to the task executor

		key.interestOps(SelectionKey.OP_WRITE | SelectionKey.OP_READ);
	}

	// Write a message to the client
	private void write(SelectionKey key) throws IOException {
		SocketChannel channel = (SocketChannel) key.channel();

		// Get a message that is waiting to be sent to this particular client
		byte[] message = this.doneGet(key);
		if (message != null) {

			// Package message with the length at the front
			int message_length = message.length;
			byte[] arr = new byte[message_length + 1];
			arr[0] = (byte) message_length;
			for (int i = 1; i < arr.length; ++i) {
				arr[i] = message[i - 1];
			}
			ByteBuffer buffer = ByteBuffer.wrap(arr);

			// Write message and log stats
			channel.write(buffer);
			this.stats.addPS();
			this.stats.incClient(channel);
		}
		key.interestOps(SelectionKey.OP_READ | SelectionKey.OP_WRITE);
	}

	// Get a message from a queue of messages for a specific client
	public synchronized byte[] doneGet(SelectionKey k) {
		if (!this.doneList.get(k).isEmpty()) {
			return this.doneList.get(k).remove(0).getBytes();
		} else {
			return null;
		}
	}

	// Add messages to the correct client queue
	public synchronized void doneAdd(Task t) {

		// If the client exists append to the queue
		if (this.doneList.containsKey(t.getKey())) {
			this.doneList.get(t.getKey()).add(t);

			// If the client does not exist create a new entry and queue
		} else {
			this.doneList.put(t.getKey(), new ArrayList<Task>());
			this.doneList.get(t.getKey()).add(t);
		}
	}

	public static void main(String args[]) {
		Server server = new Server(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
		server.initialize();
		try {
			server.startServer();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
