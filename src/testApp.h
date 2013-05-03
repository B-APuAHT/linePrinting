#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxTrueTypeFontUC.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

#define HOST "localhost"
#define PORT 12345
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    vector<int> splitLineToInts(string value);
    wstring intsToWstring(vector<int> inputs);
    void addSpacesToWstring(wstring& input);

    ofxTrueTypeFontUC myFont;
    ofxOscReceiver receiver;
    ofxXmlSettings XML;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    float textPos;
    int windowWidth;
    float speedPos;
    int spaceAmount;
    float topIndent;
    wstring tickerStr;
};
