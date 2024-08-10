#pragma once

#include "window.h"
#include "textbox.h"
#include <vector>

namespace jrat {

	class Ui_Frame : public Window {
	public:

        Ui_Frame(int width, int height, const std::string &title) : 
			Window(width, height, title) 
		{}

        ~Ui_Frame() = default;

		virtual void update() override;
        virtual void draw() override;
        void create_text_box(float x_pos, float y_pos, float width, float height );

	protected:
        std::vector<TextBox> text_boxes_;
        
        Vector2 mouse_pos_{ 0, 0 };

        int active_text_box_{-1};

	};
}