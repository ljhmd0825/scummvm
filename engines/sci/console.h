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

#ifndef SCI_CONSOLE_H
#define SCI_CONSOLE_H

#include "gui/debugger.h"
#include "sci/engine/vm.h"

namespace Sci {

class SciEngine;
struct List;

reg_t disassemble(EngineState *s, reg_t pos, const Object *obj, bool printBWTag, bool printBytecode, bool printCSyntax);
bool isJumpOpcode(EngineState *s, reg_t pos, reg_t& jumpOffset);

class Console : public GUI::Debugger {
public:
	Console(SciEngine *engine);
	~Console() override;

	/**
	 * 'Attach' the debugger. This ensures that the next time onFrame()
	 * is invoked, the debugger will activate and accept user input.
	 */
	void attach(const char *entry = nullptr) override;

private:
	void preEnter() override;
	void postEnter() override;

	// General
	bool cmdHelp(int argc, const char **argv);
	// Kernel
	bool cmdOpcodes(int argc, const char **argv);
	bool cmdSelector(int argc, const char **argv);
	bool cmdSelectors(int argc, const char **argv);
	bool cmdKernelFunctions(int argc, const char **argv);
	bool cmdKernelCall(int argc, const char **argv);
	bool cmdClassTable(int argc, const char **argv);
	// Parser
	bool cmdSuffixes(int argc, const char **argv);
	bool cmdParseGrammar(int argc, const char **argv);
	bool cmdParserNodes(int argc, const char **argv);
	bool cmdParserWords(int argc, const char **argv);
	bool cmdSentenceFragments(int argc, const char **argv);
	bool cmdParse(int argc, const char **argv);
	bool cmdSetParseNodes(int argc, const char **argv);
	bool cmdSaid(int argc, const char **argv);
	// Resources
	bool cmdDiskDump(int argc, const char **argv);
	void cmdDiskDumpWorker(ResourceType resourceType, int resourceNumber, uint32 resourceTuple);
	bool cmdHexDump(int argc, const char **argv);
	bool cmdResourceId(int argc, const char **argv);
	bool cmdResourceInfo(int argc, const char **argv);
	bool cmdResourceTypes(int argc, const char **argv);
	bool cmdList(int argc, const char **argv);
	bool cmdResourceIntegrityDump(int argc, const char **argv);
	bool cmdAllocList(int argc, const char **argv);
	bool cmdHexgrep(int argc, const char **argv);
	bool cmdVerifyScripts(int argc, const char **argv);
	// Game
	bool cmdSaveGame(int argc, const char **argv);
	bool cmdRestoreGame(int argc, const char **argv);
	bool cmdRestartGame(int argc, const char **argv);
	bool cmdGetVersion(int argc, const char **argv);
	bool cmdRoomNumber(int argc, const char **argv);
	bool cmdQuit(int argc, const char **argv);
	bool cmdListSaves(int argc, const char **argv);
	// Screen
	bool cmdShowMap(int argc, const char **argv);
	// Graphics
	bool cmdSetPalette(int argc, const char **argv);
	bool cmdDrawPic(int argc, const char **argv);
	bool cmdDrawCel(int argc, const char **argv);
	bool cmdUndither(int argc, const char **argv);
	bool cmdPicVisualize(int argc, const char **argv);
	bool cmdPlayVideo(int argc, const char **argv);
	bool cmdAnimateList(int argc, const char **argv);
	bool cmdWindowList(int argc, const char **argv);
	bool cmdPlaneList(int argc, const char **argv);
	bool cmdVisiblePlaneList(int argc, const char **argv);
	bool cmdPlaneItemList(int argc, const char **argv);
	bool cmdVisiblePlaneItemList(int argc, const char **argv);
	bool cmdSavedBits(int argc, const char **argv);
	bool cmdShowSavedBits(int argc, const char **argv);
	// Segments
	bool cmdPrintSegmentTable(int argc, const char **argv);
	bool cmdSegmentInfo(int argc, const char **argv);
	bool cmdKillSegment(int argc, const char **argv);
	// Garbage collection
	bool cmdGCInvoke(int argc, const char **argv);
	bool cmdGCObjects(int argc, const char **argv);
	bool cmdGCShowReachable(int argc, const char **argv);
	bool cmdGCShowFreeable(int argc, const char **argv);
	bool cmdGCNormalize(int argc, const char **argv);
	// Music/SFX
	bool cmdSongLib(int argc, const char **argv);
	bool cmdSongInfo(int argc, const char **argv);
	bool cmdIsSample(int argc, const char **argv);
	bool cmdStartSound(int argc, const char **argv);
	bool cmdToggleSound(int argc, const char **argv);
	bool cmdStopAllSounds(int argc, const char **argv);
	bool cmdSfx01Header(int argc, const char **argv);
	bool cmdSfx01Track(int argc, const char **argv);
	bool cmdShowInstruments(int argc, const char **argv);
	bool cmdMapInstrument(int argc, const char **argv);
	bool cmdAudioList(int argc, const char **argv);
	bool cmdAudioDump(int argc, const char **argv);
	// Script
	bool cmdAddresses(int argc, const char **argv);
	bool cmdRegisters(int argc, const char **argv);
	bool cmdDissectScript(int argc, const char **argv);
	bool cmdBacktrace(int argc, const char **argv);
	bool cmdTrace(int argc, const char **argv);
	bool cmdStepOver(int argc, const char **argv);
	bool cmdStepEvent(int argc, const char **argv);
	bool cmdStepRet(int argc, const char **argv);
	bool cmdStepGlobal(int argc, const char **argv);
	bool cmdStepCallk(int argc, const char **argv);
	bool cmdDisassemble(int argc, const char **argv);
	bool cmdDisassembleAddress(int argc, const char **argv);
	bool cmdFindKernelFunctionCall(int argc, const char **argv);
	bool cmdSend(int argc, const char **argv);
	bool cmdGo(int argc, const char **argv);
	bool cmdLogKernel(int argc, const char **argv);
	bool cmdMapVocab994(int argc, const char **argv);
	bool cmdGameFlagsInit(int argc, const char **argv);
	bool cmdGameFlagsTest(int argc, const char **argv);
	bool cmdGameFlagsSet(int argc, const char **argv);
	bool cmdGameFlagsClear(int argc, const char **argv);
	// Breakpoints
	bool cmdBreakpointList(int argc, const char **argv);
	bool cmdBreakpointDelete(int argc, const char **argv);
	bool cmdBreakpointAction(int argc, const char **argv);
	bool cmdBreakpointMethod(int argc, const char **argv);
	bool cmdBreakpointRead(int argc, const char **argv);
	bool cmdBreakpointWrite(int argc, const char **argv);
	bool cmdBreakpointKernel(int argc, const char **argv);
	bool cmdBreakpointFunction(int argc, const char **argv);
	bool cmdBreakpointAddress(int argc, const char **argv);
	// VM
	bool cmdScriptSteps(int argc, const char **argv);
	bool cmdScriptObjects(int argc, const char **argv);
	bool cmdScriptStrings(int argc, const char **argv);
	bool cmdScriptSaid(int argc, const char **argv);
	bool cmdVMVarlist(int argc, const char **argv);
	bool cmdVMVars(int argc, const char **argv);
	bool cmdLocalVars(int argc, const char **argv);
	bool cmdStack(int argc, const char **argv);
	bool cmdValueType(int argc, const char **argv);
	bool cmdViewListNode(int argc, const char **argv);
	bool cmdViewReference(int argc, const char **argv);
	bool cmdDumpReference(int argc, const char **argv);
	bool cmdViewObject(int argc, const char **argv);
	bool cmdViewActiveObject(int argc, const char **argv);
	bool cmdViewAccumulatorObject(int argc, const char **argv);
	// Variables
	bool cmdSpeedThrottle(int argc, const char **argv);

