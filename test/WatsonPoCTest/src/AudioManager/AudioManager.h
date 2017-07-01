#pragma once

#include <string>
#include <memory>

#include "AudioDevice.h"

class AudioManager {
public:
    AudioManager();

public:
    bool    play(const std::string& filename);
    bool    record(const std::string& filename, int seconds);

private:
    std::shared_ptr<AudioDevice> my_device_;
};