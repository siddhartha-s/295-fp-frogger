#include "controller.h"
#include<iostream>

using namespace frogger;
using namespace ge211;

namespace frogger{

    frogger::Controller::Controller()
            : model_()
            , view_(model_)
    {

    }

    void Controller::draw(ge211::Sprite_set & set) {
        view_.draw(set);
    }

    Dimensions Controller::initial_window_dimensions() const
    {
        return view_.screen_dimensions();
    }

    std::string Controller::initial_window_title() const
    {
        return "Frogger";
    }

    void Controller::on_key(ge211::Key key){

        if(model_.state() == State::gameover or model_.state() == State::win){
            return;
        }
        if (key == Key::right()){
            model_.move_frog(Direction::right);
        }
        else if (key == Key::left()){
            model_.move_frog(Direction::left);
        }
        else if (key == Key::down()){
            model_.move_frog(Direction::down);
        }
        else if (key == Key::up()){
            model_.move_frog(Direction::up);
        }
    }

    void Controller::on_frame(double last_frame_seconds) {
        if(model_.state() == State::gameover or model_.state() == State::win){
            return;
        }
        model_.update(last_frame_seconds);
    }

}

