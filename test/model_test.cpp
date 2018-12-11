#include "model.h"
#include <catch.h>

using namespace frogger;
using namespace std;

TEST_CASE("Example test")
{
    CHECK(true);
}

TEST_CASE("Testing model constructor"){

    frogger::Model m;

    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();

    CHECK(frog_direction == Direction::up);
    CHECK(frog_position.x == GAMESCREEN_WIDTH/2);
    CHECK(frog_position.y == GAMESCREEN_HEIGHT-CELLSIZE);

    int score = m.score();
    int lives = m.lives();
    State state = m.state();
    auto current_time = m.times_left();

    CHECK(score == 0);
    CHECK(lives == 3);
    CHECK(state == State::play);
    CHECK(current_time == 60);

}

TEST_CASE("Testing whether motion input and score updates work"){

    Model m;

    int current_lane = m.call_calculate_lane();
    int score = m.score();
    CHECK(current_lane == 0);
    CHECK(score == 0);

    m.move_frog(Direction::up);
    score = m.score();


    current_lane = m.call_calculate_lane();
    CHECK(current_lane == 1);
    CHECK(score == 10);

    m.move_frog(Direction::down);
    m.move_frog(Direction::right);
    m.move_frog(Direction::left);
    current_lane = m.call_calculate_lane();
    score = m.score();
    CHECK(current_lane == 0);
    CHECK(score == 10);

    m.move_frog(Direction::up);
    score = m.score();
    CHECK(score == 10);
}

TEST_CASE("Testing for valid moves"){

    Model m;


    CHECK(!m.call_is_move_valid(Direction::down));
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    CHECK(!m.call_is_move_valid(Direction::left));

    for(int i = 0; i<9;i++){
        m.move_frog(Direction::right);
    }

    CHECK(!m.call_is_move_valid(Direction::right));
}

TEST_CASE("Testing for collision and lives reduction"){

    Model m;

    m.move_frog(Direction::up);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left); //collides with car

    int lives = m.lives();
    CHECK(lives == 2);
    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();
    CHECK(frog_direction == Direction::up);
    CHECK(frog_position.x == GAMESCREEN_WIDTH/2);
    CHECK(frog_position.y == GAMESCREEN_HEIGHT-CELLSIZE);
}

TEST_CASE("Testing for drown checks"){

    Model m;

    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);
    m.move_frog(Direction::left);

    m.move_frog(Direction::up);
    m.move_frog(Direction::up);
    m.move_frog(Direction::up);
    m.move_frog(Direction::up);
    m.move_frog(Direction::up);

    int lives = m.lives();
    CHECK(lives == 3);
    CHECK(m.call_calculate_lane() == 5);
    m.move_frog(Direction::up); //frog drowns
    lives = m.lives();
    CHECK(lives == 2);
    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();
    CHECK(frog_direction == Direction::up);
    CHECK(frog_position.x == GAMESCREEN_WIDTH/2);
    CHECK(frog_position.y == GAMESCREEN_HEIGHT-CELLSIZE);
    CHECK(m.call_calculate_lane() == 0);
}

TEST_CASE("Testing for game over") {

    Model m;
    for(int i = 0;i<3;i++){
        m.move_frog(Direction::left);
        m.move_frog(Direction::left);
        m.move_frog(Direction::left);
        m.move_frog(Direction::left);
        m.move_frog(Direction::left);

        m.move_frog(Direction::up);
        m.move_frog(Direction::up);
        m.move_frog(Direction::up);
        m.move_frog(Direction::up);
        m.move_frog(Direction::up);
        m.move_frog(Direction::up); //frog drowns
        int lives = m.lives();
        CHECK(lives == 3-i-1);
    }
    CHECK(m.state() == State::gameover);
}

TEST_CASE("Checking on the game updates on time"){
    Model m;
    m.move_frog(Direction::up);
    m.update(int(2)); //collision of frog and car in lane 1
    CHECK(m.times_left()==60-2);
    CHECK(m.lives() == 2);
    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();
    CHECK(frog_direction == Direction::up);
    CHECK(frog_position.x == GAMESCREEN_WIDTH/2);
    CHECK(frog_position.y == GAMESCREEN_HEIGHT-CELLSIZE);
    CHECK(m.call_calculate_lane() == 0);
}