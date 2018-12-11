#include "view.h"
#include<iostream>

namespace frogger{


    View::View(Model & model)
    : model_(model){


    }

    ge211::Dimensions View::screen_dimensions() const {
        return {(int)GAMESCREEN_WIDTH,
                (int)(GAMESCREEN_HEIGHT + 3*CELLSIZE)};
    }

    void View::draw(ge211::Sprite_set & sprites) {

        if(model_.state()==State::gameover){

            sprites.add_sprite(game_over,{0,0},1);
            auto const& text_sprite2 = final_score;
            sprites.add_sprite(text_sprite2,{0,(int)(GAMESCREEN_HEIGHT)},1);
            curr_score.reconfigure(ge211::Text_sprite::Builder(sans2)
                                           << model_.score());
            sprites.add_sprite(curr_score,{(int)(GAMESCREEN_WIDTH/2 + 20),(int)(GAMESCREEN_HEIGHT)},1);
            return;
        }

        else if(model_.state()==State::win){
            auto const& sprite = you_win;
            sprites.add_sprite(you_win,{0,0},1);
            return;
        }

        //rendering safe lanes
        auto const & sprite = safe_space;

        sprites.add_sprite(sprite,{0,0},1);
        sprites.add_sprite(sprite,{0,4*CELLSIZE},1);
        sprites.add_sprite(sprite,{0,(int)(GAMESCREEN_HEIGHT-CELLSIZE)},1);

        //rendering river
        auto const & sprite_river = river;
        sprites.add_sprite(sprite_river,{0,CELLSIZE},1);
        sprites.add_sprite(sprite_river,{0,2*CELLSIZE},1);
        sprites.add_sprite(sprite_river,{0,3*CELLSIZE},1);

        //rendering obstacles
        std::vector<std::vector<ge211::Basic_position<Model::Coordinate>>> obstacles = model_.obstacles();

        for(int i = 1; i < obstacles.size()-1; i++){
            if(i == 5){
                continue;
            }
            auto const & obstacle_sprite = obstacle_sprites_[i];
            for(auto & obstacle :obstacles[i]){
                sprites.add_sprite(obstacle_sprite,obstacle.into<int>(),2);
            }
        }


        Direction curr_direction = model_.frog_direction();
        ge211::Basic_position<Model::Coordinate> curr_player_position = model_.frog_position();


        // rendering frog

        if(curr_direction == Direction::up){
            auto const& frog_sprite = frog_up;
            sprites.add_sprite(frog_sprite,curr_player_position.into<int>(),3);
        }
        else if(curr_direction == Direction::right){
            auto const& frog_sprite = frog_right;
            sprites.add_sprite(frog_sprite,curr_player_position.into<int>(),3);
        }
        else if(curr_direction == Direction::left){
            auto const& frog_sprite = frog_left;
            sprites.add_sprite(frog_sprite,curr_player_position.into<int>(),3);
        }
        else if(curr_direction == Direction::down){
            auto const& frog_sprite = frog_down;
            sprites.add_sprite(frog_sprite,curr_player_position.into<int>(),3);
        }


        //incorporating meta-data into screen eg: score, lives, time left.
        for(int i = 0; i<model_.lives(); i++){
            auto const& heart_sprite = hearts;
            sprites.add_sprite(heart_sprite,{i*10,(int)(GAMESCREEN_HEIGHT)},1);
        }

        auto const& text_sprite2 = score;
        sprites.add_sprite(text_sprite2,{(int)(GAMESCREEN_WIDTH-70),(int)(GAMESCREEN_HEIGHT)},1);

        curr_score.reconfigure(ge211::Text_sprite::Builder(sans)
                                         << model_.score());
        sprites.add_sprite(curr_score,{(int)(GAMESCREEN_WIDTH- 20),(int)(GAMESCREEN_HEIGHT)},1);

        auto const& text_sprite3 = time;
        sprites.add_sprite(text_sprite3,{0,(int)(GAMESCREEN_HEIGHT+15)},1);

        seconds.reconfigure(ge211::Text_sprite::Builder(sans)
                                    << (int) model_.times_left());
        sprites.add_sprite(seconds,{110,(int)(GAMESCREEN_HEIGHT+15)},1);
    }


}