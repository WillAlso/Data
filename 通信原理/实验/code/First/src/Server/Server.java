package Server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JDesktopPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class Server extends ServerSocket {
	
	private static final int PORT = 2018;
	private DataInputStream dis;
	private DataOutputStream dos;
	private ServerSocket server;
	private Socket client;
	public Server() throws IOException {
		server = new ServerSocket(PORT);
		while (true) {
			client = server.accept();
			dis = new DataInputStream(client.getInputStream());
			String word = dis.readUTF();
		}
	}

	public static void main(String args[]) {
		try {
			JFrame frame = new JFrame();
			JLabel me = new JLabel("ÏûÏ¢");
			frame.setBounds(100, 100, 450, 300);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			JDesktopPane panel = new JDesktopPane();
			JButton send = new JButton("·¢ËÍ");
			
			JTextArea  message = new JTextArea();
			JTextField se = new JTextField();
			me.setBounds(0, 0, 50, 25);
			message.setBounds(20, 20,400, 150);
			message.setEditable(false);
			send.setBounds(300, 200, 80, 25);
			se.setBounds(20, 200, 200, 25);
			panel.add(me);
			panel.add(send);
			panel.add(message);
			panel.add(se);
			frame.add(panel);
			frame.setVisible(true);
			Server s1 = new Server();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
