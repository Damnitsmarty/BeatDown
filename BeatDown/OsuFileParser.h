#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

struct TimingPoint
{
	int offset = 0;
	float msperbeat = 0;
	TimingPoint(float _offset,float _msperbeat) {
		offset = _offset;
		msperbeat = _msperbeat;
	}
};
struct Beat
{
	int x;
	int offset;
	
	Beat(int _x, int _offset) {
		x = _x;
		offset = _offset;
	}
};
struct OsuFileData
{
	string folderPath;
	string audioPath;
	int audioLeadIn;
	string backgroundPath;
	vector<TimingPoint> timingPoints;
	vector<Beat> beats;
};
static class OsuFileParser {
private:
	static bool parseGeneralLine(OsuFileData* data, string line) {
		smatch match;
		if (regex_match(line, match, regex("AudioFilename\: (.*?)"))) {
			data->audioPath = data->folderPath + match.str(1);
			return true;
		}else if (regex_match(line, match, regex("AudioLeadIn\: (.*?)"))) {
			data->audioLeadIn = stoi(match.str(1));
			return true;
		}
		else if (regex_match(line, match, regex(".*?,\"(.*?)\",.*"))) {
			data->backgroundPath = data->folderPath + match.str(1);
			return true;
		}
		return false;
	};
	static bool parseTimingLine(OsuFileData* data, string line) {
		smatch match;
		
		//TimingPoint line Format: offset , speed, <other stuff we don't need>

		//match the string against the pattern
		//if valid, the match should capture [offset] and [speed] in two groups
		//return if invalid format
		if (!regex_match(line, match,regex("(.*?),(.*?),.*"))) return false;

		int offset = stoi(match.str(1));
		float msperbeat = stof(match.str(2));

		//Osu contains so-called Relative Timing Points (indicated by a negative msperbeat value), which we don't need for this game.
		if (msperbeat < 0) return false;

		data->timingPoints.push_back(TimingPoint(offset,msperbeat));
		return true;
		
	}



	static bool parseBeatLine(OsuFileData* data, string line) {
		smatch match;

		//HitObject line Format: x , y, offset, <other stuff we don't need>

		//match the string against the pattern
		//if valid, the match should capture [x] and [offset] in two groups
		//(as all of our beats will be appearing from the top, we would not need the y variable)
		//return if invalid format
		if (!regex_match(line, match, regex("(.*?),.*?,(.*?),.*"))) return false;

		int x = stoi(match.str(1));
		int offset = stoi(match.str(2));
		data->beats.push_back(Beat(x, offset));
		return true;
	}



public:
	static OsuFileData parseFile(string path) {
		//The structure that we're going to return
		OsuFileData data;
		
		smatch match;
		regex_match(path, match, regex("(.*\/).*"));
		data.folderPath = match.str(1);
		//the part of the file we're currently in
		string currentHeader = "";


		//open the file for reading
		ifstream file;
		file.open(path);

		if (file.is_open()) {
			//cycle through each line
			for (string line; getline(file, line); ) {
				//The file is broken into parts separated by headers. 
				//A normal header is of the format [HEADERTITLE]
				//Use regex to update the currentHeader variable accordingly
				if (regex_match(line, regex("\\[(.*?)\\]"))) currentHeader = line;

				//Parsing is different for each part of the file:
				//Note: Switch does not work with strings; falling back to if/else statements
				if (currentHeader == "[TimingPoints]") parseTimingLine(&data,line);
				else if (currentHeader == "[HitObjects]") parseBeatLine(&data,line);
				else if (currentHeader == "[General]" || currentHeader == "[Events]") parseGeneralLine(&data,line);
			}
			//sort the file data (using lambdas)
			std::sort(data.beats.begin(), data.beats.end(), [](Beat a, Beat b) {return a.offset < b.offset; });
			std::sort(data.timingPoints.begin(), data.timingPoints.end(), [](TimingPoint a, TimingPoint b) {return a.offset < b.offset; });
		}
		return data;
	};
};