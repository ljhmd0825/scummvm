/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ags/shared/ac/common.h"
#include "ags/engine/ac/display.h"
#include "ags/engine/ac/game_state.h"
#include "ags/shared/ac/game_struct_defines.h"
#include "ags/engine/ac/global_translation.h"
#include "ags/engine/ac/string.h"
#include "ags/engine/ac/translation.h"
#include "ags/engine/platform/base/ags_platform_driver.h"
#include "ags/plugins/ags_plugin.h"
#include "ags/plugins/plugin_engine.h"
#include "ags/shared/util/memory.h"
#include "ags/engine/ac/string.h"
#include "ags/globals.h"

namespace AGS3 {

using namespace AGS::Shared::Memory;

const char *get_translation(const char *text) {
	if (text == nullptr)
		quit("!Null string supplied to CheckForTranslations");

	_G(source_text_length) = GetTextDisplayLength(text);

#if AGS_PLATFORM_64BIT
	// check if a plugin wants to translate it - if so, return that
	// TODO: plugin API is currently strictly 32-bit, so this may break on 64-bit systems
	char *plResult = Int32ToPtr<char>(pl_run_plugin_hooks(AGSE_TRANSLATETEXT, PtrToInt32(text)));
	if (plResult) {
		return plResult;
	}
#endif

	const auto &transtree = get_translation_tree();
	const auto it = transtree.find(text);
	if (it != transtree.end())
		return it->_value.GetCStr();

	// return the original text
	return text;
}

int IsTranslationAvailable() {
	// Some games don't support foreign language packs.
	// If that's the case, make them think they don't have them.
	const char guid[][MAX_GUID_LENGTH] = {
		"{cf1b8753-2ad1-4d79-b5c7-f6aff4fdc729}",	/* King's Quest I v4.1c */
		"{b85ea0b0-35c5-4e53-bfc7-2281bf481001}", 	/* King's Quest II v3.1c */
		"{19454ab9-e6dd-4f20-a2ad-24da47d91a20}",	/* King's Quest III Redux v1.1 */
	};
	char *gameguid = get_gameguid();
	for (size_t i = 0; i < sizeof(guid) / MAX_GUID_LENGTH; i++) {
		if (strcmp(gameguid, guid[i]) == 0) {
			return 0;
		}
	}
	if (get_translation_tree().size() > 0)
		return 1;
	return 0;
}

int GetTranslationName(char *buffer) {
	VALIDATE_STRING(buffer);
	snprintf(buffer, MAX_MAXSTRLEN, "%s", get_translation_name().GetCStr());
	return IsTranslationAvailable();
}

} // namespace AGS3
