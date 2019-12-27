#include "../mouse.h"

using namespace mousecontroller;

Mouse::Mouse()
{
    this->previous_event_ = kCGEventNull;
}

int Mouse::event_number_ = 32000;

void Mouse::DispatchMouseEvent(CGMouseButton button, CGEventType type, CGPoint position, uint32_t click_count, uint32_t delay)
{
    if (this->previous_event_ == kCGEventMouseMoved || this->previous_event_ == kCGEventLeftMouseDragged)
    {
        usleep(delay);
    }

    Mouse::event_number_++;
    CGEventRef event = CGEventCreateMouseEvent(NULL, type, position, button);
    CGEventSetType(event, type);
    CGEventSetIntegerValueField(event, kCGMouseEventNumber, Mouse::event_number_);
    CGEventSetIntegerValueField(event, kCGMouseEventClickState, click_count);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);
    this->previous_event_ = type;
    usleep(delay);
}

CGPoint Mouse::GetMousePosition()
{
    usleep(200000);
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    return cursor;
}

void Mouse::SetMousePosition(CGPoint position)
{
    Mouse::DispatchMouseEvent(kCGMouseButtonLeft, kCGEventMouseMoved, position);
    this->previous_event_ = kCGEventMouseMoved;
}

void Mouse::SetButtonState(Button btn, bool is_pressed, CGPoint position, int click_count)
{
    CGEventType type;
    CGMouseButton button;

    switch (btn)
    {
    case kButtonLeft:
        type = (is_pressed ? kCGEventLeftMouseDown : kCGEventLeftMouseUp);
        button = kCGMouseButtonLeft;
        break;

    case kButtonRight:
        type = (is_pressed ? kCGEventRightMouseDown : kCGEventRightMouseUp);
        button = kCGMouseButtonRight;
        break;
    };

    Mouse::DispatchMouseEvent(button, type, position, click_count, 200000);
}

void Mouse::MouseClick(Button btn, CGPoint position)
{
    Mouse::SetButtonState(btn, true, position);  // Press
    Mouse::SetButtonState(btn, false, position); // Release
}

void Mouse::MouseClick(Button btn)
{
    CGPoint position = Mouse::GetMousePosition();
    Mouse::MouseClick(btn, position);
}

void Mouse::MouseDoubleClick(Button btn, CGPoint position)
{
    Mouse::SetButtonState(btn, true, position);
    Mouse::SetButtonState(btn, false, position);
    Mouse::SetButtonState(btn, true, position, 2);
    Mouse::SetButtonState(btn, false, position, 2);
}

void Mouse::MouseDoubleClick(Button btn)
{
    CGPoint position = Mouse::GetMousePosition();
    Mouse::MouseDoubleClick(btn, position);
}

void Mouse::MouseDrag(CGPoint position)
{
    Mouse::DispatchMouseEvent(kCGMouseButtonLeft, kCGEventLeftMouseDragged, position);
}

void Mouse::MouseStartDrag(CGPoint position)
{
    Mouse::SetButtonState(kButtonLeft, true, position);
    Mouse::MouseDrag(position);
}

void Mouse::MouseEndDrag(CGPoint position)
{
    Mouse::MouseDrag(position);
    Mouse::SetButtonState(kButtonLeft, false, position);
}