	bool parseInteger(const char *argument, int &result);
	bool parseResourceNumber36(const char *userParameter, uint16 &resourceNumber, uint32 &resourceTuple);

	void printBasicVarInfo(reg_t variable);

	bool segmentInfo(int nr);
	void printList(reg_t addr);
	void printList(const List &list);
	int printNode(reg_t addr);
	void hexDumpReg(const reg_t *data, int len, int regsPerLine = 4, int startOffset = 0, bool isArray = false);
	void printOffsets(int scriptNr, uint16 showType);

private:
	/**
	 * Prints all the scripts calling the specified kernel function.
	 * NOTE: The results produced by this aren't 100% correct, as it
	 * does not dissect script exports
	 */
	void printKernelCallsFound(int kernelFuncNum, bool showFoundScripts);

	void printBreakpoint(int index, const Breakpoint &bp);
	void printReference(reg_t reg, reg_t reg_end = NULL_REG);
#ifdef ENABLE_SCI32
	void printArray(reg_t reg);
	void printBitmap(reg_t reg);
#endif

	void writeIntegrityDumpLine(const Common::String &statusName, const Common::String &resourceName, Common::WriteStream &out, Common::ReadStream *const data, const int size, const bool writeHash);
	
	enum GameFlagsOperation {
		kGameFlagsTest,
		kGameFlagsSet,
		kGameFlagsClear
	};
	bool processGameFlagsOperation(GameFlagsOperation operation, int argc, const char **argv);

	SciEngine *_engine;
	DebugState &_debugState;
	Common::String _videoFile;
	int _videoFrameDelay;
	uint16 _gameFlagsGlobal;
};

} // End of namespace Sci

#endif
