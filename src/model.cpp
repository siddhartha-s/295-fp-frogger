#include "model.h"
#include <ge211.h>
#include <cassert>
#include<iostream>

namespace frogger{

    Model::Model()
    : frog_({{GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-CELLSIZE},Direction::up}),
    lives_(3),
    score_(0),
    state_(State::play),
    highest_reached_(0),
    time_elapsed_(0.0)
    {
        for(int i = 0; i<10; i++){
            obstacles_.emplace_back();
        }

        //this is not put in a loop because you're setting the initial positions for obstacles.
        obstacles_[1].push_back({GAMESCREEN_WIDTH/7,GAMESCREEN_HEIGHT-(2*CELLSIZE)});
        obstacles_[1].push_back({(5* GAMESCREEN_WIDTH)/7,GAMESCREEN_HEIGHT-(2*CELLSIZE)});

        obstacles_[2].push_back({GAMESCREEN_WIDTH/4,GAMESCREEN_HEIGHT-(3*CELLSIZE)});
        obstacles_[2].push_back({GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-(3*CELLSIZE)});
        obstacles_[2].push_back({(3*GAMESCREEN_WIDTH)/4,GAMESCREEN_HEIGHT-(3*CELLSIZE)});

        obstacles_[3].push_back({GAMESCREEN_WIDTH/3,GAMESCREEN_HEIGHT-(4*CELLSIZE)});
        obstacles_[3].push_back({(2* GAMESCREEN_WIDTH)/3,GAMESCREEN_HEIGHT-(4*CELLSIZE)});

        obstacles_[4].push_back({GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-(5*CELLSIZE)});

        obstacles_[6].push_back({0,3*CELLSIZE});
        obstacles_[6].push_back({obstacle_dims[4].first,3*CELLSIZE});
        obstacles_[6].push_back({GAMESCREEN_WIDTH-(2*obstacle_dims[4].first),3*CELLSIZE});
        obstacles_[6].push_back({GAMESCREEN_WIDTH-obstacle_dims[4].first,3*CELLSIZE});

        obstacles_[7].push_back({0,2*CELLSIZE});
        obstacles_[7].push_back({GAMESCREEN_WIDTH-obstacle_dims[5].first,2*CELLSIZE});

        obstacles_[8].push_back({GAMESCREEN_WIDTH,CELLSIZE});

    }

    int Model::calculate_lane() const{
        return (9 - (int)(frog_.position_.y/CELLSIZE));
    }

    void Model::update_score() {
        int curr_lane = calculate_lane();
        if (curr_lane > highest_reached_){
            score_ +=10;
            highest_reached_= curr_lane;
        }
    }

    bool Model::frog_collide(int lane){
        if(lane == 0 or lane == 5 or lane == 9){
            return false;
        }
            for(auto &obstacle: obstacles_[lane]){
                if(frog_.position_.x<obstacle.x+obstacle_dims[lane].first and
                frog_.position_.x+CELLSIZE>obstacle.x and
                frog_.position_.y < obstacle.y + obstacle_dims[lane].second and
                frog_.position_.y + CELLSIZE > obstacle.y)
                {

                    return true;
            }
        }

        return false;
    }

    bool Model::is_move_valid(Direction input) const {
        const int curr_lane = calculate_lane();

        if(input == Direction::down and curr_lane == 0){
            return false;
        }
        else if(input == Direction::left and frog_.position_.x == 0 and
        curr_lane >=0 and curr_lane <=5){
            return false;
        }
        else if(input == Direction::right and frog_.position_.x == GAMESCREEN_WIDTH-CELLSIZE and
                curr_lane >=0 and curr_lane <=5){
            return false;
        }

        return true;
    }

    void Model::update_game_state(){
        if(lives_==0 or time_elapsed_ >= GAME_TIME){
            state_= State::gameover;
        }
        if(calculate_lane() == 9){
            state_= State::win;
        }
    }

    void Model::move_frog(Direction motion){
        if(motion == Direction::up and is_move_valid(motion)){
            frog_.position_.y -= CELLSIZE;
            frog_.direction_ = Direction::up;
        }
        else if(motion == Direction::down and is_move_valid(motion)){
            frog_.position_.y += CELLSIZE;
            frog_.direction_ = Direction::down;
        }
        else if(motion == Direction::left and is_move_valid(motion)){
            frog_.position_.x -= CELLSIZE;
            frog_.direction_ = Direction::left;
        }
        else if(motion == Direction::right and is_move_valid(motion)){
            frog_.position_.x += CELLSIZE;
            frog_.direction_ = Direction::right;
        }
        update_score();
        int lane = calculate_lane();

        bool check = false;
        if(lane > 0 and lane <= 4){
            check = frog_collide(lane);
        }
        else if(lane < 9 and lane >= 6){
            check = frog_drown(lane);
        }

        if(check){
            kill_frog();
        }

        update_game_state();
    }

    bool Model::frog_drown(int lane) {
        return !(frog_collide(lane));
    }

    void Model::update(double const dt) {
        update_time_elapsed_(dt);

        for (int i = 1; i <= 8; i++) {
            if (i != 5) {
                update_lane_(i, dt);
            }
        }


        int curr_lane = calculate_lane();

        if (curr_lane > 5 and curr_lane <= 8) {
            frog_.position_.x += lane_velocity[curr_lane] * dt;
        }

        bool check = false;
        if(curr_lane > 0 and curr_lane <= 4){
            check = frog_collide(curr_lane);
        }
        else if(curr_lane < 9 and curr_lane >= 6){
            check = frog_drown(curr_lane);
        }

        if(check){
            kill_frog();
        }
        update_score();
        update_game_state();

        if(curr_lane>5){
            if (lane_velocity[curr_lane]<0){
                if (frog_.position_.x <0) {
                    kill_frog();
                } else if (lane_velocity[curr_lane]>0) {
                    if (frog_.position_.x >= (GAMESCREEN_WIDTH)){
                        kill_frog();
                    }
                }
        }
        }

        update_score();
        update_game_state();
    }


    void Model::update_time_elapsed_(double dt) {
        if(state() == State::play){
            time_elapsed_ += dt;
        }
    }

    void Model::update_lane_(int i, double dt) {
        auto change = lane_velocity[i]*dt;

        for(auto &obstacle :obstacles_[i]){
            obstacle.x += change;
        }

        size_t j=0;

        while (j < obstacles_[i].size()){
            if (obstacles_[i][j].x < -obstacle_dims[i].first and lane_velocity[i] < 0){
                auto curr_y = obstacles_[i][j].y;
                //obstacles_[i][j] = std::move(obstacles_[i].back());
                std::swap(obstacles_[i][j],obstacles_[i].back());
                obstacles_[i].pop_back();
                obstacles_[i].push_back({GAMESCREEN_WIDTH, curr_y});
            } else if (obstacles_[i][j].x > GAMESCREEN_WIDTH and lane_velocity[i] > 0){
                auto curr_y = obstacles_[i][j].y;
                //obstacles_[i][j] = std::move(obstacles_[i].back());
                std::swap(obstacles_[i][j],obstacles_[i].back());
                obstacles_[i].pop_back();
                obstacles_[i].push_back({0-obstacle_dims[i].first, curr_y});
                ++j;
            }else{
                ++j;
            }
        }
    }

    void Model::kill_frog(){
        --lives_;
        frog_ = {{GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-CELLSIZE},Direction::up};
        update_game_state();
    }
}







