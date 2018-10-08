#pragma once

#include "Object.hpp"

namespace mygui {

class MYGUI_API Signal : public sf::Drawable {

public:
	Signal(int n, sf::Color col, const sf::FloatRect& region, float *max_val);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void EnableDraw();
	void DisableDraw();

	// Return false if a signal never reached the threashold value when the window was on
	void Edit(float* buf, int start, int size);

private:
	sf::VertexArray	m_curve;
	sf::FloatRect	m_graph_region;

	bool m_draw{ true };
};


class MYGUI_API Chart : public Object {

	using fptr = void(*)(const sf::Event&);

public:
	Chart::Chart(int x, int y, int w, int h, int num_of_points, std::string const& title = "Example",
		std::string const& x_axis = "x", std::string const& y_axis = "y", std::string const& font_name = "arial.ttf");	

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Handle(const sf::Event& event) override;

	void Enabled(bool enabled) override;
	bool Enabled() const override;

	void AddSignal(Signal* signal);
	void ChangeSignal(int idx, Signal* signal);

	// n_lines - number of one type of lines (vertical or horizontal), there are same number of other lines
	void CreateGrid(int n_lines);
	void CreateAxisMarkers();
	const sf::FloatRect GetGraphRegion() const;
	void SetMaxVal(float max_val);
	void ToggleDrawSignal(int idx);
	void ToggleDrawAllSignals();	

	// Actions
	void OnKeyPress(const fptr& f);

private:
	static constexpr int m_margin{ 20 };

	sf::RectangleShape	m_background;
	sf::RectangleShape	m_chart_region;
	sf::FloatRect		m_chart_rect;
	sf::VertexArray		m_outline;
	sf::VertexArray		m_axes;
	sf::VertexArray		m_grid;
	int					m_num_grid_lines{ 0 };
	sf::Text			m_x_axis;
	sf::Text			m_y_axis;
	sf::Text			m_title;

	std::vector<sf::Text> m_x_axis_markers;
	std::vector<sf::Text> m_y_axis_markers;

	sf::Font			m_font;

	std::vector<Signal*> m_signals;
	std::vector<bool>	m_draw_signal;
	int					m_num_of_points;
	float				m_max_val;

	bool	m_mouseover;

	fptr m_onKeyPress{ nullptr };
};

}