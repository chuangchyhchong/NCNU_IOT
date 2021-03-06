#include <WiFi.h>
uint8_t MacData[6];
char ssid[] = "NCNU";      // your network SSID (name)
char pass[] = "";     // your network password
int keyIndex = 0;     
IPAddress  Meip ,Megateway ,Mesubnet ;
String MacAddress ;
// your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
WiFiServer server(80);
#define RelayPin 13
#define RelayPin2 12
#define RelayPin3 11
#define RelayPin4 10
#define Turnon HIGH
#define Turnoff LOW

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(RelayPin, OUTPUT);      // set the LED pin mode
  pinMode(RelayPin2, OUTPUT);      // set the LED pin mode
    pinMode(RelayPin3, OUTPUT);      // set the LED pin mode
      pinMode(RelayPin4, OUTPUT);      // set the LED pin mode
      // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }
  
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid);    //no pass
//    status = WiFi.begin(ssid, pass);    //wpa use
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");

            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/1H\">Led1 on</a> turn Power on<br>");
            client.print("Click <a href=\"/1L\">Led1 off</a> turn Power off<br>");
            client.print("Click <a href=\"/2H\">Led2 on</a> turn Power on<br>");
            client.print("Click <a href=\"/2L\">Led2 off</a> turn Power off<br>");
            client.print("Click <a href=\"/3H\">Led3 on</a> turn Power on<br>");
            client.print("Click <a href=\"/3L\">Led3 off</a> turn Power off<br>");
            client.print("Click <a href=\"/4H\">Led4 on</a> turn Power on<br>");
            client.print("Click <a href=\"/4L\">Led4 off</a> turn Power off<br>");
//            client.print("Click <a href=\"/3H\">here</a> turn Power on<br>");
//            client.print("Click <a href=\"/4L\">here</a> turn Power off<br>");
//            client.print("Click <a href=\"/C\">here</a> turn Power off<br>");
//            client.print("Click <a href=\"/D\">here</a> turn Power off<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /1H")) {
          digitalWrite(RelayPin, Turnon);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /1L")) {
          digitalWrite(RelayPin, Turnoff);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /2H")) {
          digitalWrite(RelayPin2, Turnon);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /2L")) {
          digitalWrite(RelayPin2, Turnoff);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /3H")) {
          digitalWrite(RelayPin3, Turnon);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /3L")) {
          digitalWrite(RelayPin3, Turnoff);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /4H")) {
          digitalWrite(RelayPin4, Turnon);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /4L")) {
          digitalWrite(RelayPin4, Turnoff);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void ShowMac()
{
  
     Serial.print("MAC:");
     Serial.print(MacAddress);
     Serial.print("\n");

}




String GetWifiMac()
{
   String tt ;
    String t1,t2,t3,t4,t5,t6 ;
    WiFi.status();    //this method must be used for get MAC
  WiFi.macAddress(MacData);
  
  Serial.print("Mac:");
   Serial.print(MacData[0],HEX) ;
   Serial.print("/");
   Serial.print(MacData[1],HEX) ;
   Serial.print("/");
   Serial.print(MacData[2],HEX) ;
   Serial.print("/");
   Serial.print(MacData[3],HEX) ;
   Serial.print("/");
   Serial.print(MacData[4],HEX) ;
   Serial.print("/");
   Serial.print(MacData[5],HEX) ;
   Serial.print("~");
   
   t1 = print2HEX((int)MacData[0]);
   t2 = print2HEX((int)MacData[1]);
   t3 = print2HEX((int)MacData[2]);
   t4 = print2HEX((int)MacData[3]);
   t5 = print2HEX((int)MacData[4]);
   t6 = print2HEX((int)MacData[5]);
 tt = (t1+t2+t3+t4+t5+t6) ;
Serial.print(tt);
Serial.print("\n");
  
  return tt ;
}
String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  return ttt ;
}





void printWifiData() 
{
  // print your WiFi shield's IP address:
  Meip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(Meip);
  Serial.print("\n");

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

  // print your subnet mask:
  Mesubnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(Mesubnet);

  // print your gateway address:
  Megateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(Megateway);
}

void ShowInternetStatus()
{
    
        if (WiFi.status())
          {
               Meip = WiFi.localIP();
               Serial.print("Get IP is:");
               Serial.print(Meip);
               Serial.print("\n");
              
          }
          else
          {
                       Serial.print("DisConnected:");
                       Serial.print("\n");
          }

}
