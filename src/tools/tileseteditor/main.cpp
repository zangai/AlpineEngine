#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "shared/Log.hpp"

//#include "Snippets.hpp"
#include "App.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "################################" << endl;
    cout << "#         Alpine Engine        #" << endl;
    cout << "#      Tool: TileSetEditor     #" << endl;
    cout << "# Internal Development Release #" << endl;
    cout << "################################" << endl;

	Log::setLogLevel(LOG_LEVEL_DEBUG);
	Log::setFilters(LOG_FILTER_INPUT);

    try
    {
		App application;
		application.OnExecute();
    }
    catch (std::exception& e)
    {
        Log::outError("%s (%u)", e.what());
    }

    return 0;
}