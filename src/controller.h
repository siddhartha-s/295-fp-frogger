#pragma once

#include "model.h"
#include "view.h"
#include <ge211.h>

namespace frogger{

class Controller : public ge211::Abstract_game{

public:
    explicit Controller();

protected:
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

    //configures responses for keyboard inputs.
    void on_key(ge211::Key key) override;

    //draws the game
    void draw(ge211::Sprite_set&) override;

    //overrides the function which is when each frame is rendered/refreshed
    void on_frame(double last_frame_seconds) override;

    //shows passage of time and triggers model time-based functions
    void pass_time(double seconds);

private:
    Model model_;
    View view_;

};
}