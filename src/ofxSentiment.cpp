/*
 *  ofxSentiment.cpp
 *
 *  Created by Joan Mira on 29/08/12
 *  cc-by-sa 2012 www.wcrs.com. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Douglas Edric Stanley
 *  cf. http://www.abstractmachine.net
 *
 */

#include "ofxSentiment.h"

void ofxSentiment::setup(string _twitterid) {

	// listen to http events
    ofAddListener(httpUtils.newResponseEvent, this, &ofxSentiment::newResponse);
    httpUtils.start();

	delegate = NULL;
	twitterid = _twitterid;
	loading = false;
	positive = 0;
    negative = 0;
    neutral = 0;
    polarity = -1;
}

void ofxSentiment::startTwitterQuery(int queryIdentifier) {

	string query = "http://work.joanmira.com/demos/twitter-mood-meter/?id="+twitterid;
    tweetQueryIdentifier = queryIdentifier;
	startQuery(query);

}

void ofxSentiment::startQuery(string query) {
	// load data from web
	loading = true;
	httpUtils.addUrl(query);
}

void ofxSentiment::newResponse(ofxHttpResponse &response) {

    bool parsingSuccessful = data.parse(response.responseBody);

    for( int i = 0; i < data["data"].size(); i++ )
    {
        if( data["data"][i]["polarity"].asInt() == 4 ) positive++;
        if( data["data"][i]["polarity"].asInt() == 2 ) neutral++;
        if( data["data"][i]["polarity"].asInt() == 0 ) negative++;
    }

    if( positive > negative && positive > neutral) polarity = 4;
    if( negative > positive && negative > neutral) polarity = 0;
    if( neutral > positive && neutral > negative) neutral = 2;

    loading = false;

	// ok, send back results
	if (delegate) {
		delegate->searchResult(data, tweetQueryIdentifier);
	}

}

ofxJSONElement ofxSentiment::getLatestResponse() {
	return data["data"];
}

void ofxSentiment::clear() {
	// listen to http events
    ofRemoveListener(httpUtils.newResponseEvent, this, &ofxSentiment::newResponse);
    httpUtils.stop();
}
