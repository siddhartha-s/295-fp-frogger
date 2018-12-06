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
    highest_reached_(CELLSIZE),
    time_elapsed_(0.0)
    {
        for(int i = 0; i<8; i++){
            obstacles_.emplace_back();
        }

        obstacles_[0].push_back({GAMESCREEN_WIDTH/3,GAMESCREEN_HEIGHT-(2*CELLSIZE)});
        obstacles_[0].push_back({(2* GAMESCREEN_WIDTH)/3,GAMESCREEN_HEIGHT-(2*CELLSIZE)});

        obstacles_[1].push_back({GAMESCREEN_WIDTH/4,GAMESCREEN_HEIGHT-(3*CELLSIZE)});
        obstacles_[1].push_back({GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-(3*CELLSIZE)});
        obstacles_[1].push_back({(3*GAMESCREEN_WIDTH)/4,GAMESCREEN_HEIGHT-(3*CELLSIZE)});

        obstacles_[2].push_back({GAMESCREEN_WIDTH/3,GAMESCREEN_HEIGHT-(4*CELLSIZE)});
        obstacles_[2].push_back({(2* GAMESCREEN_WIDTH)/3,GAMESCREEN_HEIGHT-(4*CELLSIZE)});

        obstacles_[3].push_back({GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-(5*CELLSIZE)});

        obstacles_[4].push_back({0,3*CELLSIZE});
        obstacles_[4].push_back({obstacle_dims[4].first,3*CELLSIZE});
        obstacles_[4].push_back({(GAMESCREEN_WIDTH/2)-obstacle_dims[4].first,3*CELLSIZE});
        obstacles_[4].push_back({(GAMESCREEN_WIDTH/2),3*CELLSIZE});
        obstacles_[4].push_back({GAMESCREEN_WIDTH-(2*obstacle_dims[4].first),3*CELLSIZE});
        obstacles_[4].push_back({GAMESCREEN_WIDTH-obstacle_dims[4].first,3*CELLSIZE});

        obstacles_[5].push_back({0,2*CELLSIZE});
        obstacles_[5].push_back({GAMESCREEN_WIDTH-obstacle_dims[5].first,2*CELLSIZE});

        obstacles_[6].push_back({GAMESCREEN_WIDTH,CELLSIZE});
    }

    int Model::calculate_lane() {
        int lane = frog_.position_.y/CELLSIZE;
        if(lane == 0) return 100;
        if(lane > 8 or lane ==4){
            return -1;
        }
        else if(lane >= 5){
            return 8 - lane;
        }
        else if(lane >= 1){
            return 7-lane;
        }
        else{
            return -1;
        }
    }

    void Model::update_score() {
        if (frog_.position_.y < highest_reached_){
            score_ +=10;
            highest_reached_= frog_.position_.y;
        }
    }

    bool Model::frog_collide(int lane){
            for(auto &obstacle: obstacles_[lane]){
                if(frog_.position_.x<obstacle.x+obstacle_dims[lane].first and
                frog_.position_.x+CELLSIZE>obstacle.x)
                {

                    return true;
            }
        }

        return false;
    }

    bool Model::is_move_valid(Direction input) const {

        if(input == Direction::down and frog_.position_.y == GAMESCREEN_HEIGHT-CELLSIZE){
            return false;
        }
        else if(input == Direction::left and frog_.position_.x == 0 and
        frog_.position_.y >= GAMESCREEN_HEIGHT - 5*CELLSIZE){
            return false;
        }
        else if(input == Direction::right and frog_.position_.x == GAMESCREEN_WIDTH-CELLSIZE and
        frog_.position_.y >= GAMESCREEN_HEIGHT - 5*CELLSIZE){
            return false;
        }

        return true;
    }

    void Model::update_game_state() {
        if(lives_==0 or time_elapsed_ == GAME_TIME){
            state_= State::gameover;
        }
    }

    void Model::move_frog(Direction motion) {
        if(motion == Direction::up and is_move_valid(motion)){
            frog_.position_.y -= CELLSIZE;
        }
        else if(motion == Direction::down and is_move_valid(motion)){
            frog_.position_.y += CELLSIZE;
        }
        else if(motion == Direction::left and is_move_valid(motion)){
            frog_.position_.x -= CELLSIZE;
        }
        else if(motion == Direction::right and is_move_valid(motion)){
            frog_.position_.x += CELLSIZE;
        }

        int lane = calculate_lane();

        bool check = false;
        if(lane >= 0 and lane < 4){
            check = frog_collide(lane);
        }
        else if(lane < 7 and lane >= 4){
            check = frog_drown(lane);
        }
        if(check){
            --lives_;
            frog_ = {{GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-CELLSIZE},Direction::up};
        }

        update_game_state();
    }
}







