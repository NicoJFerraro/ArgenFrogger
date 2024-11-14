#include "AudioManager.h"

AudioManager& AudioManager::Instance() {
    static AudioManager instance;
    return instance;
}

AudioManager::AudioManager() : musicVolume(75.f), sfxVolume(100.f) {
}

AudioManager::~AudioManager() {
}

void AudioManager::PlaySFX(const std::string& filename) {
    if (soundBuffers.find(filename) == soundBuffers.end()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filename)) {
            std::cerr << "Error loading sound effect: " << filename << std::endl;
            return;
        }
        soundBuffers[filename] = buffer;
    }

    sounds.emplace_back();
    sf::Sound& sound = sounds.back();
    sound.setBuffer(soundBuffers[filename]);
    sound.setVolume(sfxVolume);
    sound.play();

    RemoveStoppedSounds();
}

void AudioManager::PlayMusic(const std::string& filename) {
    music.stop();

    if (!music.openFromFile(filename)) {
        std::cerr << "Error loading music: " << filename << std::endl;
        return;
    }

    music.setLoop(true);
    music.setVolume(musicVolume);
    music.play();
}

void AudioManager::StopMusic() {
    music.stop();
}

void AudioManager::SetMusicVolume(float volume) {
    musicVolume = volume;
    music.setVolume(musicVolume);
}

void AudioManager::SetSFXVolume(float volume) {
    sfxVolume = volume;
    for (auto& sound : sounds) {
        sound.setVolume(sfxVolume);
    }
}

void AudioManager::RemoveStoppedSounds() {
    for (auto it = sounds.begin(); it != sounds.end(); ) {
        if (it->getStatus() == sf::Sound::Stopped) {
            it = sounds.erase(it);
        }
        else {
            ++it;
        }
    }
}
