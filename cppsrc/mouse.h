#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
namespace mousecontroller
{

enum Button
{
    kButtonLeft = 0,
    kButtonRight = 1,
};

class Mouse
{
public:
    Mouse();
    void DispatchMouseEvent(CGMouseButton button, CGEventType type, CGPoint location, uint32_t click_count = 1, uint32_t delay = 0);
    CGPoint GetMousePosition();
    void SetMousePosition(CGPoint position);
    void SetButtonState(Button btn, bool is_pressed, CGPoint point, int click_count = 1);
    void MouseClick(Button btn, CGPoint position);
    void MouseClick(Button btn);
    void MouseDoubleClick(Button btn, CGPoint position);
    void MouseDoubleClick(Button btn);
    void MouseDrag(CGPoint position);
    void MouseStartDrag(CGPoint position);
    void MouseEndDrag(CGPoint position);

private:
    static int event_number_;
    CGEventType previous_event_;
};
} // namespace mousecontroller
