#ifndef GUI_MENU_MENU_H_
#define GUI_MENU_MENU_H_

#include <stdint.h>
#include "../../common/file/directorymanager.h"
#include "../../common/file/filemanager.h"

/*
 * All menu states as enum
 */
enum MENU
{
	MENU_NONE1,
	MENU_NONE2,
	MENU_MAIN1,
	MENU_MAIN2,
	MENU_FILE_SELECT1,
	MENU_FILE_SELECT2,
	MENU_FILE_SELECTED,
	MENU_RESET1,
	MENU_RESET2,
	MENU_RECONF1,
	MENU_RECONF2,
	MENU_SETTINGS1,
	MENU_SETTINGS2,
	MENU_ROMFILE_SELECTED,
	MENU_ROMFILE_SELECTED1,
	MENU_ROMFILE_SELECTED2,
	MENU_SETTINGS_VIDEO1,
	MENU_SETTINGS_VIDEO2,
	MENU_SETTINGS_MEMORY1,
	MENU_SETTINGS_MEMORY2,
	MENU_SETTINGS_CHIPSET1,
	MENU_SETTINGS_CHIPSET2,
	MENU_SETTINGS_DRIVES1,
	MENU_SETTINGS_DRIVES2,
	MENU_SETTINGS_HARDFILE1,
	MENU_SETTINGS_HARDFILE2,
	MENU_HARDFILE_SELECT1,
	MENU_HARDFILE_SELECT2,
	MENU_HARDFILE_SELECTED,
	MENU_HARDFILE_EXIT,
	MENU_HARDFILE_CHANGED1,
	MENU_HARDFILE_CHANGED2,
	MENU_SYNTHRDB1,
	MENU_SYNTHRDB2,
	MENU_SYNTHRDB2_1,
	MENU_SYNTHRDB2_2,
	MENU_LOADCONFIG_1,
	MENU_LOADCONFIG_2,
	MENU_SAVECONFIG_1,
	MENU_SAVECONFIG_2,
	MENU_FIRMWARE1,
	MENU_FIRMWARE2,
	MENU_FIRMWARE_CORE_FILE_SELECTED,
	MENU_ERROR,
	MENU_INFO,
	MENU_STORAGE,
	MENU_JOYDIGMAP,
	MENU_JOYDIGMAP1,
	MENU_KBDMAP,
	MENU_KBDMAP1,

	// Mist/atari specific pages
	MENU_MIST_MAIN1,
	MENU_MIST_MAIN2,
	MENU_MIST_MAIN_FILE_SELECTED,
	MENU_MIST_STORAGE1,
	MENU_MIST_STORAGE2,
	MENU_MIST_STORAGE_FILE_SELECTED,
	MENU_MIST_SYSTEM1,
	MENU_MIST_SYSTEM2,
	MENU_MIST_SYSTEM_FILE_SELECTED,
	MENU_MIST_VIDEO1,
	MENU_MIST_VIDEO2,
	MENU_MIST_VIDEO_ADJUST1,
	MENU_MIST_VIDEO_ADJUST2,

	// archimedes menu entries
	MENU_ARCHIE_MAIN1,
	MENU_ARCHIE_MAIN2,
	MENU_ARCHIE_MAIN_FILE_SELECTED,

	// 8bit menu entries
	MENU_8BIT_MAIN1,
	MENU_8BIT_MAIN2,
	MENU_8BIT_MAIN_FILE_SELECTED,
	MENU_8BIT_MAIN_IMAGE_SELECTED,
	MENU_8BIT_SYSTEM1,
	MENU_8BIT_SYSTEM2,
	MENU_8BIT_ABOUT1,
	MENU_8BIT_ABOUT2
};

enum HelpText_Message
{
	HELPTEXT_NONE,
	HELPTEXT_MAIN,
	HELPTEXT_HARDFILE,
	HELPTEXT_CHIPSET,
	HELPTEXT_MEMORY,
	HELPTEXT_VIDEO
};

class menu
{
protected:
	// Constants
	static const char* config_tos_mem[];
	static const char *config_tos_wrprot[];
	static const char *config_tos_usb[];

	static const char *config_memory_chip_msg[];
	static const char *config_memory_slow_msg[];
	static const char *config_memory_fast_msg[];

	static const char *config_filter_msg[];
	static const char *config_scanlines_msg[];
	static const char *config_ar_msg[];
	static const char *config_blank_msg[];
	static const char *config_dither_msg[];
	static const char *config_cpu_msg[];
	static const char *config_hdf_msg[];
	static const char *config_chipset_msg[];
	static const char *config_turbo_msg[];
	static const char *config_autofire_msg[];
	static const char *config_cd32pad_msg[];
	static const char *config_button_turbo_msg[];
	static const char *config_button_turbo_choice_msg[];
	static const char *joy_button_map[];

	static const char *helptexts[];

	// Fields
	uint8_t menustate = MENU_NONE1;
	uint8_t parentstate;
	uint8_t menusub = 0;
	uint8_t menusub_last = 0; //for when we allocate it dynamically and need to know last row
	uint32_t menumask = 0; // Used to determine which rows are selectable...
	uint32_t menu_timer = 0;
	const char *helptext;

	char fileExtension[13] = "xxx";
	int fileExtensionLen;

	// State fields
	string currentFolder;
	int currentMenuItemOffset = 0;

public:
	menu();
	virtual ~menu();

	void handleUI();

	bool selectFile(const char* extension);

protected:
	// Helper methods
	void menuNone1();
	void menuNone2();

	void menuArchieMain1();
	void menuArchieMain2();
	void menuArchieMainFileSelected();

	void menu8bitMain1();
	void menu8bitMain2();
	void menu8bitMainFileSelected();
	void menu8bitMainImageSelected();
	void menu8bitSystem1();
	void menu8bitSystem2();
	void menu8bitAbout1();
	void menu8bitAbout2();

	void menuMistMain1();
	void menuMistMain2();
	void menuMistMainFileSelected();
	void menuMistStorage1();
	void menuMistStorage2();
	void menuMistStorageFileSelected();
	void menuMistSystem1();
	void menuMistSystem2();
	void menuMistSystemFileSelected();
	void menuMistVideo1();
	void menuMistVideo2();
	void menuMistVideoAdjust1();
	void menuMistVideoAdjust2();

	void menuMain1();
	void menuMain2();
	void menuFileSelected();
	void menuLoadConfig1();
	void menuLoadConfig2();
	void menuFileSelect1();
	void menuFileSelect2();
	void menuReset1();
	void menuReset2();
	void menuSaveConfig1();
	void menuSaveConfig2();
	void menuSettingsChipset1();
	void menuSettingsChipset2();
	void menuSettingsMemory1();
	void menuSettingsMemory2();
	void menuSettingsHardfile1();
	void menuSettingsHardfile2();
	void menuHardfileSelected();
	void menuHardfileExit();
	void menuHardfileChanged1();
	void menuHardfileChanged2();
	void menuSynthRDB1();
	void menuSynthRDB2_1();
	void menuSynthRDB2();
	void menuSettingsVideo1();
	void menuSettingsVideo2();
	void menuRomfileSelected();
	void menuRomfileSelected1();
	void menuRomfileSelected2();
	void menuFirmware1();
	void menuFirmware2();
	void menuFirmwareCoreFileSelected();
	void menuStorage();

	void menuKbdmap();
	void menuKbdmap1();
	void menuJoydigmap();
	void menuJoydigmap1();
	void menuError();
	void menuInfo();

	void printFolder();
	bool changeCurrentFolder(const char *folderpath);
};

#endif /* GUI_MENU_MENU_H_ */
