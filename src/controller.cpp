#include "controller.h"
#include<iostream>

using namespace frogger;
using namespace ge211;

namespace frogger{

    frogger::Controller::Controller()
            : model_()
            , view_(model_)
    { }

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

    void Controller::on_mouse_move(Position screen_pos)
    {
        mouse_column_ = view_.screen_to_board(screen_pos).x;
        mouse_row_ = view_.screen_to_board(screen_pos).y;
    }

    void Controller::on_mouse_down(Mouse_button btn, Position screen_posn)
    {
        if (model_.get_turn() == Player::neither) return;
        if (btn != Mouse_button::left) return;

        int col_no = view_.screen_to_board(screen_posn).x;
        int row_no = view_.screen_to_board(screen_posn).y;
        if (!model_.is_valid_row_col(row_no,col_no)) return;

        posn selected = model_.selected();

        bool is_selected = selected.x != -1 or selected.y != -1;

        if (!is_selected) {
            model_.select_pawn(row_no,col_no);
        }
        else{
            model_.place_pawn(row_no,col_no);
        }
    }


}

