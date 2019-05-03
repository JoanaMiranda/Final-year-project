import apsync.*;
import processing.serial.*;


PFont f;
AP_Sync streamer;

StringBuilder toArduino = new StringBuilder();

Table table;

public int pump1;
public int pump2;
public int function;
public String location;
float mapExcel = 0;
float mapped = 0;


void setup() {
  size(500, 300);
  table = new Table();

  streamer = new AP_Sync(this, "/dev/cu.usbmodem14101", 9600);
  table.addColumn("data");

  background(49);

  f = createFont("Arial", 36, true);
  stroke(255);
  textFont(f, 36);
  fill(255);
}

void draw() {
  background(49);
  textAlign(CENTER);
  stroke(255);
  text(toArduino.toString(), width/2, 3*height/4);

  //if (function == '1') {
  Plot();
  saveTable(table, "pump_values.csv");
  //}
}

//if (function == '2') {
//  sleep();
//}

//if (function == '3') {
//  anxious();
//}

//if (function == '4') {
//  off();
//}
//}

void keyPressed() {

  if (keyCode == ENTER) {
    println(toArduino + " sent");
    streamer.send(toArduino.toString());
    toArduino.setLength(0);
  }
  if (keyCode == DELETE || keyCode == BACKSPACE) {
    if (toArduino.length() > 0) {
      toArduino.deleteCharAt(toArduino.length() - 1);
    }
  }

  if (keyCode != ENTER &&
    keyCode != DELETE &&
    keyCode != ESC &&
    keyCode != UP &&
    keyCode != DOWN &&
    keyCode != BACKSPACE &&
    keyCode != TAB &&
    keyCode != ALT &&
    keyCode != CONTROL &&
    keyCode != RETURN ) {

    toArduino.append(key);
  }
}
void Plot() {

  //pump1 = 255 or 0 
  //pump2 = 0 or 255
  //cycle time is (3000ms, then 1500) x 3
  if (int(location) > 0) {
    mapped = map(int(location), 0, 3000, 150, 225);
    mapExcel = map(int(location), 0, 3000, 0, 255);
    ellipse(250, 150, mapped, mapped);
    TableRow newRow = table.addRow();
    newRow.setInt("data", int(mapExcel));
    println(mapped);
  }
}
