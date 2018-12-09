#pragma once

#include <ge211.h>
#include<string>
#include<array>

namespace frogger{

    //Our screen can be represented as a grid of cells. Each cell is 25x25 px.
    // The game screen is 14 cells wide and 10 cells tall. We will have 2 extra rows below the game screen within the
    // game window to show score, lives remaining and the time remaining to play the game.


    //MODEL CONSTANTS


    //Amount of time alloted to play the game
    const int GAME_TIME = 60;

    //the size of each cell of the game
    const int CELLSIZE = 25;

    //gamescreen width
    const int GAMESCREEN_WIDTH = 14*CELLSIZE;

    //gamescreen height
    const int GAMESCREEN_HEIGHT = 10*CELLSIZE;
    //velocity for object in each lane

    const std::vector<float> lane_velocity = {0,1.5f, -2.0f,1.7f,-2.5f,0,1.5f,2.0f,-2.7f,0};

    //dimensions for object in each lane
    const std::vector<std::pair<int,int>> obstacle_dims = {{0,0},{30,25},{31,25},{29,25},{50,25},{0,0},{33,25},{87,25},{120,25},{0,0}};

    //Represents the state of the game - whether the game is in progress or over.
    enum class State{
        play, win, gameover
    };

    //used to determine the direction the frog is facing
    enum class Direction{
        up, down, left, right
    };


    /// Models an instance of a version of the classic Atari Frogger game.
    class Model {

    public:

        using Coordinate = double;

        explicit Model();

        int lives() const { return lives_; }

        float times_elapsed() const { return GAME_TIME - time_elapsed_; }


        //checks whether the flog has collided in `lane`
        bool frog_collide(int);

        //checks whether the frog has drowned in the river, in the river section
        bool frog_drown(int);

        void move_frog(Direction);

        //Updates game as time passes.
        void update(double dt);

        //getter for obstacle positions - to be used by view.
        std::vector<std::vector<ge211::Position>> obstacles() const{
            return obstacles_;
        }

        //getter for frog position - to be used by view.
        ge211::Position frog_position() const{
            return frog_.position_;

        }

        //getter for frog direction - to be used by view
        Direction frog_direction() const{
            return frog_.direction_;
        }

        //getter for score
        int score(){
            return score_;
        }

        //getter for lives
        int lives(){
            return lives_;
        }

        State state(){
            return state_;
        }
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

        //Updates positions of of obstacles in `i` as `dt` time passes
        void update_lane_(int,double);

        //Updates time_elapsed
        void update_time_elapsed_(double dt);

        //computes which lane the frog is in; to be used to make checking for collisions easier
        int calculate_lane() const;

        //reduces the lives left by 1 and resets frog's prosition to the bottom of the screen
        void kill_frog();

        /// Returns whether the coordinate is within bounds of screen.
        bool is_move_valid(Direction) const;
    };

}