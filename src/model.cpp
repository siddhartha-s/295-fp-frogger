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
        obstacles_[1].push_back({GAMESCREEN_WIDTH/3,GAMESCREEN_HEIGHT-(2*CELLSIZE)});
        obstacles_[1].push_back({(2* GAMESCREEN_WIDTH)/3,GAMESCREEN_HEIGHT-(2*CELLSIZE)});

        obstacles_[2].push_back({GAMESCREEN_WIDTH/4,GAMESCREEN_HEIGHT-(3*CELLSIZE)});
        obstacles_[2].push_back({GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-(3*CELLSIZE)});
        obstacles_[2].push_back({(3*GAMESCREEN_WIDTH)/4,GAMESCREEN_HEIGHT-(3*CELLSIZE)});

        obstacles_[3].push_back({GAMESCREEN_WIDTH/3,GAMESCREEN_HEIGHT-(4*CELLSIZE)});
        obstacles_[3].push_back({(2* GAMESCREEN_WIDTH)/3,GAMESCREEN_HEIGHT-(4*CELLSIZE)});

        obstacles_[4].push_back({GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-(5*CELLSIZE)});

        obstacles_[6].push_back({0,3*CELLSIZE});
        obstacles_[6].push_back({obstacle_dims[4].first,3*CELLSIZE});
        obstacles_[6].push_back({(GAMESCREEN_WIDTH/2)-obstacle_dims[4].first,3*CELLSIZE});
        obstacles_[6].push_back({(GAMESCREEN_WIDTH/2),3*CELLSIZE});
        obstacles_[6].push_back({GAMESCREEN_WIDTH-(2*obstacle_dims[4].first),3*CELLSIZE});
        obstacles_[6].push_back({GAMESCREEN_WIDTH-obstacle_dims[4].first,3*CELLSIZE});

        obstacles_[7].push_back({0,2*CELLSIZE});
        obstacles_[7].push_back({GAMESCREEN_WIDTH-obstacle_dims[5].first,2*CELLSIZE});

        obstacles_[8].push_back({GAMESCREEN_WIDTH,CELLSIZE});
    }

    int Model::calculate_lane() const{
        return (9 - (frog_.position_.y/CELLSIZE));
    }

    void Model::update_score() {
        if (calculate_lane() < highest_reached_){
            score_ +=10;
            highest_reached_= calculate_lane();
        }
    }

    bool Model::frog_collide(int lane){
        if(lane == 0 or lane == 5 or lane == 9){
            return false;
        }
            for(auto &obstacle: obstacles_[lane]){
                if(frog_.position_.x<obstacle.x+obstacle_dims[lane].first and
                frog_.position_.x+CELLSIZE>obstacle.x)
                {

                    return true;
            }
        }

        return false;
    }

    //TO-DO -- update this based on calculate lane, if possible.
    bool Model::is_move_valid(Direction input) const {
        const int curr_lane = calculate_lane();

        if(input == Direction::down and curr_lane == 0){
            return false;
        }
        else if(input == Direction::left and frog_.position_.x == 0 and
        curr_lane >= 1 and curr_lane <5){
            return false;
        }
        else if(input == Direction::right and frog_.position_.x == GAMESCREEN_WIDTH-CELLSIZE and
                curr_lane >= 1 and curr_lane <5){
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

    bool Model::frog_drown(int lane) {

        if(lane < 6 or lane > 8){
            return false;
        }
        else return !(frog_collide(lane));
    }

    void Model::update(double const dt) {
        for(int i = 1; i <=8; i++){
            if(i!=5){
                auto change = lane_velocity[i]*dt;

                for(auto &obstacle :obstacles_[i]){
                    obstacle.x += (int)change;
                }

                    size_t j=0;
                    while (j < obstacles_[i].size()) {
                        if (obstacles_[i][j].x < -obstacle_dims[i].first / 2 and lane_velocity[i] < 0) {
                            auto curr_y = obstacles_[i][j].y;
                            obstacles_[i][j] = std::move(obstacles_[i].back());
                            obstacles_[i].pop_back();
                            obstacles_[i].push_back({GAMESCREEN_WIDTH + 10, curr_y});
                        } else if (obstacles_[i][j].x < GAMESCREEN_WIDTH - (obstacle_dims[i].first / 2) and
                                   lane_velocity[i] > 0) {
                            auto curr_y = obstacles_[i][j].y;
                            obstacles_[i][j] = std::move(obstacles_[i].back());
                            obstacles_[i].pop_back();
                            obstacles_[i].push_back({-obstacle_dims[i].first-10, curr_y});
                        } else {
                            i++;
                        }
                    }
                }
            }

            int curr_lane = calculate_lane();
        if(curr_lane>5 and curr_lane<=8){
            frog_.position_.x += (int)(lane_velocity[curr_lane]*dt);
        }

        if(curr_lane==6 or curr_lane == 8){
            if(frog_.position_.x <=0){
                --lives_;
                frog_ = {{GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-CELLSIZE},Direction::up};
                update_game_state();
            }
            else if (curr_lane==7){
                if(frog_.position_.x >=(GAMESCREEN_WIDTH-CELLSIZE+1)){
                    --lives_;
                    frog_ = {{GAMESCREEN_WIDTH/2,GAMESCREEN_HEIGHT-CELLSIZE},Direction::up};
                    update_game_state();
                }
            }
        }
    }

    void Model::update_time_elapsed_(double dt) {
        time_elapsed_ += dt;
    }
}







