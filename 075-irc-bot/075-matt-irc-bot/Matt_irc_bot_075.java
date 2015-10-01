/*irc connection Code from http://archive.oreilly.com/pub/h/1966 */

import java.io.*;
import java.net.*;

public class Matt_irc_bot_075 {
  
  static final String SERVER = "irc.freenode.net";
  static final String NICK = "memebot1337";
  static final String LOGIN = "memebot1337";
  static final String CHANNEL = "#memebottest";
  
  public static void main(String[] args) throws Exception {
    
    TextGen bot = new TextGen();
    String out = "";
    
    // Connect directly to the IRC server.
    Socket socket = new Socket(SERVER, 6667);
    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
    BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    
    // Log on to the server.
    writer.write("NICK " + NICK + "\r\n");
    writer.write("USER " + LOGIN + " 8 * : Java IRC Bot\r\n");
    writer.flush();
    
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
    
    // Join the channel.
    writer.write("JOIN " + CHANNEL + "\r\n");
    writer.flush();
    
    // Keep reading lines from the server.
    while ((line = reader.readLine()) != null) {
      if (line.startsWith("PING ")) {
        // We must respond to PINGs to avoid being disconnected.
        writer.write("PONG " + line.substring(5) + "\r\n");
        //writer.write("PRIVMSG " + CHANNEL + " :I got pinged!\r\n");
        writer.flush();
      }else if(line.toLowerCase().contains(".speak")){
        do{
          out = bot.generateSentence(bot.dict, bot.words);
        }while(bot.countWords(out) < bot.SENT_MIN_LEN);
        out = "PRIVMSG " + CHANNEL +" :"+out+"\r\n";
        writer.write(out);
        writer.flush();
      }else{
        // Print the raw line received by the bot.
        System.out.println(line);
      }
    }
  }//main
}
