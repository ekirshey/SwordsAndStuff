#pragma once
#include <boost/polygon/point_data.hpp>
#include <boost/polygon/segment_data.hpp>
#include <boost/polygon/voronoi_diagram.hpp>

namespace SAS_Utils {
	using Point = boost::polygon::point_data<int>;
	using Segment = boost::polygon::segment_data<int>;
	using VoronoiDiagram = boost::polygon::voronoi_diagram<double>;

#ifdef FOO
	struct Point {
		int x;
		int y;
		Point(int x0, int y0) 
			: x(x0)
			, y(y0) 
		{}
	};

	struct Segment {
		Point p0;
		Point p1;
		Segment(int x0, int y0, int x1, int y1)
			: p0(x0, y0)
			, p1(x1, y1)
		{}
	};
#endif
}
