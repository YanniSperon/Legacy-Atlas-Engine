#include "InputHandler.h"
#include "Global.h"
#include "System.h"
#include <vector>

namespace Engine {

	static std::vector<int> keyButtons;
	static std::vector<int> keyActions;
	static std::vector<int> mouseButtons;
	static std::vector<int> mouseActions;

	void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keyButtons.push_back(key);
		keyActions.push_back(action);
	}

	void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		mouseButtons.push_back(button);
		mouseActions.push_back(action);
	}

	void InputHandler::ProcessEvents(KeyboardInput* keyIn, MouseInput* mouseIn)
	{
		if (keyButtons.size() == keyActions.size()) {
			for (unsigned int i = 0; i < keyButtons.size(); i++) {
				if (keyButtons[i] == GLFW_KEY_A) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->aPressed = true;
						keyIn->aHeld = false;
						keyIn->aReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->aPressed = false;
						keyIn->aHeld = false;
						keyIn->aReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_B) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->bPressed = true;
						keyIn->bHeld = false;
						keyIn->bReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->bPressed = false;
						keyIn->bHeld = false;
						keyIn->bReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_C) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->cPressed = true;
						keyIn->cHeld = false;
						keyIn->cReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->cPressed = false;
						keyIn->cHeld = false;
						keyIn->cReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_D) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->dPressed = true;
						keyIn->dHeld = false;
						keyIn->dReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->dPressed = false;
						keyIn->dHeld = false;
						keyIn->dReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_E) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->ePressed = true;
						keyIn->eHeld = false;
						keyIn->eReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->ePressed = false;
						keyIn->eHeld = false;
						keyIn->eReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_F) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->fPressed = true;
						keyIn->fHeld = false;
						keyIn->fReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->fPressed = false;
						keyIn->fHeld = false;
						keyIn->fReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_G) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->gPressed = true;
						keyIn->gHeld = false;
						keyIn->gReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->gPressed = false;
						keyIn->gHeld = false;
						keyIn->gReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_H) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->hPressed = true;
						keyIn->hHeld = false;
						keyIn->hReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->hPressed = false;
						keyIn->hHeld = false;
						keyIn->hReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_I) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->iPressed = true;
						keyIn->iHeld = false;
						keyIn->iReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->iPressed = false;
						keyIn->iHeld = false;
						keyIn->iReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_J) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->jPressed = true;
						keyIn->jHeld = false;
						keyIn->jReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->jPressed = false;
						keyIn->jHeld = false;
						keyIn->jReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_K) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->kPressed = true;
						keyIn->kHeld = false;
						keyIn->kReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->kPressed = false;
						keyIn->kHeld = false;
						keyIn->kReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_L) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->lPressed = true;
						keyIn->lHeld = false;
						keyIn->lReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->lPressed = false;
						keyIn->lHeld = false;
						keyIn->lReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_M) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->mPressed = true;
						keyIn->mHeld = false;
						keyIn->mReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->mPressed = false;
						keyIn->mHeld = false;
						keyIn->mReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_N) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->nPressed = true;
						keyIn->nHeld = false;
						keyIn->nReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->nPressed = false;
						keyIn->nHeld = false;
						keyIn->nReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_O) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->oPressed = true;
						keyIn->oHeld = false;
						keyIn->oReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->oPressed = false;
						keyIn->oHeld = false;
						keyIn->oReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_P) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->pPressed = true;
						keyIn->pHeld = false;
						keyIn->pReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->pPressed = false;
						keyIn->pHeld = false;
						keyIn->pReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_Q) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->qPressed = true;
						keyIn->qHeld = false;
						keyIn->qReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->qPressed = false;
						keyIn->qHeld = false;
						keyIn->qReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_R) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->rPressed = true;
						keyIn->rHeld = false;
						keyIn->rReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->rPressed = false;
						keyIn->rHeld = false;
						keyIn->rReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_S) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->sPressed = true;
						keyIn->sHeld = false;
						keyIn->sReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->sPressed = false;
						keyIn->sHeld = false;
						keyIn->sReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_T) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->tPressed = true;
						keyIn->tHeld = false;
						keyIn->tReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->tPressed = false;
						keyIn->tHeld = false;
						keyIn->tReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_U) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->uPressed = true;
						keyIn->uHeld = false;
						keyIn->uReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->uPressed = false;
						keyIn->uHeld = false;
						keyIn->uReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_V) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->vPressed = true;
						keyIn->vHeld = false;
						keyIn->vReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->vPressed = false;
						keyIn->vHeld = false;
						keyIn->vReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_W) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->wPressed = true;
						keyIn->wHeld = false;
						keyIn->wReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->wPressed = false;
						keyIn->wHeld = false;
						keyIn->wReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_X) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->xPressed = true;
						keyIn->xHeld = false;
						keyIn->xReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->xPressed = false;
						keyIn->xHeld = false;
						keyIn->xReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_Y) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->yPressed = true;
						keyIn->yHeld = false;
						keyIn->yReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->yPressed = false;
						keyIn->yHeld = false;
						keyIn->yReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_Z) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->zPressed = true;
						keyIn->zHeld = false;
						keyIn->zReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->zPressed = false;
						keyIn->zHeld = false;
						keyIn->zReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_LEFT_CONTROL) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->leftControlPressed = true;
						keyIn->leftControlHeld = false;
						keyIn->leftControlReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->leftControlPressed = false;
						keyIn->leftControlHeld = false;
						keyIn->leftControlReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_LEFT_SHIFT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->leftShiftPressed = true;
						keyIn->leftShiftHeld = false;
						keyIn->leftShiftReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->leftShiftPressed = false;
						keyIn->leftShiftHeld = false;
						keyIn->leftShiftReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_CAPS_LOCK) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->capsLockPressed = true;
						keyIn->capsLockHeld = false;
						keyIn->capsLockReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->capsLockPressed = false;
						keyIn->capsLockHeld = false;
						keyIn->capsLockReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_LEFT_ALT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->leftAltPressed = true;
						keyIn->leftAltHeld = false;
						keyIn->leftAltReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->leftAltPressed = false;
						keyIn->leftAltHeld = false;
						keyIn->leftAltReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_TAB) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->tabPressed = true;
						keyIn->tabHeld = false;
						keyIn->tabReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->tabPressed = false;
						keyIn->tabHeld = false;
						keyIn->tabReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_GRAVE_ACCENT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->tildePressed = true;
						keyIn->tildeHeld = false;
						keyIn->tildeReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->tildePressed = false;
						keyIn->tildeHeld = false;
						keyIn->tildeReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_0) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->zeroPressed = true;
						keyIn->zeroHeld = false;
						keyIn->zeroReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->zeroPressed = false;
						keyIn->zeroHeld = false;
						keyIn->zeroReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_1) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->onePressed = true;
						keyIn->oneHeld = false;
						keyIn->oneReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->onePressed = false;
						keyIn->oneHeld = false;
						keyIn->oneReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_2) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->twoPressed = true;
						keyIn->twoHeld = false;
						keyIn->twoReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->twoPressed = false;
						keyIn->twoHeld = false;
						keyIn->twoReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_3) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->threePressed = true;
						keyIn->threeHeld = false;
						keyIn->threeReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->threePressed = false;
						keyIn->threeHeld = false;
						keyIn->threeReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_4) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->fourPressed = true;
						keyIn->fourHeld = false;
						keyIn->fourReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->fourPressed = false;
						keyIn->fourHeld = false;
						keyIn->fourReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_5) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->fivePressed = true;
						keyIn->fiveHeld = false;
						keyIn->fiveReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->fivePressed = false;
						keyIn->fiveHeld = false;
						keyIn->fiveReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_6) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->sixPressed = true;
						keyIn->sixHeld = false;
						keyIn->sixReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->sixPressed = false;
						keyIn->sixHeld = false;
						keyIn->sixReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_7) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->sevenPressed = true;
						keyIn->sevenHeld = false;
						keyIn->sevenReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->sevenPressed = false;
						keyIn->sevenHeld = false;
						keyIn->sevenReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_8) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->eightPressed = true;
						keyIn->eightHeld = false;
						keyIn->eightReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->eightPressed = false;
						keyIn->eightHeld = false;
						keyIn->eightReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_9) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->ninePressed = true;
						keyIn->nineHeld = false;
						keyIn->nineReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->ninePressed = false;
						keyIn->nineHeld = false;
						keyIn->nineReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_MINUS) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->minusPressed = true;
						keyIn->minusHeld = false;
						keyIn->minusReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->minusPressed = false;
						keyIn->minusHeld = false;
						keyIn->minusReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_EQUAL) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->equalPressed = true;
						keyIn->equalHeld = false;
						keyIn->equalReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->equalPressed = false;
						keyIn->equalHeld = false;
						keyIn->equalReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_BACKSPACE) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->backspacePressed = true;
						keyIn->backspaceHeld = false;
						keyIn->backspaceReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->backspacePressed = false;
						keyIn->backspaceHeld = false;
						keyIn->backspaceReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_DELETE) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->deletePressed = true;
						keyIn->deleteHeld = false;
						keyIn->deleteReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->deletePressed = false;
						keyIn->deleteHeld = false;
						keyIn->deleteReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_LEFT_BRACKET) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->leftBracketPressed = true;
						keyIn->leftBracketHeld = false;
						keyIn->leftBracketReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->leftBracketPressed = false;
						keyIn->leftBracketHeld = false;
						keyIn->leftBracketReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_RIGHT_BRACKET) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->rightBracketPressed = true;
						keyIn->rightBracketHeld = false;
						keyIn->rightBracketReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->rightBracketPressed = false;
						keyIn->rightBracketHeld = false;
						keyIn->rightBracketReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_BACKSLASH) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->backslashPressed = true;
						keyIn->backslashHeld = false;
						keyIn->backslashReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->backslashPressed = false;
						keyIn->backslashHeld = false;
						keyIn->backslashReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_SLASH) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->frontslashPressed = true;
						keyIn->frontslashHeld = false;
						keyIn->frontslashReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->frontslashPressed = false;
						keyIn->frontslashHeld = false;
						keyIn->frontslashReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_COMMA) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->commaPressed = true;
						keyIn->commaHeld = false;
						keyIn->commaReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->commaPressed = false;
						keyIn->commaHeld = false;
						keyIn->commaReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_PERIOD) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->periodPressed = true;
						keyIn->periodHeld = false;
						keyIn->periodReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->periodPressed = false;
						keyIn->periodHeld = false;
						keyIn->periodReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_SEMICOLON) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->semiColonPressed = true;
						keyIn->semiColonHeld = false;
						keyIn->semiColonReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->semiColonPressed = false;
						keyIn->semiColonHeld = false;
						keyIn->semiColonReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_APOSTROPHE) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->apostrophePressed = true;
						keyIn->apostropheHeld = false;
						keyIn->apostropheReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->apostrophePressed = false;
						keyIn->apostropheHeld = false;
						keyIn->apostropheReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_ENTER) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->enterPressed = true;
						keyIn->enterHeld = false;
						keyIn->enterReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->enterPressed = false;
						keyIn->enterHeld = false;
						keyIn->enterReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_RIGHT_SHIFT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->rightShiftPressed = true;
						keyIn->rightShiftHeld = false;
						keyIn->rightShiftReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->rightShiftPressed = false;
						keyIn->rightShiftHeld = false;
						keyIn->rightShiftReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_RIGHT_CONTROL) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->rightControlPressed = true;
						keyIn->rightControlHeld = false;
						keyIn->rightControlReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->rightControlPressed = false;
						keyIn->rightControlHeld = false;
						keyIn->rightControlReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_RIGHT_ALT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->rightAltPressed = true;
						keyIn->rightAltHeld = false;
						keyIn->rightAltReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->rightAltPressed = false;
						keyIn->rightAltHeld = false;
						keyIn->rightAltReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_LEFT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->leftPressed = true;
						keyIn->leftHeld = false;
						keyIn->leftReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->leftPressed = false;
						keyIn->leftHeld = false;
						keyIn->leftReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_RIGHT) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->rightPressed = true;
						keyIn->rightHeld = false;
						keyIn->rightReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->rightPressed = false;
						keyIn->rightHeld = false;
						keyIn->rightReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_UP) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->upPressed = true;
						keyIn->upHeld = false;
						keyIn->upReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->upPressed = false;
						keyIn->upHeld = false;
						keyIn->upReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_DOWN) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->downPressed = true;
						keyIn->downHeld = false;
						keyIn->downReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->downPressed = false;
						keyIn->downHeld = false;
						keyIn->downReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_ESCAPE) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->escapePressed = true;
						keyIn->escapeHeld = false;
						keyIn->escapeReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->escapePressed = false;
						keyIn->escapeHeld = false;
						keyIn->escapeReleased = true;
					}
				}
				else if (keyButtons[i] == GLFW_KEY_SPACE) {
					if (keyActions[i] == GLFW_PRESS) {
						keyIn->spacePressed = true;
						keyIn->spaceHeld = false;
						keyIn->spaceReleased = false;
					}
					else if (keyActions[i] == GLFW_RELEASE) {
						keyIn->spacePressed = false;
						keyIn->spaceHeld = false;
						keyIn->spaceReleased = true;
					}
				}
			}
		}
		else {
			System::Err("Error keyboard key handling!");
		}

		keyButtons.clear();
		keyActions.clear();

		if (mouseButtons.size() == mouseActions.size()) {
			for (unsigned int i = 0; i < mouseButtons.size(); i++) {
				if (mouseButtons[i] == GLFW_MOUSE_BUTTON_LEFT) {
					if (mouseActions[i] == GLFW_PRESS) {
						mouseIn->leftClicked = true;
						mouseIn->leftHeld = false;
						mouseIn->leftReleased = false;
					}
					else if (mouseActions[i] == GLFW_RELEASE) {
						mouseIn->leftClicked = false;
						mouseIn->leftHeld = false;
						mouseIn->leftReleased = true;
					}
				}
				else if (mouseButtons[i] == GLFW_MOUSE_BUTTON_RIGHT) {
					if (mouseActions[i] == GLFW_PRESS) {
						mouseIn->rightClicked = true;
						mouseIn->rightHeld = false;
						mouseIn->rightReleased = false;
					}
					else if (mouseActions[i] == GLFW_RELEASE) {
						mouseIn->rightClicked = false;
						mouseIn->rightHeld = false;
						mouseIn->rightReleased = true;
					}
				}
			}
		}
		else {
			System::Err("Error mouse key handling!");
		}

		mouseButtons.clear();
		mouseActions.clear();
	}

	void InputHandler::Flush(KeyboardInput* keyIn, MouseInput* mouseIn)
	{
		if (keyIn->aPressed) {
			keyIn->aPressed = false;
			keyIn->aHeld = true;
		}
		if (keyIn->aReleased) {
			keyIn->aReleased = false;
		}

		if (keyIn->bPressed) {
			keyIn->bPressed = false;
			keyIn->bHeld = true;
		}
		if (keyIn->bReleased) {
			keyIn->bReleased = false;
		}

		if (keyIn->cPressed) {
			keyIn->cPressed = false;
			keyIn->cHeld = true;
		}
		if (keyIn->cReleased) {
			keyIn->cReleased = false;
		}

		if (keyIn->dPressed) {
			keyIn->dPressed = false;
			keyIn->dHeld = true;
		}
		if (keyIn->dReleased) {
			keyIn->dReleased = false;
		}

		if (keyIn->ePressed) {
			keyIn->ePressed = false;
			keyIn->eHeld = true;
		}
		if (keyIn->eReleased) {
			keyIn->eReleased = false;
		}

		if (keyIn->fPressed) {
			keyIn->fPressed = false;
			keyIn->fHeld = true;
		}
		if (keyIn->fReleased) {
			keyIn->fReleased = false;
		}

		if (keyIn->gPressed) {
			keyIn->gPressed = false;
			keyIn->gHeld = true;
		}
		if (keyIn->gReleased) {
			keyIn->gReleased = false;
		}

		if (keyIn->hPressed) {
			keyIn->hPressed = false;
			keyIn->hHeld = true;
		}
		if (keyIn->hReleased) {
			keyIn->hReleased = false;
		}

		if (keyIn->iPressed) {
			keyIn->iPressed = false;
			keyIn->iHeld = true;
		}
		if (keyIn->iReleased) {
			keyIn->iReleased = false;
		}

		if (keyIn->jPressed) {
			keyIn->jPressed = false;
			keyIn->jHeld = true;
		}
		if (keyIn->jReleased) {
			keyIn->jReleased = false;
		}

		if (keyIn->kPressed) {
			keyIn->kPressed = false;
			keyIn->kHeld = true;
		}
		if (keyIn->kReleased) {
			keyIn->kReleased = false;
		}

		if (keyIn->lPressed) {
			keyIn->lPressed = false;
			keyIn->lHeld = true;
		}
		if (keyIn->lReleased) {
			keyIn->lReleased = false;
		}

		if (keyIn->mPressed) {
			keyIn->mPressed = false;
			keyIn->mHeld = true;
		}
		if (keyIn->mReleased) {
			keyIn->mReleased = false;
		}

		if (keyIn->nPressed) {
			keyIn->nPressed = false;
			keyIn->nHeld = true;
		}
		if (keyIn->nReleased) {
			keyIn->nReleased = false;
		}

		if (keyIn->oPressed) {
			keyIn->oPressed = false;
			keyIn->oHeld = true;
		}
		if (keyIn->oReleased) {
			keyIn->oReleased = false;
		}

		if (keyIn->pPressed) {
			keyIn->pPressed = false;
			keyIn->pHeld = true;
		}
		if (keyIn->pReleased) {
			keyIn->pReleased = false;
		}

		if (keyIn->qPressed) {
			keyIn->qPressed = false;
			keyIn->qHeld = true;
		}
		if (keyIn->qReleased) {
			keyIn->qReleased = false;
		}

		if (keyIn->rPressed) {
			keyIn->rPressed = false;
			keyIn->rHeld = true;
		}
		if (keyIn->rReleased) {
			keyIn->rReleased = false;
		}

		if (keyIn->sPressed) {
			keyIn->sPressed = false;
			keyIn->sHeld = true;
		}
		if (keyIn->sReleased) {
			keyIn->sReleased = false;
		}

		if (keyIn->tPressed) {
			keyIn->tPressed = false;
			keyIn->tHeld = true;
		}
		if (keyIn->tReleased) {
			keyIn->tReleased = false;
		}

		if (keyIn->uPressed) {
			keyIn->uPressed = false;
			keyIn->uHeld = true;
		}
		if (keyIn->uReleased) {
			keyIn->uReleased = false;
		}

		if (keyIn->vPressed) {
			keyIn->vPressed = false;
			keyIn->vHeld = true;
		}
		if (keyIn->vReleased) {
			keyIn->vReleased = false;
		}

		if (keyIn->wPressed) {
			keyIn->wPressed = false;
			keyIn->wHeld = true;
		}
		if (keyIn->wReleased) {
			keyIn->wReleased = false;
		}

		if (keyIn->xPressed) {
			keyIn->xPressed = false;
			keyIn->xHeld = true;
		}
		if (keyIn->xReleased) {
			keyIn->xReleased = false;
		}

		if (keyIn->yPressed) {
			keyIn->yPressed = false;
			keyIn->yHeld = true;
		}
		if (keyIn->yReleased) {
			keyIn->yReleased = false;
		}

		if (keyIn->zPressed) {
			keyIn->zPressed = false;
			keyIn->zHeld = true;
		}
		if (keyIn->zReleased) {
			keyIn->zReleased = false;
		}

		if (keyIn->leftControlPressed) {
			keyIn->leftControlPressed = false;
			keyIn->leftControlHeld = true;
		}
		if (keyIn->leftControlReleased) {
			keyIn->leftControlReleased = false;
		}

		if (keyIn->leftShiftPressed) {
			keyIn->leftShiftPressed = false;
			keyIn->leftShiftHeld = true;
		}
		if (keyIn->leftShiftReleased) {
			keyIn->leftShiftReleased = false;
		}

		if (keyIn->leftAltPressed) {
			keyIn->leftAltPressed = false;
			keyIn->leftAltHeld = true;
		}
		if (keyIn->leftAltReleased) {
			keyIn->leftAltReleased = false;
		}

		if (keyIn->capsLockPressed) {
			keyIn->capsLockPressed = false;
			keyIn->capsLockHeld = true;
		}
		if (keyIn->capsLockReleased) {
			keyIn->capsLockReleased = false;
		}

		if (keyIn->tabPressed) {
			keyIn->tabPressed = false;
			keyIn->tabHeld = true;
		}
		if (keyIn->tabReleased) {
			keyIn->tabReleased = false;
		}

		if (keyIn->tildePressed) {
			keyIn->tildePressed = false;
			keyIn->tildeHeld = true;
		}
		if (keyIn->tildeReleased) {
			keyIn->tildeReleased = false;
		}

		if (keyIn->zeroPressed) {
			keyIn->zeroPressed = false;
			keyIn->zeroHeld = true;
		}
		if (keyIn->zeroReleased) {
			keyIn->zeroReleased = false;
		}

		if (keyIn->onePressed) {
			keyIn->onePressed = false;
			keyIn->oneHeld = true;
		}
		if (keyIn->oneReleased) {
			keyIn->oneReleased = false;
		}

		if (keyIn->twoPressed) {
			keyIn->twoPressed = false;
			keyIn->twoHeld = true;
		}
		if (keyIn->twoReleased) {
			keyIn->twoReleased = false;
		}

		if (keyIn->threePressed) {
			keyIn->threePressed = false;
			keyIn->threeHeld = true;
		}
		if (keyIn->threeReleased) {
			keyIn->threeReleased = false;
		}

		if (keyIn->fourPressed) {
			keyIn->fourPressed = false;
			keyIn->fourHeld = true;
		}
		if (keyIn->fourReleased) {
			keyIn->fourReleased = false;
		}

		if (keyIn->fivePressed) {
			keyIn->fivePressed = false;
			keyIn->fiveHeld = true;
		}
		if (keyIn->fiveReleased) {
			keyIn->fiveReleased = false;
		}

		if (keyIn->sixPressed) {
			keyIn->sixPressed = false;
			keyIn->sixHeld = true;
		}
		if (keyIn->sixReleased) {
			keyIn->sixReleased = false;
		}

		if (keyIn->sevenPressed) {
			keyIn->sevenPressed = false;
			keyIn->sevenHeld = true;
		}
		if (keyIn->sevenReleased) {
			keyIn->sevenReleased = false;
		}

		if (keyIn->eightPressed) {
			keyIn->eightPressed = false;
			keyIn->eightHeld = true;
		}
		if (keyIn->eightReleased) {
			keyIn->eightReleased = false;
		}

		if (keyIn->ninePressed) {
			keyIn->ninePressed = false;
			keyIn->nineHeld = true;
		}
		if (keyIn->nineReleased) {
			keyIn->nineReleased = false;
		}

		if (keyIn->minusPressed) {
			keyIn->minusPressed = false;
			keyIn->minusHeld = true;
		}
		if (keyIn->minusReleased) {
			keyIn->minusReleased = false;
		}

		if (keyIn->equalPressed) {
			keyIn->equalPressed = false;
			keyIn->equalHeld = true;
		}
		if (keyIn->equalReleased) {
			keyIn->equalReleased = false;
		}

		if (keyIn->backspacePressed) {
			keyIn->backspacePressed = false;
			keyIn->backspaceHeld = true;
		}
		if (keyIn->backspaceReleased) {
			keyIn->backspaceReleased = false;
		}

		if (keyIn->deletePressed) {
			keyIn->deletePressed = false;
			keyIn->deleteHeld = true;
		}
		if (keyIn->deleteReleased) {
			keyIn->deleteReleased = false;
		}

		if (keyIn->leftBracketPressed) {
			keyIn->leftBracketPressed = false;
			keyIn->leftBracketHeld = true;
		}
		if (keyIn->leftBracketReleased) {
			keyIn->leftBracketReleased = false;
		}

		if (keyIn->rightBracketPressed) {
			keyIn->rightBracketPressed = false;
			keyIn->rightBracketHeld = true;
		}
		if (keyIn->rightBracketReleased) {
			keyIn->rightBracketReleased = false;
		}

		if (keyIn->backslashPressed) {
			keyIn->backslashPressed = false;
			keyIn->backslashHeld = true;
		}
		if (keyIn->backslashReleased) {
			keyIn->backslashReleased = false;
		}

		if (keyIn->frontslashPressed) {
			keyIn->frontslashPressed = false;
			keyIn->frontslashHeld = true;
		}
		if (keyIn->frontslashReleased) {
			keyIn->frontslashReleased = false;
		}

		if (keyIn->commaPressed) {
			keyIn->commaPressed = false;
			keyIn->commaHeld = true;
		}
		if (keyIn->commaReleased) {
			keyIn->commaReleased = false;
		}

		if (keyIn->periodPressed) {
			keyIn->periodPressed = false;
			keyIn->periodHeld = true;
		}
		if (keyIn->periodReleased) {
			keyIn->periodReleased = false;
		}

		if (keyIn->semiColonPressed) {
			keyIn->semiColonPressed = false;
			keyIn->semiColonHeld = true;
		}
		if (keyIn->semiColonReleased) {
			keyIn->semiColonReleased = false;
		}

		if (keyIn->apostrophePressed) {
			keyIn->apostrophePressed = false;
			keyIn->apostropheHeld = true;
		}
		if (keyIn->apostropheReleased) {
			keyIn->apostropheReleased = false;
		}

		if (keyIn->enterPressed) {
			keyIn->enterPressed = false;
			keyIn->enterHeld = true;
		}
		if (keyIn->enterReleased) {
			keyIn->enterReleased = false;
		}

		if (keyIn->rightShiftPressed) {
			keyIn->rightShiftPressed = false;
			keyIn->rightShiftHeld = true;
		}
		if (keyIn->rightShiftReleased) {
			keyIn->rightShiftReleased = false;
		}

		if (keyIn->rightControlPressed) {
			keyIn->rightControlPressed = false;
			keyIn->rightControlHeld = true;
		}
		if (keyIn->rightControlReleased) {
			keyIn->rightControlReleased = false;
		}

		if (keyIn->rightAltPressed) {
			keyIn->rightAltPressed = false;
			keyIn->rightAltHeld = true;
		}
		if (keyIn->rightAltReleased) {
			keyIn->rightAltReleased = false;
		}

		if (keyIn->leftPressed) {
			keyIn->leftPressed = false;
			keyIn->leftHeld = true;
		}
		if (keyIn->leftReleased) {
			keyIn->leftReleased = false;
		}

		if (keyIn->rightPressed) {
			keyIn->rightPressed = false;
			keyIn->rightHeld = true;
		}
		if (keyIn->rightReleased) {
			keyIn->rightReleased = false;
		}

		if (keyIn->upPressed) {
			keyIn->upPressed = false;
			keyIn->upHeld = true;
		}
		if (keyIn->upReleased) {
			keyIn->upReleased = false;
		}

		if (keyIn->downPressed) {
			keyIn->downPressed = false;
			keyIn->downHeld = true;
		}
		if (keyIn->downReleased) {
			keyIn->downReleased = false;
		}

		if (keyIn->escapePressed) {
			keyIn->escapePressed = false;
			keyIn->escapeHeld = true;
		}
		if (keyIn->escapeReleased) {
			keyIn->escapeReleased = false;
		}

		if (keyIn->spacePressed) {
			keyIn->spacePressed = false;
			keyIn->spaceHeld = true;
		}
		if (keyIn->spaceReleased) {
			keyIn->spaceReleased = false;
		}
	}
}