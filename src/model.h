#pragma once

#include <ge211.h>
#include<string>
#include<array>

namespace frogger {

    const int total_lane_length = 64;
    const int lane_on_screen = 18;
    int game_time = 60;


    //how we decide to represent the state of the game - whether the game is in progress or over.
    enum class State{
        play, over
    };

    //used to determine the direction the frog is facing
    enum class Direction{
        up, down, left, right
    };

    using Coordinate = double;

    /// Models an instance of the classic Atari Frogger game.

    class Model {

    public:
        using Rectangle = ge211::Basic_rectangle<Coordinate>;

        explicit Model();

        int lives() const { return lives_; }

        int times_up() const { return time_elapsed_ - game_time <= 0; }

        bool frog_collide();

        bool frog_drown();

        void move_frog(Coordinate dx, Coordinate dy);

        //Updates game as time passes.
        void update(double const dt);

        Rectangle get_screen() { return screen_; }


    private:


        //A lane represents one row of the screen, represented by the pair
        using Lane = std::pair<Coordinate, std::array<size_t, total_lane_length>>;

        /// We represent the entire screen in terms of a vector of lanes.
        /// The screen has seven lanes. `Lane.first` represents the velocity in which the lane moves
        /// A positive velocity means the lane moves from left to right and vice versa.
        /// The `Lane.second` vector contains information on which spots are safe and which spots are unsafe for the
        /// frog to move to.
        std::vector<Lane> vecLanes;

        Rectangle const screen_;


        struct Frog {
            std::pair<Coordinate, Coordinate> position;
            Direction direction;
        };

        Frog frog;

        //State of the game - in progress or over.
        State state_ = State::play;

        int lives_; //no of lives left
        int score_;

        float time_elapsed_; //time elapsed since start of the game

        /// Updates `winner_` and `turn_` at the end of turn_'s turn.
        /// **PRECONDITION** `col_no` and `row_no` is valid and where the last move
        /// was played.
        void update_lives_game_state();

        //Updates `score_` based on player move;
        void update_score();

        //Updates all `Lane`s in `vecLanes` as time passes
        void lane_update(double const dt);

        void time_update(double const dt);

        /// Returns whether the coordinate is within bounds of screen.
        bool is_within_bounds(Coordinate dx, Coordinate dy) const;
    };

}