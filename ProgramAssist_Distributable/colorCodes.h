#pragma once

#define COLOR_FG_Black 30  
#define COLOR_BG_Black 40
#define COLOR_FG_Red 31  
#define COLOR_BG_Red 41
#define COLOR_FG_Green 32  
#define COLOR_BG_Green 42
#define COLOR_FG_Yellow 33  
#define COLOR_BG_Yellow 43
#define COLOR_FG_Blue 34  
#define COLOR_BG_Blue 44
#define COLOR_FG_Magenta 35  
#define COLOR_BG_Magenta 45
#define COLOR_FG_Cyan 36  
#define COLOR_BG_Cyan 46
#define COLOR_FG_White 37  
#define COLOR_BG_White 47
#define COLOR_FG_BrightBlack 90  
#define COLOR_BG_BrightBlack 100
#define COLOR_FG_BrightRed 91  
#define COLOR_BG_BrightRed 101
#define COLOR_FG_BrightGreen 92  
#define COLOR_BG_BrightGreen 102
#define COLOR_FG_BrightYellow 93  
#define COLOR_BG_BrightYellow 103
#define COLOR_FG_BrightBlue 94  
#define COLOR_BG_BrightBlue 104
#define COLOR_FG_BrightMagenta 95  
#define COLOR_BG_BrightMagenta 105
#define COLOR_FG_BrightCyan 96  
#define COLOR_BG_BrightCyan 106
#define COLOR_FG_BrightWhite 97  
#define COLOR_BG_BrightWhite 107

#define SET_COLOR(FG_COLOR,BG_COLOR,STYLE) std::cout << "\033[" << FG_COLOR << ";" << BG_COLOR << ";" << STYLE << "m";		
#define RESET_COLOR std::cout << "\033[0m";

#define FATAL_ERROR(E) { std::cout <<"\033[0m \033[31;40;1m\n###### FATAL ERROR : " << E << " ######\033[0m"; std::cin.get(); exit(0);}
#define ERROR(E) std::cout << "\n#### ERROR : " << E << " ####\n";
#ifdef _DEBUG
#define LOG(E) {std::cout <<"\033[0m \033[34;107;1m\n LOG : " << E << " \033[0m"; } 
#endif
#ifndef _DEBUG
#define LOG(E) 
#endif