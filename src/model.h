#pragma once

#include <ge211.h>
#include<string>
#include<array>

namespace frogger{

    //each cell is 25x25 px. the screen is 14 cells wide and 13 cells tall, 2 cel extra rows below for
    //to show score and lives and time.
    //the time the game runs for
    const int GAME_TIME = 60;
    //the size of each cell of the game
    const int CELLSIZE = 25;
    //gamescreen width
    const int GAMESCREEN_WIDTH = 14*CELLSIZE;
    //gamescreen height
    const int GAMESCREEN_HEIGHT = 10*CELLSIZE;
    //velocity for object in each lane
    const std::vector<float> lane_velocity = {2.0f, -4.0f,3.0f,-3.0f,2.0f,3.0f,-3.0f};
    //dimensions for object in each lane
    const std::vector<std::pair<int,int>> obstacle_dims = {{25,25},{25,25},{25,25},{25,25},{25,25},{25,25},{25,25}};
    //Represents the state of the game - whether the game is in progress or over.
    enum class State{
        play, win, gameover
    };
    //used to determine the direction the frog is facing
    enum class Direction{
        up, down, left, right
    };


    /// Models an instance of the classic Atari Frogger game.

    class Model {

    public:

        using Coordinate = double;

        explicit Model();

        int lives() const { return lives_; }

        int times_up() const { return time_elapsed_ - GAME_TIME <= 0; }


        //checks whether the flog has collided in `lane`
        bool frog_collide(int);

        //checks whether the frog has drowned in the river, in the river section
        bool frog_drown(int);

        void move_frog(Direction);

        //Updates game as time passes.
        void update(double const dt);

    private:


        //A vector of vectors of positions of the "obstacles" ("obstacles" are vehicles in the road section, which need
        //to be avoided and logs and floating objects in the river section which need to be landed on.
        std::vector<std::vector<ge211::Position>> obstacles_;

        struct Frog {
            ge211::Position position_;
            Direction direction_;
        };

        Frog frog_;

        //State of the game - in progress or over.
        State state_ = State::play;

        int lives_; //no of lives left
        int score_; //score
        int highest_reached_; //maintains the furthest lane the frog has reached; required to update the score.

        float time_elapsed_; //time elapsed since start of the game

        /// Updates `lives_`, `score_` and `state_`
        void update_game_state();

        //Updates `score_` based on player move;
        void update_score();

        //Updates all `Lane`s in `vecLanes` as time passes
        void update_obstacles_();

        //Updates time_elapsed
        void update_time_elapsed_();

        //computes which lane the frog is in; to be used to make checking for collisions easier
        int calculate_lane();

        /// Returns whether the coordinate is within bounds of screen.
        bool is_move_valid(Direction) const;
    };

}