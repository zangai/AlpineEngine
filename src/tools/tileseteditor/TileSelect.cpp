#include "TileSelect.hpp"
#include "shared/Log.hpp"

TileSelect::TileSelect(void)
{
	tileDim.x	= 32;
	tileDim.y	= 32;
	m_fill		= sf::Color(255.0f,0.0f,0.0f,16.0f);
	m_border	= sf::Color(255.0f,0.0f,0.0f,255.0f);
}

TileSelect::TileSelect(int w, int h)
{
	TileSelect();
	tileDim.x = w;
	tileDim.y = h;
}

TileSelect::~TileSelect(void)
{

}

void TileSelect::start(int x, int y)
{	
	if (!drag)
	{
		cord2D z = cap(x,y);
		//Log::outDebugFilter(LOG_FILTER_INPUT,"Started Dragging");
		m_start.x = z.x;
		m_start.y = z.y;
		m_end = m_start;
		drag = true;
	}
}

void TileSelect::move(int x, int y)
{
	cord2D z = cap(x,y);
	if (drag && z.x >= m_start.x && z.y >= m_start.y) // If new end(x,y) is bigger then old start(x,y), update end(x,y) values
	{
		//Log::outDebugFilter(LOG_FILTER_INPUT,"Move Dragging");
		m_end.x = z.x;
		m_end.y = z.y;
	} else {
		//Log::outDebugFilter(LOG_FILTER_INPUT,"\ns(x,y)=%i,%i\ne(x,y)=%i,%i",m_sx,m_sy,m_ex,m_ey);
	}
}

void TileSelect::end(int x, int y)
{
	cord2D z = cap(x,y);
	if (drag && z.x >= m_start.x && z.y >= m_start.y)
	{
		//Log::outDebugFilter(LOG_FILTER_INPUT,"End Dragging");
		m_end.x = z.x;
		m_end.y = z.y;
		drag = false;
	}
}

cord2D TileSelect::cap(int x, int y)
{
	cord2D z;
	z.x = (x/tileDim.x)*tileDim.x;
	z.y = (y/tileDim.y)*tileDim.y;
	return z;
}

void TileSelect::draw()
{
		float s_offset_x	= (float)m_start.x;
		float s_offset_y	= (float)m_start.y;
		float s_width		= (float)(m_end.x - m_start.x);
		float s_height		= (float)(m_end.y - m_start.y);

		// Fill
		glColor4f(m_fill.r,m_fill.g,m_fill.b,(m_fill.a)/255.0f);
		glBegin(GL_QUADS);	
			glVertex3f(s_offset_x + 00.0f, s_offset_y + 00.0f, 0.0f);				
			glVertex3f(s_offset_x + 32.0f + s_width, s_offset_y + 00.0f, 0.0f);				
			glVertex3f(s_offset_x + 32.0f + s_width, s_offset_y + 32.0f + s_height, 0.0f);				
			glVertex3f(s_offset_x + 00.0f, s_offset_y + 32.0f + s_height, 0.0f);				
		glEnd();

		glColor4f(m_border.r,m_border.g,m_border.b,(m_border.a)/255.0f);
		// Top Border
		glBegin(GL_QUADS);	
			glVertex3f(s_offset_x + 0       + 00.0f, s_offset_y + 00.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + s_width + 32.0f, s_offset_y + 00.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + s_width + 32.0f, s_offset_y + 02.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + 0       + 00.0f, s_offset_y + 02.0f + 0       , 0.0f);				
		glEnd();

		// Right Border
		glBegin(GL_QUADS);	
			glVertex3f(s_offset_x + s_width + 30.0f, s_offset_y + 00.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + s_width + 32.0f, s_offset_y + 00.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + s_width + 32.0f, s_offset_y + 32.0f + s_height, 0.0f);				
			glVertex3f(s_offset_x + s_width + 30.0f, s_offset_y + 32.0f + s_height, 0.0f);				
		glEnd();

		// Bottom Border
		glBegin(GL_QUADS);	
			glVertex3f(s_offset_x +         + 00.0f, s_offset_y + 30.0f + s_height, 0.0f);				
			glVertex3f(s_offset_x + s_width + 32.0f, s_offset_y + 30.0f + s_height, 0.0f);				
			glVertex3f(s_offset_x + s_width + 32.0f, s_offset_y + 32.0f + s_height, 0.0f);				
			glVertex3f(s_offset_x +         + 00.0f, s_offset_y + 32.0f + s_height, 0.0f);				
		glEnd();

		// Left Border
		glBegin(GL_QUADS);	
			glVertex3f(s_offset_x + 0       + 00.0f, s_offset_y + 00.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + 0       + 02.0f, s_offset_y + 00.0f + 0       , 0.0f);				
			glVertex3f(s_offset_x + 0       + 02.0f, s_offset_y + 32.0f + s_height, 0.0f);				
			glVertex3f(s_offset_x + 0       + 00.0f, s_offset_y + 32.0f + s_height, 0.0f);				
		glEnd();
}

void TileSelect::updateRect()
{
	rect.Left		= m_start.x;
	rect.Right		= m_end.x+32;
	rect.Top		= m_start.y;
	rect.Bottom		= m_end.y+32;
}

sf::Rect<int> TileSelect::getRect()
{
	updateRect();
	return rect;
}