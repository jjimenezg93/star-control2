#pragma warning(disable: 4514)

#ifndef UGINE_SCREEN_H
#define UGINE_SCREEN_H

#include "string.h"
#include "types.h"

class Screen {
public:
    static Screen& Instance();
	
	// Pantalla
    virtual void Open(uint16 width, uint16 height, bool fullscreen);
    virtual void Close();
    virtual bool IsOpened() const { return opened; }
    virtual void SetTitle(const String& title);
    virtual void Refresh();
    virtual uint16 GetWidth() const { return width; }
    virtual uint16 GetHeight() const { return height; }
    virtual uint16 GetDesktopWidth() const;
    virtual uint16 GetDesktopHeight() const;

	// Temporizador
    double ElapsedTime() const { return elapsed; }

	// Input
    virtual int32 GetMouseX() const { return mousex; }
    virtual int32 GetMouseY() const { return mousey; }
    virtual bool MouseButtonPressed(int button) const;
    virtual bool KeyPressed(int key) const;
protected:
    Screen();
    virtual ~Screen();
private:
    static Screen* screen;

    bool opened;
    uint16 width, height;
    int32 mousex, mousey;
    double lastTime;
    double elapsed;

    static int CloseCallback();
};

#endif
