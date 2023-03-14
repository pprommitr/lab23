#include <windows.h>
#include <stdio.h>
#include <string>

HWND textfield, input1, input2, button1, button2, button3, button4;
char buffer1[100];
char buffer2[100];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		/* Upon creation, create our text field */
		case WM_CREATE: {
			textfield = CreateWindow(
				"Static", /* Class name */
				"Please input two numbers", /* Text */
				WS_CHILD | WS_VISIBLE | SS_CENTER, /* Styles */
				20, /* x */
				10, /* y */
				200, /* width */
				20, /* height */
				hwnd, /* Parent window */
				NULL, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			SendMessage(textfield, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE); /* Set font for text field */
			input1 = CreateWindow(
				"Edit", /* Class name */
				"", /* Text */
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, /* Styles */
				20, /* x */
				40, /* y */
				200, /* width */
				20, /* height */
				hwnd, /* Parent window */
				NULL, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			input2 = CreateWindow(
				"Edit", /* Class name */
				"", /* Text */
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, /* Styles */
				20, /* x */
				70, /* y */
				200, /* width */
				20, /* height */
				hwnd, /* Parent window */
				NULL, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			button1 = CreateWindow(
				"Button", /* Class name */
				"+", /* Text */
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, /* Styles */
				20, /* x */
				100, /* y */
				45, /* width */
				20, /* height */
				hwnd, /* Parent window */
				(HMENU) 1, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			button2 = CreateWindow(
				"Button", /* Class name */
				"-", /* Text */
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, /* Styles */
				75, /* x */
				100, /* y */
				40, /* width */
				20, /* height */
				hwnd, /* Parent window */
				(HMENU) 2, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			button3 = CreateWindow(
				"Button", /* Class name */
				"*", /* Text */
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, /* Styles */
				125, /* x */
				100, /* y */
				40, /* width */
				20, /* height */
				hwnd, /* Parent window */
				(HMENU) 3, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			button4 = CreateWindow(
				"Button", /* Class name */
				"/", /* Text */
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, /* Styles */
				175, /* x */
				100, /* y */
				45, /* width */
				20, /* height */
				hwnd, /* Parent window */
				(HMENU) 4, /* Menu */
				NULL, /* Instance */
				NULL /* Additional application data */
			);
			break;
		}

		/* Handle the WM_CTLCOLORSTATIC message to make the background of the text field transparent */
		case WM_CTLCOLORSTATIC: {
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (LRESULT)GetStockObject(HOLLOW_BRUSH);
		}

		case WM_COMMAND: {
			switch(LOWORD(wParam)){
				case 1: {/*Plus*/
					/* Get the text from the text field */
					GetWindowText(input1, buffer1, 100);
					GetWindowText(input2, buffer2, 100);
					double a = std::stod(buffer1);
					double b = std::stod(buffer2);
					double result = a + b;
					char resultString[100];
					sprintf(resultString, "%f", result);
					MessageBox(hwnd, resultString, "Result", MB_OK);
					break;
				}
				case 2: {/*Minus*/
					GetWindowText(input1, buffer1, 100);
					GetWindowText(input2, buffer2, 100);
					double a = std::stod(buffer1);
					double b = std::stod(buffer2);
					double result = a - b;
					char resultString[100];
					sprintf(resultString, "%f", result);
					MessageBox(hwnd, resultString, "Result", MB_OK);
					break;
				}
				case 3: {/*Multiply*/
					GetWindowText(input1, buffer1, 100);
					GetWindowText(input2, buffer2, 100);
					double a = std::stod(buffer1);
					double b = std::stod(buffer2);
					double result = a * b;
					char resultString[100];
					sprintf(resultString, "%f", result);
					MessageBox(hwnd, resultString, "Result", MB_OK);
					break;
				}
				case 4: {/*Divide*/
					GetWindowText(input1, buffer1, 100);
					GetWindowText(input2, buffer2, 100);
					double a = std::stod(buffer1);
					double b = std::stod(buffer2);
					double result = a / b;
					char resultString[100];
					sprintf(resultString, "%f", result);
					MessageBox(hwnd, resultString, "Result", MB_OK);
					break;
				}
			}
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	// wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hbrBackground = CreateSolidBrush(RGB(178, 102, 255));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}