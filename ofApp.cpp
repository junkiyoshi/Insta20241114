#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 100 < 50) {

		this->noise_value += ofMap(ofGetFrameNum() % 100, 0, 50, 0.08, 0);
	}

	for (int i = 0; i < 6; i++) {

		auto radius = 200;
		auto deg = ofRandom(360);

		vector<glm::vec2> log;
		log.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
		this->log_list.push_back(log);
	}

	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		if (abs(this->log_list[i].back().x) > 460 || abs(this->log_list[i].back().y) > 460) {

			this->log_list.erase(this->log_list.begin() + i);
		}

		if (this->log_list[i].size() > 75) {

			this->log_list.erase(this->log_list.begin() + i);
		}
	}

	for (int i = 0; i < this->log_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->log_list[i].back().x * 0.005, this->log_list[i].back().y * 0.005, this->noise_value), 0, 1, -360, 360);
		auto next = this->log_list[i].back() + glm::vec2(6 * cos(deg * DEG_TO_RAD), 6 * sin(deg * DEG_TO_RAD));
		this->log_list[i].push_back(next);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(0, ofMap(this->log_list[i].size(), 0, 75, 255, 0));

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	/*
	int start = 100;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}