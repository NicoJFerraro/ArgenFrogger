#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <string>
#include <iostream> // Para manejo de errores

class AudioManager {
public:
    static AudioManager& Instance();

    void PlaySFX(const std::string& filename);
    void PlayMusic(const std::string& filename);

    void StopMusic();
    void SetMusicVolume(float volume);
    void SetSFXVolume(float volume);

private:
    AudioManager();
    ~AudioManager();

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    sf::Music music;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::list<sf::Sound> sounds;

    float musicVolume;
    float sfxVolume;

    void RemoveStoppedSounds();
};
