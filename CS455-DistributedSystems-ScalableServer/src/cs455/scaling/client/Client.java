package cs455.scaling.client;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Random;

public class Client {

	int MESSAGE_SIZE = 8192;

	// Local variables
	private String host = "";
	private int port = 0;
	private int sendRate = 0;
	private StatisticsThread statThread;
	private Thread stats;
	private Selector selector;
	private List list;

	// class constructor
	protected Client(String s, int p, int sr) {
		this.host = s;
		this.port = p;
		this.sendRate = sr;
		this.statThread = new StatisticsThread();
		this.stats = new Thread(this.statThread);
		this.list = new List(this.statThread);

		try {
			this.selector = Selector.open();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	// Initialize threads and run client
	protected void initialize() throws IOException, InterruptedException {
		// create a channel to the server
		System.out.println("Starting client");
		this.stats.start();
		this.startClient();

	}

	private void startClient() throws IOException, InterruptedException {
		SocketChannel channel = SocketChannel.open();
		channel.configureBlocking(false);
		channel.register(selector, SelectionKey.OP_CONNECT);
		channel.connect(new InetSocketAddress(this.host, this.port));
		while (true) {
			selector.select();
			// wake up to work on selected keys
			Iterator<SelectionKey> keys = this.selector.selectedKeys().iterator();
			while (keys.hasNext()) {
				SelectionKey key = keys.next();
				// see what type of key the selector has selected
				if (key.isConnectable()) {
					this.connect(key);
				}
				if (key.isWritable()) {
					this.write(key);
				}
				if (key.isReadable()) {
					this.read(key);
				}

				keys.remove();
			}
		}
	}

	// Setup connection to the server
	private void connect(SelectionKey key) throws IOException {
		SocketChannel channel = (SocketChannel) key.channel();
		channel.finishConnect();
		key.interestOps(SelectionKey.OP_WRITE);
	}

	// Write to a channel
	private void write(SelectionKey key) throws IOException, InterruptedException {
		long start = System.currentTimeMillis();
		SocketChannel channel = (SocketChannel) key.channel();

		// Wait for a given amount of time
		Thread.sleep(1000 / this.sendRate);
		ByteBuffer buffer = ByteBuffer.allocate(MESSAGE_SIZE);

		// Generate a random message and write it to the channel
		buffer = ByteBuffer.wrap(this.genMessage());
		channel.write(buffer);
		this.statThread.addPS();
		key.interestOps(SelectionKey.OP_READ | SelectionKey.OP_WRITE);
		long end = System.currentTimeMillis();
		
		System.out.println(end-start);

	}

	// Read message from a channel
	private void read(SelectionKey key) throws IOException {
		SocketChannel channel = (SocketChannel) key.channel();

		// Create container for message that is the correct size
		ByteBuffer size = ByteBuffer.allocate(1);
		channel.read(size);
		byte[] bytesize = size.array();
		ByteBuffer message = ByteBuffer.allocate((int) bytesize[0]);

		// Read in the whole message
		int read = 0;
		try {
			while (message.hasRemaining() && read != -1) {
				read = channel.read(message);
			}

			// Send message to the hash checker
			this.list.listCheck(message.array());
		} catch (IOException e) {
			/* Abnormal termination */
			// Cancel the key and close the socket channel
			key.cancel();
			channel.close();
		}
		message.flip();
		if (read == -1) {
			/* Connection was terminated by the client. */
			// Cancel the key and close the socket channel
			key.cancel();
			channel.close();
			return;
		}
		key.interestOps(SelectionKey.OP_WRITE | SelectionKey.OP_READ);
	}

	// Generate random message of size MESSAGE_SIZE
	private byte[] genMessage() {
		byte[] arr = new byte[MESSAGE_SIZE];
		Random rand = new Random();
		rand.nextBytes(arr);
		this.list.listAdd(arr);
		return arr;

	}

	public static void main(String args[]) throws InterruptedException {
		Client client = new Client(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]));
		try {
			client.initialize();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(1);
		}

	}
}
