#include "stdafx.h"

#include "CConfigurationCheck.h"
#include "CPreferences.h"


CConfigurationCheck *p_cconfigurationcheck = 0;

// A full list of keyboard layout codes can be found here:
// http://msdn.microsoft.com/en-us/goglobal/bb895996.aspx
const TCHAR k_KeyboardLayout_UK_US_English[KL_NAMELENGTH] = "00000409";


CConfigurationCheck::CConfigurationCheck()
{
	CheckEverything();
}

CConfigurationCheck::~CConfigurationCheck()
{}

void CConfigurationCheck::CheckEverything()
{
	// Check really critical settings in any case.
	// OpenHoldem will never work, if these are not right.
	CheckColourDepth();
	CheckFontSmoothing();

	// Check non-critical things, if checks are not disabled.
	// OpenHoldem may or may not work, if these are not right.
	// ToDo: Preferences!!!
	if (!prefs.configurationcheck_disable_less_critical_checks())
	{
		CheckKeyboardSettings();
		CheckMicrosoftVisualCppRuntimeLibrary();
	}
}

void CConfigurationCheck::CheckKeyboardSettings()
{
	TCHAR KeyboardLayout[KL_NAMELENGTH];
	bool Success = GetKeyboardLayoutName((LPSTR)&KeyboardLayout);
	MessageBox(0, KeyboardLayout, "Layout", 0);

	if (Success && (_tcscmp(KeyboardLayout, k_KeyboardLayout_UK_US_English) != 0))
	{
		MessageBox(0, "You seem to have non-english keyboard settings.\n"
				"Keyboard settings affect especially the decimal point in numbers\n"
				"and therefore the scraper-engine and the auto-player.\n"
				"If you continue, OpenHoldem may or may not work as expected.\n",
				"Caution: Improper keyboard settings", MB_OK|MB_ICONWARNING);
	}
}

void CConfigurationCheck::CheckColourDepth()
{
	CWindowDC dc(NULL);
	int nBitsPerPixel = dc.GetDeviceCaps(PLANES) * dc.GetDeviceCaps(BITSPIXEL);
	if (nBitsPerPixel < 24 && !prefs.disable_msgbox())
		MessageBox(0, "It appears that your Display settings are not configured according to OpenHoldem specifications.\n"
				   "24 bit color or higher is needed to reliably extract information from the poker client\n\n"
				   "For more info, look at the wiki documentation and the user forums", 
				   "Caution: Color Depth Too Low", MB_OK|MB_ICONWARNING);
}

void CConfigurationCheck::CheckFontSmoothing()
{
	BOOL fontSmoothingEnabled = FALSE;
	SystemParametersInfo(SPI_GETFONTSMOOTHING, 0, (LPVOID)&fontSmoothingEnabled, 0);
	if (fontSmoothingEnabled && !prefs.disable_msgbox())
		MessageBox(0, "It appears that font smoothing is enabled. In order for OpenHoldem to reliably\n"
				   "extract information from the poker client you should disable Font Smoothing", 
				   "Caution: Font smoothing is enabled", MB_OK|MB_ICONWARNING);
}

void CConfigurationCheck::CheckMicrosoftVisualCppRuntimeLibrary()
{
	HMODULE hMSVCRT = LoadLibrary("MSVCRT80.dll");
	if (hMSVCRT != NULL)
	{
		FreeLibrary(hMSVCRT);
	}
	else
	{
		MessageBox(0, "MSVRT 8.0 (2005) could not be found.\n"
				"That DLL is required by Perl_callback.dll.\n"
				"If you don't use Perl, you can ignore that message.\n"
				"Otherwise please install the correct runtime libraries.\n",
				"Caution: MSVCRT 8.0 not found", MB_OK|MB_ICONWARNING);
	}
}