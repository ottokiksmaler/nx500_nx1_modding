/*
 * 
 * Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)
 * Copyright (C) 2016  Otto Kiksmaler
 * uses /proc walk sample code provided by Arjun Pakrashi
 *       https://phoxis.org/author/phoxis/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 * 
 */

#ifndef _CEXEMEMPATCH_H
#define _CEXEMEMPATCH_H 1

// ====================================================================================================================
// ====================================================================================================================
// === class CExeMemPatch =============================================================================================
// ====================================================================================================================
// ====================================================================================================================

class CExeMemPatch {
	pid_t pid;
	int fd;
	int pidAttach ();
	int pidDetach ();
	bool check_if_number (const char *str);
	pid_t getPidFromProcessName (const char *sProcessName);
public:
	off_t getModuleOffset (const char *sTargetModule);
	CExeMemPatch (const char *sProcessName);
	~CExeMemPatch ();
	bool peek (const char *sTargetModule, off_t offset, char *buffer, size_t size);
	bool poke (const char *sTargetModule, off_t offset, const char *buffer, size_t size);
	bool pokeIf (const char *sTargetModule, off_t offset, const char *buffer_original, 
							char *buffer, size_t size);
	bool peekUint (const char *sTargetModule, off_t offset, unsigned int *val);
	bool pokeUint (const char *sTargetModule, off_t offset, unsigned int val);
	bool pokeIfUint (const char *sTargetModule, off_t offset, unsigned int prevVal, unsigned int newVal);
};

#endif /* _CEXEMEMPATCH_H */
