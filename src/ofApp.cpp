#include "ofApp.h"

#define BARS_OFFSET 150
#define BAR_WIDTH 40
#define APP_PADDING 20
#define CHANNEL_BOX_HEIGHT 85
#define REFRESH_RATE 2000 //every 1 minute

bool initialized = false;
int channel = 0;
int frame = 0;
int timer = 0;
bool saving = false;
bool particlesMode = false;

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(33,33,33);
	ofSetFrameRate(50);
	ofSetColor(255, 255, 255);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableAlphaBlending();

    titleFont.loadFont("bebasneue-webfont.ttf", 35);
    starFont.loadFont("bebasneue-webfont.ttf", 30);
	clientFont.loadFont("bebasneue-webfont.ttf", 15);
	tweetFont.loadFont("bebasneue-webfont.ttf", 12);

    if( ! bird.loadImage("bird.png")) printf("Bird loading failed");
    if( ! bg.loadImage("bg.jpg")) printf("Bg loading failed");

    t1Button.setPosAndSize(APP_PADDING, BARS_OFFSET - APP_PADDING, ofGetWidth() - APP_PADDING, CHANNEL_BOX_HEIGHT);
    t1Button.enableMouseEvents();

    t2Button.setPosAndSize(APP_PADDING, BARS_OFFSET - APP_PADDING + 100, ofGetWidth() - APP_PADDING, CHANNEL_BOX_HEIGHT);
    t2Button.enableMouseEvents();

    t3Button.setPosAndSize(APP_PADDING, BARS_OFFSET - APP_PADDING + 200, ofGetWidth() - APP_PADDING, CHANNEL_BOX_HEIGHT);
    t3Button.enableMouseEvents();

    t4Button.setPosAndSize(APP_PADDING, BARS_OFFSET - APP_PADDING + 300, ofGetWidth() - APP_PADDING, CHANNEL_BOX_HEIGHT);
    t4Button.enableMouseEvents();

    t5Button.setPosAndSize(APP_PADDING, BARS_OFFSET - APP_PADDING + 400, ofGetWidth() - APP_PADDING, CHANNEL_BOX_HEIGHT);
    t5Button.enableMouseEvents();

    t6Button.setPosAndSize(APP_PADDING, BARS_OFFSET - APP_PADDING + 500, ofGetWidth() - APP_PADDING, CHANNEL_BOX_HEIGHT);
    t6Button.enableMouseEvents();

    returnButton.setPosAndSize(APP_PADDING, APP_PADDING, ofGetWidth(), 100);
    returnButton.enableMouseEvents();

    ofBuffer buffer = ofBufferFromFile("tags.txt");

    if( buffer.size())
    {
        while(buffer.isLastLine() == false)
        {
            string line = buffer.getNextLine();

            if(line.empty() == false) {
                tags.push_back(line);
            }
        }
    }

    t1Sentiments.setup(tags[0]);
    t2Sentiments.setup(tags[1]);
    t3Sentiments.setup(tags[2]);
    t4Sentiments.setup(tags[3]);
    t5Sentiments.setup(tags[4]);
    t6Sentiments.setup(tags[5]);
}

