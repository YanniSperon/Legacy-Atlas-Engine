#include "InputHandler.h"
#include "Global.h"
#include <map>
#include <unordered_map>

namespace Engine {

	static bool inputAllowed;

	void InputHandler::KeyCallback(KeyboardInput* input, GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (inputAllowed) {
			if (key == GLFW_KEY_A) {
				if (action == GLFW_PRESS) {
					input->aPressed = true;
					input->aHeld = false;
					input->aReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->aPressed = false;
					input->aHeld = false;
					input->aReleased = true;
				}
			}
			else if (key == GLFW_KEY_B) {
				if (action == GLFW_PRESS) {
					input->bPressed = true;
					input->bHeld = false;
					input->bReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->bPressed = false;
					input->bHeld = false;
					input->bReleased = true;
				}
			}
			else if (key == GLFW_KEY_C) {
				if (action == GLFW_PRESS) {
					input->cPressed = true;
					input->cHeld = false;
					input->cReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->cPressed = false;
					input->cHeld = false;
					input->cReleased = true;
				}
			}
			else if (key == GLFW_KEY_D) {
				if (action == GLFW_PRESS) {
					input->dPressed = true;
					input->dHeld = false;
					input->dReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->dPressed = false;
					input->dHeld = false;
					input->dReleased = true;
				}
			}
			else if (key == GLFW_KEY_E) {
				if (action == GLFW_PRESS) {
					input->ePressed = true;
					input->eHeld = false;
					input->eReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->ePressed = false;
					input->eHeld = false;
					input->eReleased = true;
				}
			}
			else if (key == GLFW_KEY_F) {
				if (action == GLFW_PRESS) {
					input->fPressed = true;
					input->fHeld = false;
					input->fReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->fPressed = false;
					input->fHeld = false;
					input->fReleased = true;
				}
			}
			else if (key == GLFW_KEY_G) {
				if (action == GLFW_PRESS) {
					input->gPressed = true;
					input->gHeld = false;
					input->gReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->gPressed = false;
					input->gHeld = false;
					input->gReleased = true;
				}
			}
			else if (key == GLFW_KEY_H) {
				if (action == GLFW_PRESS) {
					input->hPressed = true;
					input->hHeld = false;
					input->hReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->hPressed = false;
					input->hHeld = false;
					input->hReleased = true;
				}
			}
			else if (key == GLFW_KEY_I) {
				if (action == GLFW_PRESS) {
					input->iPressed = true;
					input->iHeld = false;
					input->iReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->iPressed = false;
					input->iHeld = false;
					input->iReleased = true;
				}
			}
			else if (key == GLFW_KEY_J) {
				if (action == GLFW_PRESS) {
					input->jPressed = true;
					input->jHeld = false;
					input->jReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->jPressed = false;
					input->jHeld = false;
					input->jReleased = true;
				}
			}
			else if (key == GLFW_KEY_K) {
				if (action == GLFW_PRESS) {
					input->kPressed = true;
					input->kHeld = false;
					input->kReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->kPressed = false;
					input->kHeld = false;
					input->kReleased = true;
				}
			}
			else if (key == GLFW_KEY_L) {
				if (action == GLFW_PRESS) {
					input->lPressed = true;
					input->lHeld = false;
					input->lReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->lPressed = false;
					input->lHeld = false;
					input->lReleased = true;
				}
			}
			else if (key == GLFW_KEY_M) {
				if (action == GLFW_PRESS) {
					input->mPressed = true;
					input->mHeld = false;
					input->mReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->mPressed = false;
					input->mHeld = false;
					input->mReleased = true;
				}
			}
			else if (key == GLFW_KEY_N) {
				if (action == GLFW_PRESS) {
					input->nPressed = true;
					input->nHeld = false;
					input->nReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->nPressed = false;
					input->nHeld = false;
					input->nReleased = true;
				}
			}
			else if (key == GLFW_KEY_O) {
				if (action == GLFW_PRESS) {
					input->oPressed = true;
					input->oHeld = false;
					input->oReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->oPressed = false;
					input->oHeld = false;
					input->oReleased = true;
				}
			}
			else if (key == GLFW_KEY_P) {
				if (action == GLFW_PRESS) {
					input->pPressed = true;
					input->pHeld = false;
					input->pReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->pPressed = false;
					input->pHeld = false;
					input->pReleased = true;
				}
			}
			else if (key == GLFW_KEY_Q) {
				if (action == GLFW_PRESS) {
					input->qPressed = true;
					input->qHeld = false;
					input->qReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->qPressed = false;
					input->qHeld = false;
					input->qReleased = true;
				}
			}
			else if (key == GLFW_KEY_R) {
				if (action == GLFW_PRESS) {
					input->rPressed = true;
					input->rHeld = false;
					input->rReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->rPressed = false;
					input->rHeld = false;
					input->rReleased = true;
				}
			}
			else if (key == GLFW_KEY_S) {
				if (action == GLFW_PRESS) {
					input->sPressed = true;
					input->sHeld = false;
					input->sReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->sPressed = false;
					input->sHeld = false;
					input->sReleased = true;
				}
			}
			else if (key == GLFW_KEY_T) {
				if (action == GLFW_PRESS) {
					input->tPressed = true;
					input->tHeld = false;
					input->tReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->tPressed = false;
					input->tHeld = false;
					input->tReleased = true;
				}
			}
			else if (key == GLFW_KEY_U) {
				if (action == GLFW_PRESS) {
					input->uPressed = true;
					input->uHeld = false;
					input->uReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->uPressed = false;
					input->uHeld = false;
					input->uReleased = true;
				}
			}
			else if (key == GLFW_KEY_V) {
				if (action == GLFW_PRESS) {
					input->vPressed = true;
					input->vHeld = false;
					input->vReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->vPressed = false;
					input->vHeld = false;
					input->vReleased = true;
				}
			}
			else if (key == GLFW_KEY_W) {
				if (action == GLFW_PRESS) {
					input->wPressed = true;
					input->wHeld = false;
					input->wReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->wPressed = false;
					input->wHeld = false;
					input->wReleased = true;
				}
			}
			else if (key == GLFW_KEY_X) {
				if (action == GLFW_PRESS) {
					input->xPressed = true;
					input->xHeld = false;
					input->xReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->xPressed = false;
					input->xHeld = false;
					input->xReleased = true;
				}
			}
			else if (key == GLFW_KEY_Y) {
				if (action == GLFW_PRESS) {
					input->yPressed = true;
					input->yHeld = false;
					input->yReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->yPressed = false;
					input->yHeld = false;
					input->yReleased = true;
				}
			}
			else if (key == GLFW_KEY_Z) {
				if (action == GLFW_PRESS) {
					input->zPressed = true;
					input->zHeld = false;
					input->zReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->zPressed = false;
					input->zHeld = false;
					input->zReleased = true;
				}
			}
			else if (key == GLFW_KEY_LEFT_CONTROL) {
				if (action == GLFW_PRESS) {
					input->leftControlPressed = true;
					input->leftControlHeld = false;
					input->leftControlReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->leftControlPressed = false;
					input->leftControlHeld = false;
					input->leftControlReleased = true;
				}
			}
			else if (key == GLFW_KEY_LEFT_SHIFT) {
				if (action == GLFW_PRESS) {
					input->leftShiftPressed = true;
					input->leftShiftHeld = false;
					input->leftShiftReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->leftShiftPressed = false;
					input->leftShiftHeld = false;
					input->leftShiftReleased = true;
				}
			}
			else if (key == GLFW_KEY_CAPS_LOCK) {
				if (action == GLFW_PRESS) {
					input->capsLockPressed = true;
					input->capsLockHeld = false;
					input->capsLockReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->capsLockPressed = false;
					input->capsLockHeld = false;
					input->capsLockReleased = true;
				}
			}
			else if (key == GLFW_KEY_LEFT_ALT) {
				if (action == GLFW_PRESS) {
					input->leftAltPressed = true;
					input->leftAltHeld = false;
					input->leftAltReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->leftAltPressed = false;
					input->leftAltHeld = false;
					input->leftAltReleased = true;
				}
			}
			else if (key == GLFW_KEY_TAB) {
				if (action == GLFW_PRESS) {
					input->tabPressed = true;
					input->tabHeld = false;
					input->tabReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->tabPressed = false;
					input->tabHeld = false;
					input->tabReleased = true;
				}
			}
			else if (key == GLFW_KEY_GRAVE_ACCENT) {
				if (action == GLFW_PRESS) {
					input->tildePressed = true;
					input->tildeHeld = false;
					input->tildeReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->tildePressed = false;
					input->tildeHeld = false;
					input->tildeReleased = true;
				}
			}
			else if (key == GLFW_KEY_0) {
				if (action == GLFW_PRESS) {
					input->zeroPressed = true;
					input->zeroHeld = false;
					input->zeroReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->zeroPressed = false;
					input->zeroHeld = false;
					input->zeroReleased = true;
				}
			}
			else if (key == GLFW_KEY_1) {
				if (action == GLFW_PRESS) {
					input->onePressed = true;
					input->oneHeld = false;
					input->oneReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->onePressed = false;
					input->oneHeld = false;
					input->oneReleased = true;
				}
			}
			else if (key == GLFW_KEY_2) {
				if (action == GLFW_PRESS) {
					input->twoPressed = true;
					input->twoHeld = false;
					input->twoReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->twoPressed = false;
					input->twoHeld = false;
					input->twoReleased = true;
				}
			}
			else if (key == GLFW_KEY_3) {
				if (action == GLFW_PRESS) {
					input->threePressed = true;
					input->threeHeld = false;
					input->threeReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->threePressed = false;
					input->threeHeld = false;
					input->threeReleased = true;
				}
			}
			else if (key == GLFW_KEY_4) {
				if (action == GLFW_PRESS) {
					input->fourPressed = true;
					input->fourHeld = false;
					input->fourReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->fourPressed = false;
					input->fourHeld = false;
					input->fourReleased = true;
				}
			}
			else if (key == GLFW_KEY_5) {
				if (action == GLFW_PRESS) {
					input->fivePressed = true;
					input->fiveHeld = false;
					input->fiveReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->fivePressed = false;
					input->fiveHeld = false;
					input->fiveReleased = true;
				}
			}
			else if (key == GLFW_KEY_6) {
				if (action == GLFW_PRESS) {
					input->sixPressed = true;
					input->sixHeld = false;
					input->sixReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->sixPressed = false;
					input->sixHeld = false;
					input->sixReleased = true;
				}
			}
			else if (key == GLFW_KEY_7) {
				if (action == GLFW_PRESS) {
					input->sevenPressed = true;
					input->sevenHeld = false;
					input->sevenReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->sevenPressed = false;
					input->sevenHeld = false;
					input->sevenReleased = true;
				}
			}
			else if (key == GLFW_KEY_8) {
				if (action == GLFW_PRESS) {
					input->eightPressed = true;
					input->eightHeld = false;
					input->eightReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->eightPressed = false;
					input->eightHeld = false;
					input->eightReleased = true;
				}
			}
			else if (key == GLFW_KEY_9) {
				if (action == GLFW_PRESS) {
					input->ninePressed = true;
					input->nineHeld = false;
					input->nineReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->ninePressed = false;
					input->nineHeld = false;
					input->nineReleased = true;
				}
			}
			else if (key == GLFW_KEY_MINUS) {
				if (action == GLFW_PRESS) {
					input->minusPressed = true;
					input->minusHeld = false;
					input->minusReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->minusPressed = false;
					input->minusHeld = false;
					input->minusReleased = true;
				}
			}
			else if (key == GLFW_KEY_EQUAL) {
				if (action == GLFW_PRESS) {
					input->equalPressed = true;
					input->equalHeld = false;
					input->equalReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->equalPressed = false;
					input->equalHeld = false;
					input->equalReleased = true;
				}
			}
			else if (key == GLFW_KEY_BACKSPACE) {
				if (action == GLFW_PRESS) {
					input->backspacePressed = true;
					input->backspaceHeld = false;
					input->backspaceReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->backspacePressed = false;
					input->backspaceHeld = false;
					input->backspaceReleased = true;
				}
			}
			else if (key == GLFW_KEY_DELETE) {
				if (action == GLFW_PRESS) {
					input->deletePressed = true;
					input->deleteHeld = false;
					input->deleteReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->deletePressed = false;
					input->deleteHeld = false;
					input->deleteReleased = true;
				}
			}
			else if (key == GLFW_KEY_LEFT_BRACKET) {
				if (action == GLFW_PRESS) {
					input->leftBracketPressed = true;
					input->leftBracketHeld = false;
					input->leftBracketReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->leftBracketPressed = false;
					input->leftBracketHeld = false;
					input->leftBracketReleased = true;
				}
			}
			else if (key == GLFW_KEY_RIGHT_BRACKET) {
				if (action == GLFW_PRESS) {
					input->rightBracketPressed = true;
					input->rightBracketHeld = false;
					input->rightBracketReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->rightBracketPressed = false;
					input->rightBracketHeld = false;
					input->rightBracketReleased = true;
				}
			}
			else if (key == GLFW_KEY_BACKSLASH) {
				if (action == GLFW_PRESS) {
					input->backslashPressed = true;
					input->backslashHeld = false;
					input->backslashReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->backslashPressed = false;
					input->backslashHeld = false;
					input->backslashReleased = true;
				}
			}
			else if (key == GLFW_KEY_SLASH) {
				if (action == GLFW_PRESS) {
					input->frontslashPressed = true;
					input->frontslashHeld = false;
					input->frontslashReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->frontslashPressed = false;
					input->frontslashHeld = false;
					input->frontslashReleased = true;
				}
			}
			else if (key == GLFW_KEY_COMMA) {
				if (action == GLFW_PRESS) {
					input->commaPressed = true;
					input->commaHeld = false;
					input->commaReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->commaPressed = false;
					input->commaHeld = false;
					input->commaReleased = true;
				}
			}
			else if (key == GLFW_KEY_PERIOD) {
				if (action == GLFW_PRESS) {
					input->periodPressed = true;
					input->periodHeld = false;
					input->periodReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->periodPressed = false;
					input->periodHeld = false;
					input->periodReleased = true;
				}
			}
			else if (key == GLFW_KEY_SEMICOLON) {
				if (action == GLFW_PRESS) {
					input->semiColonPressed = true;
					input->semiColonHeld = false;
					input->semiColonReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->semiColonPressed = false;
					input->semiColonHeld = false;
					input->semiColonReleased = true;
				}
			}
			else if (key == GLFW_KEY_APOSTROPHE) {
				if (action == GLFW_PRESS) {
					input->apostrophePressed = true;
					input->apostropheHeld = false;
					input->apostropheReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->apostrophePressed = false;
					input->apostropheHeld = false;
					input->apostropheReleased = true;
				}
			}
			else if (key == GLFW_KEY_ENTER) {
				if (action == GLFW_PRESS) {
					input->enterPressed = true;
					input->enterHeld = false;
					input->enterReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->enterPressed = false;
					input->enterHeld = false;
					input->enterReleased = true;
				}
			}
			else if (key == GLFW_KEY_APOSTROPHE) {
				if (action == GLFW_PRESS) {
					input->apostrophePressed = true;
					input->apostropheHeld = false;
					input->apostropheReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->apostrophePressed = false;
					input->apostropheHeld = false;
					input->apostropheReleased = true;
				}
			}
			else if (key == GLFW_KEY_RIGHT_SHIFT) {
				if (action == GLFW_PRESS) {
					input->rightShiftPressed = true;
					input->rightShiftHeld = false;
					input->rightShiftReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->rightShiftPressed = false;
					input->rightShiftHeld = false;
					input->rightShiftReleased = true;
				}
			}
			else if (key == GLFW_KEY_RIGHT_CONTROL) {
				if (action == GLFW_PRESS) {
					input->rightControlPressed = true;
					input->rightControlHeld = false;
					input->rightControlReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->rightControlPressed = false;
					input->rightControlHeld = false;
					input->rightControlReleased = true;
				}
			}
			else if (key == GLFW_KEY_RIGHT_ALT) {
				if (action == GLFW_PRESS) {
					input->rightAltPressed = true;
					input->rightAltHeld = false;
					input->rightAltReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->rightAltPressed = false;
					input->rightAltHeld = false;
					input->rightAltReleased = true;
				}
			}
			else if (key == GLFW_KEY_LEFT) {
				if (action == GLFW_PRESS) {
					input->leftPressed = true;
					input->leftHeld = false;
					input->leftReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->leftPressed = false;
					input->leftHeld = false;
					input->leftReleased = true;
				}
			}
			else if (key == GLFW_KEY_RIGHT) {
				if (action == GLFW_PRESS) {
					input->rightPressed = true;
					input->rightHeld = false;
					input->rightReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->rightPressed = false;
					input->rightHeld = false;
					input->rightReleased = true;
				}
			}
			else if (key == GLFW_KEY_UP) {
				if (action == GLFW_PRESS) {
					input->upPressed = true;
					input->upHeld = false;
					input->upReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->upPressed = false;
					input->upHeld = false;
					input->upReleased = true;
				}
			}
			else if (key == GLFW_KEY_DOWN) {
				if (action == GLFW_PRESS) {
					input->downPressed = true;
					input->downHeld = false;
					input->downReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->downPressed = false;
					input->downHeld = false;
					input->downReleased = true;
				}
			}
			else if (key == GLFW_KEY_ESCAPE) {
				if (action == GLFW_PRESS) {
					input->escapePressed = true;
					input->escapeHeld = false;
					input->escapeReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->escapePressed = false;
					input->escapeHeld = false;
					input->escapeReleased = true;
				}
			}
			else if (key == GLFW_KEY_SPACE) {
				if (action == GLFW_PRESS) {
					input->spacePressed = true;
					input->spaceHeld = false;
					input->spaceReleased = false;
				}
				else if (action == GLFW_RELEASE) {
					input->spacePressed = false;
					input->spaceHeld = false;
					input->spaceReleased = true;
				}
			}
		}
	}

	void InputHandler::StartInput()
	{
		inputAllowed = true;
	}

	void InputHandler::EndInput()
	{
		inputAllowed = false;
	}

	void InputHandler::Flush(KeyboardInput* keyIn, MouseInput* mouseIn)
	{
		printf("Flushing\n");
		if (inputAllowed) {
			if (keyIn->aPressed) {
				keyIn->aPressed = false;
				keyIn->aHeld = true;
			}
			if (keyIn->aReleased) {
				keyIn->aReleased = false;
			}
		}
	}
}