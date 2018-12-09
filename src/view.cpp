#include "view.h"
#include<iostream>

namespace frogger{


    View::View(Model & model)
    : model_(model){

    }

    ge211::Dimensions View::screen_dimensions() const {
        return {GAMESCREEN_WIDTH,
                GAMESCREEN_HEIGHT + 3*CELLSIZE};
    }

    void View::draw(ge211::Sprite_set & sprites) {


        //rendering safe lanes
        auto const & sprite = safe_space;

        sprites.add_sprite(sprite,{0,0},1);
        sprites.add_sprite(sprite,{0,4*CELLSIZE},1);
        sprites.add_sprite(sprite,{0,GAMESCREEN_HEIGHT-CELLSIZE},1);

        //rendering obstacles
        std::vector<std::vector<ge211::Position>> obstacles = model_.obstacles();

        for(int i = 1; i < obstacles.size()-1; i++){
            if(i == 5){
                continue;
            }
            auto const & obstacle_sprite = obstacle_sprites_[i];
            for(auto & obstacle :obstacles[i]){
                sprites.add_sprite(obstacle_sprite,obstacle,2);
            }
        }


        Direction curr_direction = model_.frog_direction();
        ge211::Position curr_player_position = model_.frog_position();


        // rendering frog

        if(curr_direction == Direction::up){
            auto const& frog_sprite = frog_up;
            sprites.add_sprite(frog_sprite,curr_player_position,3);
        }
        else if(curr_direction == Direction::right){
            auto const& frog_sprite = frog_right;
            sprites.add_sprite(frog_sprite,curr_player_position,3);
        }
        else if(curr_direction == Direction::left){
            auto const& frog_sprite = frog_left;
            sprites.add_sprite(frog_sprite,curr_player_position,3);
        }
        else if(curr_direction == Direction::down){
            auto const& frog_sprite = frog_down;
            sprites.add_sprite(frog_sprite,curr_player_position,3);
        }

        //incorporating text

        auto const& text_sprite1 = lives;
        sprites.add_sprite(text_sprite1,{0,GAMESCREEN_HEIGHT},1);

        for(int i = 0; i<model_.lives(); i++){
            auto const& heart_sprite = hearts;
            sprites.add_sprite(heart_sprite,{i*10,GAMESCREEN_HEIGHT+15},1);
        }

        auto const& text_sprite2 = score;
        sprites.add_sprite(text_sprite2,{GAMESCREEN_WIDTH-90,GAMESCREEN_HEIGHT},1);

        curr_score.reconfigure(ge211::Text_sprite::Builder(sans)
                                         << model_.score());
        sprites.add_sprite(curr_score,{GAMESCREEN_WIDTH- 70,GAMESCREEN_HEIGHT},1);

        auto const& text_sprite3 = time;
        sprites.add_sprite(text_sprite3,{0,GAMESCREEN_HEIGHT+15},1);

        seconds.reconfigure(ge211::Text_sprite::Builder(sans)
                                    << model_.times_elapsed());
        sprites.add_sprite(seconds,{110,GAMESCREEN_HEIGHT+15},1);
    }


}