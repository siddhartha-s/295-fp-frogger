#pragma once
#include "model.h"
#include <ge211.h>

namespace frogger{


    //length of one game-unit
    int const cell_size = 8;


    class View {
    public:
        /// The view has const& access to the model--it can see it but cannot
        /// change it.
        explicit View(Model &);

        /// Renders the current state of the model.
        void draw(ge211::Sprite_set&);

        /// The actual screen dimensions of the required game window. This would be larger than Model::get_screen()
        /// but same aspect ratio.
        ge211::Dimensions screen_dimensions() const;

    private:
        /// The model.
        Model & model_;

        /// The sprites.

        ge211::Image_sprite const frog_left = ge211::Image_sprite("frog1_left.png");
        ge211::Image_sprite const frog_right = ge211::Image_sprite("frog1_right.png");
        ge211::Image_sprite const frog_up = ge211::Image_sprite("frog1_up.png");
        ge211::Image_sprite const frog_down = ge211::Image_sprite("frog1_down.png");

        ge211::Image_sprite const turtle_ = ge211::Image_sprite("turtle2.png");

        ge211::Image_sprite const log1_ = ge211::Image_sprite("log3.png");
        ge211::Image_sprite const log2_ = ge211::Image_sprite("log4.png");


        ge211::Image_sprite const car1_ = ge211::Image_sprite("car1.png");
        ge211::Image_sprite const car2_ = ge211::Image_sprite("car2.png");
        ge211::Image_sprite const car3_ = ge211::Image_sprite("car3.png");
        ge211::Image_sprite const truck1_ = ge211::Image_sprite("truck1.png");

        ge211::Image_sprite const safe_space = ge211::Image_sprite("safe_space_2.png");
        ge211::Image_sprite const river = ge211::Image_sprite("river2.png");

        ge211::Image_sprite const hearts = ge211::Image_sprite("heart2.png");
        std::vector<ge211::Image_sprite> obstacle_sprites_ = {safe_space,car1_,car2_,car3_,truck1_,safe_space,turtle_,
                                                              log1_,log2_,safe_space};

        // ge211::Image_sprite const river;
        ge211::Font sans {"sans.ttf", 15};
        ge211::Font sans2 {"sans.ttf", 25};
        ge211::Text_sprite const time{"Time Left: ",sans};
        ge211::Text_sprite seconds;
        ge211::Text_sprite const score{"Score: ",sans};
        ge211::Text_sprite const final_score{"Final Score: ",sans2};
        ge211::Text_sprite curr_score;
        ge211::Image_sprite const game_over = ge211::Image_sprite("gameover.jpg");
        ge211::Image_sprite const you_win = ge211::Image_sprite("you_win.jpg");
    };

}