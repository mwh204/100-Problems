/*irc connection Code from http://archive.oreilly.com/pub/h/1966 */

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import java.net.Socket;

public class Matt_irc_bot_075 {
  
  static final String SERVER = "irc.freenode.net";
  static final String NICK = "memebot1337";
  static final String LOGIN = "memebot1337";
  static final String CHANNEL = "#memebottest";
  
  public static void main(String[] args) throws Exception {
    
    TextGen2 bot = new TextGen2("v.txt");
    String out = "";
    
    // Connect directly to the IRC server.
    Socket socket = new Socket(SERVER, 6667);
    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
    BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    
    // Log on to the server.
    sendMsg(writer, "NICK " + NICK);
    sendMsg(writer, "USER " + LOGIN + " 8 * : Java IRC Bot");
    
    // Read lines from the server until it tells us we have connected.
    String line = null;
    while ((line = reader.readLine()) != null) {
      if (line.indexOf("004") >= 0) {
        // We are now logged in.
        break;
      }else if (line.indexOf("433") >= 0) {
        System.out.println("Nickname is already in use.");
        return;
      }
    }
    
    //Join the channel.  
    sendMsg(writer, "JOIN " + CHANNEL);
    
    // Keep reading lines from the server.
    while ((line = reader.readLine()) != null) {
      if (line.startsWith("PING ")) {
        // We must respond to PINGs to avoid being disconnected.
        sendMsg(writer, "PONG " + line.substring(5));
      }else if(line.toLowerCase().contains(".speak")){
        out = bot.generateSentence();
        sendMsg(writer, "PRIVMSG " + CHANNEL +" :"+out);
      }else if(line.toLowerCase().contains(".command")){
        //add other commands here
      }else{
        // Print the raw line received by the bot.
        System.out.println(line);
      }
    }
  }//main
  
  public static void sendMsg(BufferedWriter writer, String msg) throws Exception{
    writer.write(msg + "\r\n");
    writer.flush();
  }
}
