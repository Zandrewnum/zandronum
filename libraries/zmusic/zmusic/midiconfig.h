#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../../libraries/music_common/fileio.h"

struct ADLConfig
{
	int adl_chips_count = 6;
	int adl_emulator_id = 0;
	int adl_bank = 14;
	int adl_volume_model = 3; // DMX
	bool adl_run_at_pcm_rate = 0;
	bool adl_fullpan = 1;
	std::string adl_custom_bank;
};

struct FluidConfig
{
	std::string fluid_lib;
	std::vector<std::string> fluid_patchset;
	bool fluid_reverb = false;
	bool fluid_chorus = false;
	int fluid_voices = 128;
	int fluid_interp = 1;
	int fluid_samplerate = 0;
	int fluid_threads = 1;
	int fluid_chorus_voices = 3;
	int fluid_chorus_type = 0;
	float fluid_gain = 0.5f;
	float fluid_reverb_roomsize = 0.61f;
	float fluid_reverb_damping = 0.23f;
	float fluid_reverb_width = 0.76f;
	float fluid_reverb_level = 0.57f;
	float fluid_chorus_level = 1.2f;
	float fluid_chorus_speed = 0.3f;
	float fluid_chorus_depth = 8;
};

struct OPLConfig
{
	int numchips = 2;
	int core = 0;
	bool fullpan = true;
	bool genmidiset = false;
	uint8_t OPLinstruments[36 * 175]; // it really is 'struct GenMidiInstrument OPLinstruments[GENMIDI_NUM_TOTAL]'; but since this is a public header it cannot pull in a dependency from oplsynth.
};

struct OpnConfig
{
	int opn_chips_count = 8;
	int opn_emulator_id = 0;
	bool opn_run_at_pcm_rate = false;
	bool opn_fullpan = 1;
	std::string opn_custom_bank;
	std::vector<uint8_t> default_bank;
};

namespace Timidity
{
	class Instruments;
	class SoundFontReaderInterface;
}

struct GUSConfig
{
	// This one is a bit more complex because it also implements the instrument cache.
	int midi_voices = 32;
	int gus_memsize = 0;
	void (*errorfunc)(int type, int verbosity_level, const char* fmt, ...) = nullptr;

	MusicIO::SoundFontReaderInterface *reader;
	std::string readerName;
	std::vector<uint8_t> dmxgus;				// can contain the contents of a DMXGUS lump that may be used as the instrument set. In this case gus_patchdir must point to the location of the GUS data.
	std::string gus_patchdir;
	
	// These next two fields are for caching the instruments for repeated use. The GUS device will work without them being cached in the config but it'd require reloading the instruments each time.
	// Thus, this config should always be stored globally to avoid this.
	// If the last loaded instrument set is to be reused or the caller wants to manage them itself, both 'reader' and 'dmxgus' fields should be left empty.
	std::string loadedConfig;
	std::shared_ptr<Timidity::Instruments> instruments;	// this is held both by the config and the device
};

namespace TimidityPlus
{
	class Instruments;
	class SoundFontReaderInterface;
}

struct TimidityConfig
{
	void (*errorfunc)(int type, int verbosity_level, const char* fmt, ...) = nullptr;

	MusicIO::SoundFontReaderInterface* reader;
	std::string readerName;

	// These next two fields are for caching the instruments for repeated use. The GUS device will work without them being cached in the config but it'd require reloading the instruments each time.
	// Thus, this config should always be stored globally to avoid this.
	// If the last loaded instrument set is to be reused or the caller wants to manage them itself, 'reader' should be left empty.
	std::string loadedConfig;
	std::shared_ptr<TimidityPlus::Instruments> instruments;	// this is held both by the config and the device

};

namespace WildMidi
{
	struct Instruments;
	class SoundFontReaderInterface;
}

struct WildMidiConfig
{
	bool reverb = false;
	bool enhanced_resampling = true;
	void (*errorfunc)(const char* wmfmt, va_list args) = nullptr;

	MusicIO::SoundFontReaderInterface* reader;
	std::string readerName;

	// These next two fields are for caching the instruments for repeated use. The GUS device will work without them being cached in the config but it'd require reloading the instruments each time.
	// Thus, this config should always be stored globally to avoid this.
	// If the last loaded instrument set is to be reused or the caller wants to manage them itself, 'reader' should be left empty.
	std::string loadedConfig;
	std::shared_ptr<WildMidi::Instruments> instruments;	// this is held both by the config and the device

};


struct DumbConfig
{
	int  mod_samplerate;
    int  mod_volramp;
    int  mod_interp;
    bool mod_autochip;
    int  mod_autochip_size_force;
    int  mod_autochip_size_scan;
    int  mod_autochip_scan_threshold;
    float mod_dumb_mastervolume;
};

// The rest is not used yet.

struct misc
{
	bool snd_midiprecache;
	float gme_stereodepth;
	int snd_streambuffersize;
};


namespace ZMusic
{

enum EZMusicIntConfigKey
{
	adl_chips_count,
	adl_emulator_id,
	adl_run_at_pcm_rate,
	adl_fullpan,
	adl_bank,
	adl_use_custom_bank,
	adl_volume_model,

	fluid_reverb,
	fluid_chorus,
	fluid_voices,
	fluid_interp,
	fluid_samplerate,
	fluid_threads,
	fluid_chorus_voices,
	fluid_chorus_type,

	opl_numchips,
	opl_core,
	opl_fullpan,

	opn_chips_count,
	opn_emulator_id,
	opn_run_at_pcm_rate,
	opn_fullpan,
	opn_use_custom_bank,

	midi_dmxgus,
	midi_voices,
	gus_memsize,

	timidity_modulation_wheel,
	timidity_portamento,
	timidity_reverb,
	timidity_reverb_level,
	timidity_chorus,
	timidity_surround_chorus,
	timidity_channel_pressure,
	timidity_lpf_def,
	timidity_temper_control,
	timidity_modulation_envelope,
	timidity_overlap_voice_allow,
	timidity_drum_effect,
	timidity_pan_delay,
	timidity_key_adjust,

	wildmidi_reverb,
	wildmidi_enhanced_resampling,

	snd_midiprecache,

	mod_samplerate,
	mod_volramp,
	mod_interp,
	mod_autochip,
	mod_autochip_size_force,
	mod_autochip_size_scan,
	mod_autochip_scan_threshold,

	snd_streambuffersize,
	
	NUM_INT_CONFIGS
};

enum EZMusicFloatConfigKey
{
	fluid_gain,
	fluid_reverb_roomsize,
	fluid_reverb_damping,
	fluid_reverb_width,
	fluid_reverb_level,
	fluid_chorus_level,
	fluid_chorus_speed,
	fluid_chorus_depth,

	timidity_drum_power,
	timidity_tempo_adjust,
	min_sustain_time,

	gme_stereodepth,
	mod_dumb_mastervolume,

	NUM_FLOAT_CONFIGS
};

enum EMusicStringConfigKey
{
	adl_custom_bank,
	fluid_lib,
	fluid_patchset,
	opn_custom_bank,
	midi_config,
	gus_patchdir,
	timidity_config,
	wildmidi_config,

	NUM_STRING_CONFIGS
};

}