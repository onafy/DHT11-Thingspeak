#include <ESP8266WiFi.h>
#include <DHT.h>
//apikey coba
//String apikey = "4LF7QP8OFKR0I4FC";
//String apikey = "78YULG5KVH0FB397";
//String apikey = "W3HYJ2EWEQ1NKKMH";

//suhu dalam
String apikey ="D5FWUZ8ASFKFPBRE";

//suhu luar
//String apikey = "6O4IBTKRI2G7NKIH";

//const char* ssid="nov";
//const char* password="";
const char* ssid="TP-Link_4D4A";
const char* password="87293630";
const char* server="api.thingspeak.com";

#define DHTPIN D8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  //delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   dht.begin();

  }


void loop() {
  int i=1;
  float ratasuhu=0;
  float ratakelembaban =0;
  for(i=1;i<=15;i++)
  {
    float suhu = dht.readTemperature();
    float kelembaban = dht.readHumidity();
    ratasuhu = ratasuhu + suhu;
    ratakelembaban= ratakelembaban+ kelembaban;
     Serial.print("Temperature = ");
     Serial.print(suhu);
     Serial.print("Humidity = ");
     Serial.println(kelembaban);
     delay(1000);
  }
  Serial.println("------------------------------------------------------------------------------");
  ratasuhu = ratasuhu / 15;
  ratakelembaban = ratakelembaban / 15;
  Serial.print("Rata Temperature = ");
  Serial.print(ratasuhu);
  Serial.print("Rata Kelembaban = ");
  Serial.println(ratakelembaban);

  
  if (client.connect(server,80)) {
  String postStr = apikey;
  postStr +="&field1=";
  postStr += String(ratasuhu);
  postStr +="&field2=";
  postStr += String(ratakelembaban);
  postStr += "\r\n\r\n";
  //delay(1000); 

  //kirim data
  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apikey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\n\n");
  client.print(postStr);
  //delay(1000);

 
  Serial.println("Mengirim Data Thingspeak");
  }
  else{
    client.stop();
    Serial.println("Gagal Koneksi Thingspeak");
  }
  
  //delay(4000);
  Serial.println("Delay 2 detik");
  delay(2000);
}
