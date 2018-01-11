#pragma once

#include "clock.hpp"
#include <string>
#include <cmath>
#include <cassert>

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 800;
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;
static const std::string WINDOW_TITLE = "Clock";

static const float CLOCK_RADIUS = 350;
static const float CLOCK_X = (WINDOW_WIDTH - 2 * CLOCK_RADIUS) / 2;
static const float CLOCK_Y = (WINDOW_HEIGHT - 2 * CLOCK_RADIUS) / 2;

static const float CENTER_X = CLOCK_X + CLOCK_RADIUS;
static const float CENTER_Y = CLOCK_Y + CLOCK_RADIUS;

static const float CENTER_RADIUS = 20;

static const float HOUR_HAND_LENGHT = (10.0f / 16.0f) * CLOCK_RADIUS;
static const float MINUTE_HAND_LENGHT = (14.0f / 16.0f) * CLOCK_RADIUS;
static const float SECOND_HAND_LENGHT = (15.0f / 16.0f) * CLOCK_RADIUS;

static const float HOUR_HAND_WIDTH = 6.0f;
static const float MINUTE_HAND_WIDTH = 6.0f;
static const float SECOND_HAND_WIDTH = 3.0f;

void init(Clock &clock, sf::RenderWindow &window);

void pollEvents(sf::RenderWindow &window);

void update(Clock &clock);

void redrawFrame(sf::RenderWindow &window, Clock &clock);

void createWindow(sf::RenderWindow &window);