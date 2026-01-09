/*
    Scan code set 1 (for a us qwerty keyboard)
*/

#ifndef SC1_H
#define SC1_H

#define SCANCODE1 0x43

/* chatgpt generated since its too much work */
enum ScanCodeSet1 {
    kEscape       = 0x01,
    kNumOne       = 0x02,
    kNumTwo       = 0x03,
    kNumThree     = 0x04,
    kNumFour      = 0x05,
    kNumFive      = 0x06,
    kNumSix       = 0x07,
    kNumSeven     = 0x08,
    kNumEight     = 0x09,
    kNumNine      = 0x0A,
    kNumZero      = 0x0B,
    kMinus        = 0x0C,
    kEqual        = 0x0D,
    kBackspace    = 0x0E,
    kTab          = 0x0F,
    kQ            = 0x10,
    kW            = 0x11,
    kE            = 0x12,
    kR            = 0x13,
    kT            = 0x14,
    kY            = 0x15,
    kU            = 0x16,
    kI            = 0x17,
    kO            = 0x18,
    kP            = 0x19,
    kLeftBracket  = 0x1A,
    kRightBracket = 0x1B,
    kEnter        = 0x1C,
    kLeftCtrl     = 0x1D,
    kA            = 0x1E,
    kS            = 0x1F,
    kD            = 0x20,
    kF            = 0x21,
    kG            = 0x22,
    kH            = 0x23,
    kJ            = 0x24,
    kK            = 0x25,
    kL            = 0x26,
    kSemicolon    = 0x27,
    kApostrophe   = 0x28,
    kBacktick     = 0x29,
    kLeftShift    = 0x2A,
    kBackslash    = 0x2B,
    kZ            = 0x2C,
    kX            = 0x2D,
    kC            = 0x2E,
    kV            = 0x2F,
    kB            = 0x30,
    kN            = 0x31,
    kM            = 0x32,
    kComma        = 0x33,
    kDot          = 0x34,
    kSlash        = 0x35,
    kRightShift   = 0x36,
    kKeypadStar   = 0x37,
    kLeftAlt      = 0x38,
    kSpace        = 0x39,
    kCapsLock     = 0x3A,
    kF1           = 0x3B,
    kF2           = 0x3C,
    kF3           = 0x3D,
    kF4           = 0x3E,
    kF5           = 0x3F,
    kF6           = 0x40,
    kF7           = 0x41,
    kF8           = 0x42,
    kF9           = 0x43,
    kF10          = 0x44,
    kNumLock      = 0x45,
    kScrollLock   = 0x46,
    kKeypad7      = 0x47,
    kKeypad8      = 0x48,
    kKeypad9      = 0x49,
    kKeypadMinus  = 0x4A,
    kKeypad4      = 0x4B,
    kKeypad5      = 0x4C,
    kKeypad6      = 0x4D,
    kKeypadPlus   = 0x4E,
    kKeypad1      = 0x4F,
    kKeypad2      = 0x50,
    kKeypad3      = 0x51,
    kKeypad0      = 0x52,
    kKeypadDot    = 0x53,

    // Extended keys (prefix 0xE0)
    kF11          = 0x57,
    kF12          = 0x58,
    
    // Optional extras (E0-prefixed, for completeness)
    kKeypadEnter  = 0xE01C,
    kRightCtrl    = 0xE01D,
    kKeypadSlash  = 0xE035,
    kRightAlt     = 0xE038,
    kHome         = 0xE047,
    kUpArrow      = 0xE048,
    kPageUp       = 0xE049,
    kLeftArrow    = 0xE04B,
    kRightArrow   = 0xE04D,
    kEnd          = 0xE04F,
    kDownArrow    = 0xE050,
    kPageDown     = 0xE051,
    kInsert       = 0xE052,
    kDelete       = 0xE053
};

// Scan Code Set 1 → ASCII lookup (non-shifted)
static const char scancode_ascii[128] = {
    0,  27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00–0x0E
    '\t',  // Tab
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // 0x0F–0x1C
    0,      // Ctrl
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', // 0x1D–0x29
    0,      // Left Shift
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,  // 0x2A–0x36
    '*',
    0,      // Alt
    ' ',    // Space
    0,      // CapsLock
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F1–F10
    0,      // NumLock
    0,      // ScrollLock
    0,      // Home
    0,      // Up
    0,      // PgUp
    '-',
    0,      // Left
    0,
    0,      // Right
    '+',
    0,      // End
    0,      // Down
    0,      // PgDn
    0,      // Insert
    0       // Delete
};

// Shifted ASCII lookup
static const char scancode_ascii_shift[128] = {
    0,  27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*',
    0,
    ' ',
    0,
    0,0,0,0,0,0,0,0,0,0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0
};


#endif