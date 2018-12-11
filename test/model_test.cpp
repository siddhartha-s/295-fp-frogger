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
    CHECK(m.call_calculate_lane() == 1);
    m.move_frog(Direction::down);
    CHECK(m.call_calculate_lane() == 0);

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

TEST_CASE("Checking on the game updates on time and collisions are detected"){
    Model m;
    m.move_frog(Direction::up);
    m.update(int(2)); //collision of frog and car in lane 1
    //tests update_time() functions
    CHECK(m.times_left()==60-2);
    CHECK(m.lives() == 2);
    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();
    CHECK(frog_direction == Direction::up);
    CHECK(frog_position.x == GAMESCREEN_WIDTH/2);
    CHECK(frog_position.y == GAMESCREEN_HEIGHT-CELLSIZE);
    CHECK(m.call_calculate_lane() == 0);
}

TEST_CASE("Checking on update in position of obstacle ?(turtle swimming with) update in time and frog can land on turtle and not drown"){
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

    m.update(int(5)); //turtle's position is updated to be in front of frog
    m.move_frog(Direction::up);
    CHECK(m.lives() == 3);
    CHECK(m.call_calculate_lane() == 6);
}

TEST_CASE("Checking time's up, game over"){
    Model m;
    m.update(int(60));
    CHECK(m.times_left()==0);
    CHECK(m.state()==State::gameover);
}

TEST_CASE("Checking whether frog's position is updated with time in river"){
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
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    CHECK(m.lives() == 3);
    m.update(2.5);
    m.move_frog(Direction::up);
    CHECK(m.lives() == 3);//frog is on top of turtle
    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();
    m.update(2.5);
    CHECK(frog_position != m.frog_position()); //the frog moves with time while on top of turtle
}

TEST_CASE("Checking whether frog dies if it reaches end of screen in river section while on top of obstacle"){
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
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    CHECK(m.lives() == 3);
    m.update(2.5);
    m.move_frog(Direction::up);
    CHECK(m.lives() == 3);//frog is on top of turtle
    Direction frog_direction = m.frog_direction();
    ge211::Basic_position<double> frog_position = m.frog_position();
    m.update(2.5);
    CHECK(frog_position != m.frog_position()); //the frog moves with time while on top of turtle
    m.update(10); //post 10 seconds, the frog reaches the end of the screen due to constant time-based updates and dies
    CHECK(m.lives() == 2);
    ge211::Basic_position<double> frog_position2 = m.frog_position();
    CHECK(frog_position2.x == GAMESCREEN_WIDTH/2);
    CHECK(frog_position2.y == GAMESCREEN_HEIGHT-CELLSIZE);

}

TEST_CASE("Testing a win situation"){
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
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    m.move_frog(Direction::right);
    CHECK(m.lives() == 3);
    m.update(2);
    m.move_frog(Direction::up);
    CHECK(m.lives() == 3);//frog is on top of turtle
    m.move_frog(Direction::up);
    CHECK(m.lives() == 3);//frog is on top of first log
    m.move_frog(Direction::up);
    m.update(.25);
    CHECK(m.lives() == 3);//frog is on top of first log
    m.move_frog(Direction::up);
    CHECK(m.call_calculate_lane()==9);
    CHECK(m.state() == State::win);

}