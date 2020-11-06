#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 12, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

	int radius = 80;
	for (int i = 0; i < 50; i++) {

		int start_deg = ofGetFrameNum() + i * ofRandom(1, 3);
		auto noise_location = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i * 3) * 0.005), 0, 1, -300, 300), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i * 3) * 0.005), 0, 1, -300, 300), 0);
		auto tmp_location = glm::vec3(0, 0, -radius);
		for (int deg = start_deg; deg < start_deg + 180; deg += 15) {

			auto rotation_y = glm::rotate(glm::mat4(), (float)(deg * DEG_TO_RAD), glm::vec3(0, 1, 0));
			auto location = noise_location + glm::vec4(tmp_location, 0) * rotation_y;

			ofPushMatrix();
			ofTranslate(location);
			ofRotateY(180 - deg);

			char noise_value = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 'A', 'Z');
			this->font.drawString({ noise_value }, 0, 0);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}