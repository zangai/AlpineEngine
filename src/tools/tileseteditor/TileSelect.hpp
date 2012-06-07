#ifndef _TILESELECT_HPP_
#define _TILESELECT_HPP_

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Rect.hpp"

struct cord2D {
  int x;
  int y;
};

class TileSelect {
	public:
		// Init and destruct
		TileSelect();
		TileSelect(int w, int h);
		~TileSelect();
		
		// Event Voids
		void start(int x, int y);
		void move(int x, int y);
		void end(int x, int y);

		// Draw
		void draw();

		// Capping the positions based on the width and height of the tiles
		cord2D cap(int x, int y);
		
		// Start x,y
		cord2D m_start;

		// End x,y
		cord2D m_end;

		// Get Rectangle
		sf::Rect<int> getRect();

	private:

		void updateRect();
		
		// Rectangle
		sf::Rect<int> rect;

		// Tile Width/Height
		cord2D tileDim;

		// Fill and Border color
		sf::Color m_fill;
		sf::Color m_border;

		// Boolean
		bool drag;
		bool visible;
};

#endif