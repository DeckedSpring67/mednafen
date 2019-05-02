#ifndef __MDFN_DRIVERS_HELP_H
#define __MDFN_DRIVERS_HELP_H

void Help_Draw(MDFN_Surface* surface, const MDFN_Rect& rect);
bool Help_IsActive(void);
bool Help_Toggle(void);
void Help_Init(void) MDFN_COLD;
void Help_Close(void) MDFN_COLD;
void Change_speed(double);

#endif
