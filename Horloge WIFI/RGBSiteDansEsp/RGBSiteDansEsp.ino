/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

//Load Wi-Fi library

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
// Replace with your network credentials
const char* ssid     = "Freebox-5C9A25";
const char* password = "viebas-plasmari?3-occultati!-incogitans";
SoftwareSerial ESPserial(3, 1); // RX | TX
// Set web server port number to 80
WiFiServer server(80);

// Decode HTTP GET value
String redString = "0";
String greenString = "0";
String blueString = "0";
String PanneauString = "0";
int r;
int g;
int b;
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5= 0;
// Variable to store the HTTP req  uest
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Start the software serial for communication with the ESP8266
   /* ESPserial.begin(115200);  
    
    ESPserial.write("");
    ESPserial.write("Remember to to set Both NL & CR in the serial monitor.");
    ESPserial.write("Ready");
    ESPserial.write("");   */
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  /*Serial.print("A");
  Serial.print("255");
  Serial.print("\n");
  delay(1000);*/
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
   // Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {            // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
     //   Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
                   
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">");
            client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/jscolor/2.0.4/jscolor.min.js\"></script>");
            client.println("</head><body><div class=\"container\"><div class=\"row\"><h1>Panneau 1</h1></div>");
            client.println("<a class=\"btn btn-primary btn-lg\" href=\"#\" id=\"change_color1\" role=\"button\">Change Color</a> ");
            client.println("<input class=\"jscolor {onFineChange:'update(this)'}\" id=\"P1\"></div>");
            client.println("<div class=\"container\"><div class=\"row\"><h1>Panneau 2</h1></div><a class=\"btn btn-primary btn-lg\" href=\"\" id=\"change_color2\" role=\"button\">Change Color</a><input class=\"jscolor {onFineChange:'update(this)'}\" id=\"P2\"></div>");
            client.println("<div class=\"container\"><div class=\"row\"><h1>Panneau 3</h1></div><a class=\"btn btn-primary btn-lg\" href=\"\" id=\"change_color3\" role=\"button\">Change Color</a><input class=\"jscolor {onFineChange:'update(this)'}\" id=\"P3\"></div>");
            client.println("<div class=\"container\"><div class=\"row\"><h1>Panneau 4</h1></div><a class=\"btn btn-primary btn-lg\" href=\"\" id=\"change_color4\" role=\"button\">Change Color</a><input class=\"jscolor {onFineChange:'update(this)'}\" id=\"P4\"></div>");
            client.println("<div id=\"buttons\"><a  href=\"\" id=\"Horloge\" role=\"button\"><button onclick=sendTime()>SetClock</button> </a></div>");
            client.println("<div id=\"buttons\"><a  href=\"\" id=\"Rainbow\" role=\"button\"><button onclick=rainbow()>Rainbow</button> </a></div>");
            client.println("<script>function update(picker) {document.getElementById(picker.targetElement.id).innerHTML = Math.round(picker.rgb[0]) + ', ' +  Math.round(picker.rgb[1]) + ', ' + Math.round(picker.rgb[2]);document.getElementById(\"change_color\"+picker.targetElement.id.slice(-1)).href=\"?r\" + Math.round(picker.rgb[0]) + \"g\" +  Math.round(picker.rgb[1]) + \"b\" + Math.round(picker.rgb[2]) +picker.targetElement.id+ \"&\";}");          // The HTTP response ends with another blank line
            client.println("function checkTime(i) {return (i < 10) ? \"0\" + i : i;}function sendTime() {var today = new Date();h = checkTime(today.getHours());min = checkTime(today.getMinutes());s = checkTime(today.getSeconds());document.getElementById(\"Horloge\").href=\"?r\"+h+\"g\"+min+\"b\"+s+\"P5&\";console.log(\"T\"+h+min+s);}");
            client.println("function rainbow(){document.getElementById(\"Rainbow\").href=\"?r1g1b1P6&\";}</script>");
            client.println();

            // Request sample: /?r201g32b255&
            // Red = 201 | Green = 32 | Blue = 255
            if(header.indexOf("GET /?r") >= 0) {
              pos1 = header.indexOf('r');
              pos2 = header.indexOf('g');
              pos3 = header.indexOf('b');
              pos4 = header.indexOf('P');
              pos5= header.indexOf('&');
              redString = header.substring(pos1+1, pos2);
              greenString = header.substring(pos2+1, pos3);
              blueString = header.substring(pos3+1, pos4);
              PanneauString= header.substring(pos4+1, pos5);
             /* Serial.println("RGBP");
              Serial.println(redString.toInt());
              Serial.println(greenString.toInt());
              Serial.println(blueString.toInt());
              Serial.println(PanneauString.toInt());*/
              delay(100);
              r=redString.toInt();
              g=greenString.toInt();
              b=blueString.toInt();
            
              sendToArduino(PanneauString.toInt(),r,g,b);
              
              
            }
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
   // Serial.println("Client disconnected.");
    //Serial.println("");
  }
}

void sendToArduino(int P,int r,int g,int b){
 /*
const char LEDRdH='A' ,LEDGdH='B',LEDBdH='C';
const char LEDRmH='D' ,LEDGmH='E',LEDBmH='F';
const char LEDRdM='G' ,LEDGdM='N',LEDBdM='I';
const char LEDRmM='J' ,LEDGmM='K',LEDBmM='L'; 
const char SetHeure='Q', SetMin='M',SetSec='S';
*/
   switch (P)
    {
      case 1:
      {
       Serial.print('A');
       Serial.print(r);
       delay(100);
       Serial.print('B');
       Serial.print(g);
       delay(100);
       Serial.print('C');
       Serial.print(b);
        delay(100);
      break;
      }
      case 2:
      {
       Serial.print('D');
       Serial.print(r);
       delay(100);
       Serial.print('E');
       Serial.print(g);
       delay(100);
       Serial.print('F');
       Serial.print(b);
        delay(100);
      break;
      }
      case 3:
      {
       Serial.print('G');
       Serial.print(r);
       delay(100);
       Serial.print('N');
       Serial.print(g);
       delay(100);
       Serial.print('I');
       Serial.print(b);
        delay(100);
      break;
      }
      case 4:
      {
       Serial.print('J');
       Serial.print(r);
       delay(100);
       Serial.print('K');
       Serial.print(g);
       delay(100);
       Serial.print('L');
       Serial.print(b);
        delay(100);
      break;
      }
      case 5:
      {
       Serial.print('Q');
       Serial.print(r);
       delay(100);
       Serial.print('M');
       Serial.print(g);
       delay(100);
       Serial.print('S');
       Serial.print(b);
        delay(100);
      break;
      }
      case 6:
      {
       Serial.print('O');
       Serial.print(1);
  
      break;
      }
}
}
