#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    //ofBackground(255,255,255);
    receiver.setup(PORT);
    if( XML.loadFile("mySettings.xml") ){
		cout << "mySettings.xml loaded!";
	}else{
		cout << "unable to load mySettings.xml check data/ folder";
	}

	string fontName = XML.getValue("font","mono.ttf");
	int fontSize = XML.getValue("fontSize", 7);
	myFont.loadFont(fontName, fontSize, true, true);
	float red =   XML.getValue("color:red", 100);
    float green = XML.getValue("color:green", 100);
    float blue =  XML.getValue("color:blue", 100);
	ofSetColor(red,green,blue);
	speedPos = XML.getValue("speed", 1.0f);
	spaceAmount = XML.getValue("spacesAmount", 1);
	topIndent = XML.getValue("topIndent", 100.0f);
	textPos = 0.0f;
	windowWidth = ofGetWidth();
	tickerStr = L"";
}

//--------------------------------------------------------------
void testApp::update(){
        // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        // unrecognized message: display on the bottom of the screen
        string msg_string = "";
        tickerStr = L"";
        //msg_string = m.getAddress();
        //msg_string += ": ";
        for(int i = 0; i < m.getNumArgs(); i++){
            // get the argument type
            //msg_string += m.getArgTypeName(i);
            //msg_string += ":";
            // display the argument - make sure we get the right type
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                msg_string += ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msg_string += ofToString(m.getArgAsFloat(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                msg_string += m.getArgAsString(i);
                tickerStr += intsToWstring(splitLineToInts(m.getArgAsString(i)));
                addSpacesToWstring(tickerStr);
            }
            else{
                msg_string += "unknown";
            }
        }
        cout << msg_string << endl;

        textPos = 0;
        // add to the list of strings to display
        /*msg_strings[current_msg_string] = msg_string;
        timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
        current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
        // clear the next line
        msg_strings[current_msg_string] = "";*/

	}
	if (textPos > windowWidth + myFont.stringWidth(tickerStr)) textPos = 0;
	textPos += speedPos;
}

//--------------------------------------------------------------
void testApp::draw(){
    myFont.drawString(tickerStr, windowWidth - textPos, topIndent);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

vector<int> testApp::splitLineToInts(string value)
{
    vector<string> stringInts;
    vector<int> result;
    istringstream iss(value);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(stringInts));
    for (int i = 0; i < stringInts.size(); i++)
        result.push_back( atoi(stringInts.at(i).c_str()));
    return result;
}

wstring  testApp::intsToWstring(vector<int> inputs)
{
    wstring result = L"";
    for (int i = 0; i < inputs.size(); i++)
        result += wchar_t(inputs.at(i));

    return result;
}

void testApp::addSpacesToWstring(wstring& input)
{
    for (int i = 0; i < spaceAmount; i++)
        input += L" ";
}
