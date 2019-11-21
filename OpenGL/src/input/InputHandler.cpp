#include "InputHandler.h"

void InputHandler::KeyCallback(KeyboardInput* input, GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) {
			if (input->aPressed || input->aHeld) {
				input->aHeld = true;
				input->aPressed = false;
			}
			else {
				input->aPressed = true;
			}
		}
		else if (action == GLFW_RELEASE) {
			input->aPressed = false;
			input->aHeld = false;
		}
	} else if (key == GLFW_KEY_B) {
		if (action == GLFW_PRESS) {
			input->bPressed = true;
		}
		else if (action == GLFW_RELEASE) {
			input->bPressed = false;
		}
	} else if (key == GLFW_KEY_C) {
		if (action == GLFW_PRESS) {
			input->cPressed = true;
		}
		else if (action == GLFW_RELEASE) {
			input->cPressed = false;
		}
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		input->cPressed = true;
	}
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
		input->cPressed = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		input->dPressed = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		input->dPressed = false;
	}

	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		input->ePressed = true;
	}
	else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
		input->ePressed = false;
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		input->fPressed = true;
	}
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
		input->fPressed = false;
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		input->gPressed = true;
	}
	else if (key == GLFW_KEY_G && action == GLFW_RELEASE) {
		input->gPressed = false;
	}

	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		input->hPressed = true;
	}
	else if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
		input->hPressed = false;
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		input->iPressed = true;
	}
	else if (key == GLFW_KEY_I && action == GLFW_RELEASE) {
		input->iPressed = false;
	}

	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		input->jPressed = true;
	}
	else if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
		input->jPressed = false;
	}

	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		input->kPressed = true;
	}
	else if (key == GLFW_KEY_K && action == GLFW_RELEASE) {
		input->kPressed = false;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		input->lPressed = true;
	}
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE) {
		input->lPressed = false;
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		input->mPressed = true;
	}
	else if (key == GLFW_KEY_M && action == GLFW_RELEASE) {
		input->mPressed = false;
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		input->nPressed = true;
	}
	else if (key == GLFW_KEY_N && action == GLFW_RELEASE) {
		input->nPressed = false;
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		input->oPressed = true;
	}
	else if (key == GLFW_KEY_O && action == GLFW_RELEASE) {
		input->oPressed = false;
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		input->pPressed = true;
	}
	else if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
		input->pPressed = false;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		input->qPressed = true;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
		input->qPressed = false;
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		input->rPressed = true;
	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
		input->rPressed = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		input->sPressed = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		input->sPressed = false;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		input->tPressed = true;
	}
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
		input->tPressed = false;
	}

	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		input->uPressed = true;
	}
	else if (key == GLFW_KEY_U && action == GLFW_RELEASE) {
		input->uPressed = false;
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		input->vPressed = true;
	}
	else if (key == GLFW_KEY_V && action == GLFW_RELEASE) {
		input->vPressed = false;
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		input->wPressed = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		input->wPressed = false;
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		input->xPressed = true;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		input->xPressed = false;
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		input->yPressed = true;
	}
	else if (key == GLFW_KEY_Y && action == GLFW_RELEASE) {
		input->yPressed = false;
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		input->zPressed = true;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		input->zPressed = false;
	}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		input->leftControlPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
		input->leftControlPressed = false;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		input->leftShiftPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		input->leftShiftPressed = false;
	}

	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS) {
		input->capsLockPressed = true;
	}
	else if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_RELEASE) {
		input->capsLockPressed = false;
	}

	if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
		input->leftAltPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE) {
		input->leftAltPressed = false;
	}

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		input->tabPressed = true;
	}
	else if (key == GLFW_KEY_TAB && action == GLFW_RELEASE) {
		input->tabPressed = false;
	}

	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
		input->tildePressed = true;
	}
	else if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_RELEASE) {
		input->tildePressed = false;
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		input->zeroPressed = true;
	}
	else if (key == GLFW_KEY_0 && action == GLFW_RELEASE) {
		input->zeroPressed = false;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		input->onePressed = true;
	}
	else if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
		input->onePressed = false;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		input->twoPressed = true;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
		input->twoPressed = false;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		input->threePressed = true;
	}
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
		input->threePressed = false;
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		input->fourPressed = true;
	}
	else if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
		input->fourPressed = false;
	}

	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		input->fivePressed = true;
	}
	else if (key == GLFW_KEY_5 && action == GLFW_RELEASE) {
		input->fivePressed = false;
	}

	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		input->sixPressed = true;
	}
	else if (key == GLFW_KEY_6 && action == GLFW_RELEASE) {
		input->sixPressed = false;
	}

	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		input->sevenPressed = true;
	}
	else if (key == GLFW_KEY_7 && action == GLFW_RELEASE) {
		input->sevenPressed = false;
	}

	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		input->eightPressed = true;
	}
	else if (key == GLFW_KEY_8 && action == GLFW_RELEASE) {
		input->eightPressed = false;
	}

	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		input->ninePressed = true;
	}
	else if (key == GLFW_KEY_9 && action == GLFW_RELEASE) {
		input->ninePressed = false;
	}

	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
		input->minusPressed = true;
	}
	else if (key == GLFW_KEY_MINUS && action == GLFW_RELEASE) {
		input->minusPressed = false;
	}

	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
		input->equalPressed = true;
	}
	else if (key == GLFW_KEY_EQUAL && action == GLFW_RELEASE) {
		input->equalPressed = false;
	}

	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
		input->backspacePressed = true;
	}
	else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE) {
		input->backspacePressed = false;
	}

	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		input->deletePressed = true;
	}
	else if (key == GLFW_KEY_DELETE && action == GLFW_RELEASE) {
		input->deletePressed = false;
	}

	if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS) {
		input->leftBracketPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
		input->leftBracketPressed = false;
	}

	if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS) {
		input->rightBracketPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_RELEASE) {
		input->rightBracketPressed = false;
	}

	if (key == GLFW_KEY_BACKSLASH && action == GLFW_PRESS) {
		input->backslashPressed = true;
	}
	else if (key == GLFW_KEY_BACKSLASH && action == GLFW_RELEASE) {
		input->backslashPressed = false;
	}

	if (key == GLFW_KEY_SLASH && action == GLFW_PRESS) {
		input->frontslashPressed = true;
	}
	else if (key == GLFW_KEY_SLASH && action == GLFW_RELEASE) {
		input->frontslashPressed = false;
	}

	if (key == GLFW_KEY_COMMA && action == GLFW_PRESS) {
		input->commaPressed = true;
	}
	else if (key == GLFW_KEY_COMMA && action == GLFW_RELEASE) {
		input->commaPressed = false;
	}

	if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) {
		input->periodPressed = true;
	}
	else if (key == GLFW_KEY_PERIOD && action == GLFW_RELEASE) {
		input->periodPressed = false;
	}

	if (key == GLFW_KEY_BACKSLASH && action == GLFW_PRESS) {
		input->backslashPressed = true;
	}
	else if (key == GLFW_KEY_BACKSLASH && action == GLFW_RELEASE) {
		input->backslashPressed = false;
	}

	if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS) {
		input->semiColonPressed = true;
	}
	else if (key == GLFW_KEY_SEMICOLON && action == GLFW_RELEASE) {
		input->semiColonPressed = false;
	}

	if (key == GLFW_KEY_APOSTROPHE && action == GLFW_PRESS) {
		input->apostrophePressed = true;
	}
	else if (key == GLFW_KEY_APOSTROPHE && action == GLFW_RELEASE) {
		input->apostrophePressed = false;
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		input->enterPressed = true;
	}
	else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
		input->enterPressed = false;
	}

	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		input->deletePressed = true;
	}
	else if (key == GLFW_KEY_DELETE && action == GLFW_RELEASE) {
		input->deletePressed = false;
	}

	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) {
		input->rightShiftPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE) {
		input->rightShiftPressed = false;
	}

	if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS) {
		input->rightControlPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_RELEASE) {
		input->rightControlPressed = false;
	}

	if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS) {
		input->rightAltPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_RELEASE) {
		input->rightAltPressed = false;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		input->leftPressed = true;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		input->leftPressed = false;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		input->rightPressed = true;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		input->rightPressed = false;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		input->upPressed = true;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		input->upPressed = false;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		if (!input->downPressed) {
			input->downHeld = true;
		}
		else {
			input->downPressed = true;
		}
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		input->downPressed = false;
		input->downHeld = false;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		if (!input->escapePressed) {
			input->escapeHeld = true;
		}
		else {
			input->escapePressed = true;
		}
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		input->escapePressed = false;
		input->escapeHeld = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		input->spacePressed = true;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		input->spacePressed = false;
	}
}
