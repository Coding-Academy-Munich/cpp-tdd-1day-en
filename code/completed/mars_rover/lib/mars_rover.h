#pragma once
#ifndef LIB_MARS_ROVER_H
#define LIB_MARS_ROVER_H


#include <string>
#include <stdexcept>
#include <vector>
#include <memory>

namespace rover
{

// A simple struct to represent a point on the grid.
// Overloading the == operator is crucial for easy comparisons in tests.
struct Point {
    int x;
    int y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Using a scoped enum makes the direction type-safe and more readable than
// chars or ints.
enum class Direction {
    N, E, S, W
};

/**
 * @class Grid
 * @brief Represents the planetary grid the rover moves on.
 *
 * This class was introduced during a refactoring step. Initially, the Rover
 * handled its own movement logic. A test for wrapping around the grid edges
 * revealed that the Rover had too much responsibility (knowing the world's
 * boundaries). Extracting the Grid class follows the Single Responsibility
 * Principle. The Grid is now solely responsible for calculating valid
 * positions.
 */
class Grid {
private:
    int width;
    int height;

public:
    Grid(int w, int h) : width(w), height(h) {
        if (w <= 0 || h <= 0) {
            throw std::invalid_argument("Grid dimensions must be positive.");
        }
    }

    // Calculates the next position, handling the "wrapping" at the edges.
    Point calculateNextPosition(const Point& current, Direction dir) const {
        Point next = current;
        switch (dir) {
            case Direction::N:
                next.y = (next.y + 1) % height;
                break;
            case Direction::S:
                next.y = (next.y - 1 + height) % height;
                break;
            case Direction::E:
                next.x = (next.x + 1) % width;
                break;
            case Direction::W:
                next.x = (next.x - 1 + width) % width;
                break;
        }
        return next;
    }
};


/**
 * @class Rover
 * @brief Represents a Mars Rover that can navigate a grid.
 *
 * The Rover's design evolved through TDD. It started with just a position
 * and direction. Tests for turning and moving added new methods.
 * A key design change occurred when the Grid was introduced; the Rover now
 * collaborates with a Grid object to determine its movement, making the design
 * more modular and easier to test.
 */
class Rover {
private:
    Point position;
    Direction direction;
    std::shared_ptr<Grid> grid; // Use a shared_ptr to allow multiple rovers on the same grid later.

    void turnRight() {
        switch (direction) {
            case Direction::N: direction = Direction::E; break;
            case Direction::E: direction = Direction::S; break;
            case Direction::S: direction = Direction::W; break;
            case Direction::W: direction = Direction::N; break;
        }
    }

    void turnLeft() {
        switch (direction) {
            case Direction::N: direction = Direction::W; break;
            case Direction::W: direction = Direction::S; break;
            case Direction::S: direction = Direction::E; break;
            case Direction::E: direction = Direction::N; break;
        }
    }

    void move() {
        // The Rover delegates the responsibility of calculating the next position to the Grid.
        // This is a key design insight driven by the tests.
        position = grid->calculateNextPosition(position, direction);
    }

public:
    // The Rover is initialized with a grid and a starting position/direction.
    Rover(std::shared_ptr<Grid> g, Point startPos = {0, 0}, Direction startDir = Direction::N)
        : grid(g), position(startPos), direction(startDir) {
        if (!grid) {
            throw std::invalid_argument("Rover must be placed on a valid grid.");
        }
    }

    // Public getters for testing and state inspection.
    Point getPosition() const { return position; }
    Direction getDirection() const { return direction; }

    // Processes a string of commands.
    void executeCommands(const std::string& commands) {
        for (char command : commands) {
            switch (command) {
                case 'R':
                    turnRight();
                    break;
                case 'L':
                    turnLeft();
                    break;
                case 'M':
                    move();
                    break;
                default:
                    // In a real system, you might throw an exception or log an error.
                    // For this Kata, we can choose to ignore invalid commands.
                    break;
            }
        }
    }
};


} // namespace rover
#endif // LIB_MARS_ROVER_H
