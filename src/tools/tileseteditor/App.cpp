#include "App.hpp"
//#include "Snippets.hpp" No content yet, so not needed

#include "TileSelect.hpp"

using namespace std;



#define W_WIDTH	 = 1024
#define W_HEIGHT = 768

bool active = false;

string cmd;
string debugSts = "";
bool typing = true;
bool clipFull = false;
enum modes { COMMAND, KEY};
bool comSwitch = false;

modes mode = COMMAND;

sf::Image* clipboard;
sf::Image* surface;

sf::Font terminalFnt;

TileSelect ss = TileSelect();
//TileSelect ds = new TileSelect();
cord2D mousePosition;

App::~App(void)
{

}

int App::OnExecute()
{
    if(OnInit() == false)
        return -1;

    while (RenderWin->IsOpened())
    {
        sf::Event e;
        while (RenderWin->GetEvent(e))
            OnEvent(e);

        OnLoop();
        OnRender();

        while (RenderWin->GetEvent(e))
            OnEvent(e);
    }

    OnCleanup();

    return 1;
}

bool App::OnInit(void)
{

    this->RenderWin = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "Alpine Engine", sf::Style::Resize);
    this->Clock = new sf::Clock();
    this->Clock->Reset();
	surface = new sf::Image(1024,768);
	clipboard = new sf::Image(128,128);
	terminalFnt.LoadFromFile("consolas.ttf");
 
	RenderWin->PreserveOpenGLStates(true);
    glEnable( GL_TEXTURE_2D);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glViewport( 0, 0, RenderWin->GetWidth(), RenderWin->GetHeight() );
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0f, RenderWin->GetWidth(), RenderWin->GetHeight(), 0.0f, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    RenderWin->SetActive();

    return 1;
}

void App::OnLoop()
{
	// Loop code
}

void App::OnRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sf::Sprite sSurf;
	sf::Sprite sClip;
	sSurf.SetImage(*surface);
	sClip.SetImage(*clipboard);
	RenderWin->Draw(sSurf);

	if (active) {
		ss.draw();
	}

	if (clipFull) {
		sClip.SetColor(sf::Color(255.0f,255.0f,255.0f,128.0f));
		sClip.SetX((mousePosition.x/32)*32);
		sClip.SetY((mousePosition.y/32)*32);
		RenderWin->Draw(sClip);
	}

	glColor4f(0.0f,0.0f,0.0f,0.9f);
	glBegin(GL_QUADS);
		glVertex3f(0.0f,	740.0f,	0.0f);
		glVertex3f(1024.0f,	740.0f,	0.0f);
		glVertex3f(1024.0f, 768.0f,	0.0f);
		glVertex3f(0.0f,	768.0f,	0.0f);
	glEnd();

	sf::String text;
	text.SetFont(terminalFnt);
	text.SetColor(sf::Color::Red);
	text.SetSize(16.0f);
	text.Move(8,745);

	if (typing) {
		text.SetText("Execute> "+cmd);
	} else {
		text.SetText(" Output< "+cmd);
	}
	
	//sf::String deb;
	//deb.SetColor(sf::Color::Yellow);
	//deb.SetSize(12.0f);
	//deb.Move(500,5);
	//deb.SetText(debugSts);

	RenderWin->Draw(text);
	//RenderWin->Draw(deb);
    RenderWin->Display();

}

void App::OnEvent(sf::Event e)
{
    if (e.Type == sf::Event::Closed)
        this->RenderWin->Close();

	// MouseButtonPressed
	if (e.Type == sf::Event::MouseButtonPressed) {
		if (!active) active = true;
		ss.start(
			e.MouseButton.X,
			e.MouseButton.Y
		);
	}
	
	// Mouse Moved
	if (e.Type == sf::Event::MouseMoved) {
		mousePosition.x = e.MouseMove.X;
		mousePosition.y = e.MouseMove.Y;
		ss.move(
			e.MouseMove.X,
			e.MouseMove.Y
		);
	}

	// MouseButton Released
	if (e.Type == sf::Event::MouseButtonReleased) {
		ss.end(
			e.MouseButton.X,
			e.MouseButton.Y
		);
	}

	if (e.Type == sf::Event::TextEntered) {
		if (mode == COMMAND) {
			int i; i = e.Text.Unicode;
			if (i != 8 && i != 13) {
				if (!typing)
					cmd.clear();
					typing = true;
				if (!comSwitch) {
					cmd += (char)e.Text.Unicode;
				} else {
					comSwitch = false;
				}
			}
		}
	}

	if(e.Type == sf::Event::KeyPressed) {
		string tmp;
		switch (e.Key.Code) {
		case sf::Key::Escape:
			mode = KEY;
			termOutput("Mode? ([c]Copy [v]Paste [e]command [q]Quit)");
			break;
		case sf::Key::Q:
			if (mode == KEY) 
				this->RenderWin->Close();
			break;
		case sf::Key::C:
			if (mode == KEY)
			{
				termOutput("[Copy]");
				sf::Rect<int> r = ss.getRect();
				clipboard->Create(r.GetWidth(),r.GetHeight());
				clipboard->Copy(*surface,0,0,r);
				termOutput("Copied to clipboard.");
				clipFull = true;
			}
			break;
		case sf::Key::V:
			if (mode == KEY)
			{
				surface->Copy(*clipboard,(mousePosition.x/32)*32,(mousePosition.y/32)*32);
				termOutput("Pasted from clipboard.");
			}
			break;
		case sf::Key::E:
			if (mode == KEY) {
				mode = COMMAND;
			    comSwitch = true;
			}
			break;
		case sf::Key::Return:
			tmp = cmd;
			cmd.clear();
			handleCommand(tmp);
			break;
		case sf::Key::Back:
			if (cmd.length() > 0) {
				cmd.erase(cmd.end()-1,cmd.end());
			}
			break;
		default:

			break;
		}
	}
}

// Cleaning Up
void App::OnCleanup()
{
    delete this->RenderWin;
    delete this->Clock;
}

void App::handleCommand(string com) {
	if (com == "clear") {
		active = false;
		clipboard->Create(0,0);
		clipFull = false;
	} else if (com == "reset") {
		surface->Create(1024,768);
	} else if (com == "debug routine alpha") {
		sf::Image s2;
		s2.LoadFromFile("palet.png");
		surface->Copy(s2,0,0);
		termOutput("Debug Routine Alpha Launched!");
	} else if (com == "debug routine beta") {
		sf::Image s2;
		s2.LoadFromFile("tmp2.bmp");
		surface->Copy(s2,128,128);
		termOutput("Debug Routine Beta Launched!");
	} else if (com == "about") {
		termOutput("Dev7 Studios - Basic Terminal System - v1.0");
	} else {
		char txtBuf[128];
		sprintf_s(txtBuf,"Unknown command: '%s'\n",com.data());
		termOutput(txtBuf);
	}
}

void App::termOutput(char* msg) {
		cmd.clear();
		cmd += msg;
		typing = false;
}
