#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "ofTrueTypeFont.h"
#include "ofxSentiment.h"
#include "ofxMSAInteractiveObject.h"
#include "particles2.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void showTweets();
		void drawTweet( string text, string date, int polarity, int position );

		void drawStar(float xpos, float ypos, float radius, int npts);
		void roundedRect(float x, float y, float w, float h, float r);
		void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY);
		void drawParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxSentiment t1Sentiments;
		ofxSentiment t2Sentiments;
		ofxSentiment t3Sentiments;
		ofxSentiment t4Sentiments;
		ofxSentiment t5Sentiments;
		ofxSentiment t6Sentiments;

        ofTrueTypeFont titleFont;
        ofTrueTypeFont starFont;
		ofTrueTypeFont clientFont;
		ofTrueTypeFont tweetFont;

		ofImage bird;
		ofImage bg;

		vector<string> tags;

		ofxMSAInteractiveObject t1Button;
		ofxMSAInteractiveObject t2Button;
		ofxMSAInteractiveObject t3Button;
		ofxMSAInteractiveObject t4Button;
		ofxMSAInteractiveObject t5Button;
		ofxMSAInteractiveObject t6Button;
		ofxMSAInteractiveObject returnButton;

		Particle2 *particles;
};
