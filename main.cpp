#define STUI_IMPLEMENTATION
#include <stui_extensions.h>

using namespace stui;

int orientation = 0;
void flipScreenCallback()
{
    if (orientation == 0)
    {
        system("echo 2 | sudo tee /sys/class/graphics/fbcon/rotate_all");
        orientation = 2;
    }
    else
    {
        system("echo 0 | sudo tee /sys/class/graphics/fbcon/rotate_all");
        orientation = 0;
    }
}

int main()
{
    Terminal::configure();

    Page p;

    p.registerComponent(new Banner("Hello, World!"), "b");
    p.registerComponent(new BorderedBox(p["b"], ""), "bb");
    p.registerComponent(new TextInputBox("...", nullptr, true), "tib");
    p.registerComponent(new BorderedBox(p["tib"], ""), "bb2");
    p.registerComponent(new Button("flip screen", flipScreenCallback, true), "flip_button");
    p.registerComponent(new VerticalBox({ p["bb"], p["bb2"], p["flip_button"] }), "vb");

    p.setRoot(p["vb"]);
    p.focusable_component_sequence.push_back(p["tib"]);
    p.focusable_component_sequence.push_back(p["flip_button"]);

    p.render();
    p.render();

    bool dirty = false;
    while (true)
    {
        p.framerate(8);
        dirty |= p.checkInput();
        
        if (dirty) p.render();
        dirty = false;
    }

    return 1;
}