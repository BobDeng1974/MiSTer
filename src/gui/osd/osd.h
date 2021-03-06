#ifndef GUI_OSD_OSD_H_
#define GUI_OSD_OSD_H_

#include <string>
#include <stdint.h>

using namespace std;

// OSD menu control constants
#define OSDCTRLUP        0x01        /*OSD up control*/
#define OSDCTRLDOWN      0x02        /*OSD down control*/
#define OSDCTRLSELECT    0x04        /*OSD select control*/
#define OSDCTRLMENU      0x08        /*OSD menu control*/
#define OSDCTRLRIGHT     0x10        /*OSD right control*/
#define OSDCTRLLEFT      0x20        /*OSD left control*/

// ---- old Minimig v1 constants -------
#define MM1_OSDCMDREAD     0x00      // OSD read controller/key status
#define MM1_OSDCMDWRITE    0x20      // OSD write video data command
#define MM1_OSDCMDDISABLE  0x40      // OSD disable command
#define MM1_OSDCMDENABLE   0x41      // OSD enable command
#define MM1_OSDCMDRST      0x80      // OSD reset command
#define MM1_OSDCMDAUTOFIRE 0x84      // OSD autofire command
#define MM1_OSDCMDCFGSCL   0xA0      // OSD settings: scanlines effect
#define MM1_OSDCMDCFGIDE   0xB0      // OSD enable HDD command
#define MM1_OSDCMDCFGFLP   0xC0      // OSD settings: floppy config
#define MM1_OSDCMDCFGCHP   0xD0      // OSD settings: chipset config
#define MM1_OSDCMDCFGFLT   0xE0      // OSD settings: filter
#define MM1_OSDCMDCFGMEM   0xF0      // OSD settings: memory config
#define MM1_OSDCMDCFGCPU   0xFC      // OSD settings: CPU config

// ---- new Minimig v2 constants -------
#define OSD_CMD_READ      0x00
#define OSD_CMD_RST       0x08
#define OSD_CMD_CLK       0x18
#define OSD_CMD_OSD       0x28		// OSD enable/disable command (high-res)
#define OSD_CMD_CHIP      0x04
#define OSD_CMD_CPU       0x14
#define OSD_CMD_MEM       0x24
#define OSD_CMD_VID       0x34
#define OSD_CMD_FLP       0x44
#define OSD_CMD_HDD       0x54
#define OSD_CMD_JOY       0x64
#define OSD_CMD_OSD_WR    0x0c
#define OSD_CMD_WR        0x1c
#define OSD_CMD_VERSION   0x88

#define DISABLE_KEYBOARD 0x02        // disable keyboard while OSD is active

#define REPEATDELAY      500         // repeat delay in 1ms units
#define REPEATRATE       50          // repeat rate in 1ms units
#define BUTTONDELAY      20          // repeat rate in 1ms units

#define CONFIG_TURBO     1
#define CONFIG_NTSC      2
#define CONFIG_A1000     4
#define CONFIG_ECS       8
#define CONFIG_AGA      16

#define CONFIG_FLOPPY1X  0
#define CONFIG_FLOPPY2X  1

#define OSD_ARROW_LEFT 1
#define OSD_ARROW_RIGHT 2

// OSD_CMD_OSD params
#define OSD_ENABLE		((uint8_t)0x01)
#define OSD_DISABLE		((uint8_t)0x00)

class OSD
{
public:
	// Low-res mode (32x8 symbols, 256x8 bytes)
	// High-res mode (32x16 symbols, 256x16 bytes)

	// Constants
	static const uint8_t OSD_HEIGHT_LINES = 8;
	static const uint8_t OSD_HEIGHT_PX = OSD_HEIGHT_LINES * 8;
	static const uint16_t OSD_TITLE_WIDTH_PX = OSD_HEIGHT_PX;
	static const uint8_t OSD_HIGHRES_HEIGHT_LINES = 16;
	static const uint16_t OSD_HIGHRES_HEIGHT_PX = OSD_HIGHRES_HEIGHT_LINES * 8;
	static const uint16_t OSD_HIGHRES_TITLE_WIDTH_PX = OSD_HIGHRES_HEIGHT_PX;
	static const uint16_t OSD_LINE_LENGTH_BYTES = 256;
	static const uint16_t OSD_LINE_LENGTH = OSD_LINE_LENGTH_BYTES / 8;

protected:
	// Fields
	uint8_t titlebuffer[2][OSD_HIGHRES_HEIGHT_LINES * 8]; // Horizontal buffer for initial title rendering. After rotation - 16 symbols height in highres and 8 in lowres
	uint8_t framebuffer[OSD_HIGHRES_HEIGHT_LINES][OSD_LINE_LENGTH_BYTES];

	bool arrowDirection;

	uint32_t scroll_offset = 0; // file/dir name scrolling position
	uint32_t scroll_timer = 0;  // file/dir name scrolling timer

public:
	static OSD& instance();
	OSD(OSD &that) = delete; // Copy constructor is forbidden here (C++11 feature)
	virtual ~OSD();

	// Show/hide logic methods
	void show();
	void showHighres();
	void hide();

	// Content methods
	void fill();
	void clear();
	void compose();
	void setTitle(const string& title, uint8_t arrows = 0);
	void printLine(uint8_t line, const string& text, bool invert = false);

	void printSymbol(uint8_t row, uint8_t column, char symbol, bool invert = false);
	bool getPixel(const int x, const int y);
	void setPixel(const int x, const int y, bool invert = false);

	// Rectangular region operations
	void fillRect(uint8_t left, uint8_t top, uint8_t width, uint8_t height, bool clear = false);
	void invertRect(uint8_t left, uint8_t top, uint8_t width, uint8_t height);

	void fillRectOptimized(uint8_t left, uint8_t top, uint8_t width, uint8_t height, bool clear = false);
	void invertRectOptimized(uint8_t left, uint8_t top, uint8_t width, uint8_t height);

protected:
	// Helper methods
	void clearFramebuffer();
	void rotateCharacter(uint8_t *in, uint8_t *out);
	uint8_t scale4Bits(uint8_t byte);
	uint16_t scale8Bits(uint8_t byte);
	void transferFramebuffer();

private:
	OSD() {}; // Prevent creation. Only singleton via instance() should be accessible
};

#endif /* GUI_OSD_OSD_H_ */
