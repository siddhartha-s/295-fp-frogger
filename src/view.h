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
        explicit View(Model const&);

        /// Renders the current state of the model.
        void draw(ge211::Sprite_set&) const;

        /// The actual screen dimensions of the required game window. This would be larger than Model::get_screen()
        /// but same aspect ratio.
        ge211::Dimensions screen_dimensions() const;

    private:
        /// The model.
        Model const& model_;

        /// The sprites.

        //Frog sprites facing each direction
        ge211::Image_sprite const frog_left;
        ge211::Image_sprite const frog_right;
        ge211::Image_sprite const frog_up;
        ge211::Image_sprite const frog_down;

        ge211::Image_sprite const frog_dead;

        ge211::Image_sprite const turtle;
        ge211::Image_sprite const log_beg;
        ge211::Image_sprite const log_middle;
        ge211::Image_sprite const log_end;

        ge211::Image_sprite const car1_beg;
        ge211::Image_sprite const car1_end;

        ge211::Image_sprite const car2_beg;
        ge211::Image_sprite const car2_end;

        ge211::Image_sprite const truck_beg;
        ge211::Image_sprite const car2_middle;
        ge211::Image_sprite const truck_end;

        ge211::Image_sprite const safe;
        ge211::Image_sprite const river;
        ge211::Font sans {"sans.ttf", 30};
        ge211::Text_sprite const W1message{"Game Over!", sans};
        ge211::Text_sprite const time{"Time: ",sans};
        ge211::Text_sprite seconds;
        ge211::Text_sprite const lives{"Lives: ",sans};
        ge211::Text_sprite no_of_lives;
        ge211::Text_sprite const score{"Score: ",sans};
        ge211::Text_sprite const live_score{"Score: ",sans};
        ge211::Text_sprite const you_win{"You Win!", sans};
        ge211::Text_sprite const you_lose{"You Lose!", sans};

    };

}