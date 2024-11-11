#include "tinyxml2.h"
#include <string>
#include <iostream>
#pragma once

class SaveManager {
public:
    static void SaveGame(const std::string& filePath, int seed, int lives, int currentCheckpoint) {
        tinyxml2::XMLDocument doc;

        // Add element to the root
        tinyxml2::XMLElement* root = doc.NewElement("ArgenFrogger-SaveData");
        doc.InsertFirstChild(root);

        // Save game seed
        tinyxml2::XMLElement* seedElement = doc.NewElement("Seed");
        seedElement->SetText(seed);
        root->InsertEndChild(seedElement);

        // Save game lives
        tinyxml2::XMLElement* livesElement = doc.NewElement("Lives");
        livesElement->SetText(lives);
        root->InsertEndChild(livesElement);

        // Save current checkpoint
        tinyxml2::XMLElement* checkpointElement = doc.NewElement("CurrentCheckpoint");
        checkpointElement->SetText(currentCheckpoint);
        root->InsertEndChild(checkpointElement);

        // SaveFile
        doc.SaveFile(filePath.c_str());
    }

    static bool LoadGame(const std::string& filePath, int& seed, int& lives, int& currentCheckpoint) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Error loading save file!" << std::endl;
            return false;
        }

        // Load root
        tinyxml2::XMLElement* root = doc.FirstChildElement("ArgenFrogger-SaveData");
        if (root == nullptr) return false;

        // Load seed
        root->FirstChildElement("Seed")->QueryIntText(&seed);

        // Load lives
        root->FirstChildElement("Lives")->QueryIntText(&lives);

        // Load checkpoint
        root->FirstChildElement("CurrentCheckpoint")->QueryIntText(&currentCheckpoint);

        return true;
    }
};