//--------------------------------------------------------------
void ofApp::update()
{
	if( (frame == 5 && !initialized) || (timer == REFRESH_RATE - 500) )
        t1Sentiments.startTwitterQuery(0);

	if( (frame == 60 && !initialized) || (timer == REFRESH_RATE - 400) )
        t2Sentiments.startTwitterQuery(0);

	if( (frame == 120 && !initialized) || (timer == REFRESH_RATE - 300) )
        t3Sentiments.startTwitterQuery(0);

	if( (frame == 180 && !initialized) || (timer == REFRESH_RATE - 200) )
        t4Sentiments.startTwitterQuery(0);

	if( (frame == 240 && !initialized) || (timer == REFRESH_RATE - 100) )
        t5Sentiments.startTwitterQuery(0);

	if( (frame == 300 && !initialized) || (timer == REFRESH_RATE) )
        t6Sentiments.startTwitterQuery(0);

    if( frame > 360)
    {
        frame = 1;
        initialized = true;
    }
    else
        frame++;

    if( timer == REFRESH_RATE)
        timer = 0;
    else
        timer++;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    string title = "Tweet-mood-meter / FPS: " + ofToString(ofGetFrameRate(), 2) + " / Frame: " + ofToString(frame);
    ofSetWindowTitle(title);

    bg.resize(ofGetWidth(), ofGetHeight());
    bg.draw(0,0);

    if( !initialized )
    {
        starFont.drawString("ANALYZING SENTIMENTS", ofGetWidth() / 2 - 130, ofGetHeight() / 2);

        if( frame > 320 ) clientFont.drawString("READY!", ofGetWidth() / 2 - 130, ofGetHeight() / 2 + 30);
        else clientFont.drawString("LOADING ", ofGetWidth() / 2 - 130, ofGetHeight() / 2 + 30);

        if( frame > 0 && frame <= 50 ) clientFont.drawString("TWEETS...", ofGetWidth() / 2 - 70, ofGetHeight() / 2 + 30);
        if( frame > 50 && frame <= 100 ) clientFont.drawString("GENETIC PATTERNS...", ofGetWidth() / 2 - 70, ofGetHeight() / 2 + 30);
        if( frame > 100 && frame <= 150 ) clientFont.drawString("PREDICTIVE ALGORITHMS...", ofGetWidth() / 2 - 70, ofGetHeight() / 2 + 30);
        if( frame > 150 && frame <= 200 ) clientFont.drawString("DECISION TREES...", ofGetWidth() / 2 - 70, ofGetHeight() / 2 + 30);
        if( frame > 200 && frame <= 250 ) clientFont.drawString("ASSOCIATION RULES...", ofGetWidth() / 2 - 70, ofGetHeight() / 2 + 30);
        if( frame > 250 && frame <= 320 ) clientFont.drawString("ARTIFICIAL NEURAL NETWORKS...", ofGetWidth() / 2 - 70, ofGetHeight() / 2 + 30);
    }
    else
    {
        if( !particlesMode )
        {
            ofSetColor(254, 199, 11); //YELLOWISH
            titleFont.drawString("TWEET-MOOD-METER MEASURES THE ", 20, 60);
            ofSetColor(0, 255, 0);
            titleFont.drawString("LOVE ", 570, 60);
            ofSetColor(254, 199, 11);
            titleFont.drawString("AND ", 660, 60);
            ofSetColor(255, 0, 0);
            titleFont.drawString("HATE ", 20, 100);
            ofSetColor(254, 199, 11);
            titleFont.drawString("FEEDBACK OF CONSUMERS ON TWITTER", 110, 100);

            // Draw the star
            ofPushMatrix();

            ofSetColor(255, 255, 255);
            ofTranslate(ofGetWidth() - 100,50,0);
            ofRotate(frame, 0, 1, 0);
            drawStar(0, 0, 120, 100);
            ofSetColor(0, 0, 0);
            starFont.drawString("SENTIMENT", -70, 10);
            starFont.drawString("EXTRACTION", -78, 50);

            ofPopMatrix();
        }

        ofSetColor(255, 255, 255);
        string loadingText = "Analyzing ";
        bool loading = false;

        if( channel == 0 )
        {
            for( int j = 0; j < 6; j++ )
            {
                ofxJSONElement tweets;
                bird.draw(20, BARS_OFFSET + (j*100));

                switch(j)
                {
                    case 0: if( t1Sentiments.loading ) { loading = true; clientFont.drawString( loadingText + tags[0] + " ...", 50, BARS_OFFSET + 20 + (j*100)); }
                            else { tweets = t1Sentiments.getLatestResponse(); clientFont.drawString( tags[0], 50, BARS_OFFSET + 20 + (j*100)); } break;

                    case 1: if( t2Sentiments.loading ) { loading = true; clientFont.drawString( loadingText + tags[1] + " ...", 50, BARS_OFFSET + 20 + (j*100)); }
                            else { tweets = t2Sentiments.getLatestResponse(); clientFont.drawString( tags[1], 50, BARS_OFFSET + 20 + (j*100)); } break;

                    case 2: if( t3Sentiments.loading ) { loading = true; clientFont.drawString( loadingText + tags[2] + " ...", 50, BARS_OFFSET + 20 + (j*100)); }
                            else { tweets = t3Sentiments.getLatestResponse(); clientFont.drawString( tags[2], 50, BARS_OFFSET + 20 + (j*100)); } break;

                    case 3: if( t4Sentiments.loading ) { loading = true; clientFont.drawString( loadingText + tags[3] + " ...", 50, BARS_OFFSET + 20 + (j*100)); }
                            else { tweets = t4Sentiments.getLatestResponse(); clientFont.drawString( tags[3], 50, BARS_OFFSET + 20 + (j*100)); } break;

                    case 4: if( t5Sentiments.loading ) { loading = true; clientFont.drawString( loadingText + tags[4] + " ...", 50, BARS_OFFSET + 20 + (j*100)); }
                            else { tweets = t5Sentiments.getLatestResponse(); clientFont.drawString( tags[4], 50, BARS_OFFSET + 20 + (j*100)); } break;

                    case 5: if( t6Sentiments.loading ) { loading = true; clientFont.drawString( loadingText + tags[5] + " ...", 50, BARS_OFFSET + 20 + (j*100)); }
                            else { tweets = t6Sentiments.getLatestResponse(); clientFont.drawString( tags[5], 50, BARS_OFFSET + 20 + (j*100)); } break;
                }

                if( tweets.size() > 0 )
                {
                    int barFactor = ofGetWidth() / BAR_WIDTH;
                    int totalWidth = tweets.size() * barFactor;

                    string tweetText = "";
                    string tweetDate = "";
                    int positive = 0;
                    int negative = 0;
                    int n = 0;

                    tweetText = tweets[n]["text"].asString();
                    tweetDate = tweets[n]["date"].asString().substr(4, 18);

                    for( int i = 0; i < tweets.size(); i++ )
                    {
                        if( tweets[i]["polarity"].asInt() == 4 ) positive++;
                        if( tweets[i]["polarity"].asInt() == 0 ) negative++;
                    }

                    roundedRect(20, BARS_OFFSET + 30 + (j*100), totalWidth, 10, 5);
                    ofSetColor(255, 0, 0);
                    roundedRect(20, BARS_OFFSET + 30 + (j*100), (positive + negative) * barFactor, 10, 5);
                    ofSetColor(0, 255, 0);
                    roundedRect(20, BARS_OFFSET + 30 + (j*100), positive * barFactor, 10, 5);
                    ofSetColor(255, 255, 255);

                    tweetFont.drawString(ofToString(tweets.size() * 3) + "% HYPE", 20 + tweets.size() * barFactor + 10, BARS_OFFSET + 40 + (j*100));
                    ofSetColor(254, 199, 11);
                    tweetFont.drawString(tweetDate, 20, BARS_OFFSET + 60 + (j*100));
                    ofSetColor(255, 255, 255);
                    tweetFont.drawString(tweetText, 150, BARS_OFFSET + 60 + (j*100));
                }
                else
                {
                    /*switch( j )
                    {
                        case 0: if( !t1Sentiments.loading ) t1Sentiments.startTwitterQuery(0); break;
                        case 1: if( !t2Sentiments.loading ) t2Sentiments.startTwitterQuery(0); break;
                        case 2: if( !t3Sentiments.loading ) t3Sentiments.startTwitterQuery(0); break;
                        case 3: if( !t4Sentiments.loading ) t4Sentiments.startTwitterQuery(0); break;
                        case 4: if( !t5Sentiments.loading ) t5Sentiments.startTwitterQuery(0); break;
                        case 5: if( !t6Sentiments.loading ) t6Sentiments.startTwitterQuery(0); break;
                    }*/
                }
            }
        }

        if( channel == 0 )
        {
            //Check buttons
            ofSetColor(255,255,255);
            ofNoFill();

            if( t1Button.isMouseOver() ) roundedRect(10,BARS_OFFSET - 10,ofGetWidth() - 20,CHANNEL_BOX_HEIGHT, 5);
            if( t2Button.isMouseOver() ) roundedRect(10,BARS_OFFSET - 10 + 100,ofGetWidth() - 20,CHANNEL_BOX_HEIGHT, 5);
            if( t3Button.isMouseOver() ) roundedRect(10,BARS_OFFSET - 10 + 200,ofGetWidth() - 20,CHANNEL_BOX_HEIGHT, 5);
            if( t4Button.isMouseOver() ) roundedRect(10,BARS_OFFSET - 10 + 300,ofGetWidth() - 20,CHANNEL_BOX_HEIGHT, 5);
            if( t5Button.isMouseOver() ) roundedRect(10,BARS_OFFSET - 10 + 400,ofGetWidth() - 20,CHANNEL_BOX_HEIGHT, 5);
            if( t6Button.isMouseOver() ) roundedRect(10,BARS_OFFSET - 10 + 500,ofGetWidth() - 20,CHANNEL_BOX_HEIGHT, 5);

            ofFill();

            if( t1Button.isMouseDown() ) channel = 1;
            if( t2Button.isMouseDown() ) channel = 2;
            if( t3Button.isMouseDown() ) channel = 3;
            if( t4Button.isMouseDown() ) channel = 4;
            if( t5Button.isMouseDown() ) channel = 5;
            if( t6Button.isMouseDown() ) channel = 6;

            tweetFont.drawString( "Keys: 1,2,3,4,5,6 (update), F (fullscreen), P (particles)", APP_PADDING, ofGetHeight() - 20);
            tweetFont.drawString( "Accounts updated every " + ofToString(ceil(REFRESH_RATE / ofGetFrameRate())) + " seconds", ofGetWidth() - 220, ofGetHeight() - 20);
        }
        else
        {
            if( particlesMode ) drawParticles();
            else showTweets();
        }
    }
}

