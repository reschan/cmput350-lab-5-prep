#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <math.h>

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS_LIMIT = 30;

sf::CircleShape circle;
float frame = 0;
int func = 0;

// global tween function
std::function<float(float, float, float)> tween = [](float a, float b, float t) {
    return (1 - t) * a + t * b;
};

std::function<float(float, float)> easeInSine = [](float frame, float dist) { 
    return (1 - std::cos((frame * 3.141f) / 2)) * dist; 
};

std::function<float(float, float)> easeOutSine = [](float frame, float dist) {
    return (std::sin((frame * 3.141f) / 2)) * dist;
};

std::function<float(float, float)> easeInOutSine = [](float frame, float dist) {
    return ((-1 * (std::cos(3.141f * frame) - 1)) / 2) * dist;
};

std::function<float(float, float)> easeInQuad = [](float frame, float dist) {
    return (frame * frame) * dist;
};

std::function<float(float, float)> easeOutQuad = [](float frame, float dist) {
    return (1 - (1 - frame) * (1 - frame)) * dist;
};

std::function<float(float, float)> easeInOutQuad = [](float frame, float dist) {
    return (frame < 0.5 ? 2 * frame * frame : 1 - std::pow(-2 * frame + 2, 2) / 2) * dist;
};

std::function<float(float, float)> easeInCubic = [](float frame, float dist) {
    return (frame * frame * frame) * dist;
};

std::function<float(float, float)> easeOutCubic = [](float frame, float dist) {
    return (1 - std::pow(1 - frame, 3)) * dist;
};

std::function<float(float, float)> easeInOutCubic = [](float frame, float dist) {
    return (frame < 0.5 ? 4 * frame * frame * frame : 1 - std::pow(-2 * frame + 2, 3) / 2) * dist;
};



void handleInput(sf::Window& window, bool& shouldQuit) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            shouldQuit = true;
        }

        // ====== ====== ======
        // TODO: (Q2)
        //  implement key presses (1-9) that replace the tween function
        //  with different alternate tween functions.
        //  Functions can be from lecture or from https://easings.net/#
        // ====== ====== ======
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scan::Num1) {
                func = 1;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num2) {
                func = 2;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num3) {
                func = 3;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num4) {
                func = 4;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num5) {
                func = 5;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num6) {
                func = 6;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num7) {
                func = 7;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num8) {
                func = 8;
            }
            if (keyPressed->scancode == sf::Keyboard::Scan::Num9) {
                func = 9;
            }
            frame = 0;
        }

    }
}

void render(sf::RenderWindow& window) {
    // Clear with blue background (sky)
    window.clear(sf::Color::Black);
    // ====== ====== ======
    // TODO: (Q1) Draw circle that moves between
    // the left/right half of the screen.
    // Movement should be governed by the tween function.
    // ====== ====== ======


    if (func == 0) {
        circle.setPosition({tween(0.0f, 25.0f, frame), 267});
    } else if (func == 1) {
        circle.setPosition({easeInSine(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 2) {
        circle.setPosition({easeOutSine(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 3) {
        circle.setPosition({easeInOutSine(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 4) {
        circle.setPosition({easeInQuad(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 5) {
        circle.setPosition({easeOutQuad(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 6) {
        circle.setPosition({easeInOutQuad(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 7) {
        circle.setPosition({easeInCubic(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 8) {
        circle.setPosition({easeOutCubic(frame / 30, WINDOW_WIDTH), 267});
    } else if (func == 9) {
        circle.setPosition({easeInOutCubic(frame / 30, WINDOW_WIDTH), 267});
    } 

    window.draw(circle);

    // ====== ====== ======
    // TODO: (Q3) Draw tween function graph with a dot
    // on the current portion of the curve
    // ====== ====== ======

    sf::RectangleShape line_up({300.0f, 2.0f});
    line_up.setPosition({0, 700});
    line_up.rotate(sf::degrees(270));
    window.draw(line_up);

    sf::RectangleShape line_across({800.0f, 2.0f});
    line_across.setPosition({0, 700});
    window.draw(line_across);

    sf::CircleShape point;
    point.setRadius(5.0f);
    point.setFillColor(sf::Color::Red);
    point.setPosition({0, 700});

    if (func == 0) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({tween(0.0f, 25.0f, i), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({tween(0.0f, 25.0f, frame), 700 - (10 * frame)});
    } else if (func == 1) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeInSine(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeInSine(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 2) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeOutSine(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeOutSine(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 3) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeInOutSine(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeInOutSine(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 4) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeInQuad(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeInQuad(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 5) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeOutQuad(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeOutQuad(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 6) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeInOutQuad(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeInOutQuad(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 7) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeInCubic(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeInCubic(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 8) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeOutCubic(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeOutCubic(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } else if (func == 9) {
        for (float i = 0; i <= 30; i++) {
            sf::CircleShape line_graph;
            line_graph.setRadius(2.0f);
            line_graph.setFillColor(sf::Color::White);
            line_graph.setPosition({easeInOutCubic(i / 30, WINDOW_WIDTH), 700 - (10 * i)});
            window.draw(line_graph);
        }
        point.setPosition({easeInOutCubic(frame / 30, WINDOW_WIDTH), 700 - (10 * frame)});
    } 

    window.draw(point);

    if (++frame > 30) {
        frame = 0;
    }
    window.display();
}

int main() {
    sf::RenderWindow window;

    circle.setRadius(20.0f);
    circle.setFillColor(sf::Color::Red);

    try {
        // Initialize window
        window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tween");
        window.setFramerateLimit(FPS_LIMIT);
        // Prevent key repeats.
        window.setKeyRepeatEnabled(false);

        bool shouldQuit = false;
        // Main game loop
        while (window.isOpen()) {
            handleInput(window, shouldQuit);
            if (shouldQuit) {
                break;
            }
            render(window);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
