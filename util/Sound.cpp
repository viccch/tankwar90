#include "Sound.h"

SoundEngine::SoundEngine(){
	engine = irrklang::createIrrKlangDevice();
	last_play_time = 0.0;
	min_play_internal = 0.1;/*s*/
}
SoundEngine::~SoundEngine(){
	engine->drop();
}
void SoundEngine::play(const std::string& music_path,double current_time){
	if (last_play_time + min_play_internal >= current_time)
		return;

	last_play_time = current_time;
	engine->play2D(music_path.c_str(),false);
}

void SoundEngine::play_loop(const std::string& music_path, double current_time) {
	if (last_play_time + min_play_internal <= current_time)return;

	last_play_time = current_time;
	engine->play2D(music_path.c_str(), true);
}