void ofApp::drawStar(float xpos, float ypos, float radius, int npts)
{
    bool useInner=false;
    ofBeginShape();
    for(int i=0; i<360; i+=360/npts)
    {
        int r = useInner ? radius*.9 : radius;
        int x = xpos + cos( ofDegToRad(i) ) * r;
        int y = ypos + sin( ofDegToRad(i) ) * r;
        ofVertex(x, y);
        useInner = !useInner;
    }
    ofEndShape();
}

void ofApp::roundedRect(float x, float y, float w, float h, float r) {
    ofBeginShape();
        ofVertex(x+r, y);
        ofVertex(x+w-r, y);
        quadraticBezierVertex(x+w, y, x+w, y+r, x+w-r, y);
        ofVertex(x+w, y+h-r);
        quadraticBezierVertex(x+w, y+h, x+w-r, y+h, x+w, y+h-r);
        ofVertex(x+r, y+h);
        quadraticBezierVertex(x, y+h, x, y+h-r, x+r, y+h);
        ofVertex(x, y+r);
        quadraticBezierVertex(x, y, x+r, y, x, y+r);
    ofEndShape();
}

void ofApp::quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY) {
  float cp1x = prevX + 2.0/3.0*(cpx - prevX);
  float cp1y = prevY + 2.0/3.0*(cpy - prevY);
  float cp2x = cp1x + (x - prevX)/3.0;
  float cp2y = cp1y + (y - prevY)/3.0;

  // finally call cubic Bezier curve function
  ofBezierVertex(cp1x, cp1y, cp2x, cp2y, x, y);
}

