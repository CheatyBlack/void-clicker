#include "../main.h"
#include "modules.h"

std::string getbindtext(size_t hex);
std::string getrbindtext(size_t hex);
std::string getrodbindtext(size_t hex);

void modules::bind::thread() {
    size_t selected_bind = 0;
    bool bind_break = false;

	while (!iso::auth::auth) {
		Sleep(1);

		if (modules::clicker::bind_pressed) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			selected_bind = 1;
			modules::clicker::sel_bind = 0;
			bool zoop = false; size_t bool_counter = 0;
			while (modules::clicker::sel_bind == 0) {
				if (bool_counter < 1) { zoop = true; }
				else { zoop = false; }
				std::this_thread::sleep_for(std::chrono::milliseconds(2));
				for (size_t i = 3; i < 256; i++) {
					if (i != 13) {
						if (GetAsyncKeyState((i)&SHRT_MAX) && modules::clicker::sel_bind == 0) {
							if (!zoop) {
								modules::clicker::sel_bind = i;
								modules::clicker::bind = getbindtext(i);
								if (i == 27) {
									modules::clicker::bind = "[click to bind]";
									selected_bind = 1;
									modules::clicker::sel_bind = 0;
									bind_break = true;
								}
								std::this_thread::sleep_for(std::chrono::milliseconds(250));
							}
						}
					}
				}
				if (bind_break) { bind_break = false; break; }
				selected_bind = 0;
				modules::clicker::bind_pressed = false;
				bool_counter++;
			}
		}
		if(modules::clicker::toggled){
            if (GetAsyncKeyState(modules::clicker::sel_bind) & 0x8000) {
                if (!modules::clicker::enabled) {
                    while (GetAsyncKeyState(modules::clicker::sel_bind) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }modules::clicker::enabled = true;
                }
                else {
                    while (GetAsyncKeyState(modules::clicker::sel_bind) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }modules::clicker::enabled = false;
                }
            }
		}
		else{
            if (GetAsyncKeyState(modules::clicker::sel_bind) & 0x8000){
                int ldelay = 500 / modules::clicker::cps;
                POINT clickerpos;
                GetCursorPos(&clickerpos);
                HWND window = WindowFromPoint(clickerpos);
                if (modules::clicker::mconly) {
                    if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
                        if (ScreenToClient(window, &clickerpos)) {
                            if (clickerpos.y > 20) {

                                SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(clickerpos.x, clickerpos.y));
                                Sleep(ldelay);
                                SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(clickerpos.x, clickerpos.y));
                                Sleep(ldelay);
                            }
                        }
                    }

                } else {
                    if (ScreenToClient(window, &clickerpos)) {
                        if (clickerpos.y > 20) {
                            SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(clickerpos.x, clickerpos.y));
                            Sleep(ldelay);
                            SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(clickerpos.x, clickerpos.y));
                            Sleep(ldelay);
                        }
                    }
                }
            }
		}

	}
}
void modules::rbind::rthread() {
    size_t selected_bind = 0;
    bool rbind_break = false;

    while (!iso::auth::auth) {
        Sleep(1);

        if (modules::rclicker::rbind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            modules::rclicker::rsel_bind = 0;
            bool zoop = false; size_t bool_counter = 0;
            while (modules::rclicker::rsel_bind == 0) {
                if (bool_counter < 1) { zoop = true; }
                else { zoop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && modules::rclicker::rsel_bind == 0) {
                            if (!zoop) {
                                modules::rclicker::rsel_bind = i;
                                modules::rclicker::rbind = getrbindtext(i);
                                if (i == 27) {
                                    modules::rclicker::rbind = "[click to bind]";
                                    selected_bind = 1;
                                    modules::rclicker::rsel_bind = 0;
                                    rbind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (rbind_break) { rbind_break = false; break; }
                selected_bind = 0;
                modules::rclicker::rbind_pressed = false;
                bool_counter++;
            }
        }

        if(modules::rclicker::toggled){
            if (GetAsyncKeyState(modules::rclicker::rsel_bind) & 0x8000) {
                if (!modules::rclicker::renabled) {
                    while (GetAsyncKeyState(modules::rclicker::rsel_bind) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }modules::rclicker::renabled = true;
                }
                else {
                    while (GetAsyncKeyState(modules::rclicker::rsel_bind) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }modules::rclicker::renabled = false;
                }
            }
        }
        else{
            if (GetAsyncKeyState(modules::rclicker::rsel_bind) & 0x8000) {
                POINT rclickerpos;
                GetCursorPos(&rclickerpos);
                HWND window = WindowFromPoint(rclickerpos);
                int delay = 500 / modules::rclicker::rcps;
                if (modules::rclicker::rmconly) {
                    if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
                        if (ScreenToClient(window, &rclickerpos)) {
                            if (rclickerpos.y > 20) {
                                SendMessage(window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                                Sleep(delay);
                                SendMessage(window, WM_RBUTTONUP, 0, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                                Sleep(delay);
                            }
                        }
                    }
                }
                else {
                    if (ScreenToClient(window, &rclickerpos)) {
                        if (rclickerpos.y > 20) {
                            SendMessage(window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                            Sleep(delay);
                            SendMessage(window, WM_RBUTTONUP, 0, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                            Sleep(delay);
                        }
                    }
                }
            }
        }


    }
}
void modules::rodbind::rodthread() {
    size_t selected_bind = 0;
    bool bind_break = false;

    while (!iso::auth::auth) {
        Sleep(1);

        if (modules::autorod::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            modules::autorod::sel_bind = 0;
            bool zoop = false; size_t bool_counter = 0;
            while (modules::autorod::sel_bind == 0) {
                if (bool_counter < 1) { zoop = true; }
                else { zoop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && modules::autorod::sel_bind == 0) {
                            if (!zoop) {
                                modules::autorod::sel_bind = i;
                                modules::autorod::bind = getrodbindtext(i);
                                if (i == 27) {
                                    modules::autorod::bind = "[click to bind]";
                                    selected_bind = 1;
                                    modules::autorod::sel_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                modules::autorod::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(modules::autorod::sel_bind) & 0x8000) {
            if (!modules::autorod::enabled) {
                while (GetAsyncKeyState(modules::autorod::sel_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
            }
            else {
                while (GetAsyncKeyState(modules::autorod::sel_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }modules::autorod::state += 1;
            }
        }
    }
}

std::string getrodbindtext(size_t hex) {
    const char* const keystring[] = {
            "Unknown",
            "LButton",
            "RButton",
            "CANCEL",
            "MButton",
            "MButton2",
            "MButton3",
            "Unknown",
            "Back",
            "Tab",
            "Unknown",
            "Unknown",
            "Clear",
            "Return",
            "Unknown",
            "Unknown",
            "Shift",
            "Control",
            "Menu",
            "Pause",
            "Capital",
            "Unknown",
            "Unknown",
            "Unknown",
            "Final",
            "Unknown",
            "Unknown",
            "Escape",
            "Convert",
            "NonConvert",
            "Accept",
            "ModeChange",
            "Space",
            "Prior",
            "Next",
            "End",
            "Home",
            "Left",
            "Up",
            "Right",
            "Down",
            "Select",
            "Print",
            "Execute",
            "SnpShot",
            "Insert",
            "Delete",
            "Help",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            "Lwin",
            "Rwin",
            "Apps",
            "Unknown",
            "Sleep",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "*",
            "+",
            "Separator",
            "-",
            "Decimal",
            "/",
            "F1",
            "F2",
            "F3",
            "F4",
            "F5",
            "F6",
            "F7",
            "F8",
            "F9",
            "F10",
            "F11",
            "F12",
            "F13",
            "F14",
            "F15",
            "F16",
            "F17",
            "F18",
            "F19",
            "F20",
            "F21",
            "F22",
            "F23",
            "F24",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Numlock",
            "Scroll",
            "Equal",
            "Masshou",
            "Touroku",
            "Loya",
            "Roya",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "LShift",
            "RShift",
            "Control",
            "Control",
            "Menu",
            "RMenu",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
    };
    return "[binded to: " + std::string(keystring[hex]) + "]";
}
std::string getbindtext(size_t hex) {
	const char* const keystring[] = {
		"Unknown",
		"LButton",
		"RButton",
		"CANCEL",
		"MButton",
		"MButton2",
		"MButton3",
		"Unknown",
		"Back",
		"Tab",
		"Unknown",
		"Unknown",
		"Clear",
		"Return",
		"Unknown",
		"Unknown",
		"Shift",
		"Control",
		"Menu",
		"Pause",
		"Capital",
		"Unknown",
		"Unknown",
		"Unknown",
		"Final",
		"Unknown",
		"Unknown",
		"Escape",
		"Convert",
		"NonConvert",
		"Accept",
		"ModeChange",
		"Space",
		"Prior",
		"Next",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"Select",
		"Print",
		"Execute",
		"SnpShot",
		"Insert",
		"Delete",
		"Help",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Lwin",
		"Rwin",
		"Apps",
		"Unknown",
		"Sleep",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"*",
		"+",
		"Separator",
		"-",
		"Decimal",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Numlock",
		"Scroll",
		"Equal",
		"Masshou",
		"Touroku",
		"Loya",
		"Roya",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"LShift",
		"RShift",
		"Control",
		"Control",
		"Menu",
		"RMenu",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
	};
	return "[binded to: " + std::string(keystring[hex]) + "]";
}
std::string getrbindtext(size_t hex) {
    const char* const keystring[] = {
            "Unknown",
            "LButton",
            "RButton",
            "CANCEL",
            "MButton",
            "MButton2",
            "MButton3",
            "Unknown",
            "Back",
            "Tab",
            "Unknown",
            "Unknown",
            "Clear",
            "Return",
            "Unknown",
            "Unknown",
            "Shift",
            "Control",
            "Menu",
            "Pause",
            "Capital",
            "Unknown",
            "Unknown",
            "Unknown",
            "Final",
            "Unknown",
            "Unknown",
            "Escape",
            "Convert",
            "NonConvert",
            "Accept",
            "ModeChange",
            "Space",
            "Prior",
            "Next",
            "End",
            "Home",
            "Left",
            "Up",
            "Right",
            "Down",
            "Select",
            "Print",
            "Execute",
            "SnpShot",
            "Insert",
            "Delete",
            "Help",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            "Lwin",
            "Rwin",
            "Apps",
            "Unknown",
            "Sleep",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "*",
            "+",
            "Separator",
            "-",
            "Decimal",
            "/",
            "F1",
            "F2",
            "F3",
            "F4",
            "F5",
            "F6",
            "F7",
            "F8",
            "F9",
            "F10",
            "F11",
            "F12",
            "F13",
            "F14",
            "F15",
            "F16",
            "F17",
            "F18",
            "F19",
            "F20",
            "F21",
            "F22",
            "F23",
            "F24",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Numlock",
            "Scroll",
            "Equal",
            "Masshou",
            "Touroku",
            "Loya",
            "Roya",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "LShift",
            "RShift",
            "Control",
            "Control",
            "Menu",
            "RMenu",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
            "Unknown",
    };
    return "[binded to: " + std::string(keystring[hex]) + "]";
}