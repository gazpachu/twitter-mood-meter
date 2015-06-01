/*
 *  ofxSentiment.h
 *
 *  Created by Joan Mira on 29/08/12
 *  cc-by-sa 2012 www.wcrs.com. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Douglas Edric Stanley
 *  cf. http://www.abstractmachine.net
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxJSONElement.h"
#include "TwitterDelegate.h"

class ofxSentiment
{
    public:

        void setup(string _twitterid);
        void setSearchDelegate(TwitterDelegate *_delegate) { delegate = _delegate; }

        void startQuery(string query);
        void startTwitterQuery(int queryIdentifier=0);

        ofxJSONElement getLatestResponse();
        void newResponse(ofxHttpResponse &response);

        void clear();

        ofxHttpUtils httpUtils;

        int tweetQueryIdentifier;
        bool loading;

        int positive;
        int negative;
        int neutral;

        int polarity;
        string twitterid;

    private:

        TwitterDelegate *delegate;
        ofxJSONElement data;
};