void ofApp::showTweets()
{
    bird.draw(20, BARS_OFFSET - 20);
    clientFont.drawString(tags[channel-1], 50, BARS_OFFSET);

    int n = 0;
    ofxJSONElement newTweet;

    if( channel == 1 ) newTweet = t1Sentiments.getLatestResponse();
    if( channel == 2 ) newTweet = t2Sentiments.getLatestResponse();
    if( channel == 3 ) newTweet = t3Sentiments.getLatestResponse();
    if( channel == 4 ) newTweet = t4Sentiments.getLatestResponse();
    if( channel == 5 ) newTweet = t5Sentiments.getLatestResponse();
    if( channel == 6 ) newTweet = t6Sentiments.getLatestResponse();

    if( newTweet.size() > 0 )
        for( int i = 0; i < newTweet.size(); i++ )
            drawTweet( newTweet[i]["text"].asString(), newTweet[i]["date"].asString().substr(4, 18), newTweet[i]["polarity"].asInt(), i );

    if( returnButton.isMouseDown() ) channel = 0;
}

void ofApp::drawTweet( string text, string date, int polarity, int position )
{
    ofSetColor(254, 199, 11);
    tweetFont.drawString(date, 20, BARS_OFFSET + 20 + (position*20));

    if( polarity == 4 ) //positive
        ofSetColor(0, 255, 0);

    if( polarity == 2 ) //neutral
        ofSetColor(255, 255, 255);

    if( polarity == 0 ) //negative
        ofSetColor(255, 0, 0);

    tweetFont.drawString(text, 150, BARS_OFFSET + 20 + (position*20));

    ofSetColor(255, 255, 255);
}

