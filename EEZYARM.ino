#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#include <Servo.h>

Servo serv0;
Servo serv1;
Servo serv2;
Servo serv3;

const char* ssid = "AllYourWifiAreBelongToUs";
const char* password = "chanchitos";
 
const int P0 = 16;   
const int P1 = 5;  
const int P2 = 4;    
const int P3 = 0;    

String pos0 = "90";   
String pos1 = "90";  
String pos2 = "90";    
String pos3 = "90";  

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  serv0.attach(P0); 
  serv1.attach(P1);
  serv2.attach(P2); 
  serv3.attach(P3); 
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  server.on("/", handleRootPath);      //Associate the handler function to the path
 
}
 
void loop() {
  server.handleClient();         //Handling of incoming requests
}


void handleRootPath() {            //Handler for the rooth path
  
  for (int i = 0; i < server.args(); i++) {
    if (server.argName(i) == "servo0") {
        pos0 = server.arg(i);
        serv0.write(server.arg(i).toInt());
    }
    if (server.argName(i) == "servo1") {
        pos1 = server.arg(i);
        serv1.write(server.arg(i).toInt());
    }
    if (server.argName(i) == "servo2") {
        pos2 = server.arg(i);
        serv2.write(server.arg(i).toInt());
    }
    if (server.argName(i) == "servo3") {
        pos3 = server.arg(i);
        serv3.write(server.arg(i).toInt());
    }
  } 
  
  String message = "<html><form>"
  "<input name=\"servo0\" value=\"" + pos0 + "\" type=\"range\" min=\"80\" max=\"135\" step=\"1\" /><br>"
  "<input name=\"servo1\" value=\"" + pos1 + "\" type=\"range\" min=\"20\" max=\"135\" step=\"1\" /><br>"
  "<input name=\"servo2\" value=\"" + pos2 + "\" type=\"range\" min=\"80\" max=\"120\" step=\"1\" /><br>"
  "<input name=\"servo3\" value=\"" + pos3 + "\" type=\"range\" min=\"60\" max=\"135\" step=\"1\" /><br>"
  "<button type=\"submit\">GO</button></form></html>";
  server.send(200, "text/html", message);

}
//  client.println("<br>" + message + "<br>");
//  client.print("<form>");
//  
//  client.println("<input name=\"servo0\" type=\"range\" min=\"60\" max=\"135\" step=\"1\" />");
//  client.println("<input name=\"servo1\" type=\"range\" min=\"60\" max=\"135\" step=\"1\" />");
//  client.println("<input name=\"servo2\" type=\"range\" min=\"60\" max=\"135\" step=\"1\" />");
//  client.println("<input name=\"servo3\" type=\"range\" min=\"60\" max=\"135\" step=\"1\" />");
//  client.println("<button type=\"submit\">GO</button></form>");
//  client.println("</html>");
// 
//  delay(1);
//  Serial.println("Client disonnected");
//  Serial.println("");
