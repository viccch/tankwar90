#include "../third_party/include/irrklang/irrKlang.h"
#include <string>

class SoundEngine{
private:
	double last_play_time;
	double min_play_internal;
	irrklang::ISoundEngine* engine;
public:
	SoundEngine();
	~SoundEngine();
	void play(const std::string& music_path,  double current_time);
	void play_loop(const std::string& music_path,  double current_time);
};