void ofApp::drawParticles()
{
    ofSetColor(255, 255, 255);

    for(int i = 0; i < 1000; i++)
    {
        particles[i].update();
        particles[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch( key )
    {
        case 49: t1Sentiments.startTwitterQuery(0); break;
        case 50: t2Sentiments.startTwitterQuery(0); break;
        case 51: t3Sentiments.startTwitterQuery(0); break;
        case 52: t4Sentiments.startTwitterQuery(0); break;
        case 53: t5Sentiments.startTwitterQuery(0); break;
        case 54: t6Sentiments.startTwitterQuery(0); break;
        case 'f': ofToggleFullscreen(); break;
        case 'p': if(particlesMode) particlesMode = false;
                  else
                  {
                        particlesMode = true;

                        particles = new Particle2[1000];

                        int polarity = 2;

                        /*if( channel == 1 ) polarity = t1Sentiments.polarity;
                        if( channel == 2 ) polarity = t2Sentiments.polarity;
                        if( channel == 3 ) polarity = t3Sentiments.polarity;
                        if( channel == 4 ) polarity = t4Sentiments.polarity;
                        if( channel == 5 ) polarity = t5Sentiments.polarity;
                        if( channel == 6 ) polarity = t6Sentiments.polarity;*/

                        for(int i = 0; i < 1000; i++){
                            particles[i] = Particle2(ofPoint(100, ofGetHeight()-100));

                            if( polarity == 4 ) particles[i].setColor(ofRandom(255), 0, 0);
                            if( polarity == 0 ) particles[i].setColor(0, ofRandom(255), 0);
                            if( polarity == 2 ) particles[i].setColor(ofRandom(255), ofRandom(255), ofRandom(255));
                        }
                  }
                  break;
    }
}

//--------------------------------------------------------------f
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::exit()
{
    t1Sentiments.clear();
    t2Sentiments.clear();
    t3Sentiments.clear();
    t4Sentiments.clear();
    t5Sentiments.clear();
    t6Sentiments.clear();
}
