#pragma once
#pragma once

#ifdef _DEBUG  
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")  
#else  
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")  
#endif  

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <SFML/Audio.hpp>


class Particle
{
public:
    sf::RectangleShape shape;
    float vx, vy;
    float lifetime;
};